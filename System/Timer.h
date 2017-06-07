#ifndef TIMER_H
#define TIMER_H


class Timer
{
    public:
        enum TimerMode{OneShot = 0, Continuous};

    public:
        Timer(float pPeriod = 1, unsigned int pMode = 0);

        bool isRunning();

        float getPeriod();
        void setPeriod(float pPeriod);

        float getCounter();
        void Count(float pElapsedTime);

        bool Triggered();

        void StartTimer(float pPeriod = 0);  // Start Timer
        void PauseTimer();
        void ReleaseTimer();
        void StopTimer();                   // Stop

        unsigned int getMode();
        void setMode(unsigned int pMode);


    private:
        unsigned int Mode;  // Timer mode according to enum TimerMode
        bool Running;

        float Period;       //Time till event trigger in s
        float Counter;      //Elapsed time since start in s
        bool Trigger;       //Event triggered
};

#endif // TIMER_H
