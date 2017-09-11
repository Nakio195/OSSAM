#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Spaceship;
class Weapon;
class Bullet;

template <class Type>
class Animation : public sf::Sprite
{
    public:
        enum AnimationMode{Event, Sprite};

    public:
        Animation(Type* pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode = Timer::OneShot);
        Animation(Type* pParent, float Period, unsigned int pAnimationMode, sf::Texture* Texture, unsigned int pTimerMode = Timer::OneShot);

        //Animation(Weapon* pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode = Timer::OneShot);
        //Animation(Weapon* pParent, float Period, unsigned int pAnimationMode, sf::Texture* Texture, unsigned int pTimerMode = Timer::OneShot);

        void setTimerMode(unsigned int pMode);
        unsigned int getTimerMode();

        sf::Vector2f getRelativePosition();
        void setRelativePosition(sf::Vector2f Position);
        void setFrame(unsigned int pFrame, sf::IntRect FrameSize);

        bool isRunning();

        void setPeriod(float pPeriod);
        float getPeriod();

        void Start(float Period = 0);
        void Stop();

        void Pause();
        void Release();

        void Play(float ElapsedTime);

        void setStartAction(void (Type::*Action)(void));
        void setRepeatAction(void (Type::*Action)(void));
        void setEndAction(void (Type::*Action)(void));

    private:
        Timer AnimationTimer;

        unsigned int Mode;
        sf::Vector2f RelativePosition;

        sf::Texture *SpriteTexture;
        sf::IntRect FrameRect;
        unsigned int Frame;
        unsigned int CurrentFrame;

        Type* Parent;

        void (Type::*StartAction)(void);
        void (Type::*RepeatAction)(void);
        void (Type::*EndAction)(void);
};

#endif // ANIMATION_H
