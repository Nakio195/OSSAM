#include "Entity.h"

/**
 * @brief Entity::Entity
 * @param pName
 */

Entity::Entity(string pName)
{
    Name = pName;
    Clock.restart();
    OnGoingPosition = getPosition();
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

void Entity::MoveLinearTo(sf::Vector2f Position)
{
    OnGoingPosition = Position;
}
