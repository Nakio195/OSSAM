#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Weapon.h"
#include "../../Entities/Spaceship.h"

using namespace std;

class Weapon;
class Spaceship;

class Bullet : public Entity
{
    public:
        Bullet(Bullet *copy);
        Bullet(Spaceship *pParent, string pName = "Laser Simple", unsigned int pHit = 10, string PathToBulletTexture = "Ressources/Sprite/LaserBleu.png", string PathToBlastTexture = "Ressources/Sprite/boom1.png");

        unsigned int getHit();
        void setHit(unsigned int pHit);

        void setDirection(sf::Vector2f pDirection);
        sf::Vector2f getDirection();

        void setSpeed(float pSpeed);
        float getSpeed();

        void setBlastTexture(string Path);
        void setBlastTexture(sf::Texture *pBlast);

        void setBulletTexture(string Path);
        void setBulletTexture(sf::Texture *pBullet);

        void setParent(Spaceship *pParent);
        Spaceship *getParent();

        void Hitting(Spaceship *Shooter, Spaceship *Shooted);

    private:
        unsigned int Hit;       //Dégats en HP/tirs

        sf::Vector2f Direction;

        float Speed; // Vitesse de déplacment en pixels/s
        Spaceship *Parent;

        sf::Texture *BlastTexture;
        sf::Texture *BulletTexture;
};

#endif // BULLET_H
