#include "Missile.h"
#include "../../../Entities/Spaceship.h"

/**
 * @brief Missile::Missile
 * @param Parent
 */


extern list<Bullet*> FiredBullets;
extern list<Spaceship*> Spaceships;

Missile::Missile(Spaceship *Parent, Spaceship *pTarget) : Bullet(Parent)
{
    Type = Bullet::Missile;
    DamageRadius = 100;
    Speed = 500;
}


Missile::Missile(Missile *copy) : Bullet(copy)
{
    Type = Bullet::Missile;
    DamageRadius = 100;
    Speed = 500;
}

Missile::~Missile()
{

}


float Missile::getDamageRadius()
{
    return DamageRadius;
}

void Missile::setDamageRadius(float Radius)
{
    DamageRadius = Radius;
}

void Missile::setTarget(Spaceship* pTarget)
{
    Target = pTarget;
}

void Missile::Move()
{
    if(Target != NULL)
    {
        Direction = getLinearDirectionTo(Target);
        if(Direction.x < 0.1)
            Target = NULL;

        move(sf::Vector2f(Speed*ElapsedTime*Direction.x, Speed*ElapsedTime*Direction.y));
        setRotation(atan2(Direction.y, Direction.x)/3.14159*180);
    }

    else
        Bullet::Move();
}

void Missile::draw(sf::RenderWindow *Window)
{
    sf::CircleShape Zone(DamageRadius);
    Zone.setPosition(getPosition().x-DamageRadius/2, getPosition().y-DamageRadius/2);

    if(BlastAnim->isRunning())
    {
        //Window->draw(Zone);
        BlastAnim->setPosition(getPosition().x-30, getPosition().y-40);
        Window->draw(*BlastAnim);
    }

    else
    {
        Window->draw(*this);
    }
}

void Missile::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    sf::CircleShape Zone(DamageRadius);
    Zone.setPosition(getPosition().x-DamageRadius/2, getPosition().y-DamageRadius/2);

    if(!Exploded)
    {
        for (list<Spaceship*>::iterator jt = Spaceships.begin(); jt != Spaceships.end(); ++jt)
        {
            Spaceship* CurrentSpaceship = *jt;

            if(Zone.getGlobalBounds().intersects(CurrentSpaceship->getGlobalBounds()))
            {
                if(getParent()->getFaction() != CurrentSpaceship->getFaction())
                {
                    CurrentSpaceship->TakeDamage(this);

                    if(CurrentSpaceship->isDead())
                        Shooter->setAimedTarget(NULL);
                }
            }
        }

        Exploded = true;
        BlastAnim->Start();
    }

    else if(Exploded && !BlastAnim->isRunning())
    {
        Remove = true;
    }
}
