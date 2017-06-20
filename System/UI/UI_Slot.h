#ifndef UI_SLOT_H
#define UI_SLOT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "../UserInterface.h"

class UI_Slot : public UserInterface
{
    public:
        enum States{Enabled, Disabled, Clicked, Released, Draged};

    public:
        UI_Slot(std::string Path, UserInterface *pParent);
        UI_Slot(sf::Texture *Texture, UserInterface *pParent);

        bool isTriggered();
        bool isHovered();
        void setState(unsigned int pState);

        void setIcon(sf::Texture* pTexture);

        void setRelativePosition(float x, float y);
        void setRelativePosition(sf::Vector2f RelativePosition);
        sf::Vector2f getRelativePosition();

        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);

    private:
        UserInterface *Parent;
        sf::Texture *Background;
        sf::Vector2f Position;
        sf::Vector2f DragStartPosition;
        unsigned int State;
        bool Triggered;
        bool Hovered;

};

#endif // UI_SLOT_H
