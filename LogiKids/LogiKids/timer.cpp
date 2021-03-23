#include "timer.h"

Timer::Timer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

std::string Timer::toMinutesAndSeconds(Uint32 ticks)//, int& outMinutes, int& outSeconds)
{
	int inSeconds = ticks / 1000;
	int outMinutes = inSeconds / 60;
	int outSeconds = inSeconds % 60;

	std::string time;

	if (outMinutes < 10)
		time += "0";

	time += std::to_string(outMinutes);
	time += ":";

	if (outSeconds < 10)
		time += "0";

	time += std::to_string(outSeconds);

	return time;
}