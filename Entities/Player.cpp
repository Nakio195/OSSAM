#include "Player.h"

/**
 * @brief Window_Height
 */

extern int Window_Height;
extern int Window_Width;

Player::Player(string pName, string PathTotexture, unsigned int pLife, unsigned int pShield, unsigned int pAttack, unsigned int pDefense, unsigned int pGenerator, float pSpeed, unsigned int pXP, unsigned int pAmmo) : Spaceship(pName, PathTotexture, pLife, pShield, pAttack, pDefense, pGenerator, pSpeed, pXP, pAmmo)
{

    MainWeapon = new Weapon(this, "Laser Simple", "Ressources/Sprite/Player/canon.png", 0.3);
    MainWeapon->setShootingDirection(sf::Vector2f(1, 0));
    MainWeapon->setRelativePosition(sf::Vector2f(-27, -30));
    MainWeapon->setShootPosition(sf::Vector2f(80, -6));
    MainWeapon->setBlastAnim("Ressources/Sprite/blast-CP.png", 2, sf::IntRect(0, 0, 40, 24));
    MainWeapon->setIcon("Ressources/System/Icon/RG_1.png");

    Laser MainWeaponBullet(this);
    MainWeaponBullet.setHit(10);
    MainWeaponBullet.setBulletTexture("Ressources/Sprite/LaserBleu.png");
    MainWeapon->setBullet(MainWeaponBullet);


    SecondaryWeapon = new Weapon(this, "Lance Missile", "", 1);
    SecondaryWeapon->setShootingDirection(sf::Vector2f(1, 0));
    SecondaryWeapon->setRelativePosition(sf::Vector2f(-27, -30));
    SecondaryWeapon->setShootPosition(sf::Vector2f(80, -6));
    SecondaryWeapon->setBlastAnim("Ressources/Sprite/blast-LM.png", 3, sf::IntRect(0, 0, 50, 31));
    SecondaryWeapon->setIcon("Ressources/System/Icon/LM_1.png");

    Missile SecondaryWeaponBullet(this);
    SecondaryWeaponBullet.setHit(40);
    SecondaryWeaponBullet.setBulletTexture("Ressources/Sprite/missile.png");
    SecondaryWeapon->setBullet(SecondaryWeaponBullet);

    DyingAnim->setFrame(4, sf::IntRect(0, 0, 177, 153));

    UI->setBackground("Ressources/ATH/ath2.png");
    UI->setShieldBar(sf::Color(78, 206, 182), sf::Vector2f(217, 21), sf::Vector2f(41, 14));
    UI->setHealthBar(sf::Color(102, 204, 51), sf::Vector2f(217, 21), sf::Vector2f(41, 51));
    UI->Fix(sf::Vector2f(10, 10));

    mInventory = new Inventory();
    mInventory->addItem(MainWeapon);
    mInventory->addItem(SecondaryWeapon);
    mInventory->addItem(MainShield);

    /*
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
    */
}


Inventory* Player::getInventory()
{
    return mInventory;
}
