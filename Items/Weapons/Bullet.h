#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../Entity.h"

using namespace std;

class Weapon;
class Spaceship;

class Bullet : public Entity
{
    public:
        enum BulletType{Laser, Missile};

    public:
        Bullet(Bullet *copy);
        Bullet(Spaceship *pParent, string pName = "Laser Simple", unsigned int pHit = 10, string PathToBulletTexture = "Ressources/Sprite/LaserBleu.png", string PathToBlastTexture = "Ressources/Sprite/boom1.png");
        ~Bullet();

        unsigned int getType();
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

        virtual void Hitting(Spaceship *Shooter, Spaceship *Shooted);

    protected:
        unsigned int Type;      // Identifie la sous classe de munition
        unsigned int Hit;       // Dégats en HP/tirs

        sf::Vector2f Direction;

        float Speed; // Vitesse de déplacment en pixels/s
        Spaceship *Parent;

        Animation<Bullet> *BlastAnim;
        sf::Texture *BlastTexture;
        sf::Texture *BulletTexture;
};

#endif // BULLET_H
