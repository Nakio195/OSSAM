#ifndef SPACESHIP_H
#define SPACESHIP_H


#include "Entity.h"
#include "System/ATH.h"
#include "Items/Shield.h"
#include "System/Inventory.h"

class Weapon;
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
        }Statistics;

        enum SpaceshipFaction{FactionPlayer, FactionWasp};

        enum SpaceshipType {Kaahl, Bleuton, Picard};

    public:
        Spaceship(SpaceshipType pType, string pName = "Cap'tain Khaal'A.Gan", string PathTotexture = "Ressources/Sprite/Galile.png", int pLife = 100, int pShield = 50, unsigned int pAttack = 10, unsigned int pDefense = 10, unsigned int pGenerator = 10, float pSpeed = 600, unsigned int pXP = 0, unsigned int pAmmo = 3);
        ~Spaceship();

        Spaceship::Statistics getStats();

        int getHealth();
        int getShield();
        int getShieldMax();

        Inventory* getInventory();
        bool addItem(Item* newItem);

        bool Shoot(int UsedWeapon);
        bool Shoot(IA_ShootNode<Spaceship> *Node);
        void TakeDamage(Bullet* Damage);

        int Move();
        void MoveLinearTo(IA_PathNode<Spaceship> *Node);

        void StartSequencer();
        void AddSequencerNode(IA_Node<Spaceship> NewNode);
        bool isPlayer();
        void setFaction(int pFaction);
        int getFaction();

        void setAimedTarget(Spaceship* pTarget);
        Spaceship* getAimedTarget();
        void setAimed(bool pAimed);

        bool isDead();
        void Die();

        void RefreshElapsedTime(bool Release = false);
        ATH* getUI();
        void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

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

        int HealthPoints;
        int Faction;
        SpaceshipType Type;

        Statistics Stats;
        bool Dying;
        bool Dead;

        /** IA and automations **/
        IA_PathNode<Spaceship> *AutoMoveNode;
        IA_Sequencer<Spaceship> Sequencer;

        Spaceship *Target;
        bool Aimed;

        /** Inventory **/
        Inventory *mInventory;

        /** Shield **/
        Shield *MainShield;

        /** Weapons **/
        Weapon *MainWeapon;
        Weapon *SecondaryWeapon;

        /** ATH **/
        ATH *UI;

        /** Animations **/

        sf::Sprite Sprite;
        //Icons and main        
        sf::Texture *Aimed_Texture;
        sf::Sprite Aimed_Sprite;

        sf::Texture *Texture_Spaceship;
        sf::Texture *Texture_FullLife;
        sf::Texture *Texture_HalfLife;

        //Hitted
        Animation<Spaceship> *HittedAnim;

        //Dying
        Animation<Spaceship> *DyingAnim;
        sf::Texture *Texture_Dying;

};

#endif // SPACESHIP_H
