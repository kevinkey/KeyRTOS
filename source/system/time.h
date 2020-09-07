#ifndef TIME_H
#define TIME_H

#include "types.h"

typedef uint32_t time_t;

extern time_t Time;

static inline time_t time_now(void)
{
    return Time;
}

static inline time_t time_elapsed(time_t const start)
{
    time_t const now = time_now();

    return (now - start);
}

static inline void time_increment(time_t const amount)
{
    time_t const now = time_now();
    time_t const total = now + amount;

    Time = total;
}

#endif
