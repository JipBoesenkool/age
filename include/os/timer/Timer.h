//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_TIMER_H
#define AGE_TIMER_H

class Timer
{
//Members
protected:
	double mStartTimeInMicroSec;                // starting time in micro-second
	double mEndTimeInMicroSec;                  // ending time in micro-second
	int    mStopped;                            // stop flag
//Functions
public:
	Timer();                                    // default constructor
	~Timer();                                   // default destructor

	virtual void   Start();                     // start timer
	virtual void   Stop();                      // stop the timer
	virtual double GetElapsedTimeInMicroSec();  // get elapsed time in micro-second

	double GetElapsedTime();            		// get elapsed time in second
	double GetElapsedTimeInSec();       		// get elapsed time in second (same as getElapsedTime)
	double GetElapsedTimeInMilliSec();  		// get elapsed time in milli-second
};

#endif //AGE_TIMER_H
