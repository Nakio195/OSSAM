#include "UI_Slot.h"

UI_Slot::UI_Slot(UserInterface *pParent) : UserInterface()
{
    Background = new sf::Texture();

    if(Background->loadFromFile("Ressources/System/Icon/Empty.png"))
        sf::Sprite::setTexture(*Background);

    TextureIcon = new sf::Texture();

    Parent = pParent;

    State = UI_Slot::Enabled;
    Dropped = false;
    Empty = true;
    Type = UI_Slot::Equipement;
}

void UI_Slot::setType(unsigned int pType)
{
    if(pType == UI_Slot::Bag || UI_Slot::Equipement)
    {
        Type = pType;
    }
}

unsigned int UI_Slot::getType()
{
    return Type;
}

sf::FloatRect UI_Slot::getDropPosition()
{
    if(Dropped)
    {
        Position = Origin;
        return Icon.getGlobalBounds();
    }

    else
        return sf::FloatRect();
}

bool UI_Slot::isDropped()
{
    return Dropped;
}

void UI_Slot::ValidateDrop()
{
    Dropped = false;
}

void UI_Slot::UnvalidateDrop()
{
    Dropped = false;
    Position = Origin;
}

bool UI_Slot::isHovered()
{

}

bool UI_Slot::isEmpty()
{
    return Empty;
}


void UI_Slot::Clear()
{
    Container = NULL;
    setTexture(*Background);
    Empty = true;
}

void UI_Slot::setItem(Item* pItem)
{
    Container = pItem;
    setIcon(pItem->getIcon());
    Empty = false;
}

Item* UI_Slot::getItem()
{
    return Container;
}

void UI_Slot::setIcon(sf::Texture* pTexture)
{
    TextureIcon = pTexture;
    Icon.setTexture(*pTexture);
}

void UI_Slot::setState(unsigned int pState)
{
    if(pState == UI_Slot::Enabled)
    {
        Icon.setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }

    else if(pState == UI_Slot::Disabled)
    {
        Icon.setColor(sf::Color(0x80, 0x80, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Clicked)
    {
        Icon.setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Draged)
    {
        Icon.setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }
}


unsigned int UI_Slot::getState()
{
    return State;
}

void UI_Slot::setRelativePosition(float x, float y)
{
    Position = sf::Vector2f(x, y);
    Origin = Position;
}

void UI_Slot::setRelativePosition(sf::Vector2f RelativePosition)
{
    Position = RelativePosition;
    Origin = Position;
}

sf::Vector2f UI_Slot::getRelativePosition()
{
    return Position;
}

void UI_Slot::Display(sf::RenderWindow &Window)
{
    setPosition(Parent->getPosition() + Origin);
    Icon.setPosition(Parent->getPosition() + Position);
    Window.draw(*this);

    if(!Empty)
        Window.draw(Icon);
}

void UI_Slot::HandleEvent(sf::Event &Event)
{
    if(State == UI_Slot::Disabled || Empty)
        return;

    switch(Event.type)
    {
        case sf::Event::MouseButtonPressed:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(this->getGlobalBounds().contains(Event.mouseButton.x, Event.mouseButton.y))
                {
                    setState(UI_Slot::Draged);
                    DragStartPosition = sf::Vector2f(Event.mouseButton.x, Event.mouseButton.y);
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(State == UI_Slot::Draged)
                {
                    setState(UI_Slot::Enabled);
                    Dropped = true;
                }
            }
            break;

        case sf::Event::MouseMoved:
            if(State == UI_Slot::Draged)
            {
                Position += sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y) - DragStartPosition;
                DragStartPosition = sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y);
            }
            break;

        default:
            break;
    }
}
