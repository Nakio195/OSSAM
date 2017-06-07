#include "Animation.h"

Animation::Animation(Spaceship *pParent, float Period, unsigned int pAnimationMode, sf::Texture *Texture, unsigned int pTimerMode)
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

Animation::Animation(Spaceship *pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode)
{
    Parent = pParent;
    AnimationTimer.setMode(pTimerMode);
    AnimationTimer.setPeriod(Period);
    Mode = pAnimationMode;

    StartAction = NULL;
    EndAction = NULL;

    CurrentFrame = 0;
}

Animation::Animation(Weapon *pParent, float Period, unsigned int pAnimationMode, sf::Texture *Texture, unsigned int pTimerMode)
{
    Parent = NULL;
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

Animation::Animation(Weapon *pParent, float Period, unsigned int pAnimationMode, unsigned int pTimerMode)
{
    Parent = NULL;
    StartAction = NULL;
    EndAction = NULL;
    AnimationTimer.setMode(pTimerMode);
    AnimationTimer.setPeriod(Period);
    Mode = pAnimationMode;

    CurrentFrame = 0;
}


sf::Vector2f Animation::getRelativePosition()
{
    return RelativePosition;
}

void Animation::setRelativePosition(sf::Vector2f Position)
{
    RelativePosition = Position;
}

void Animation::setFrame(unsigned int pFrame, sf::IntRect FrameSize)
{
    Frame = pFrame;
    FrameRect = FrameSize;

    RelativePosition = sf::Vector2f(FrameRect.width/-2, FrameRect.height/-2);
}


bool Animation::isRunning()
{
    return AnimationTimer.isRunning();
}

void Animation::setTimerMode(unsigned int pMode)
{
    AnimationTimer.setMode(pMode);
}

unsigned int Animation::getTimerMode()
{
    return AnimationTimer.getMode();
}

void Animation::setPeriod(float pPeriod)
{
    AnimationTimer.setPeriod(pPeriod);
}

float Animation::getPeriod()
{
    return AnimationTimer.getPeriod();
}

void Animation::Start(float Period)
{
    AnimationTimer.StartTimer(Period);

    if(StartAction != NULL && Parent != NULL)
        (Parent->*StartAction)();

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

void Animation::Stop()
{
    AnimationTimer.StopTimer();

    if(Mode == Animation::Sprite)
        CurrentFrame = 0;

    if(EndAction != NULL && Parent != NULL)
        (Parent->*EndAction)();
}

void Animation::Pause()
{
    AnimationTimer.PauseTimer();
}

void Animation::Release()
{
    AnimationTimer.ReleaseTimer();
}

void Animation::Play(float ElapsedTime)
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

void Animation::setStartAction(void (Spaceship::*Action)(void))
{
    StartAction = Action;
}

void Animation::setRepeatAction(void (Spaceship::*Action)(void))
{
    RepeatAction = Action;
}

void Animation::setEndAction(void (Spaceship::*Action)(void))
{
    EndAction = Action;
}
