#ifndef AUTOMOVEPATH_H
#define AUTOMOVEPATH_H

#include <SFML/Graphics.hpp>
#include <functional>

template <typename T>
class PathNode
{
    public:
        enum AutoMove{Linear};

    public:
        PathNode(T *Parent, sf::Vector2f pDestination, unsigned int pMoveType);
        sf::Vector2f Origin;
        sf::Vector2f Destination;
        float Delay;
        bool RunToNextNode;
        unsigned int MoveType;

        void setOriginAction(std::function<void(T*)> Action);
        void setTravelAction(std::function<void(T *, PathNode<T>*)> Action);
        void setDestinationAction(std::function<void(T*)> Action);

        void RunOriginAction();
        void StartTravel();
        void RunDestinationAction();

    protected:
        T* Parent;
        std::function<void(T*)> OriginAction;
        std::function<void(T *, PathNode<T>*)> TravelAction;
        std::function<void(T*)> DestinationAction;

};

template <typename T>
class AutoMovePath
{
    public:
        enum PathMode{Single, Repeat};

    public:
        AutoMovePath();
        void AddPoint(PathNode<T> PathPoint);
        PathNode<T> getCurrentNode();
        void Clear();
        void Play(float ElapsedTime);
        void Start();
        void Stop();

    public:
        unsigned int Mode;
        bool Running;

    protected:
        bool OnTravel;
        float TempoDelay;
        unsigned int CurrentNode;
        std::vector<PathNode<T>> Path;
};

#endif // AUTOMOVEPATH_H
