#include "Bullet.h"
#include "../../Entities/Spaceship.h"


/**
 * @brief Bullet::Bullet
 * @param pParent
 * @param pName
 * @param pHit
 * @param PathToBulletTexture
 * @param PathToBlastTexture
 */

Bullet::Bullet(Spaceship *pParent, string pName, unsigned int pHit, string PathToBulletTexture, string PathToBlastTexture) : Entity(pName)
{
    setHit(pHit);
    setParent(pParent);
    Speed = 500;
    BulletTexture = new sf::Texture();
    BulletTexture->loadFromFile(PathToBulletTexture);
    ChangeTexture(BulletTexture);

    BlastTexture = new sf::Texture();
    BlastTexture->loadFromFile(PathToBlastTexture);

    setOrigin(getTexture()->getSize().x, getTexture()->getSize().y/2);
}


Bullet::Bullet(Bullet *copy) : Entity(copy->getName())
{
    Hit = copy->Hit;
    Direction = copy->Direction;
    Parent = copy->Parent;
    Speed = copy->Speed;
    BulletTexture = copy->BulletTexture;
    BlastTexture = copy->BlastTexture;
    Type = copy->Type;
    ChangeTexture(BulletTexture);
}

Bullet::~Bullet()
{

}

unsigned int Bullet::getType()
{
    return Type;
}


void Bullet::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    Shooted->TakeDamage(this);
}


unsigned int Bullet::getHit()
{
    return Hit;
}

void Bullet::setHit(unsigned int pHit)
{
    Hit = pHit;
}

void Bullet::setBlastTexture(string Path)
{
    BlastTexture->loadFromFile(Path);
}

void Bullet::setBlastTexture(sf::Texture *pBlast)
{
    BulletTexture = pBlast;
}

void Bullet::setBulletTexture(string Path)
{
    BulletTexture->loadFromFile(Path);
}

void Bullet::setBulletTexture(sf::Texture *pBullet)
{
    BulletTexture = pBullet;
}

void Bullet::setSpeed(float pSpeed)
{
    Speed = pSpeed;
}

float Bullet::getSpeed()
{
    return Speed;
}


void Bullet::setParent(Spaceship *pParent)
{
    Parent = pParent;
}

Spaceship *Bullet::getParent()
{
    return Parent;
}

void Bullet::setDirection(sf::Vector2f pDirection)
{
    Direction = pDirection;
}

sf::Vector2f Bullet::getDirection()
{
    return Direction;
}
