#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string.h>
#include <System/Animation.h>

using namespace std;

class Entity : public sf::Sprite
{
    public:
        Entity(string pName = "Entity");

        float getElapsedTime();
        void RefreshElapsedTime(bool Release = false);

        void ChangeTexture(sf::Texture *NewTexture);

        void MoveLinearTo(sf::Vector2f Position);

        string getName();

    protected:
        string Name;
        float ElapsedTime;
        sf::Clock Clock;

        sf::Vector2f OnGoingPosition;
};

#endif // ENTITY_H
