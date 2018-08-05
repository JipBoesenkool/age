//
// Created by Jip Boesenkool on 05/08/2018.
//

#if defined(__APPLE__) || defined(__linux__)

#include "os/timer/TimerUnix.h"

TimerUnix::TimerUnix()
{
	mStopped = 0;
	mStartTimeInMicroSec = 0;
	mEndTimeInMicroSec = 0;

	mStartCount.tv_sec = mStartCount.tv_usec = 0;
	mEndCount.tv_sec   = mStartCount.tv_usec = 0;
}
TimerUnix::~TimerUnix(){  }

void TimerUnix::Start()
{
	mStopped = 0;
	gettimeofday(&mStartCount, NULL);
}

void TimerUnix::Stop()
{
	mStopped = 1;
	gettimeofday(&mEndCount, NULL);
}

double TimerUnix::GetElapsedTimeInMicroSec()
{
	if(!mStopped)
	{
		gettimeofday(&mEndCount, NULL);
	}

	mStartTimeInMicroSec = (mStartCount.tv_sec * 1000000.0) + mStartCount.tv_usec;
	mEndTimeInMicroSec = (mEndCount.tv_sec * 1000000.0) + mEndCount.tv_usec;

	return mEndTimeInMicroSec - mStartTimeInMicroSec;
}

#endif