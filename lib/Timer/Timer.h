

#ifndef Timer_h
#define Timer_h
#include "Arduino.h"

class Timer{
    private:
    unsigned long _startTime, _stopTime, _time;
    bool _paused;
    public:
    Timer();
    Timer(long unsigned startingTime);
    void reset();
    unsigned long update();
    void start();
    void stop();
    bool running();
};

#endif