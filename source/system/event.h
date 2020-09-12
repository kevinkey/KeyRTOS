#ifndef EVENT_H
#define EVENT_H

#include "types.h"

typedef bool event_t;

static inline void event_set(event_t * event)
{
    *event = true;
}

static inline void event_clear(event_t * event)
{
    *event = false;
}

static inline bool event_status(event_t * event)
{
    return *event;
}

#endif
