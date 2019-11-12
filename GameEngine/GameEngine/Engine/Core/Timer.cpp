#include "Timer.h"



Timer::Timer()
{
	// default the values to 0
	prevTicks = 0;
	currentTicks = 0;
}


Timer::~Timer()
{
}


// start timer
void Timer::Start()
{
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();
}
// get the current ticks and update it
void Timer::UpdateFramTicks()
{
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();

}

// get the delta time
float Timer::GetDeltaTime() const
{
	return static_cast<float>(currentTicks - prevTicks) / 1000.0f;
};

unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	unsigned int milliPerFrame = 1000 / fps_;
	if(milliPerFrame == 0)
	{
		return 0;
	}
	unsigned int sleepTime = milliPerFrame - (SDL_GetTicks());
	if(sleepTime > milliPerFrame)
	{
		return  milliPerFrame;
	}
	return  sleepTime;
};

// get the current ticks
float Timer::GetCurrentTicks()
{
	return  static_cast<float>(currentTicks);
}