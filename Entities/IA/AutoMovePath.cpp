#include "AutoMovePath.h"


template<typename T>
PathNode<T>::PathNode(T *pParent, sf::Vector2f pDestination, unsigned int pMoveType)
{
    Parent = pParent;
    Origin = sf::Vector2f(0, 0);
    Destination = pDestination;
    MoveType = pMoveType;
    Delay = 3;

    RunToNextNode = false;
    OriginAction = NULL;
    TravelAction = NULL;
    DestinationAction = NULL;
}

template<typename T>
void PathNode<T>::setOriginAction(std::function<void(T *)> Action)
{
    OriginAction = Action;
}

template<typename T>
void PathNode<T>::setTravelAction(std::function<void(T *, PathNode<T>*)> Action)
{
    TravelAction = Action;
}

template<typename T>
void PathNode<T>::setDestinationAction(std::function<void(T *)> Action)
{
    DestinationAction = Action;
}

template<typename T>
void PathNode<T>::RunOriginAction()
{
    if(OriginAction != NULL && Parent != NULL)
        OriginAction(Parent);
}

template<typename T>
void PathNode<T>::StartTravel()
{
    if(TravelAction != NULL && Parent != NULL)
        TravelAction(Parent, this);
}

template<typename T>
void PathNode<T>::RunDestinationAction()
{
    if(DestinationAction != NULL && Parent != NULL)
        DestinationAction(Parent);
}


template<typename T>
AutoMovePath<T>::AutoMovePath()
{
    Mode = Single;
    Running = false;
    CurrentNode = 0;
    OnTravel = false;
    Path.clear();
}


template<typename T>
void AutoMovePath<T>::AddPoint(PathNode<T> PathPoint)
{
    Path.push_back(PathPoint);
}

template<typename T>
PathNode<T> AutoMovePath<T>::getCurrentNode()
{
    return Path.at(CurrentNode);
}

template<typename T>
void AutoMovePath<T>::Play(float ElapsedTime)
{
    if(Running)
    {
        PathNode<T> *Node = &(Path.at(CurrentNode));

        if(Node->RunToNextNode == false && OnTravel == false)
        {
            Node->RunOriginAction();
            Node->StartTravel();
            OnTravel = true;
        }

        else if(Node->RunToNextNode == true)
        {
            TempoDelay += ElapsedTime;

            if(TempoDelay > Node->Delay)
            {
                TempoDelay = 0;
                Node->RunDestinationAction();
                Node->RunToNextNode = false;
                OnTravel = false;

                CurrentNode++;

                if(CurrentNode >= Path.size())
                {
                    if(Mode == Repeat)
                    {
                        CurrentNode = 0;
                    }

                    else if(Mode == Single)
                    {
                        CurrentNode = 0;
                        Running = false;
                    }
                }
            }
        }
    }
}

template<typename T>
void AutoMovePath<T>::Start()
{
    CurrentNode = 0;
    Running = true;
}


template<typename T>
void AutoMovePath<T>::Stop()
{
    Running = false;
    CurrentNode = 0;
}


template<typename T>
void AutoMovePath<T>::Clear()
{
    Running = false;
    OnTravel = false;
    Path.clear();
    CurrentNode = 0;
}

class Entity;
class Spaceship;

template class PathNode<Entity>;
template class PathNode<Spaceship>;
template class AutoMovePath<Entity>;
template class AutoMovePath<Spaceship>;
