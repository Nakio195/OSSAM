#include "Spaceship.h"
#include <math.h>
#include "Game.h"

/**
 * @brief Window_Height
 */

extern int Window_Height;
extern int Window_Width;

extern list<Spaceship*> Spaceships;

Spaceship::Spaceship(string pName, string PathToTexture, unsigned int pLife, unsigned int pShield, unsigned int pAttack, unsigned int pDefense, unsigned int pGenerator, float pSpeed, unsigned int pXP, unsigned int pAmmo) : Entity(pName)
{
    Stats.Life = pLife;
    Stats.Shield = pShield;
    Stats.Attack = pAttack;
    Stats.Defense = pDefense;
    Stats.Generator = pGenerator;
    Speed = pSpeed;

    HealthPoints = pLife;

    Target = NULL;
    Aimed = false;

    Inertia = 1.0;
    Direction = sf::Vector2f(0, 0);

    UI = new ATH(this);

    Dying = false;
    Dead = false;

    Aimed_Texture = new sf::Texture();

    Aimed_Texture->loadFromFile("Ressources/System/InGame/Target.png");
    Aimed_Sprite.setTexture(*Aimed_Texture);
    Aimed_Sprite.setOrigin(Aimed_Texture->getSize().x/2, Aimed_Texture->getSize().y/2);

    Texture_Dying = new sf::Texture();
    Texture_HalfLife = new sf::Texture();

    HittedAnim = new Animation<Spaceship>(this, 0.1, Animation<Spaceship>::Event);
    HittedAnim->setStartAction(&Spaceship::Anim_start_HitMark);
    HittedAnim->setEndAction(&Spaceship::Anim_stop_HitMark);

    DyingAnim = new Animation<Spaceship>(this, 0.2, Animation<Spaceship>::Sprite, Texture_Dying);
    DyingAnim->setStartAction(&Spaceship::Anim_start_Dying);
    DyingAnim->setEndAction(&Spaceship::Anim_stop_Dying);

    Texture_FullLife = new sf::Texture();
    Texture_FullLife->loadFromFile(PathToTexture);

    Texture_Spaceship = Texture_FullLife;
    ChangeTexture(Texture_Spaceship);
    this->setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);

    MainShield = new Shield(this, pShield, "Pouclier !");
}

Spaceship::~Spaceship()
{
    /** Weapons **/
    delete MainWeapon;
    delete SecondaryWeapon;

    /** Animations **/

    delete Texture_FullLife;

    //Hitted
    delete HittedAnim;
    //Dying
    delete DyingAnim;
    delete Texture_Dying;
}

int Spaceship::getHealth()
{
    if(HealthPoints > 0)
        return HealthPoints;
    else
        return 0;
}

int Spaceship::getShield()
{
    return MainShield->getShieldPoints();
}


int Spaceship::getShieldMax()
{
    return MainShield->getShieldMax();
}

Spaceship::Statistics Spaceship::getStats()
{
    return Stats;
}

bool Spaceship::isPlayer()
{
    if(Faction == Spaceship::FactionPlayer)
        return true;
    else
        return false;
}

void Spaceship::setFaction(int pFaction)
{
    if(pFaction == Spaceship::FactionPlayer || pFaction == Spaceship::FactionWasp)
        Faction = pFaction;
}

int Spaceship::getFaction()
{
    return Faction;
}

bool Spaceship::isDead()
{
    return Dead;
}

bool Spaceship::Shoot(int UsedWeapon)
{
    if(Dying || Dead)
        return false;

    if(UsedWeapon == Weapon::Main)
    {
        return MainWeapon->Shoot();
    }

    if(UsedWeapon == Weapon::Secondary)
    {
        return SecondaryWeapon->Shoot();
    }
}


bool Spaceship::Shoot(IA_ShootNode<Spaceship> *Node)
{
    if(Dying || Dead)
        return false;

    if(Node->WeaponChoice == Weapon::Main)
    {
        return MainWeapon->Shoot();
    }

    if(Node->WeaponChoice == Weapon::Secondary)
    {
        return MainWeapon->Shoot();
    }
}

void Spaceship::Die()
{
    Dead = true;
}

void Spaceship::TakeDamage(Bullet* Damage)
{
    int Damages = MainShield->TakeDamage(Damage);

    cout << Name << " hitted by " << Damage->getHit() << " points !" << endl;

    if(Damages > 0)
    {
        HealthPoints -= Damages;

        if(HealthPoints <= Stats.Life/2)
        {
            Texture_Spaceship = Texture_HalfLife;
            ChangeTexture(Texture_Spaceship);
        }

        if(HealthPoints <= 0)
        {
            HealthPoints = 0;
            cout << endl;
            cout << Name << " was killed with " << Damage->getName() << " by " << Damage->getParent()->getName() << endl << endl;

            if(Damage->getParent()->getAimedTarget() == this)
                Damage->getParent()->setAimedTarget(NULL);

            if(!DyingAnim->isRunning())
            {
                Dying = true;
                DyingAnim->Start();
            }
        }

        else
            HittedAnim->Start();
    }
}

void Spaceship::StartSequencer()
{
    Sequencer.Start();
}


void Spaceship::AddSequencerNode(IA_Node<Spaceship> NewNode)
{
    Sequencer.AddNode(NewNode);
}

void Spaceship::MoveLinearTo(IA_PathNode<Spaceship> *Node)
{
    AutoMoveNode = Node;

    AutoMoveRunning = true;
    AutoMoveNeedRefresh = true;
    AutoMoveDeparturePosition = getPosition();

    cout << "On Going : " << AutoMoveNode->Destination.x << "  " << AutoMoveNode->Destination.y << endl;
    cout << "Position : " << getPosition().x << "  " << getPosition().y << endl;
}

int Spaceship::Move()
{
    sf::Vector2f Vector;

    if(Dying)
        return 0;

    if(AutoMoveRunning == true)
    {
        if(AutoMoveNode->MoveType == IA_PathNode<Entity>::Linear)
        {
            sf::Vector2f Position = getPosition();

            float dX = (AutoMoveNode->Destination.x-Position.x);
            float dY = (AutoMoveNode->Destination.y-Position.y);

            if(AutoMoveNeedRefresh)
            {
                float Phi = atan(dX/dY);

                AutoMoveDirection.x = sin(Phi);
                AutoMoveDirection.y = cos(Phi);

                if((dX < 0 && dY < 0) || dY < 0)
                {
                    AutoMoveDirection.x *= -1.0;
                    AutoMoveDirection.y *= -1.0;
                }


                AutoMoveNeedRefresh = false;
            }

            if(abs(getPosition().x - AutoMoveDeparturePosition.x)/abs(AutoMoveNode->Destination.x - AutoMoveDeparturePosition.x) > 0.9 &&
               abs(getPosition().y - AutoMoveDeparturePosition.y)/abs(AutoMoveNode->Destination.y - AutoMoveDeparturePosition.y) > 0.9)
            {
                AutoMoveDirection.x *= Inertia*0.8;
                AutoMoveDirection.y *= Inertia*0.8;
            }


            if((abs(dX) < 5 && abs(dY) < 5) || (abs(AutoMoveDirection.x) < 0.01 && abs(AutoMoveDirection.y) < 0.01))
            {
                AutoMoveRunning = false;
                AutoMoveNeedRefresh = false;
                AutoMoveDirection = sf::Vector2f(0, 0);

                AutoMoveNode->setEndOfTravel();
            }

            Direction = AutoMoveDirection;
        }
    }

    else
    {
        Direction.x *= Inertia;
        Direction.y *= Inertia;

        if(Direction.x < 0.01 && Direction.x > 0)
            Direction.x = 0;
        if(Direction.x > -0.01 && Direction.x < 0)
            Direction.x = 0;

        if(Direction.y < 0.01 && Direction.y > 0)
            Direction.y = 0;
        if(Direction.y > -0.01 && Direction.y < 0)
            Direction.y = 0;
    }

    Vector = sf::Vector2f(ElapsedTime*Direction.x*Speed, ElapsedTime*Direction.y*Speed);

    if(getPosition().y - getOrigin().y + getTexture()->getSize().y*getScale().y + Vector.y >= Window_Height) // Bas
    {
        Vector.y = 0;
    }

    if(getPosition().y - getOrigin().y + Vector.y <= 0)     // Haut
    {
        Vector.y = 0;
    }

    if(getPosition().x  - getOrigin().x + getTexture()->getSize().x*getScale().x + Vector.x >= Window_Width) // Droite
    {
        Vector.x = 0;
    }

    if(getPosition().x  - getOrigin().x + Vector.x <= 0)  // Gauche
    {
        Vector.x = 0;
    }

    //cout << Vector.x << "  " << Vector.y << endl;
    move(Vector);
    return 1;
}


void Spaceship::setAimedTarget(Spaceship* pTarget)
{
    Target = pTarget;
}

Spaceship* Spaceship::getAimedTarget()
{
    return Target;
}

void Spaceship::setAimed(bool pAimed)
{
    Aimed = pAimed;
}

void Spaceship::RefreshElapsedTime(bool Release)
{
    Entity::RefreshElapsedTime(Release);

    if(SecondaryWeapon != NULL)
        SecondaryWeapon->RefreshElapsedTime(Release);
    if(MainWeapon != NULL)
        MainWeapon->RefreshElapsedTime(Release);
    if(MainShield != NULL)
        MainShield->RefreshElapsedTime(Release);

    HittedAnim->Play(ElapsedTime);
    DyingAnim->Play(ElapsedTime);
    Sequencer.Play(ElapsedTime);
}

void Spaceship::draw(sf::RenderWindow *Window)
{
    if(Dead)
        return;

    UI->draw(Window);

    if(Dying)
    {
        DyingAnim->setPosition(this->getPosition()+DyingAnim->getRelativePosition());
        Window->draw(*DyingAnim);
    }

    else
    {
        Window->draw(*this);
        SecondaryWeapon->draw(Window);
        MainWeapon->draw(Window);

        if(Aimed)
        {
            Aimed_Sprite.setPosition(this->getPosition()+this->getOrigin());
            Window->draw(Aimed_Sprite);
        }
        MainShield->draw(Window);
    }

}

void Spaceship::setTexture_Shield(sf::Texture *pTexture)
{
    MainShield->setShieldTexture(pTexture);
}
void Spaceship::setTexture_Shield(string PathShield, string PathBroken)
{
    MainShield->setShieldTexture(PathShield, PathBroken);
}


void Spaceship::setTexture_HalfLife(sf::Texture *pTexture)
{
    Texture_HalfLife = pTexture;
}

void Spaceship::setTexture_HalfLife(string Path)
{
    Texture_HalfLife->loadFromFile(Path);
}


void Spaceship::Anim_start_HitMark()
{
   /* if(HealthPoints <= Stats.Life /2)
        ChangeTexture(Texture_HalfLife_Hitmark);
    else
        ChangeTexture(Texture_FullLife_Hitmark);
        */
    setColor(sf::Color(220, 100, 100));
}

void Spaceship::Anim_stop_HitMark()
{
    setColor(sf::Color(255, 255, 255));
}

void Spaceship::setTexture_Dying(sf::Texture *pTexture)
{
    Texture_Dying = pTexture;
}

void Spaceship::setTexture_Dying(string Path)
{
    Texture_Dying->loadFromFile(Path);
}

void Spaceship::Anim_start_Dying()
{

}

void Spaceship::Anim_stop_Dying()
{
    Die();
}
