#ifndef AUTOMOVEPATH_H
#define AUTOMOVEPATH_H

#include <SFML/Graphics.hpp>
#include <functional>

class Spaceship;
class IA_PathNode;

template <typename T>
class AutoMovePath
{
    public:
        enum PathMode{Single, Repeat};

    public:
        AutoMovePath();
        void AddPoint(IA_PathNode<T> PathPoint);
        IA_PathNode<T> getCurrentNode();
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
        std::vector<IA_PathNode<T>> Path;
};

#endif // AUTOMOVEPATH_H
