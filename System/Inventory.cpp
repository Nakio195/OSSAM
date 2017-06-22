#include "Inventory.h"

Inventory::Inventory()
{
    Opened = false;

    Background.loadFromFile("Ressources/System/Inventory.png");
    setTexture(Background);
    setPosition(1400/2-Background.getSize().x/2, 800/2-Background.getSize().y/2);

    CloseBtn = new UI_Button("Ressources/System/UI/CloseBtn.png", this);
    CloseBtn->setRelativePosition(753, 36);
    PreviousBtn = new UI_Button("Ressources/System/UI/PreviousBtn.png", this);
    PreviousBtn->setRelativePosition(621, 97);
    NextBtn = new UI_Button("Ressources/System/UI/NextBtn.png", this);
    NextBtn->setRelativePosition(745, 97);

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        MyBag[i] = new UI_Slot(this);
        MyBag[i]->setRelativePosition(sf::Vector2f(622 + i%2 *75, 141 + i/2 * 76));
    }

    TextFont.loadFromFile("Ressources/System/UI/TYPO KLM.ttf");
    CategoryTxt.setFont(TextFont);
    CategoryTxt.setPosition(this->getPosition()+sf::Vector2f(647, 95));
    CategoryTxt.setCharacterSize(20);
    CategoryTxt.setColor(sf::Color(75, 221, 155));
}


void Inventory::Display(sf::RenderWindow &Window)
{
    Window.draw(*this);
    CloseBtn->Display(Window);
    PreviousBtn->Display(Window);
    NextBtn->Display(Window);

    Window.draw(CategoryTxt);

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        if(MyBag[i]->getState() != UI_Slot::Draged)
            MyBag[i]->Display(Window);
    }

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        if(MyBag[i]->getState() == UI_Slot::Draged)
            MyBag[i]->Display(Window);
    }
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

    if(PreviousBtn->isTriggered())
    {
        if(CurrentTab > 0)
            selectTab(CurrentTab -1);
    }

    if(NextBtn->isTriggered())
    {
        if(CurrentTab < 3)
            selectTab(CurrentTab +1);
    }


    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        sf::FloatRect DropPlace;

        MyBag[i]->HandleEvent(Event);
        DropPlace = MyBag[i]->isDropped();

        if(DropPlace != sf::FloatRect())
        {
            for(unsigned int j = 0; j < BAG_SIZE; j++)
            {
                if(i != j)
                {
                    if(MyBag[j]->getGlobalBounds().intersects(DropPlace))
                    {
                        if(!MyBag[j]->isEmpty())
                        {
                            Item* Temp = MyBag[j]->getItem();
                            MyBag[j]->setItem(MyBag[i]->getItem());
                            MyBag[i]->setItem(Temp);
                        }

                        else
                        {
                            MyBag[j]->setItem(MyBag[i]->getItem());
                            MyBag[i]->Clear();
                        }

                        break;
                    }
                }
            }
        }
    }
}


void Inventory::selectTab(unsigned int Category)
{
    unsigned int i = 0;

    for(int i = 0; i < BAG_SIZE; i++)
    {
        MyBag[i]->Clear();
    }

    switch (Category)
    {
        case Item::Weapon:

            CurrentTab = Item::Weapon;
            CategoryTxt.setString("ARMES");
            CategoryTxt.setPosition(this->getPosition()+sf::Vector2f(658, 95));
            CategoryTxt.setCharacterSize(20);

            for (list<Weapon*>::iterator it = MyWeapons.begin(); it != MyWeapons.end(); ++it)
            {
                Weapon* CurrentWeapon = *it;

                if(i < BAG_SIZE)
                {
                    MyBag[i]->setItem(CurrentWeapon);
                }

                i++;
            }
            break;

        case Item::Shield:

            CurrentTab = Item::Shield;
            CategoryTxt.setString("POUCLIERS");
            CategoryTxt.setPosition(this->getPosition()+sf::Vector2f(645, 97));
            CategoryTxt.setCharacterSize(17);

            for (list<Shield*>::iterator it = MyShields.begin(); it != MyShields.end(); ++it)
            {
                Shield* CurrentShield = *it;

                if(i < BAG_SIZE)
                {
                    MyBag[i]->setItem(CurrentShield);
                }

                i++;
            }
            break;

        default:
            break;
    }
}

void Inventory::addItem(Item *NewItem)
{
    switch(NewItem->getCategory())
    {
        case Item::Weapon:
            MyWeapons.push_back(static_cast<Weapon*>(NewItem));
            break;

        case Item::Shield:
            MyShields.push_back(static_cast<Shield*>(NewItem));
            break;

        default:
            break;
    }
}

bool Inventory::isOpen()
{
    return Opened;
}

void Inventory::Open()
{
    Opened = true;
    selectTab(Item::Weapon);
}

void Inventory::Close()
{
    Opened = false;
}
