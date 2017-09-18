#include "Weapon.h"

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
    switch(BulletType->getType())
    {
        case Bullet::Laser:
            return new Laser(static_cast<Laser*>(BulletType));
        break;

        case Bullet::Missile:
            return new Missile(static_cast<Missile*>(BulletType));
        break;
    }

    return NULL;
}


void Weapon::setBlastAnim(std::string Path, unsigned int NbFrames, sf::IntRect Rect)
{
    Blast_Texture->loadFromFile(Path);
    BlastAnim->setFrame(NbFrames, Rect);

}

void Weapon::setBullet(unsigned int pHit, string PathToBulletTexture, string PathToBlastTexture)
{
    BulletType->setHit(pHit);
    BulletType->setBlastTexture(PathToBlastTexture);
    BulletType->setBulletTexture(PathToBulletTexture);
}

void Weapon::setBullet(Bullet BulletReference)
{
    BulletType = new Bullet(&BulletReference);
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

void Weapon::Shoot(sf::Vector2f InitialPosition)
{
    if(!ReloadTimer.isRunning())
    {
        Bullet *newBullet = copyBullet();
        newBullet->setDirection(ShootingDirection);
        newBullet->setPosition(MainSprite.getPosition().x+ShootPosition.x+RelativePosition.x, MainSprite.getPosition().y+ShootPosition.y+RelativePosition.y);
        FiredBullets.push_back(newBullet);

        ReloadTimer.StartTimer();
        BlastAnim->Start();
    }

    else
    {
        if(ReloadTimer.Triggered())
            ReloadTimer.StopTimer();
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
