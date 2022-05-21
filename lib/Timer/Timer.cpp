#include "Arduino.h"
#include "Timer.h"

Timer::Timer(long unsigned startingTime){
    _startTime = millis();
    _stopTime = startingTime;
    _time = millis() - _startTime + _stopTime;
    _paused = false;
}
Timer::Timer(){
    Timer(0);
}

unsigned long Timer::update(){
    if (!_paused) {
        _time = millis() - _startTime + _stopTime;
      }
      return _time;
}

void Timer::reset(){
    _startTime= millis();
    _stopTime = 0;
}

void Timer::start(){
    if(_paused = true){
    _paused = false;
    _startTime = millis();
    }
}
void Timer::stop(){
    _stopTime = update();
    _paused = true;
}

bool Timer::running(){
    return !_paused;
}