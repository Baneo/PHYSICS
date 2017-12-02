#include "timing.h"
#include <stdlib.h>
#include <sys/time.h>

// flag pour le timing interne du pc
static bool qpcFlag;
#define TIMING_UNIX	1
// pour linux
typedef unsigned long long	LONGLONG;

unsigned systemTime()
{
struct timeval tv;
gettimeofday(&tv, 0);
return tv.tv_sec * 1000 + tv.tv_usec/1000;

}

unsigned TimingData::getTime()
{
    return systemTime();
}

//récuperation du système de temps interne
unsigned long TimingData::getClock()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * 1000 + tv.tv_usec/1000;
}

//mise en place timer
void initTime()
{
    qpcFlag = false;
}


// Holds the global frame time that is passed around
static TimingData *timingData = NULL;

// Retrieves the global frame info instance
TimingData& TimingData::get()
{
    return (TimingData&)*timingData;
}

// Updates the global frame information. Should be called once per frame.
void TimingData::update()
{
    if (!timingData) return;

    // Advance the frame number.
    if (!timingData->isPaused)
    {
        timingData->frameNumber++;
    }

    // Update the timing information.
    unsigned thisTime = systemTime();
    timingData->lastFrameDuration = thisTime -
        timingData->lastFrameTimestamp;
    timingData->lastFrameTimestamp = thisTime;

    // Update the tick information.
    unsigned long thisClock = getClock();
    timingData->lastFrameClockTicks =
    thisClock - timingData->lastFrameClockstamp;
    timingData->lastFrameClockstamp = thisClock;

    // Update the RWA frame rate if we are able to.
    if (timingData->frameNumber > 1) {
        if (timingData->averageFrameDuration <= 0)
        {
            timingData->averageFrameDuration =
                (double)timingData->lastFrameDuration;
        }
        else
        {
            // RWA over 100 frames.
            timingData->averageFrameDuration *= 0.99;
            timingData->averageFrameDuration +=
                0.01 * (double)timingData->lastFrameDuration;

            // Invert to get FPS
            timingData->fps =
                (float)(1000.0/timingData->averageFrameDuration);
        }
    }
}

void TimingData::init()
{
    // Set up the timing system.
    initTime();

    // Create the frame info object
    if (!timingData) timingData = new TimingData();

    // Set up the frame info structure.
    timingData->frameNumber = 0;

    timingData->lastFrameTimestamp = systemTime();
    timingData->lastFrameDuration = 0;

    timingData->lastFrameClockstamp = getClock();
    timingData->lastFrameClockTicks = 0;

    timingData->isPaused = false;

    timingData->averageFrameDuration = 0;
    timingData->fps = 0;
}

void TimingData::deinit()
{
        delete timingData;
        timingData = NULL;
}
