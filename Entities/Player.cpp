#include "Player.h"

/**
 * @brief Window_Height
 */

extern int Window_Height;
extern int Window_Width;

extern list<Spaceship*> Spaceships;

Player::Player(string pName, string PathTotexture, unsigned int pLife, unsigned int pShield, unsigned int pAttack, unsigned int pDefense, unsigned int pGenerator, float pSpeed, unsigned int pXP, unsigned int pAmmo) : Spaceship(pName, PathTotexture, pLife, pShield, pAttack, pDefense, pGenerator, pSpeed, pXP, pAmmo)
{


    DyingAnim->setFrame(4, sf::IntRect(0, 0, 177, 153));

    UI->setBackground("Ressources/ATH/ath2.png");
    UI->setShieldBar(sf::Color(78, 206, 182), sf::Vector2f(217, 21), sf::Vector2f(41, 14));
    UI->setHealthBar(sf::Color(102, 204, 51), sf::Vector2f(217, 21), sf::Vector2f(41, 51));
    UI->Fix(sf::Vector2f(10, 10));

    cout << endl;

    cout << Name << endl;
    cout << "\t" << "Life : " << Stats.Life << endl;
    cout << "\t" << "XP : " << Xp << endl;
    cout << "\t" << "Attack : " << Stats.Attack << endl;
    cout << "\t" << "Defense : " << Stats.Defense << endl;
    cout << "\t" << "Shield : " << Stats.Shield << endl;
    cout << "\t" << "Energy Generator : " << Stats.Generator << endl;
    cout << "\t" << "Movement Speed : " << Speed << endl;
    cout << "\t" << "Skin : " << PathTotexture << endl;
    cout << endl;

}


void Player::AimNext()
{
    if(Target == NULL)
    {
        for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
        {
            if(*it != NULL && *it != this)
            {
                Spaceship *CurrentSpaceship = *it;
                Target = CurrentSpaceship;
                CurrentSpaceship->setAimed(true);
                break;
            }
        }
    }

    else
    {
        for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
        {
            if(*it != NULL && *it == Target)
            {
                Target->setAimed(false);

                ++it;

                if(it == Spaceships.end())
                    it = Spaceships.begin();


                if(*it == this)
                {
                    ++it;
                }

                Spaceship *CurrentSpaceship = *it;
                Target = CurrentSpaceship;
                CurrentSpaceship->setAimed(true);
                break;
            }
        }
    }
}

void Player::AimPrevious()
{
    if(Target == NULL)
    {
        for (list<Spaceship*>::iterator it = Spaceships.begin(); it != Spaceships.end(); ++it)
        {
            if(*it != NULL && *it != this)
            {
                Spaceship *CurrentSpaceship = *it;
                Target = CurrentSpaceship;
                CurrentSpaceship->setAimed(true);
                break;
            }
        }
    }

    else
    {
        for (list<Spaceship*>::iterator it = Spaceships.end(); it != Spaceships.begin(); --it)
        {
            if(*it != NULL && *it == Target)
            {
                Target->setAimed(false);

                if(it == Spaceships.begin())
                    it = Spaceships.end();

                else
                    --it;

                if(*it == this)
                {
                    --it;
                    if(*it == NULL)
                        it = --(Spaceships.end());
                }

                Spaceship *CurrentSpaceship = *it;
                Target = CurrentSpaceship;
                CurrentSpaceship->setAimed(true);
                break;
            }
        }
    }
}
