#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class Item
{
    public:
        Item(std::string pName);
        void setName(std::string pName);
        std::string getName();

        float getElapsedTime();
        void RefreshElapsedTime(bool Release = false);

    protected:
        std::string Name;
        float ElapsedTime;
        sf::Clock Clock;

        sf::Texture Icon;


};

#endif // ITEM_H
