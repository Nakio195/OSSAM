#include "Item.h"

Item::Item(std::string pName)
{
    Name = pName;
    Clock.restart();
    Category = Item::Passive;
    State = Item::InBag;
}

void Item::setName(std::string pName)
{
    if(pName.empty() == false)
        Name = pName;
}

std::string Item::getName()
{
    return Name;
}

unsigned int Item::getState()
{
    return State;
}

void Item::setState(unsigned int pState)
{
    if(pState == Item::Equiped || pState == Item::InBag)
        State = pState;
}

sf::Texture* Item::getIcon()
{
    return &Icon;
}

void Item::setIcon(std::string Path)
{
    Icon.loadFromFile(Path);
}

unsigned int Item::getCategory()
{
    return Category;
}

float Item::getElapsedTime()
{
    return ElapsedTime;
}

void Item::RefreshElapsedTime(bool Release)
{
    if(Release)
    {
        Clock.restart();
        ElapsedTime = 0;
    }

    else
        ElapsedTime = Clock.restart().asSeconds();
}


void Item::setCategory(unsigned int pCategory)
{
    Category = pCategory;
}
