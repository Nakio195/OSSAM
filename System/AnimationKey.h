#ifndef ANIMATIONKEY
#define ANIMATIONKEY

#include <SFML/Graphics.hpp>

class AnimationKey
{
    public:
        enum KeyType{Rotation, Translation, Scale};
        enum RotationDir{Clockwise, CounterClockwise};
        enum KeyStatus{Stopped, Running, Finished};

    public:
        AnimationKey(unsigned int pMode, float pDuration);

        unsigned int getStatus();
        float getCompletion();

        void Start();
        void Play(float ElapsedTime);
        virtual void Update() = 0;
        void Stop();

    protected:
        float Duration;
        unsigned int Mode;
        unsigned int Status;

        float Completion;
        float Timer;
};

#endif // ANIMATIONKEY
