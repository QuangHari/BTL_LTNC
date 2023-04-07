#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick = 0;
    paused_tick =0;
    is_pause = false;
    is_started = false;

}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start(){
    is_started = true;
    is_pause =false;
    start_tick = SDL_GetTicks();
}

void ImpTimer::stop(){
    is_started = false;
    is_pause =false;
}

void ImpTimer::paused(){
    if (is_started == true && is_pause ==false ){
        is_pause =true;
        paused_tick=SDL_GetTicks() - start_tick;

    }
}

void ImpTimer::unpaused(){
    if (is_pause ==true ){
        is_pause =false;
        start_tick=SDL_GetTicks() - paused_tick;
        paused_tick =0;
    }
}

int ImpTimer::getTick(){
    if (is_started == true){
        if (is_pause == true){
            return paused_tick;
        }else {
            return SDL_GetTicks() - start_tick;
        }

    }
    return 0;
}

bool ImpTimer::isStarted(){
    return is_started;
}

bool ImpTimer::isPaused(){
    return is_pause;
}
