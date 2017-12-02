#include "AutoMovePath.h"

/******************************* AutoMovePath ************************************/

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
void AutoMovePath<T>::AddPoint(IA_PathNode<T> PathPoint)
{
    Path.push_back(PathPoint);
}

template<typename T>
IA_PathNode<T> AutoMovePath<T>::getCurrentNode()
{
    return Path.at(CurrentNode);
}

template<typename T>
void AutoMovePath<T>::Play(float ElapsedTime)
{
    if(Running)
    {
        IA_PathNode<T> *Node = &(Path.at(CurrentNode));

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
