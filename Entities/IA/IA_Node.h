#ifndef IA_NODE_H
#define IA_NODE_H

class Spaceship;

#include <SFML/Graphics.hpp>
#include <functional>

template <typename T>
class IA_PathNode
{
    public:
        enum AutoMove{Linear};

    public:
        IA_PathNode(T *Parent, sf::Vector2f pDestination, unsigned int pMoveType);
        ~IA_PathNode();

        sf::Vector2f Destination;

        bool isStarted();
        void setEndOfTravel();
        bool isEnded();
        unsigned int MoveType;

        void setTravelAction(std::function<void(T *, IA_PathNode<T>*)> Action);

        void StartTravel();
        void Stop();

    protected:
        bool Started;
        bool RunToNextNode;

        T* Parent;
        std::function<void(T *, IA_PathNode<T>*)> TravelAction;

};


template <typename T>
class IA_ShootNode
{
    public:
        enum ShootingMode{Single, Continuous};
    public:
        IA_ShootNode(T *pParent, unsigned int Choice, unsigned int Number);
        ~IA_ShootNode();

        void Play(float ElapsedTime);
        void Stop();

        void setShootAction(std::function<bool(T*, IA_ShootNode<T>*)> Action);
        void setShootTarget(Spaceship* pTarget);
        bool RunShootAction();
        bool isEnded();

    public:
        unsigned int Mode;

        //Shoot action
        unsigned int WeaponChoice;

        unsigned int ShootNumber;
        float ShootingPeriod;


    protected:
        T* Parent;
        bool RunToNextNode;
        std::function<bool(T *, IA_ShootNode<T>*)> ShootAction;

        Spaceship *Target;

        unsigned int CurrentShoot;
        float ShootTimer;
};



template <typename T>
class IA_Node
{
    public:
        enum Mode{Single = 1, Repeat = 2};

    public:
        IA_Node(T *Parent);
        ~IA_Node();

        bool RunToNextNode();
        void Play(float ElapsedTime);
        void Stop();

        IA_ShootNode<T> *ShootNode;
        IA_PathNode<T> *PathNode;

    public:
        float Delay;
};
#endif // IA_NODE_H
