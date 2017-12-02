#include "Timer.h"

/**
 * @brief Timer::Timer
 * @param pPeriod
 * @param pMode
 */

Timer::Timer(float pPeriod, unsigned int pMode)
{
    Period = pPeriod;
    Mode = pMode;

    Counter = 0;

    Running = false;
    Trigger = false;
}


bool Timer::isRunning()
{
    if(Counter <= Period && Running == false)
        return false;
    else
        return true;
}

float Timer::getPeriod()
{
    return Period;
}

void Timer::setPeriod(float pPeriod)
{
    Period = pPeriod;
    Counter = 0;
}

float Timer::getCounter()
{
    return Counter;
}

void Timer::Count(float pElapsedTime)
{
    if(Running)
    {
        Counter += pElapsedTime;

        if(Counter >= Period)
            Trigger = 1;
    }
}

bool Timer::Triggered() // Read timer Trigger and reset it if enabled
{
    bool TriggerValue;

    TriggerValue = Trigger;

    if(Trigger == true)
    {
        Trigger = false;

        if(Mode == OneShot)
        {
            Running = false;
            Counter = 0;
        }

        else if(Mode == Continuous)
        {
            Running = true;
            Counter = 0;
        }
    }

    return TriggerValue;
}

void Timer::StartTimer(float pPeriod) // Start Timer from beginning (see ReleaseTimer() and PauseTimer() )
{
    if(pPeriod != 0)
        Period = pPeriod;

    Counter = 0;
    Running = true;
}

void Timer::StopTimer() // Stop timer and reset it
{
    Running = 0;
    Counter = 0;
}


void Timer::PauseTimer()
{
    Running = false;
}

void Timer::ReleaseTimer()
{
    Running = true;
}

unsigned int Timer::getMode()
{
    return Mode;
}

void Timer::setMode(unsigned int pMode)
{
    if(pMode == Continuous || pMode == OneShot)
        Mode = pMode;
}
