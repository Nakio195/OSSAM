#ifndef ENTITY_H
#define ENTITY_H

#include <string.h>
#include <System/Scene/SceneNode.h>
#include <System/Animation.h>
#include "Entities/IA/IA_Sequencer.h"

using namespace std;

class Entity : public SceneNode
{
    public:
        Entity(string pName = "Entity");

        float getElapsedTime();
        void RefreshElapsedTime(bool Release = false);

        void ChangeTexture(sf::Texture *NewTexture);

        void setInertia(float pInertia);
        sf::Vector2f getDirection();

        void setDirection(sf::Vector2f pDirection);
        sf::Vector2f getLinearDirectionTo(Entity* Target);

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
