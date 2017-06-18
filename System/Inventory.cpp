#include "Inventory.h"

Inventory::Inventory()
{
    Opened = false;

    Background.loadFromFile("Ressources/System/Inventory.png");
    setTexture(Background);
    setPosition(200, 200);

    CloseBtn = new UI_Button("Ressources/System/UI/CloseBtn.png", this);
    CloseBtn->setRelativePosition(753, 36);
    PreviousBtn = new UI_Button("Ressources/System/UI/PreviousBtn.png", this);
    PreviousBtn->setRelativePosition(621, 97);
    NextBtn = new UI_Button("Ressources/System/UI/NextBtn.png", this);
    NextBtn->setRelativePosition(745, 97);
}


void Inventory::Display(sf::RenderWindow &Window)
{
    Window.draw(*this);
    CloseBtn->Display(Window);
    PreviousBtn->Display(Window);
    NextBtn->Display(Window);
}


void Inventory::HandleEvent(sf::Event &Event)
{
    CloseBtn->HandleEvent(Event);
    PreviousBtn->HandleEvent(Event);
    NextBtn->HandleEvent(Event);

    if(CloseBtn->isTriggered())
    {
        CloseBtn->setState(UI_Button::Released);
        Close();
    }
}

bool Inventory::isOpen()
{
    return Opened;
}

void Inventory::Open()
{
    Opened = true;
}

void Inventory::Close()
{
    Opened = false;
}
