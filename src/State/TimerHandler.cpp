#include "State/TimerHandler.h"

Uint32 TimerHandler::TimerCallback(Uint32 interval, void* param) {
    TimerHandler* handler = static_cast<TimerHandler*>(param);

    if (handler->secondsLeft > 0) {
        handler->secondsLeft--;
    } else {
        if (handler->function) {
            handler->function();
            if (handler->timerID) {
                SDL_RemoveTimer(handler->timerID);
                handler->timerID = 0;
            }
        }

        return 0;
    }

    return interval;
}

void TimerHandler::startTimer() {
    SDL_AddTimer(1000, TimerCallback, this);
}