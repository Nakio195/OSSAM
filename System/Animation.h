#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>

#include "AnimationKey/RotationKey.h"
#include "AnimationKey/TranslationKey.h"
#include "AnimationKey/ScaleKey.h"

using namespace std;

class Spaceship;
class Weapon;
class Bullet;

template <class Type>
class Animation : public sf::Sprite
{
    public:
        enum AnimationMode{Event, Sprite, KeySequence};
        enum AnimationSequence{Running, Finished};

    public:
        Animation(Type* pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode = Timer::OneShot);
        Animation(Type* pParent, float Period, unsigned int pAnimationMode, sf::Texture* Texture, unsigned int pTimerMode = Timer::OneShot);
        Animation(Animation<Type>* copy);

        void setParent(Type* pParent);
        void loadTexture(std::string Path);
        void setTimerMode(unsigned int pMode);
        unsigned int getTimerMode();

        sf::Vector2f getRelativePosition();
        void setRelativePosition(sf::Vector2f Position);

        // Frame Mode
        void setFrame(unsigned int pFrame, sf::IntRect FrameSize);
        sf::IntRect getFrameRect();

        // Key Mode
        void addKey(RotationKey Key);
        void addKey(TranslationKey Key);
        void addKey(ScaleKey Key);

        bool isRunning();

        void setPeriod(float pPeriod);
        float getPeriod();

        void Start(float Period = 0);
        void Stop();

        void Pause();
        void Release();

        void Play(float ElapsedTime);

        void setStartAction(std::function<void(Type*)> Action);
        void setRepeatAction(std::function<void(Type*)> Action);
        void setEndAction(std::function<void(Type*)> Action);

    private:
        // Core
        sf::Texture *SpriteTexture;
        Timer AnimationTimer;

        unsigned int Mode;
        sf::Vector2f RelativePosition;

        //Frame Mode
        sf::IntRect FrameRect;
        unsigned int Frame;
        unsigned int CurrentFrame;

        // Key Mode
        std::vector<RotationKey> RotationKeys;
        std::vector<TranslationKey> TranslationKeys;
        std::vector<ScaleKey> ScaleKeys;

        unsigned int CurrentRotationKey;
        unsigned int CurrentTranslationKey;
        unsigned int CurrentScaleKey;

        bool RotationSequence;
        bool TranslationSequence;
        bool ScaleSequence;


        // Callbacks functions
        Type* Parent;

        std::function<void(Type*)> StartAction;
        std::function<void(Type*)> RepeatAction;
        std::function<void(Type*)> EndAction;
};

#endif // ANIMATION_H
