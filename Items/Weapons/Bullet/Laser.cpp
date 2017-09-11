#include "Laser.h"
#include "../../../Entities/Spaceship.h"

/**
 * @brief Laser::Laser
 * @param Parent
 */

Laser::Laser(Spaceship* Parent) : Bullet(Parent)
{
    Type = Bullet::Laser;
}


Laser::Laser(Laser *copy) : Bullet(copy)
{
    Type = Bullet::Laser;
}

Laser::~Laser()
{

}


void Laser::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    Shooted->TakeDamage(this);
}
