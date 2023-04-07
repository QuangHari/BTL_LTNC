#ifndef IMPTIMER_H
#define IMPTIMER_H

#include "CommonFunc.h"

class ImpTimer
{
    public:
        ImpTimer();
        ~ImpTimer();

        void start();
        void stop();
        void paused();
        void unpaused();

        int getTick();
        bool isStarted();
        bool isPaused();

    private:
        int start_tick;
        int paused_tick;

        bool is_pause;
        bool is_started;

};

#endif // IMPTIMER_H
