#include "Weapon.h"
#include <iostream>

/**
 * @brief FiredBullets
 */

extern list<Bullet*> FiredBullets;

Weapon::Weapon(Spaceship *pParent, string pName, string PathToWeapon, float pSpeed) : Item(pName)
{
    setCategory(Item::Weapon);

    Parent = pParent;
    setSpeed(pSpeed);

    ShootingDirection.x = -1;
    ShootingDirection.y = 0;

    Blast_Texture = new sf::Texture();
    BlastAnim = new Animation<Weapon>(this, 0.1, Animation<Weapon>::Sprite, Blast_Texture);

    ReloadTimer.setPeriod(Speed);
    ReloadTimer.setMode(Timer::OneShot);

    Base_Texture = new sf::Texture();
    Base_Texture->loadFromFile(PathToWeapon);
    MainSprite.setTexture(*Base_Texture);

    setIcon("Ressources/System/Icon/CP_1.png");
}

Weapon::~Weapon()
{
    delete Base_Texture;
    delete BlastAnim;
    delete Blast_Texture;
}

Bullet* Weapon::copyBullet()
{
    switch(BulletType)
    {
        case Bullet::Laser:
            return new Laser(LaserBullet);
        break;

        case Bullet::Missile:
            return new Missile(MissileBullet);
        break;
    }

    return NULL;
}


void Weapon::setBlastAnim(std::string Path, unsigned int NbFrames, sf::IntRect Rect)
{
    Blast_Texture->loadFromFile(Path);
    BlastAnim->setFrame(NbFrames, Rect);

}

void Weapon::setBullet(Missile BulletReference)
{
    BulletType = Bullet::Missile;
    MissileBullet = new Missile(BulletReference);
}

void Weapon::setBullet(Laser BulletReference)
{
    BulletType = Bullet::Laser;
    LaserBullet = new Laser(BulletReference);
}


void Weapon::setShootingDirection(sf::Vector2f Direction)
{
    ShootingDirection = Direction;
}

void Weapon::setRelativePosition(sf::Vector2f Position)
{
    RelativePosition = Position;
}

void Weapon::setShootPosition(sf::Vector2f Position)
{
    ShootPosition = Position;
}

sf::Vector2f Weapon::getRelativePosition()
{
    return RelativePosition;
}

sf::Vector2f Weapon::getShootPosition()
{
    return ShootPosition;
}


void Weapon::draw(sf::RenderWindow *Window)
{
    MainSprite.setPosition(Parent->getPosition()+RelativePosition);
    Window->draw(MainSprite);

    if(BlastAnim->isRunning())
    {
        BlastAnim->setPosition(MainSprite.getPosition().x+ShootPosition.x+RelativePosition.x, MainSprite.getPosition().y+ShootPosition.y+RelativePosition.y);
        Window->draw(*BlastAnim);
    }
}

bool Weapon::Shoot()
{
    if(ReloadTimer.Triggered())
        ReloadTimer.StopTimer();

    if(!ReloadTimer.isRunning())
    {
        Bullet *newBullet = copyBullet();

        if(newBullet->getType() == Bullet::Missile)
           static_cast<Missile*>(newBullet)->setTarget(Parent->getAimedTarget());

        newBullet->setDirection(ShootingDirection);
        newBullet->setPosition(MainSprite.getPosition().x+ShootPosition.x+RelativePosition.x, MainSprite.getPosition().y+ShootPosition.y+RelativePosition.y);
        FiredBullets.push_back(newBullet);

        std::cout << "Bullet in the list : " << FiredBullets.size() << std::endl;

        ReloadTimer.StartTimer();
        BlastAnim->Start();

        return true;
    }

    else
    {
        return false;
    }
}

float Weapon::getSpeed()
{
    return Speed;
}

void Weapon::setSpeed(float pSpeed)
{
    Speed = pSpeed;
}

void Weapon::RefreshElapsedTime(bool Release)
{
    Item::RefreshElapsedTime(Release);
    ReloadTimer.Count(ElapsedTime);
    BlastAnim->Play(ElapsedTime);
}
