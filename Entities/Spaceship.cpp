#include "Spaceship.h"
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
    Stats.Speed = pSpeed;

    HealthPoints = pLife;

    UI = new ATH(this);

    Dying = false;
    Dead = false;

    Texture_Dying = new sf::Texture();
    Texture_HalfLife = new sf::Texture();

    HittedAnim = new Animation<Spaceship>(this, 0.1, Animation<Spaceship>::Event);
    HittedAnim->setStartAction(&Spaceship::Anim_start_HitMark);
    HittedAnim->setEndAction(&Spaceship::Anim_stop_HitMark);

    DyingAnim = new Animation<Spaceship>(this, 0.1, Animation<Spaceship>::Sprite, Texture_Dying);
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

void Spaceship::Shoot(int UsedWeapon)
{
    if(Dying || Dead)
        return;

    if(UsedWeapon == Weapon::Main)
        MainWeapon->Shoot(getPosition());

    if(UsedWeapon == Weapon::Secondary)
        SecondaryWeapon->Shoot(getPosition());
}

void Spaceship::Die()
{
    Dead = true;
}

int Spaceship::Move(sf::Vector2f Direction)
{
    if(Dying)
        return 0;

    sf::Vector2f Vector(ElapsedTime*Stats.Speed*Direction.x, ElapsedTime*Stats.Speed*Direction.y);

    if(getPosition().y - getOrigin().y + getTexture()->getSize().y*getScale().y + Vector.y >= Window_Height)  // Bas
        return 0;

    if(getPosition().y - getOrigin().y + Vector.y <= 0)     // Haut
        return 0;

    if(getPosition().x  - getOrigin().x + getTexture()->getSize().x*getScale().x + Vector.x >= Window_Width) // Droite
        return 0;

    if(getPosition().x  - getOrigin().x + Vector.x <= 0)  // Gauche
        return 0;

    move(Vector);
    return 1;
}

void Spaceship::TakeDamage(Bullet* Damage)
{
    int Damages = MainShield->TakeDamage(Damage);

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
            cout << Name << " was killed with " << Damage->getName() << endl << endl;

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



void Spaceship::RefreshElapsedTime(bool Release)
{
    Entity::RefreshElapsedTime(Release);

    if(MainWeapon != NULL)
        MainWeapon->RefreshElapsedTime(Release);
    if(SecondaryWeapon != NULL)
        SecondaryWeapon->RefreshElapsedTime(Release);
    if(MainShield != NULL)
        MainShield->RefreshElapsedTime(Release);

    HittedAnim->Play(ElapsedTime);
    DyingAnim->Play(ElapsedTime);
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
        MainWeapon->draw(Window);
        SecondaryWeapon->draw(Window);

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
