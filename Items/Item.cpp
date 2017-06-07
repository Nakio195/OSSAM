#include "Item.h"

Item::Item(std::string pName)
{
    Name = pName;
    Clock.restart();
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
