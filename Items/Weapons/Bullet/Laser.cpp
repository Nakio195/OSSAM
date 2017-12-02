#include "Laser.h"
#include "../../../Entities/Spaceship.h"

/**
 * @brief Laser::Laser
 * @param Parent
 */

Laser::Laser(Spaceship* Parent) : Bullet(Parent)
{
    Type = Bullet::Laser;
    Speed = 1500;
}


Laser::Laser(Laser *copy) : Bullet(copy)
{
    Type = Bullet::Laser;
    Speed = 1500;
}

Laser::~Laser()
{

}


void Laser::Move()
{
    Bullet::Move();
}

void Laser::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    if(!Exploded)
    {
        Shooted->TakeDamage(this);
        Exploded = true;

        if(Shooted->isDead())
            Shooter->setAimedTarget(NULL);

        BlastAnim->Start();
    }

    else if(Exploded && !BlastAnim->isRunning())
    {
        Remove = true;
    }
}
