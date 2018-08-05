//
// Created by Jip Boesenkool on 05/08/2018.
//
#include "os/Platform.h"

Platform::Platform()
{
	Time.Start();
}

Platform::~Platform()
{
	Time.Stop();
}

