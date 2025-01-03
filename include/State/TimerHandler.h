#include <iostream>
#include "SDL2/SDL.h"

class TimerHandler {
public:
    int secondsLeft;

    TimerHandler(int initialSeconds) : secondsLeft(initialSeconds) {}

    static Uint32 TimerCallback(Uint32 interval, void* param) {
        // Cast param to TimerHandler pointer
        TimerHandler* handler = static_cast<TimerHandler*>(param);

        if (handler->secondsLeft > 0) {
            handler->secondsLeft--;
        } else {
            return 0; // Stop the timer
        }

        return interval; // Continue the timer
    }

    void startTimer(Uint32 interval) {
        SDL_AddTimer(interval, TimerCallback, this);
    }
};
