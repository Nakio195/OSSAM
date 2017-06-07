#ifndef SPACESHIP_H
#define SPACESHIP_H


#include "Entity.h"
#include "Items/Weapons/Weapon.h"
#include "System/ATH.h"
#include "Items/Shield.h"
#include "System/Inventory.h"

class Weapon;
class Bullet;
class ATH;
class Shield;
class Inventory;

class Spaceship : public Entity
{
    public:
        typedef struct
        {
            /** Common caracteristics **/
            int Life;
            int Shield;
            unsigned int Generator;
            unsigned int Attack;
            unsigned int Defense;
            float Speed;
        }Statistics;

        enum SpaceshipFaction{FactionPlayer, FactionWasp};

    public:
        Spaceship(string pName = "Cap'tain Barbare", string PathTotexture = "Ressources/Sprite/Galile.png", unsigned int pLife = 100, unsigned int pShield = 50, unsigned int pAttack = 10, unsigned int pDefense = 10, unsigned int pGenerator = 10, float pSpeed = 300, unsigned int pXP = 0, unsigned int pAmmo = 3);
        ~Spaceship();

        Spaceship::Statistics getStats();

        int getHealth();
        int getShield();
        int getShieldMax();

        void Shoot(int UsedWeapon);
        void TakeDamage(Bullet* Damage);

        bool isPlayer();
        void setFaction(int pFaction);
        int getFaction();


        bool isDead();
        void Die();
        int Move(sf::Vector2f Direction);

        void RefreshElapsedTime(bool Release = false);
        void draw(sf::RenderWindow *Window);

        Inventory* getInventory();

        /** Animations and Textures **/
        //Shield
        void setTexture_Shield(sf::Texture *pTexture);
        void setTexture_Shield(string PathShield, string PathBroken);

        // Half Life
        void setTexture_HalfLife(sf::Texture *pTexture);
        void setTexture_HalfLife(string Path);

        //Hitted
        void Anim_start_HitMark();
        void Anim_stop_HitMark();

        //Dying
        void setTexture_Dying(sf::Texture *pTexture);
        void setTexture_Dying(string Path);
        void Anim_start_Dying();
        void Anim_stop_Dying();

    protected:

        Inventory MainInventory;

        int HealthPoints;
        int Faction;

        Statistics Stats;
        bool Dying;
        bool Dead;

        /** Shield **/
        Shield *MainShield;

        /** Weapons **/
        Weapon *MainWeapon;
        Weapon *SecondaryWeapon;

        /** ATH **/
        ATH *UI;

        /** Animations **/
        sf::Texture *Texture_Spaceship;
        sf::Texture *Texture_FullLife;
        sf::Texture *Texture_HalfLife;

        //Hitted
        Animation *HittedAnim;

        //Dying
        Animation *DyingAnim;
        sf::Texture *Texture_Dying;

};

#endif // SPACESHIP_H
