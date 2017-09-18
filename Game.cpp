#include "Game.h"

#include <ctime>
#include <cstdlib>

int Window_Height = 0;
int Window_Width = 0;

list<Bullet*> FiredBullets;
list<Spaceship*> Spaceships;

/**
 * @brief OSSAM::OSSAM
 */

OSSAM::OSSAM()
{
    sf::ContextSettings Settings;
    Settings.antialiasingLevel = ANTI_ALIAS;

    Window.create(sf::VideoMode(WINDOW_WIDHT, WINDOW_HEIGHT), "#OSSAM 2017", sf::Style::Fullscreen, Settings);

    Window_Height = Window.getSize().y;
    Window_Width = Window.getSize().x;

    srand(time(0));

    GameState = OSSAM::Playing;

    Captain = new Player("Cap'tain Khaal", "Ressources/Sprite/Player/Player.png", 500, 200);
    Captain->setFaction(Spaceship::FactionPlayer);
    Captain->setInertia(0.95);
    Captain->setTexture_HalfLife("Ressources/Sprite/Player/Player_Quarter.png");
    Captain->setTexture_Shield("Ressources/Sprite/Player/Pouclier.png", "Ressources/Sprite/Player/Pouclier_casse.png");
    Captain->setTexture_Dying("Ressources/Sprite/explosion.png");
    Spaceships.push_back(Captain);

    Bleuton = new Ennemy("Bleuton", "Ressources/Sprite/Ennemies/Intercepteur.png", 100,  0);
    Bleuton->setFaction(Spaceship::FactionWasp);
    Bleuton->setTexture_HalfLife("Ressources/Sprite/Ennemies/Intercepteur.png");
    Bleuton->setTexture_Dying("Ressources/Sprite/explo enn.png");
    Bleuton->setTexture_Shield("Ressources/Sprite/Ennemies/Pouclier.png", "Ressources/Sprite/Ennemies/Pouclier_casse.png");
    Spaceships.push_back(Bleuton);

    Captain->setPosition(Window_Width/5, Window_Height/2-60);
    Bleuton->setPosition(Window_Width-300, Window_Height/2+200);

    Text_Background.loadFromFile("Ressources/Sprite/background3.jpg");
    Background.setTexture(Text_Background);
}

void OSSAM::Play()
{
    Window.setVerticalSyncEnabled(true);
    Window.setKeyRepeatEnabled(false);

    while (Window.isOpen())
    {
        HandleEvents();

        if(GameState == OSSAM::Playing)
        {
            HandlePhysics();
        }

        HandleDisplay();
        HandleTime();
    }
}


void OSSAM::HandleAnnimation()
{

}

void OSSAM::HandlePhysics()
{


    /*Gestion des tirs */

    int randomval = rand() %100;

    if(!Bleuton->isDead())
    {
        if(randomval < 25)
            Bleuton->Shoot(Weapon::Main);
    }



    for (list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end();)
    {
        bool RemoveBullet = false;

        Bullet* CurrentBullet = *it;

        if(!CurrentBullet->isExploded())
            CurrentBullet->move(sf::Vector2f(CurrentBullet->getSpeed()*CurrentBullet->getElapsedTime()*CurrentBullet->getDirection().x, CurrentBullet->getSpeed()*CurrentBullet->getElapsedTime()*CurrentBullet->getDirection().y));

        /* Déplacement des tirs et collisions */
        if (CurrentBullet->getPosition().x > Window_Width || CurrentBullet->getPosition().x + CurrentBullet->getTexture()->getSize().x < 0)
            RemoveBullet = true;

        if(RemoveBullet)
            it = FiredBullets.erase(it);

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
            it = FiredBullets.erase(it);
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        Bleuton->StartAutoMove();
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

            if(OpenedInventory->isOpen() == false)
                GameState = OSSAM::Playing;

        }
    }


}

void OSSAM::HandleTime()
{

    bool Release = false;

    if(GameState != OSSAM::Playing)
        Release = true;

    for (list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end(); ++it)
    {
        Bullet* CurrentBullet = *it;
        CurrentBullet->RefreshElapsedTime(Release);
    }

    for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
    {
        Spaceship* CurrentSpaceship = *it;
        bool RemoveSpaceship = true;

        if(!CurrentSpaceship->isDead())
            CurrentSpaceship->RefreshElapsedTime(Release);
    }

}


void OSSAM::HandleDisplay()
{
    Window.clear();

    Window.draw(Background);

    for(list<Bullet*>::iterator it = FiredBullets.begin(); it != FiredBullets.end(); it++)
    {
        if(*it != NULL)
        {
            Bullet *CurrentBullet = *it;
            CurrentBullet->draw(&Window);
        }
    }

    for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
    {
        if(*it != NULL)
        {
            Spaceship *CurrentSpaceship = *it;
            CurrentSpaceship->draw(&Window);
        }
    }

    //Drawing ATH
    if(GameState == OSSAM::OnInventory)
    {
        if(OpenedInventory == NULL)
            OpenedInventory = Captain->getInventory();

        OpenedInventory->Display(Window);
    }

    Window.display();
}
