//
// Created by Jip Boesenkool on 05/08/2018.
//

#ifndef AGE_PLATFORM_H
#define AGE_PLATFORM_H

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
};

#endif

#endif //AGE_PLATFORM_H
