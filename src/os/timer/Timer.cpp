//
// Created by Jip Boesenkool on 05/08/2018.
//
#include "os/timer/Timer.h"
#include <assert.h>

Timer::Timer()
{
	mStopped = 0;
	mStartTimeInMicroSec = 0;
	mEndTimeInMicroSec = 0;
}
Timer::~Timer(){  }

void Timer::Start()
{
	assert(false);
	mStopped = 0;
}

void Timer::Stop()
{
	assert(false);
	mStopped = 1;
}

double Timer::GetElapsedTimeInMicroSec()
{
	assert(false);
	return 0.0;
}

double Timer::GetElapsedTime()
{
	return this->GetElapsedTimeInSec();
}

double Timer::GetElapsedTimeInSec()
{
	return this->GetElapsedTimeInMicroSec() * 0.000001;
}

double Timer::GetElapsedTimeInMilliSec()
{
	return this->GetElapsedTimeInMicroSec() * 0.001;
}