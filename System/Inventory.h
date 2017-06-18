#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include "UserInterface.h"
#include "UI/UI_Button.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Shield.h"

class Spaceship;

class Inventory : public UserInterface
{
    public:
        Inventory();
        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);
        bool isOpen();
        void Close();
        void Open();

    private:
        bool Opened;
        sf::Texture Background;
        UI_Button *CloseBtn;
        UI_Button *NextBtn;
        UI_Button *PreviousBtn;

        std::list<Weapon*> MyWeapons;
        std::list<Shield*> MyWeapons;

        Weapon *MainWeapon;
        Weapon *SecondaryWeapon;

        Shield *MainShield;


};

#endif // INVENTORY_H
