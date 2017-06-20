#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include "UserInterface.h"
#include "UI/UI_Button.h"
#include "UI/UI_Slot.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Shield.h"

#define BAG_SIZE    10

class Spaceship;
class Shield;

class Inventory : public UserInterface
{
    public:
        Inventory();
        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);
        void addItem(Item *NewItem);
        void selectTab(unsigned int Category);
        bool isOpen();
        void Close();
        void Open();

    private:
        bool Opened;
        sf::Texture Background;
        sf::Font TextFont;
        sf::Text CategoryTxt;

        UI_Slot* Slot_MainWeapon;
        UI_Slot* Slot_SecondaryWeapon;
        UI_Slot* Slot_MainShield;
        UI_Slot* Slot_MainBumper;
        UI_Slot* MyBag[BAG_SIZE];
        UI_Button *CloseBtn;
        UI_Button *NextBtn;
        UI_Button *PreviousBtn;

        unsigned int CurrentTab;

        std::list<Weapon*> MyWeapons;
        std::list<Shield*> MyShields;
        std::list<Shield*> MyPowerUp;

        Weapon *MainWeapon;
        Weapon *SecondaryWeapon;

        Shield *MainShield;


};

#endif // INVENTORY_H
