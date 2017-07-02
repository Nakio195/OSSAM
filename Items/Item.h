#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class Item
{
    public:
        enum {Weapon, Shield, PowerUp, Passive};
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

    protected:
        void setCategory(unsigned int pCategory);

        std::string Name;
        unsigned int Category;

        float ElapsedTime;
        sf::Clock Clock;

        sf::Texture Icon;

        unsigned int State;


};

#endif // ITEM_H
