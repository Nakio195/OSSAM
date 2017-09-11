#include "Missile.h"
#include "../../../Entities/Spaceship.h"

/**
 * @brief Missile::Missile
 * @param Parent
 */

Missile::Missile(Spaceship *Parent) : Bullet(Parent)
{
    Type = Bullet::Missile;
}


Missile::Missile(Missile *copy) : Bullet(copy)
{
    Type=  Bullet::Missile;
}

Missile::~Missile()
{

}

void Missile::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    Shooted->TakeDamage(this);
}
