#ifndef MISSILE_H
#define MISSILE_H

#include "../Bullet.h"

class Spaceship;

class Missile : public Bullet
{
    public:
        Missile(Spaceship *Parent);
        Missile(Missile *copy);
        ~Missile();

        virtual void Hitting(Spaceship *Shooter, Spaceship *Shooted);
};

#endif // MISSILE_H
