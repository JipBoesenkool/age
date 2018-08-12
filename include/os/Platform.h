//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_PLATFORM_H
#define AGE_PLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#include "os/timer/TimerWin.h"

class Platform
{
//Members
public:
	TimerWin Time;
//Functions
public:
	Platform();
	~Platform();

	Timer* CreateTimer(){ return new TimerWin(); }
};

#endif

#if defined(__APPLE__) || defined(__linux__)
#include "os/timer/TimerUnix.h"

class Platform
{
//Members
public:
	TimerUnix Time;
//Functions
public:
	Platform();
	~Platform();

	Timer* CreateTimer(){ return new TimerUnix(); }
};

#endif

#endif //AGE_PLATFORM_H
