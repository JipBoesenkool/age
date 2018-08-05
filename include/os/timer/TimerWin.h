//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_TIMER_WIN_H
#define AGE_TIMER_WIN_H

#include <sys/time.h>

#include "Timer.h"

static const long NANOSECONDS_PER_SECOND = 1000000000L;

class TimerWin : public Timer
{
//Members
private:
	LARGE_INTEGER mFrequency;                    // ticks per second
	LARGE_INTEGER mStartCount;
	LARGE_INTEGER mEndCount;
//Functions
public:
	TimerWin();                                 // default constructor
	~TimerWin();                                // default destructor

	void   Start() override;                     // start timer
	void   Stop() override;                      // stop the timer
	double GetElapsedTimeInMicroSec() override;  // get elapsed time in micro-second
};

#endif //AGE_TIMER_WIN_H
