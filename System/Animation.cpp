#include "Animation.h"

/**
 * @brief Animation::Animation
 * @param pParent
 * @param Period
 * @param pAnimationMode
 * @param Texture
 * @param pTimerMode
 */
template<typename Type>
Animation<Type>::Animation(Type* pParent, float Period, unsigned int pAnimationMode, sf::Texture *Texture, unsigned int pTimerMode)
{
    Parent = pParent;
    AnimationTimer.setMode(pTimerMode);
    AnimationTimer.setPeriod(Period);
    Mode = pAnimationMode;

    StartAction = NULL;
    EndAction = NULL;

    CurrentFrame = 0;

    RelativePosition = sf::Vector2f(0,0);

    if(Texture != NULL)
    {
        SpriteTexture = Texture;
        setTexture(*SpriteTexture);
    }
}

template<typename Type>
Animation<Type>::Animation(Type *pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode)
{
    Parent = pParent;
    AnimationTimer.setMode(pTimerMode);
    AnimationTimer.setPeriod(Period);
    Mode = pAnimationMode;

    StartAction = NULL;
    EndAction = NULL;

    CurrentFrame = 0;
}


template<typename Type>
Animation<Type>::Animation(Animation<Type>* copy)
{
    CurrentFrame = 0;
    Frame = copy->Frame;
    FrameRect = copy->FrameRect;
    SpriteTexture = copy->SpriteTexture;

    if(SpriteTexture != NULL)
        setTexture(*SpriteTexture);

    AnimationTimer = copy->AnimationTimer;
    AnimationTimer.StopTimer();
    Mode = copy->Mode;

    Parent = copy->Parent;
}


template<typename Type>
void Animation<Type>::setParent(Type* pParent)
{
    Parent = pParent;
}

template<typename Type>
sf::Vector2f Animation<Type>::getRelativePosition()
{
    return RelativePosition;
}

template<typename Type>
void Animation<Type>::setRelativePosition(sf::Vector2f Position)
{
    RelativePosition = Position;
}

template<typename Type>
void Animation<Type>::setFrame(unsigned int pFrame, sf::IntRect FrameSize)
{
    Frame = pFrame;
    FrameRect = FrameSize;

    RelativePosition = sf::Vector2f(FrameRect.width/-2, FrameRect.height/-2);
}


template<typename Type>
bool Animation<Type>::isRunning()
{
    return AnimationTimer.isRunning();
}

template<typename Type>
void Animation<Type>::setTimerMode(unsigned int pMode)
{
    AnimationTimer.setMode(pMode);
}

template<typename Type>
unsigned int Animation<Type>::getTimerMode()
{
    return AnimationTimer.getMode();
}

template<typename Type>
void Animation<Type>::setPeriod(float pPeriod)
{
    AnimationTimer.setPeriod(pPeriod);
}

template<typename Type>
float Animation<Type>::getPeriod()
{
    return AnimationTimer.getPeriod();
}

template<typename Type>
void Animation<Type>::Start(float Period)
{
    AnimationTimer.StartTimer(Period);

    if(StartAction != NULL && Parent != NULL)
        StartAction(Parent);

    if(Mode == Animation::Sprite)
    {
        setTimerMode(Timer::Continuous);

        if(CurrentFrame < Frame)
        {
            sf::IntRect Rect;
            Rect.height = FrameRect.height;
            Rect.width = FrameRect.width;
            Rect.top = 0;
            Rect.left = CurrentFrame*FrameRect.width;

            this->setTextureRect(Rect);
            CurrentFrame++;
        }

        else
            Stop();
    }

}

template<typename Type>
void Animation<Type>::Stop()
{
    AnimationTimer.StopTimer();

    if(Mode == Animation::Sprite)
        CurrentFrame = 0;

    if(EndAction != NULL && Parent != NULL)
        EndAction(Parent);
}

template<typename Type>
void Animation<Type>::Pause()
{
    AnimationTimer.PauseTimer();
}

template<typename Type>
void Animation<Type>::Release()
{
    AnimationTimer.ReleaseTimer();
}

template<typename Type>
void Animation<Type>::Play(float ElapsedTime)
{
    AnimationTimer.Count(ElapsedTime);

    if(AnimationTimer.Triggered())
    {
        if(AnimationTimer.getMode() == Timer::Continuous)
            Start();

        else
            Stop();
    }
}

template<typename Type>
void Animation<Type>::setStartAction(std::function<void(Type *)> Action)
{
    StartAction = Action;
}

template<typename Type>
void Animation<Type>::setRepeatAction(std::function<void(Type *)> Action)
{
    RepeatAction = Action;
}

template<typename Type>
void Animation<Type>::setEndAction(std::function<void(Type *)> Action)
{
    EndAction = Action;
}


template class Animation<Spaceship>;
template class Animation<Weapon>;
template class Animation<Bullet>;
