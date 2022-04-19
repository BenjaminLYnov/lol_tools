#ifndef TIMER_H
#define TIMER_H
#pragma once


class Timer
{
private:
	float chrono;
	bool isStart;
	bool isStop;

public:
	Timer();
	~Timer();
	void reset();
	void upTime();
	float getTime();
};
#endif