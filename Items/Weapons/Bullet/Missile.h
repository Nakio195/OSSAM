#ifndef MISSILE_H
#define MISSILE_H

#include "../Bullet.h"

class Missile : public Bullet
{
    public:
        Missile(Weapon *Parent);
};

#endif // MISSILE_H
