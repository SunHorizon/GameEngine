#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;


	Timer();
	~Timer();

	// start timer
	void Start();
	// get the current ticks and update it
	void UpdateFramTicks();
	// get the delta time
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	// get the current ticks
	float GetCurrentTicks();

private:

	unsigned int prevTicks;
	unsigned int currentTicks;
};
#endif
