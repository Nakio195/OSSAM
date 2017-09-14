#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <list>

#include <SFML/Graphics.hpp>
#include "../Item.h"
#include "Entities/Spaceship.h"

using namespace std;

#include "Bullet/Laser.h"
#include "Bullet/Missile.h"

class Bullet;

class Weapon : public Item
{
    public:
        enum Select{Main, Secondary};

        Weapon(Spaceship *pParent, string pName = "Laser Simple", string PathToWeapon = "", float pSpeed = 0.33);
        virtual ~Weapon();

        Bullet* copyBullet();
        void setBullet(unsigned int pHit, string PathToBulletTexture, string PathToBlastTexture);
        void setBullet(Bullet BulletReference);
        void setShootingDirection(sf::Vector2f Direction);
        void setRelativePosition(sf::Vector2f Position);
        void setShootPosition(sf::Vector2f Position);
        sf::Vector2f getRelativePosition();
        sf::Vector2f getShootPosition();

        void draw(sf::RenderWindow *Window);

        void setBlastAnim(std::string Path, unsigned int NbFrames, sf::IntRect Rect);
        virtual void Shoot(sf::Vector2f InitialPosition);

        float getSpeed();
        void setSpeed(float pSpeed);

        void RefreshElapsedTime(bool Release = false);

    private:
        float Speed;     //Cadence de tir en tir/s
        Bullet* BulletType;      //Type de tir
        Timer ReloadTimer;
        Entity *Parent;
        sf::Vector2f ShootingDirection;

        sf::Vector2f RelativePosition;
        sf::Vector2f ShootPosition;

        sf::Sprite MainSprite;
        //Textures et anim
        sf::Texture *Base_Texture;

        Animation<Weapon> *BlastAnim;
        sf::Texture *Blast_Texture;

};

#endif // WEAPON_H
