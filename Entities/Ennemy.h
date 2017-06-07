#ifndef ENNEMY_H
#define ENNEMY_H

#include <iostream>

#include "Spaceship.h"


class Ennemy : public Spaceship
{
    public:
        Ennemy(string PathTotexture = "Ressources/Sprite/ennemi1.png", string pName = "Bleuton", unsigned int pLife = 100, unsigned int pShield = 50, unsigned int pAttack = 10, unsigned int pDefense = 10, unsigned int pGenerator = 10, float pSpeed = 0.5, unsigned int pXP = 0, unsigned int pAmmo = 3);
        sf::Vector2f Direction;


};

#endif // ENNEMY_H
