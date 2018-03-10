//
// Created by Sergey Savelyev on 3/10/18.
//

#ifndef SPHERALIZER_UTILS_H
#define SPHERALIZER_UTILS_H

#include <sys/time.h>

void delay(unsigned int howLong) {
    struct timespec sleeper, dummy;

    sleeper.tv_sec = (time_t) (howLong / 1000);
    sleeper.tv_nsec = (long) (howLong % 1000) * 1000000;

    nanosleep(&sleeper, &dummy);
}

void delayMicrosecondsHard(unsigned int howLong) {
    struct timeval tNow, tLong, tEnd;

    gettimeofday(&tNow, NULL);
    tLong.tv_sec = howLong / 1000000;
    tLong.tv_usec = howLong % 1000000;
    timeradd (&tNow, &tLong, &tEnd);

    while (timercmp (&tNow, &tEnd, <))
        gettimeofday(&tNow, NULL);
}

void delayMicroseconds(unsigned int howLong) {
    struct timespec sleeper;
    unsigned int uSecs = howLong % 1000000;
    unsigned int wSecs = howLong / 1000000;

    /**/ if (howLong == 0)
        return;
    else if (howLong < 100)
        delayMicrosecondsHard(howLong);
    else {
        sleeper.tv_sec = wSecs;
        sleeper.tv_nsec = (long) (uSecs * 1000L);
        nanosleep(&sleeper, NULL);
    }
}

static uint64_t epochMilli, epochMicro;

static void initialiseEpoch(void) {
#ifdef    OLD_WAY
    struct timeval tv ;

  gettimeofday (&tv, NULL) ;
  epochMilli = (uint64_t)tv.tv_sec * (uint64_t)1000    + (uint64_t)(tv.tv_usec / 1000) ;
  epochMicro = (uint64_t)tv.tv_sec * (uint64_t)1000000 + (uint64_t)(tv.tv_usec) ;
#else
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    epochMilli = (uint64_t) ts.tv_sec * (uint64_t) 1000 + (uint64_t) (ts.tv_nsec / 1000000L);
    epochMicro = (uint64_t) ts.tv_sec * (uint64_t) 1000000 + (uint64_t) (ts.tv_nsec / 1000L);
#endif
}

unsigned int millis(void) {
    uint64_t now;

#ifdef    OLD_WAY
    struct timeval tv ;

  gettimeofday (&tv, NULL) ;
  now  = (uint64_t)tv.tv_sec * (uint64_t)1000 + (uint64_t)(tv.tv_usec / 1000) ;

#else
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    now = (uint64_t) ts.tv_sec * (uint64_t) 1000 + (uint64_t) (ts.tv_nsec / 1000000L);
#endif

    return (uint32_t) (now - epochMilli);
}

unsigned int micros(void) {
    uint64_t now;
#ifdef    OLD_WAY
    struct timeval tv ;

  gettimeofday (&tv, NULL) ;
  now  = (uint64_t)tv.tv_sec * (uint64_t)1000000 + (uint64_t)tv.tv_usec ;
#else
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    now = (uint64_t) ts.tv_sec * (uint64_t) 1000000 + (uint64_t) (ts.tv_nsec / 1000);
#endif


    return (uint32_t) (now - epochMicro);
}


#endif //SPHERALIZER_UTILS_H
