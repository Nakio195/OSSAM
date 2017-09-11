#include "Inventory.h"

/**
 * @brief Inventory::Inventory
 */

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

    Slot_MainWeapon = new UI_Slot(this, UI_Slot::Weapon);
    Slot_SecondaryWeapon = new UI_Slot(this, UI_Slot::Weapon);
    Slot_MainShield = new UI_Slot(this, UI_Slot::Shield);
    Slot_MainBumper = new UI_Slot(this, UI_Slot::Bumper);

    Slot_MainWeapon->setRelativePosition(sf::Vector2f(470, 158));
    Slot_SecondaryWeapon->setRelativePosition(sf::Vector2f(470, 231));
    Slot_MainBumper->setRelativePosition(sf::Vector2f(470, 366));
    Slot_MainShield->setRelativePosition(sf::Vector2f(248, 366));


    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        MyBag[i] = new UI_Slot(this, UI_Slot::Bag);
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

    if(Slot_MainWeapon->getState() != UI_Slot::Dragged)
        Slot_MainWeapon->Display(Window);
    if(Slot_SecondaryWeapon->getState() != UI_Slot::Dragged)
        Slot_SecondaryWeapon->Display(Window);
    if(Slot_MainShield->getState() != UI_Slot::Dragged)
        Slot_MainShield->Display(Window);
    if(Slot_MainBumper->getState() != UI_Slot::Dragged)
        Slot_MainBumper->Display(Window);

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        if(MyBag[i]->getState() != UI_Slot::Dragged)
            MyBag[i]->Display(Window);
    }

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        if(MyBag[i]->getState() == UI_Slot::Dragged)
            MyBag[i]->Display(Window);
    }

    if(Slot_MainWeapon->getState() == UI_Slot::Dragged)
        Slot_MainWeapon->Display(Window);
    if(Slot_SecondaryWeapon->getState() == UI_Slot::Dragged)
        Slot_SecondaryWeapon->Display(Window);
    if(Slot_MainShield->getState() == UI_Slot::Dragged)
        Slot_MainShield->Display(Window);
    if(Slot_MainBumper->getState() == UI_Slot::Dragged)
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

    for(unsigned int i = 0; i < BAG_SIZE; i++)
    {
        MyBag[i]->HandleEvent(Event);
    }

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
        if(CurrentTab < 1)
            selectTab(CurrentTab +1);
    }

    //Handling Drag&Drop   

    UI_Slot *DraggedSlot = NULL;
    UI_Slot *MovedSlot = NULL;
    UI_Slot *DestinationSlot = NULL;

    sf::Vector2f DropPlace;

    //Identifying DraggedSlot
    if(Slot_MainWeapon->getState() == UI_Slot::Dragged)
        DraggedSlot = Slot_MainWeapon;
    else if(Slot_SecondaryWeapon->getState() == UI_Slot::Dragged)
        DraggedSlot = Slot_SecondaryWeapon;
    else if(Slot_MainShield->getState() == UI_Slot::Dragged)
        DraggedSlot = Slot_MainShield;
    else if(Slot_MainBumper->getState() == UI_Slot::Dragged)
        DraggedSlot = Slot_MainBumper;

    if(Slot_MainWeapon->isDropped())
        MovedSlot = Slot_MainWeapon;
    else if(Slot_SecondaryWeapon->isDropped())
        MovedSlot = Slot_SecondaryWeapon;
    else if(Slot_MainShield->isDropped())
        MovedSlot = Slot_MainShield;
    else if(Slot_MainBumper->isDropped())
        MovedSlot = Slot_MainBumper;

    else
    {
        for(unsigned int i = 0; i < BAG_SIZE; i++)
        {
            if(MyBag[i]->getState() == UI_Slot::Dragged)
                DraggedSlot = MyBag[i];

            if(MyBag[i]->isDropped())
            {
                MovedSlot = MyBag[i];
                break;
            }
        }
    }

    if(Slot_MainWeapon->isHovered() && DraggedSlot != NULL)
    {
        if(DraggedSlot->getItem()->getCategory() == Slot_MainWeapon->getType())
            Slot_MainWeapon->setState(UI_Slot::Accept);
        else
            Slot_MainWeapon->setState(UI_Slot::Reject);
    }

    if(Slot_SecondaryWeapon->isHovered() && DraggedSlot != NULL)
    {
        if(DraggedSlot->getItem()->getCategory() == Slot_SecondaryWeapon->getType())
            Slot_SecondaryWeapon->setState(UI_Slot::Accept);
        else
            Slot_SecondaryWeapon->setState(UI_Slot::Reject);
    }

    if(Slot_MainShield->isHovered() && DraggedSlot != NULL)
    {
        if(DraggedSlot->getItem()->getCategory() == Slot_MainShield->getType())
            Slot_MainShield->setState(UI_Slot::Accept);
        else
            Slot_MainShield->setState(UI_Slot::Reject);
    }

    if(Slot_MainBumper->isHovered() && DraggedSlot != NULL)
    {
        if(DraggedSlot->getItem()->getCategory() == Slot_MainBumper->getType())
            Slot_MainBumper->setState(UI_Slot::Accept);
        else
            Slot_MainBumper->setState(UI_Slot::Reject);
    }

    //Finding DestinationSlot
    if(MovedSlot != NULL)
    {
        DropPlace = MovedSlot->getDropPosition();

        if(Slot_MainWeapon->getGlobalBounds().contains(DropPlace))
            DestinationSlot = Slot_MainWeapon;

        else if(Slot_SecondaryWeapon->getGlobalBounds().contains(DropPlace))
            DestinationSlot = Slot_SecondaryWeapon;

        else if(Slot_MainShield->getGlobalBounds().contains(DropPlace))
            DestinationSlot = Slot_MainShield;

        else if(Slot_MainBumper->getGlobalBounds().contains(DropPlace))
            DestinationSlot = Slot_MainBumper;

        else
        {
            for(unsigned int i = 0; i < BAG_SIZE; i++)
            {
                if(MyBag[i] != MovedSlot)
                {
                    if(MyBag[i]->getGlobalBounds().contains(DropPlace))
                    {
                        DestinationSlot = MyBag[i];
                        break;
                    }
                }
            }
        }

        if(DestinationSlot != NULL)
        {
            if(DestinationSlot->getType() == MovedSlot->getItem()->getCategory() || DestinationSlot->getType() == UI_Slot::Bag)
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
                else
                    DestinationSlot->getItem()->setState(Item::Equiped);

                MovedSlot->ValidateDrop();
                DestinationSlot->setState(UI_Slot::Enabled);
            }

            else
            {
                MovedSlot->UnvalidateDrop();
                DestinationSlot->setState(UI_Slot::Enabled);
            }
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
                    if(CurrentShield->getState() == Item::InBag)
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
