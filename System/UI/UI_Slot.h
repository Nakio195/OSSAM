#ifndef UI_SLOT_H
#define UI_SLOT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "../UserInterface.h"
#include "../../Items/Item.h"

class UI_Slot : public UserInterface
{
    public:
        enum States{Enabled, Disabled, Clicked, Draged};
        enum Types{Bag, Equipement};

    public:
        UI_Slot(UserInterface *pParent);

        bool isDropped();
        bool isHovered();
        bool isEmpty();

        void setState(unsigned int pState);
        unsigned int getState();

        void Clear();
        void setType(unsigned int pType);
        unsigned int getType();
        void setItem(Item* pItem);
        Item* getItem();

        void setIcon(sf::Texture* pTexture);

        void setRelativePosition(float x, float y);
        void setRelativePosition(sf::Vector2f RelativePosition);
        sf::Vector2f getRelativePosition();
        sf::FloatRect getDropPosition();

        void ValidateDrop();
        void UnvalidateDrop();

        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);

    private:
        UserInterface *Parent;

        unsigned int Type;

        sf::Texture *Background;

        sf::Sprite Icon;
        sf::Texture *TextureIcon;

        sf::Vector2f Position;
        sf::Vector2f Origin;
        sf::Vector2f DragStartPosition;
        unsigned int State;
        bool Dropped;
        bool Hovered;
        bool Empty;

        Item *Container;

};

#endif // UI_SLOT_H
