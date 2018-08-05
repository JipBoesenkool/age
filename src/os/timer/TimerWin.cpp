//
// Created by Jip Boesenkool on 05/08/2018.
//

#if defined(_WIN32) || defined(_WIN64)
#include "os/timer/TimerWin.h"

//TODO: Test on windows
TimerWin::TimerWin()
{
	mStopped = 0;
	mStartTimeInMicroSec = 0;
	mEndTimeInMicroSec = 0;

	QueryPerformanceFrequency(&mFrequency);
    mStartCount.QuadPart = 0;
    mEndCount.QuadPart = 0;
}
TimerWin::~TimerWin(){  }

void TimerWin::Start()
{
	mStopped = 0;
	QueryPerformanceCounter(&mStartCount);
}

void TimerWin::Stop()
{
	mStopped = 1;
	QueryPerformanceCounter(&mEndCount);
}

double TimerWin::GetElapsedTimeInMicroSec()
{
	if(!mStopped)
	{
		QueryPerformanceCounter(&mEndCount);
	}

	mStartTimeInMicroSec = mStartCount.QuadPart * (1000000.0 / mFrequency.QuadPart);
    mEndTimeInMicroSec = mEndCount.QuadPart * (1000000.0 / mFrequency.QuadPart);

	return mEndTimeInMicroSec - mStartTimeInMicroSec;
}

#endif