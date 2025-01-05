#include <iostream>
#include "SDL2/SDL.h"
#include <functional>

class TimerHandler {
public:
    int secondsLeft;
    std::function<void()> function; // Replace void (*)() with std::function<void()>
    TimerHandler(int initialSeconds) : secondsLeft(initialSeconds) {}
    SDL_TimerID timerID; // Store the timer ID
    TimerHandler(){};
    static Uint32 TimerCallback(Uint32 interval, void* param);
    void startTimer();
};
