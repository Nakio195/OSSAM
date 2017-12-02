#include "IA_Sequencer.h"
#include <iostream>

template<typename T>
IA_Sequencer<T>::IA_Sequencer()
{
    Mode = Repeat;
    Running = false;
    CurrentNode = 0;
    TempoDelay = 0.0;
    Sequence.clear();
}

template<typename T>
IA_Sequencer<T>::~IA_Sequencer()
{

}

template<typename T>
void IA_Sequencer<T>::AddNode(IA_Node<T> NewNode)
{
    Sequence.push_back(NewNode);
}

template<typename T>
IA_Node<T> IA_Sequencer<T>::getCurrentNode()
{
    return Sequence.at(CurrentNode);
}


template<typename T>
void IA_Sequencer<T>::Play(float ElapsedTime)
{
    if(Running)
    {
        IA_Node<T> *Node = &(Sequence.at(CurrentNode));

        if(TempoDelay < Node->Delay)
        {
            TempoDelay += ElapsedTime;
        }

        else
        {
            Node->Play(ElapsedTime);

            if(Node->RunToNextNode())
            {
                std::cout << "[+] Going to next Node" << std::endl;
                Node->Stop();
                CurrentNode++;
                TempoDelay = 0.0;

                if(CurrentNode >= Sequence.size())
                {
                    if(Mode == Repeat)
                        CurrentNode = 0;

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
void IA_Sequencer<T>::Start()
{
    CurrentNode = 0;
    Running = true;
    TempoDelay = 0.0;
}


template<typename T>
void IA_Sequencer<T>::Stop()
{
    Running = false;
    CurrentNode = 0;
    TempoDelay = 0;
}


template<typename T>
void IA_Sequencer<T>::Clear()
{
    Running = false;
    Sequence.clear();
    CurrentNode = 0;
    TempoDelay = 0;
}

class Entity;
class Spaceship;
class Ennemy;

template class IA_Sequencer<Entity>;
template class IA_Sequencer<Ennemy>;
template class IA_Sequencer<Spaceship>;

