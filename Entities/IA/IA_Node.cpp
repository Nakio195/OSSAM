#include "IA_Node.h"
#include <iostream>

template<typename T>
IA_Node<T>::IA_Node(T *Parent)
{
    Delay = 0;
    ShootNode = new IA_ShootNode<T>(Parent, 0, 0);
    PathNode = new IA_PathNode<T>(Parent, sf::Vector2f(), 0);
}

template<typename T>
IA_Node<T>::~IA_Node()
{

}


template<typename T>
bool IA_Node<T>::RunToNextNode()
{
    if(PathNode->isEnded() && ShootNode->isEnded())
        return true;
    else
        return false;
}

template<typename T>
void IA_Node<T>::Play(float ElapsedTime)
{

    if(!PathNode->isStarted())
    {
        PathNode->StartTravel();
    }

    ShootNode->Play(ElapsedTime);
}


template<typename T>
void IA_Node<T>::Stop()
{
    ShootNode->Stop();
    PathNode->Stop();
}



/******************************* Path Node ************************************/


template<typename T>
IA_PathNode<T>::IA_PathNode(T *pParent, sf::Vector2f pDestination, unsigned int pMoveType)
{
    Parent = pParent;
    Destination = pDestination;
    MoveType = pMoveType;
    Started = false;

    RunToNextNode = false;
    TravelAction = NULL;
}

template<typename T>
IA_PathNode<T>::~IA_PathNode()
{

}

template<typename T>
void IA_PathNode<T>::setTravelAction(std::function<void(T *, IA_PathNode<T>*)> Action)
{
    TravelAction = Action;
}


template<typename T>
void IA_PathNode<T>::StartTravel()
{
    Started = true;
    if(TravelAction != NULL && Parent != NULL)
        TravelAction(Parent, this);
}

template<typename T>
void IA_PathNode<T>::Stop()
{
    Started = false;
    RunToNextNode = false;
}

template<typename T>
bool IA_PathNode<T>::isStarted()
{
    return Started;
}

template<typename T>
void IA_PathNode<T>::setEndOfTravel()
{
    RunToNextNode = true;
}


template<typename T>
bool IA_PathNode<T>::isEnded()
{
    return RunToNextNode;
}

/******************************* Shoot Node **************************************/



template<typename T>
IA_ShootNode<T>::IA_ShootNode(T *pParent, unsigned int Choice, unsigned int Number)
{
    Parent = pParent;
    WeaponChoice = Choice;
    ShootNumber = Number;
    ShootingPeriod = 1.0;
    CurrentShoot = 0;
    ShootTimer = 0.0;

    Mode = IA_Node<T>::Single;
    Target = NULL;

    ShootAction = NULL;

    RunToNextNode = false;
}

template<typename T>
IA_ShootNode<T>::~IA_ShootNode()
{

}

template<typename T>
void IA_ShootNode<T>::setShootAction(std::function<bool (T *, IA_ShootNode<T> *)> Action)
{
    if(Action != NULL)
        ShootAction = Action;
}

template<typename T>
void IA_ShootNode<T>::setShootTarget(Spaceship *pTarget)
{
    if(pTarget != NULL)
    {
        Target = pTarget;
    }
}



template<typename T>
void IA_ShootNode<T>::Play(float ElapsedTime)
{

    ShootTimer += ElapsedTime;

    if(Mode == Continuous)
    {
        RunToNextNode = true;

        if(ShootTimer > ShootingPeriod)
        {
            ShootTimer = 0;
            RunShootAction();
        }
    }

    else if(Mode == Single)
    {
        if(CurrentShoot < ShootNumber)
        {
            if(ShootTimer > ShootingPeriod)
            {
                std::cout << "Shoot " << CurrentShoot+1 << "/" << ShootNumber << std::endl;
                ShootTimer = 0;
                if(RunShootAction())
                    CurrentShoot++;
            }
        }

        else
        {
            RunToNextNode = true;
        }
    }
}


template<typename T>
void IA_ShootNode<T>::Stop()
{
    CurrentShoot = 0;
    ShootTimer = 0;
    RunToNextNode = false;
}


template<typename T>
bool IA_ShootNode<T>::RunShootAction()
{
    if(ShootAction != NULL && Parent != NULL)
    {
        return ShootAction(Parent, this);
    }

    return false;

}


template<typename T>
bool IA_ShootNode<T>::isEnded()
{
    return RunToNextNode;
}

class Entity;
class Spaceship;
class Ennemy;

template class IA_Node<Entity>;
template class IA_Node<Spaceship>;
template class IA_Node<Ennemy>;

template class IA_PathNode<Entity>;
template class IA_PathNode<Spaceship>;
template class IA_PathNode<Ennemy>;

template class IA_ShootNode<Entity>;
template class IA_ShootNode<Spaceship>;
template class IA_ShootNode<Ennemy>;
