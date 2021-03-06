#include "AnimationKey.h"

AnimationKey::AnimationKey(unsigned int pMode, float pDuration)
{
    Mode = pMode;
    Status = Stopped;
    Duration = pDuration;
    Completion = 0.0;
    Timer = 0;
}

unsigned int AnimationKey::getStatus()
{
    return Status;
}

float AnimationKey::getCompletion()
{
    return Timer / Duration;
}

void AnimationKey::Start()
{
    Status = Running;
    Timer = 0;
}

void AnimationKey::Play(float ElapsedTime)
{
    if(Status == Running)
    {
        Timer += ElapsedTime;

        if(Timer >= Duration)
        {
            Timer = 0;
            Status = Finished;
            Completion = 1.0;
        }

        else
        {
            Completion = Timer / Duration;
            Update();
        }
    }
}

void AnimationKey::Stop()
{
    Timer = 0;
    Status = Stopped;
    Completion = 0.0;
}

