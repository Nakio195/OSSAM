#include "Shield.h"

/**
 * @brief Shield::Shield
 * @param pParent
 * @param Shield
 * @param pName
 */

Shield::Shield(Entity *pParent, unsigned int Shield, std::string pName) : Item(pName)
{
    setCategory(Item::Shield);
    setIcon("Ressources/System/Icon/SH_1.png");

    ShieldMax = Shield;
    ShieldPoints = ShieldMax;

    Hitmark.setPeriod(0.8);
    Hitmark.setMode(Timer::OneShot);
    Hitted = 0;

    ReloadTimer.setMode(Timer::Continuous);
    ReloadTimer.setPeriod(0.2);
    ReloadTimer.StartTimer();

    CooldownTimer.setMode(Timer::OneShot);

    Parent = pParent;
    Texture_Shield = new sf::Texture();
    Texture_Broken = new sf::Texture();
}


int Shield::getShieldPoints()
{
    if(ShieldPoints > 0)
        return ShieldPoints;
    else
        return 0;
}


int Shield::getShieldMax()
{
    return ShieldMax;
}

int Shield::TakeDamage(Bullet* Damage)
{
    int ExtraDamage = 0;

    if(ShieldMax == 0)
        return Damage->getHit();

    if((ShieldPoints - int(Damage->getHit())) < 0)
    {
        ExtraDamage = Damage->getHit() - ShieldPoints;
        ShieldPoints = 0;

        Broken = true;
        Hitted = false;
        Hitmark.StopTimer();

        MainSprite.setTexture(*Texture_Broken);

        if(!CooldownTimer.isRunning())
        {
            CooldownTimer.StartTimer(3.0);
            Hitted = true;
            Hitmark.StartTimer(0.4);
            ExtraDamage = 0;
        }

    }

    else
    {
        ShieldPoints -= Damage->getHit();
        Hitmark.StartTimer(0.8);
        Hitted = true;
    }

    return ExtraDamage;
}

void Shield::RefreshElapsedTime(bool Release)
{
    Item::RefreshElapsedTime(Release);

    ReloadTimer.Count(ElapsedTime);
    Hitmark.Count(ElapsedTime);
    CooldownTimer.Count(ElapsedTime);

    if(CooldownTimer.Triggered())
    {
        MainSprite.setTexture(*Texture_Shield);
        Broken = false;
    }

    if(Hitmark.Triggered())
        Hitted = false;

    if(ReloadTimer.Triggered() && !Broken)
    {
        if(ShieldPoints < ShieldMax)
            ShieldPoints ++;
    }

}

sf::Vector2f Shield::getRelativePosition()
{
    return RelativePosition;
}

void Shield::setShieldTexture(sf::Texture *Texture)
{
    Texture_Shield = Texture;
    MainSprite.setTexture(*Texture_Shield);
}

void Shield::setShieldTexture(std::string PathShield, string PathBroken)
{
    if(PathBroken == string(""))
        PathBroken = PathShield;

    Texture_Broken->loadFromFile(PathBroken);
    Texture_Shield->loadFromFile(PathShield);

    MainSprite.setTexture(*Texture_Shield);
    MainSprite.setOrigin(MainSprite.getTexture()->getSize().x/2, MainSprite.getTexture()->getSize().y/2);

}

void Shield::draw(sf::RenderWindow *Window)
{
    MainSprite.setPosition(Parent->getPosition()+RelativePosition);

    if(Hitted)
        Window->draw(MainSprite);
}

