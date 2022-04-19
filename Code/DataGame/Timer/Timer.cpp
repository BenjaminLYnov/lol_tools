#include "Timer.hpp"

Timer::Timer()
{
     chrono = 0;
     isStart = false;
     isStop = true;
}

Timer::~Timer()
{
}

void Timer::reset()
{
     chrono = 0;
}

float Timer::getTime()
{
     return chrono;
}

void Timer::upTime()
{
     chrono += ((float)1) / ((float)60);
}