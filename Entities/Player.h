#ifndef PLAYER_H
#define PLAYER_H

#include <string.h>
#include <iostream>

#include "Spaceship.h"

using namespace std;

class Player : public Spaceship
{
    public:
        Player(string pName = "Cap'tain Barbare", string PathTotexture = "Ressources/Sprite/Galile.png", unsigned int pLife = 100, unsigned int pShield = 50, unsigned int pAttack = 10, unsigned int pDefense = 10, unsigned int pGenerator = 10, float pSpeed = 300, unsigned int pXP = 0, unsigned int pAmmo = 3);

    private:
        unsigned int Xp;
        int Level;
        Inventory *myInventory;
};

#endif // PLAYER_H
