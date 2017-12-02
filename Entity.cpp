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


sf::Vector2f Entity::getLinearDirectionTo(Entity* Target)
{
    sf::Vector2f LinearDirection(0, 0);

    float dX = (Target->getPosition().x-getPosition().x);
    float dY = (Target->getPosition().y-getPosition().y);
    float Phi = atan(dX/dY);

    LinearDirection.x = sin(Phi);
    LinearDirection.y = cos(Phi);

    if((dX < 0 && dY < 0) || dY < 0)
    {
        LinearDirection.x *= -1.0;
        LinearDirection.y *= -1.0;
    }

    return LinearDirection;
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
    {
        ElapsedTime = Clock.restart().asSeconds();
        if(ElapsedTime < 0.0)
            ElapsedTime = 0.0;
    }
}

