#include "CommonDefines.h"

#include "bOSTimer.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

Timer::Timer()
{
	dMilliseconds=0;
}

Timer::~Timer()
{
}

void Timer::start()
{
	Time::currentTime (&tmStart);
}

long Timer::stop()
{
	Time tmEnd;

	Time::currentTime(&tmEnd);

	dMilliseconds = tmStart.millisecondsTo (tmEnd);

	return dMilliseconds;
}

long Timer::getTicks()
{
	return dMilliseconds;
}