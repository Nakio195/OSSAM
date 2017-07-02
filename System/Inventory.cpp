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

    Slot_MainWeapon = new UI_Slot(this);
    Slot_SecondaryWeapon = new UI_Slot(this);
    Slot_MainShield = new UI_Slot(this);
    Slot_MainBumper = new UI_Slot(this);

    Slot_MainWeapon->setRelativePosition(sf::Vector2f(470, 158));
    Slot_SecondaryWeapon->setRelativePosition(sf::Vector2f(470, 231));
    Slot_MainBumper->setRelativePosition(sf::Vector2f(470, 366));
    Slot_MainShield->setRelativePosition(sf::Vector2f(248, 366));


    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        MyBag[i] = new UI_Slot(this);
        MyBag[i]->setRelativePosition(sf::Vector2f(622 + i%2 *75, 141 + i/2 * 76));
        MyBag[i]->setType(UI_Slot::Bag);
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

    if(Slot_MainWeapon->getState() != UI_Slot::Draged)
        Slot_MainWeapon->Display(Window);
    if(Slot_SecondaryWeapon->getState() != UI_Slot::Draged)
        Slot_SecondaryWeapon->Display(Window);
    if(Slot_MainShield->getState() != UI_Slot::Draged)
        Slot_MainShield->Display(Window);
    if(Slot_MainBumper->getState() != UI_Slot::Draged)
        Slot_MainBumper->Display(Window);

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

    if(Slot_MainWeapon->getState() == UI_Slot::Draged)
        Slot_MainWeapon->Display(Window);
    if(Slot_SecondaryWeapon->getState() == UI_Slot::Draged)
        Slot_SecondaryWeapon->Display(Window);
    if(Slot_MainShield->getState() == UI_Slot::Draged)
        Slot_MainShield->Display(Window);
    if(Slot_MainBumper->getState() == UI_Slot::Draged)
        Slot_MainBumper->Display(Window);
}


void Inventory::HandleEvent(sf::Event &Event)
{
    CloseBtn->HandleEvent(Event);
    PreviousBtn->HandleEvent(Event);
    NextBtn->HandleEvent(Event);
    Slot_MainBumper->HandleEvent(Event);
    Slot_MainWeapon->HandleEvent(Event);
    Slot_SecondaryWeapon->HandleEvent(Event);
    Slot_MainShield->HandleEvent(Event);

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

    //Handling Drag&Drop

    UI_Slot *MovedSlot = NULL;
    UI_Slot *DestinationSlot = NULL;

    sf::FloatRect DropPlace;


    //Identifying MovedSlot
    if(Slot_MainWeapon->isDropped())
    {
        MovedSlot = Slot_MainWeapon;
        DropPlace = MovedSlot->getDropPosition();
    }

    else if(Slot_SecondaryWeapon->isDropped())
    {
        MovedSlot = Slot_SecondaryWeapon;
        DropPlace = MovedSlot->getDropPosition();
    }

    else if(Slot_MainShield->isDropped())
    {
        MovedSlot = Slot_MainShield;
        DropPlace = MovedSlot->getDropPosition();
    }

    else if(Slot_MainBumper->isDropped())
    {
        MovedSlot = Slot_MainBumper;
        DropPlace = MovedSlot->getDropPosition();
    }

    else
    {
        for(unsigned int i = 0; i < BAG_SIZE; i++)
        {
            MyBag[i]->HandleEvent(Event);

            if(MyBag[i]->isDropped())
            {
                MovedSlot = MyBag[i];
                DropPlace = MovedSlot->getDropPosition();
                break;
            }
        }
    }

    //Finding DestinationSlot
    if(DropPlace != sf::FloatRect())
    {
        if(Slot_MainWeapon->getGlobalBounds().intersects(DropPlace))
            DestinationSlot = Slot_MainWeapon;

        else if(Slot_SecondaryWeapon->getGlobalBounds().intersects(DropPlace))
            DestinationSlot = Slot_SecondaryWeapon;

        else if(Slot_MainShield->getGlobalBounds().intersects(DropPlace))
            DestinationSlot = Slot_MainShield;

        else if(Slot_MainBumper->getGlobalBounds().intersects(DropPlace))
            DestinationSlot = Slot_MainBumper;

        else
        {
            for(unsigned int i = 0; i < BAG_SIZE; i++)
            {
                if(MyBag[i] != MovedSlot)
                {
                    if(MyBag[i]->getGlobalBounds().intersects(DropPlace))
                    {
                        DestinationSlot = MyBag[i];
                        break;
                    }
                }
            }
        }

        if(DestinationSlot != NULL)
        {
            if(!DestinationSlot->isEmpty())
            {
                Item* Temp = DestinationSlot->getItem();
                DestinationSlot->setItem(MovedSlot->getItem());
                MovedSlot->setItem(Temp);
            }

            else
            {
                DestinationSlot->setItem(MovedSlot->getItem());
                MovedSlot->Clear();
            }

            if(DestinationSlot->getType() == UI_Slot::Bag)
                DestinationSlot->getItem()->setState(Item::InBag);
            else if(DestinationSlot->getType() == UI_Slot::Equipement)
                DestinationSlot->getItem()->setState(Item::Equiped);

            MovedSlot->ValidateDrop();
        }

        else
            MovedSlot->UnvalidateDrop();
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
                    if(CurrentWeapon->getState() == Item::InBag)
                    {
                        MyBag[i]->setItem(CurrentWeapon);
                        i++;
                    }
                }
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
                    if(MyBag[i]->getState() == Item::InBag)
                    {
                        MyBag[i]->setItem(CurrentShield);
                        i++;
                    }
                }
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
