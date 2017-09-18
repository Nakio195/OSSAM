#include "Ennemy.h"

/**
 * @brief Ennemy::Ennemy
 * @param PathTotexture
 * @param pName
 * @param pLife
 * @param pShield
 * @param pAttack
 * @param pDefense
 * @param pGenerator
 * @param pSpeed
 * @param pXP
 * @param pAmmo
 */


extern int Window_Height;
extern int Window_Width;

Ennemy::Ennemy(string PathTotexture, string pName, unsigned int pLife, unsigned int pShield, unsigned int pAttack, unsigned int pDefense, unsigned int pGenerator, float pSpeed, unsigned int pXP, unsigned int pAmmo) : Spaceship(PathTotexture, pName)
{
    cout << endl;
    cout << pName << endl;
    cout << "\t" << "Life : " << pLife << endl;
    cout << "\t" << "XP : " << pXP << endl;
    cout << "\t" << "Attack : " << pAttack << endl;
    cout << "\t" << "Defense : " << pDefense << endl;
    cout << "\t" << "Shield : " << pShield << endl;
    cout << "\t" << "Energy Generator : " << pGenerator << endl;
    cout << "\t" << "Movement Speed : " << pSpeed << endl;
    cout << "\t" << "Ammunitions size : " << pAmmo << endl;
    cout << "\t" << "Skin : " << PathTotexture << endl;
    cout << endl;

    PathNode<Spaceship> First = PathNode<Spaceship>(this, sf::Vector2f(Window_Width*0.9, Window_Height*0.1), PathNode<Spaceship>::Linear);
    First.setTravelAction(&Spaceship::MoveLinearTo);
    First.Delay = 1;
    PathNode<Spaceship> Second = PathNode<Spaceship>(this, sf::Vector2f(Window_Width*0.6, Window_Height*0.25), PathNode<Spaceship>::Linear);
    Second.setTravelAction(&Spaceship::MoveLinearTo);
    Second.Delay = 0.5;
    PathNode<Spaceship> Third = PathNode<Spaceship>(this, sf::Vector2f(Window_Width*0.6, Window_Height*0.75), PathNode<Spaceship>::Linear);
    Third.setTravelAction(&Spaceship::MoveLinearTo);
    Third.Delay = 1;
    PathNode<Spaceship> Fourth = PathNode<Spaceship>(this, sf::Vector2f(Window_Width*0.9, Window_Height*0.9), PathNode<Spaceship>::Linear);
    Fourth.setTravelAction(&Spaceship::MoveLinearTo);
    Fourth.Delay = 0.5;

    MovePath.AddPoint(First);
    MovePath.AddPoint(Second);
    MovePath.AddPoint(Third);
    MovePath.AddPoint(Fourth);

    MovePath.Mode = AutoMovePath<Spaceship>::Repeat;
    MovePath.Start();

    UI->setShieldBar(sf::Color(78, 206, 182), sf::Vector2f(50, 5), sf::Vector2f(-50, -45));
    UI->setHealthBar(sf::Color(102, 204, 51), sf::Vector2f(50, 5), sf::Vector2f(-50, -40));
    UI->setPosition(sf::Vector2f(10, 10));

    MainWeapon = new Weapon(this, "Laser Rouge", "", 0.1);
    MainWeapon->setRelativePosition(sf::Vector2f(0, 12));
    MainWeapon->setShootPosition(sf::Vector2f(-27-125, -6));
    MainWeapon->setBlastAnim("Ressources/Sprite/blast-CP.png", 2, sf::IntRect(0, 0, 40, 24));

    Laser MainWeaponBullet(this);
    MainWeaponBullet.setHit(100);
    MainWeaponBullet.setBulletTexture("Ressources/Sprite/LaserRouge.png");
    MainWeaponBullet.setBlastTexture("Ressources/Sprite/boom2.png");
    MainWeapon->setBullet(MainWeaponBullet);

    SecondaryWeapon = new Weapon(this);

    DyingAnim->setFrame(3, sf::IntRect(0, 0, 130, 140));
}
