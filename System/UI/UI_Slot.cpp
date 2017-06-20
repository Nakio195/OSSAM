#include "UI_Slot.h"

UI_Slot::UI_Slot(std::string Path, UserInterface *pParent) : UserInterface()
{
    Background = new sf::Texture();

    if(Background->loadFromFile(Path))
        sf::Sprite::setTexture(*Background);

    Parent = pParent;

    State = UI_Slot::Enabled;
    Triggered = false;
}

UI_Slot::UI_Slot(sf::Texture *Texture, UserInterface *pParent) : UserInterface()
{
    Background = Texture;
    sf::Sprite::setTexture(*Background);
    Parent = pParent;

    State = UI_Slot::Enabled;
    Triggered = false;
}

bool UI_Slot::isTriggered()
{
    if(Triggered)
    {
        Triggered = false;
        return true;
    }

    else
        return false;
}

bool UI_Slot::isHovered()
{

}

void UI_Slot::setIcon(sf::Texture* pTexture)
{
    Background = pTexture;
    setTexture(*Background);
}

void UI_Slot::setState(unsigned int pState)
{
    if(pState == UI_Slot::Enabled)
    {
        this->setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }

    else if(pState == UI_Slot::Disabled)
    {
        this->setColor(sf::Color(0x80, 0x80, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Clicked)
    {
        this->setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Released)
    {
        this->setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }

    else if(pState == UI_Slot::Draged)
    {
        this->setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }
}

void UI_Slot::setRelativePosition(float x, float y)
{
    Position = sf::Vector2f(x, y);
}

void UI_Slot::setRelativePosition(sf::Vector2f RelativePosition)
{
    Position = RelativePosition;
}

sf::Vector2f UI_Slot::getRelativePosition()
{
    return Position;
}

void UI_Slot::Display(sf::RenderWindow &Window)
{
    setPosition(Parent->getPosition() + Position);
    Window.draw(*this);
}

void UI_Slot::HandleEvent(sf::Event &Event)
{
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
                    setState(UI_Slot::Released);
                    Triggered = true;
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
