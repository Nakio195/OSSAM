#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include "System/Timer.h"
#include "Weapons/Bullet.h"

class Bullet;

class Shield : public Item
{
    public:
        Shield(Entity *pParent, unsigned int Shield = 50, std::string pName = "Pouclier");
        int TakeDamage(Bullet* Damage);
        int getShieldPoints();
        int getShieldMax();
        void RefreshElapsedTime(bool Release = false);

        sf::Vector2f getRelativePosition();
        void setShieldTexture(sf::Texture *Texture);
        void setShieldTexture(string PathShield, string PathBroken = "");
        void draw(sf::RenderWindow *Window);

    private:        
        int ShieldMax;
        int ShieldPoints;
        Timer ReloadTimer;
        Timer CooldownTimer;

        Entity *Parent;
        sf::Sprite MainSprite;
        sf::Texture *Texture_Shield;
        sf::Texture *Texture_Broken;
        sf::Vector2f RelativePosition;

        bool Hitted;
        bool Broken;
        Timer Hitmark;

};

#endif // SHIELD_H
