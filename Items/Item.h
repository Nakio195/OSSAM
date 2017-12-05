#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class Spaceship;
class UI_Slot;

class Item
{
    public:
        enum {Weapon, Shield, PowerUp, Bumper, Passive};
        enum {InBag, Equiped};

    public:
        Item(std::string pName);
        void setName(std::string pName);
        std::string getName();
        unsigned int getCategory();

        void setIcon(std::string Path);
        sf::Texture* getIcon();

        unsigned int getState();
        void setState(unsigned int pState);

        float getElapsedTime();
        void RefreshElapsedTime(bool Release = false);

        void setOwner(Spaceship *newOwner);
        void setMySlot(UI_Slot* MyNewSlot);

    protected:
        void setCategory(unsigned int pCategory);

        UI_Slot *mySlot;
        Spaceship *Owner;

        std::string Name;
        unsigned int Category;

        float ElapsedTime;
        sf::Clock Clock;

        sf::Texture Icon;

        unsigned int State;


};

#endif // ITEM_H
