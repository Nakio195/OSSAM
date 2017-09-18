#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string.h>
#include <System/Animation.h>
#include "Entities/IA/AutoMovePath.h"

using namespace std;

class Entity : public sf::Sprite
{
    public:
        Entity(string pName = "Entity");

        float getElapsedTime();
        void RefreshElapsedTime(bool Release = false);

        void ChangeTexture(sf::Texture *NewTexture);

        void setInertia(float pInertia);
        sf::Vector2f getDirection();

        void setDirection(sf::Vector2f pDirection);

        string getName();

    protected:
        string Name;
        float Inertia;
        float Speed;

        sf::Vector2f Direction;
        float ElapsedTime;
        sf::Clock Clock;


        bool AutoMoveNeedRefresh;
        sf::Vector2f AutoMoveDirection;
        sf::Vector2f AutoMoveDeparturePosition;
        bool AutoMoveRunning;

};

#endif // ENTITY_H
