#include "Game.h"

#include <ctime>
#include <cstdlib>

unsigned int Window_Height = 0;
unsigned int Window_Width = 0;

list<Bullet*> FiredBullets;
list<Spaceship*> Spaceships;

/**
 * @brief OSSAM::OSSAM
 */

OSSAM::OSSAM()
{
    sf::ContextSettings Settings;
    Settings.antialiasingLevel = ANTI_ALIAS;

    Window.create(sf::VideoMode::getDesktopMode(), "#OSSAM 2017", sf::Style::Fullscreen, Settings);

    Window_Height = Window.getSize().y;
    Window_Width = Window.getSize().x;

    BackgroundView = sf::View(sf::Vector2f(Window_Width/2, Window_Height/2), sf::Vector2f(Window_Width, Window_Height));
    MiddlegroundView = sf::View(sf::Vector2f(Window_Width/2, Window_Height/2), sf::Vector2f(Window_Width, Window_Height));

    Animation<OSSAM>* Planet = new Animation<OSSAM>(this, 0, Animation<OSSAM>::KeySequence, Timer::Continuous);
    Planet->loadTexture("Ressources/Levels/planet1.png");
    Planet->setOrigin(Planet->getTexture()->getSize().x/2, Planet->getTexture()->getSize().y/2);
    Planet->setPosition(300, Window_Height*0.8);
    Planet->addKey(RotationKey(360, RotationKey::Clockwise, 600));
    Planet->Start();
    MiddlegroundElements.push_back(Planet);

    GameView = sf::View(sf::Vector2f(Window_Width/2, Window_Height/2), sf::Vector2f(Window_Width, Window_Height));
    ForegroundView = sf::View(sf::Vector2f(Window_Width/2, Window_Height/2), sf::Vector2f(Window_Width, Window_Height));
    ATH_View = sf::View(sf::Vector2f(Window_Width/2, Window_Height/2), sf::Vector2f(Window_Width, Window_Height));

    srand(time(0));

    GameState = OSSAM::Playing;

    Captain = new Player("Cap'tain Khaal", "Ressources/Sprite/Player/Player.png", 500, 200);
    Captain->setFaction(Spaceship::FactionPlayer);
    Captain->setInertia(0.95);
    Captain->setTexture_HalfLife("Ressources/Sprite/Player/Player_Quarter.png");
    //Captain->setTexture_Shield("Ressources/Sprite/Player/Pouclier.png", "Ressources/Sprite/Player/Pouclier_casse.png");
    Captain->setTexture_Dying("Ressources/Sprite/explosion.png");


    Weapon *MainWeapon = new Weapon("Laser Simple", "Ressources/Sprite/Player/canon.png", 0.07);
    MainWeapon->setShootingDirection(sf::Vector2f(1, 0));
    MainWeapon->setRelativePosition(sf::Vector2f(-27, -30));
    MainWeapon->setShootPosition(sf::Vector2f(104, 38));
    MainWeapon->setBlastAnim("Ressources/Sprite/blast-CP.png", 2, sf::IntRect(0, 0, 40, 24));
    MainWeapon->setIcon("Ressources/System/Icon/RG_1.png");

    Laser MainWeaponBullet(Captain);
    MainWeaponBullet.setHit(10);
    MainWeaponBullet.setBulletTexture("Ressources/Sprite/LaserBleu.png");
    MainWeapon->setBullet(MainWeaponBullet);


    Weapon *SecondaryWeapon = new Weapon("Lance Missile", "Ressources/Sprite/Player/LM.png", 10);
    SecondaryWeapon->setShootingDirection(sf::Vector2f(1, 0));
    SecondaryWeapon->setRelativePosition(sf::Vector2f(-30, -47));
    SecondaryWeapon->setShootPosition(sf::Vector2f(55, 40));
    SecondaryWeapon->setBlastAnim("Ressources/Sprite/blast-LM.png", 3, sf::IntRect(0, 0, 50, 31));
    SecondaryWeapon->setIcon("Ressources/System/Icon/LM_1.png");

    Missile SecondaryWeaponBullet(Captain);
    SecondaryWeaponBullet.setHit(100);
    SecondaryWeaponBullet.setBlastTexture("Ressoures/Sprite/missile-blast.png");
    SecondaryWeaponBullet.setBulletTexture("Ressources/Sprite/missile.png");
    SecondaryWeapon->setBullet(SecondaryWeaponBullet);

    Shield *MainShield = new Shield(Captain, 50);
    MainShield->setShieldTexture("Ressources/Sprite/Player/Pouclier.png", "Ressources/Sprite/Player/Pouclier_casse.png");

    Captain->addItem(MainShield);
    Captain->addItem(MainWeapon);
    Captain->addItem(SecondaryWeapon);

    Spaceships.push_back(Captain);

    Bleuton = new Ennemy("Bleuton", "Ressources/Sprite/Ennemies/Intercepteur.png", 100,  0);
    Bleuton->setFaction(Spaceship::FactionWasp);
    Bleuton->setTexture_HalfLife("Ressources/Sprite/Ennemies/Intercepteur.png");
    Bleuton->setTexture_Dying("Ressources/Sprite/explo enn.png");
    Spaceships.push_back(Bleuton);

    IA_Node<Spaceship> First(Bleuton);
    First.PathNode = new IA_PathNode<Spaceship>(Bleuton, sf::Vector2f(Window_Width*0.90, Window_Height*0.05), IA_PathNode<Spaceship>::Linear);
    First.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    First.Delay = 1;
    First.ShootNode = new IA_ShootNode<Spaceship>(Bleuton, Weapon::Main, 5);
    First.ShootNode->ShootNumber = 5;
    First.ShootNode->ShootingPeriod = 1.5;
    First.ShootNode->Mode = IA_ShootNode<Spaceship>::Single;
    First.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> Second(Bleuton);
    Second.PathNode = new IA_PathNode<Spaceship>(Bleuton, sf::Vector2f(Window_Width*0.6, Window_Height*0.40), IA_PathNode<Spaceship>::Linear);
    Second.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    Second.Delay = 0.5;
    Second.ShootNode = new IA_ShootNode<Spaceship>(Bleuton, Weapon::Main, 5);
    Second.ShootNode->ShootingPeriod = 0.2;
    Second.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    Second.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> Third(Bleuton);
    Third.PathNode = new IA_PathNode<Spaceship>(Bleuton, sf::Vector2f(Window_Width*0.9, Window_Height*0.75), IA_PathNode<Spaceship>::Linear);
    Third.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    Third.Delay = 0.5;
    Third.ShootNode = new IA_ShootNode<Spaceship>(Bleuton, Weapon::Main, 5);
    Third.ShootNode->ShootingPeriod = 0.2;
    Third.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    Third.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> Fourth(Bleuton);
    Fourth.PathNode = new IA_PathNode<Spaceship>(Bleuton, sf::Vector2f(Window_Width*0.9, Window_Height*0.05), IA_PathNode<Spaceship>::Linear);
    Fourth.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    Fourth.Delay = 1;

    Bleuton->AddSequencerNode(First);
    Bleuton->AddSequencerNode(Second);
    Bleuton->AddSequencerNode(Third);

    Shield *MainShieldB = new Shield(Bleuton, 50);
    MainShieldB->setShieldTexture("Ressources/Sprite/Ennemies/Pouclier.png", "Ressources/Sprite/Ennemies/Pouclier_casse.png");
    Bleuton->addItem(MainShieldB);

    //Bleuton->AddSequencerNode(Fourth);

    Vador = new Ennemy("Vador", "Ressources/Sprite/Ennemies/ennemi2.png", 100, 0);
    Vador->setFaction(Spaceship::FactionWasp);
    Vador->setTexture_HalfLife("Ressources/Sprite/Ennemies/ennemi2.png");
    Vador->setTexture_Dying("Ressources/Sprite/explo enn.png");
    Spaceships.push_back(Vador);

    IA_Node<Spaceship> FirstV(Vador);
    FirstV.PathNode = new IA_PathNode<Spaceship>(Vador, sf::Vector2f(Window_Width*0.8, Window_Height*0.15), IA_PathNode<Spaceship>::Linear);
    FirstV.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    FirstV.Delay = 1;
    FirstV.ShootNode = new IA_ShootNode<Spaceship>(Vador, Weapon::Main, 5);
    FirstV.ShootNode->ShootNumber = 5;
    FirstV.ShootNode->ShootingPeriod = 1.5;
    FirstV.ShootNode->Mode = IA_ShootNode<Spaceship>::Single;
    FirstV.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> SecondV(Vador);
    SecondV.PathNode = new IA_PathNode<Spaceship>(Vador, sf::Vector2f(Window_Width*0.5, Window_Height*0.5), IA_PathNode<Spaceship>::Linear);
    SecondV.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    SecondV.Delay = 0.5;
    SecondV.ShootNode = new IA_ShootNode<Spaceship>(Vador, Weapon::Main, 5);
    SecondV.ShootNode->ShootingPeriod = 0.2;
    SecondV.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    SecondV.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> ThirdV(Vador);
    ThirdV.PathNode = new IA_PathNode<Spaceship>(Vador, sf::Vector2f(Window_Width*0.8, Window_Height*0.85), IA_PathNode<Spaceship>::Linear);
    ThirdV.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    ThirdV.Delay = 0.5;
    ThirdV.ShootNode = new IA_ShootNode<Spaceship>(Vador, Weapon::Main, 5);
    ThirdV.ShootNode->ShootingPeriod = 0.2;
    ThirdV.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    ThirdV.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> FourthV(Vador);
    FourthV.PathNode = new IA_PathNode<Spaceship>(Vador, sf::Vector2f(Window_Width*0.8, Window_Height*0.15), IA_PathNode<Spaceship>::Linear);
    FourthV.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    FourthV.Delay = 1;

    Vador->AddSequencerNode(FirstV);
    Vador->AddSequencerNode(SecondV);
    Vador->AddSequencerNode(ThirdV);
    //Vador->AddSequencerNode(FourthV);

    Shield *MainShieldV = new Shield(Vador, 150);
    MainShieldV->setShieldTexture("Ressources/Sprite/Ennemies/Pouclier.png", "Ressources/Sprite/Ennemies/Pouclier_casse.png");
    Vador->addItem(MainShieldV);

    Picard = new Ennemy("Bleuton", "Ressources/Sprite/Ennemies/Intercepteur.png", 100,  0);
    Picard->setFaction(Spaceship::FactionWasp);
    Picard->setTexture_HalfLife("Ressources/Sprite/Ennemies/Intercepteur.png");
    Picard->setTexture_Dying("Ressources/Sprite/explo enn.png");
    Spaceships.push_back(Picard);

    IA_Node<Spaceship> FirstP(Picard);
    FirstP.PathNode = new IA_PathNode<Spaceship>(Picard, sf::Vector2f(Window_Width*0.90, Window_Height*0.25), IA_PathNode<Spaceship>::Linear);
    FirstP.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    FirstP.Delay = 1;
    FirstP.ShootNode = new IA_ShootNode<Spaceship>(Picard, Weapon::Main, 5);
    FirstP.ShootNode->ShootNumber = 5;
    FirstP.ShootNode->ShootingPeriod = 1.5;
    FirstP.ShootNode->Mode = IA_ShootNode<Spaceship>::Single;
    FirstP.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> SecondP(Picard);
    SecondP.PathNode = new IA_PathNode<Spaceship>(Picard, sf::Vector2f(Window_Width*0.6, Window_Height*0.6), IA_PathNode<Spaceship>::Linear);
    SecondP.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    SecondP.Delay = 0.5;
    SecondP.ShootNode = new IA_ShootNode<Spaceship>(Picard, Weapon::Main, 5);
    SecondP.ShootNode->ShootingPeriod = 0.2;
    SecondP.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    SecondP.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    IA_Node<Spaceship> ThirdP(Picard);
    ThirdP.PathNode = new IA_PathNode<Spaceship>(Picard, sf::Vector2f(Window_Width*0.9, Window_Height*0.95), IA_PathNode<Spaceship>::Linear);
    ThirdP.PathNode->setTravelAction(&Spaceship::MoveLinearTo);
    ThirdP.Delay = 0.5;
    ThirdP.ShootNode = new IA_ShootNode<Spaceship>(Picard, Weapon::Main, 5);
    ThirdP.ShootNode->ShootingPeriod = 0.2;
    ThirdP.ShootNode->Mode = IA_ShootNode<Spaceship>::Continuous;
    ThirdP.ShootNode->setShootAction(static_cast<bool (Spaceship::*)(IA_ShootNode<Spaceship>*)>(&Spaceship::Shoot));

    Picard->AddSequencerNode(FirstP);
    Picard->AddSequencerNode(SecondP);
    Picard->AddSequencerNode(ThirdP);

    Shield *MainShieldP = new Shield(Picard, 50);
    MainShieldP->setShieldTexture("Ressources/Sprite/Ennemies/Pouclier.png", "Ressources/Sprite/Ennemies/Pouclier_casse.png");
    Picard->addItem(MainShieldP);

    Vador->setPosition(Window_Width*0.8, Window_Height*0.15);
    Bleuton->setPosition(Window_Width*0.9, Window_Height*0.05);
    Picard->setPosition(Window_Width*0.9, Window_Height*0.25);
    Captain->setPosition(Window_Width/5, Window_Height/2);

    Text_Background.loadFromFile("Ressources/Sprite/background3.png");
    Background.setTexture(Text_Background);
}

void OSSAM::Play()
{
    Window.setVerticalSyncEnabled(true);
    Window.setKeyRepeatEnabled(false);

    while (Window.isOpen())
    {
        HandleEvents();

        HandleTime();
        if(GameState == OSSAM::Playing)
        {
            HandlePhysics();
        }

        HandleDisplay();
    }
}


void OSSAM::HandleAnnimation()
{

}

void OSSAM::HandlePhysics()
{

    /* Gestion des tirs */

    for (list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end();)
    {
        bool RemoveBullet = false;

        Bullet* CurrentBullet = *it;

        if(!CurrentBullet->isExploded())
            CurrentBullet->Move();

        /* Déplacement des tirs et collisions */
        if (CurrentBullet->getPosition().x > Window_Width || CurrentBullet->getPosition().x + CurrentBullet->getTexture()->getSize().x < 0)
            RemoveBullet = true;

        if(RemoveBullet)
        {
            std::cout << "Bullet Position = x : " << CurrentBullet->getPosition().x << " y : "<< CurrentBullet->getPosition().y << std::endl;
            it = FiredBullets.erase(it);
            std::cout << "Removing Bullet" << endl;
        }

        else
            ++it;
    }

    /* Détection des collisions */
    for (list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end();)
    {
        bool RemoveBullet = false;

        Bullet* CurrentBullet = *it;

        for (list<Spaceship*>::iterator jt = Spaceships.begin(); jt != Spaceships.end(); ++jt)
        {
            Spaceship* CurrentSpaceship = *jt;

            if(CurrentBullet->getGlobalBounds().intersects(CurrentSpaceship->getGlobalBounds()))
            {
                if(CurrentBullet->getParent()->getFaction() != CurrentSpaceship->getFaction())
                {
                    CurrentBullet->Hitting(CurrentBullet->getParent(), CurrentSpaceship);
                }
            }
        }

        if(CurrentBullet->NeedRemove())
        {
            it = FiredBullets.erase(it);
            std::cout << "Removing Bullet" << endl;
        }
        else
            ++it;
    }


    for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
    {
        Spaceship* CurrentSpaceship = *it;
        bool RemoveSpaceship = true;

        if(CurrentSpaceship->isDead())
        {
            for (list<Bullet*>::iterator jt = FiredBullets.begin(); jt != FiredBullets.end();)
            {
                Bullet* CurrentBullet = *jt;

                if(CurrentBullet->getParent() == CurrentSpaceship)
                {
                    RemoveSpaceship = false;
                    break;
                }

                ++jt;
            }

            if(RemoveSpaceship)
            {
                it = Spaceships.erase(it);
                delete CurrentSpaceship;
            }
        }

        CurrentSpaceship->Move();
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Captain->Shoot(Weapon::Secondary);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Captain->Shoot(Weapon::Main);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        Captain->setDirection(sf::Vector2f(0, -1));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Captain->setDirection(sf::Vector2f(1, 0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        Captain->setDirection(sf::Vector2f(-1, 0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        Captain->setDirection(sf::Vector2f(0, 1));
    }

}

void OSSAM::HandleEvents()
{
    sf::Event event;

    while (Window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            Window.close();

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            Window.close();


        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
        {
            Captain->AimPrevious();
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
        {
            Captain->AimNext();
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
        {
            if(GameState != OSSAM::OnInventory)
            {
                GameState = OSSAM::OnInventory;
                OpenedInventory = Captain->getInventory();
                OpenedInventory->Open();
            }

            else
                GameState = OSSAM::Playing;
        }

        if(GameState == OSSAM::OnInventory)
        {
            OpenedInventory->HandleEvent(event);

            if(OpenedInventory->isOpened() == false)
                GameState = OSSAM::Playing;

        }
    }


}

void OSSAM::HandleTime()
{
    float ElapsedTime = GameClock.restart().asSeconds();
    bool Release = false;

    if(GameState != OSSAM::Playing)
        Release = true;

    if(Release)
        ElapsedTime = 0.0;

    for (list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end(); ++it)
    {
        Bullet* CurrentBullet = *it;

        if(!CurrentBullet->NeedRemove())
            CurrentBullet->RefreshElapsedTime(Release);
    }

    for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
    {
        Spaceship* CurrentSpaceship = *it;

        if(!CurrentSpaceship->isDead())
            CurrentSpaceship->RefreshElapsedTime(Release);
    }


    for (list<Animation<OSSAM>*>::iterator it = MiddlegroundElements.begin(); it != MiddlegroundElements.end(); ++it)
    {
        Animation<OSSAM>* CurrentElement = *it;

        CurrentElement->Play(ElapsedTime);
    }
}


void OSSAM::HandleDisplay()
{
    Window.clear();

    Window.setView(BackgroundView);
    Window.draw(Background);

    Window.setView(MiddlegroundView);

    for (list<Animation<OSSAM>*>::iterator it = MiddlegroundElements.begin(); it != MiddlegroundElements.end(); ++it)
    {
        Animation<OSSAM>* CurrentElement = *it;

        Window.draw(*CurrentElement);
    }

    Window.setView(GameView);

    for(list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end(); it++)
    {
        if(*it != nullptr)
        {
            Bullet *CurrentBullet = *it;
            CurrentBullet->draw(&Window);
        }
    }

    for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
    {
        if(*it != nullptr)
        {
            Spaceship *CurrentSpaceship = *it;
            CurrentSpaceship->draw(&Window);
        }
    }

    Window.setView(ATH_View);

    //Drawing ATH

    Captain->getUI()->draw(&Window);

    if(GameState == OSSAM::OnInventory)
    {
        if(OpenedInventory == nullptr)
            OpenedInventory = Captain->getInventory();

        OpenedInventory->Display(Window);
    }

    Window.display();
}
