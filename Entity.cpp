#include "Entity.h"

/**
 * @brief Entity::Entity
 * @param pName
 */

extern int Window_Height;
extern int Window_Width;

Entity::Entity(string pName)
{
    Name = pName;
    Speed = 300;
    Inertia = 1.0;
    Direction = sf::Vector2f(0,0);
    Clock.restart();
    AutoMoveRunning = false;
}

void Entity::ChangeTexture(sf::Texture *NewTexture)
{
    if(NewTexture != NULL)
        sf::Sprite::setTexture(*NewTexture);
}

string Entity::getName()
{
    return Name;
}

float Entity::getElapsedTime()
{
    return ElapsedTime;
}

void Entity::setInertia(float pInertia)
{
    Inertia = pInertia;
}

sf::Vector2f Entity::getDirection()
{
    return Direction;
}

void Entity::setDirection(sf::Vector2f pDirection)
{
    Direction += pDirection;

    if(Direction.x > 1)
        Direction.x = 1;
    if(Direction.y > 1)
        Direction.y = 1;
    if(Direction.x < -1)
        Direction.x = -1;
    if(Direction.y < -1)
        Direction.y = -1;

}

void Entity::RefreshElapsedTime(bool Release)
{
    if(Release)
    {
        Clock.restart();
        ElapsedTime = 0;
    }

    else
        ElapsedTime = Clock.restart().asSeconds();
}

