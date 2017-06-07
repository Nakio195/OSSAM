#include "Inventory.h"

Inventory::Inventory()
{
    Background.loadFromFile("Ressources/System/Inventory.png");
    MainSprite.setTexture(Background);

    CloseBtn = new UI_Button("Ressources/System/UI/CloseBtn.png");
    CloseBtn->setRelativePosition(100, 100);
    PreviousBtn = new UI_Button("Ressources/System/UI/PreviousBtn.png");
    PreviousBtn->setRelativePosition(100, 50);
    NextBtn = new UI_Button("Ressources/System/UI/NextBtn.png");
    NextBtn->setRelativePosition(50, 100);
}


void Inventory::Display(sf::RenderWindow &Window)
{
    Window.draw(MainSprite);
    CloseBtn->Display(Window);
    PreviousBtn->Display(Window);
    NextBtn->Display(Window);
}


void Inventory::HandleEvent(sf::Event &Event)
{
    CloseBtn->HandleEvent(Event);
    PreviousBtn->HandleEvent(Event);
    NextBtn->HandleEvent(Event);
}
