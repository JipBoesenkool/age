//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_TIMER_UNIX_H
#define AGE_TIMER_UNIX_H

#include <sys/time.h>

#include "Timer.h"

static const long NANOSECONDS_PER_SECOND = 1000000000L;

class TimerUnix : public Timer
{
//Members
private:
	timeval mStartCount;
	timeval mEndCount;
//Functions
public:
	TimerUnix();                                 // default constructor
	~TimerUnix();                                // default destructor

	void   Start() override;                     // start timer
	void   Stop() override;                      // stop the timer
	double GetElapsedTimeInMicroSec() override;  // get elapsed time in micro-second
};

#endif //AGE_TIMER_UNIX_H
