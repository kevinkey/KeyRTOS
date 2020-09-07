#ifndef TASK_H
#define TASK_H

#include "types.h"
#include "event.h"
#include "list.h"
#include "stack.h"
#include "time.h"

enum task_priority_t
{
    TASK_PRIORITY_LOW,
    TASK_PRIORITY_NORMAL,
    TASK_PRIORITY_HIGH,
    TASK_PRIORITY_CRITICAL
};

struct task_t
{
    struct list_item_t item;
    uint_t * p_stack;
    enum task_priority_t priority;
    event_t * p_event;
    time_t timeout;
};

void task_init(struct task_t * p_task, enum task_priority_t priority);
void task_wait(struct task_t * p_task, event_t * p_event, time_t timeout);
bool task_ready(struct task_t * p_task);

static inline enum task_priority_t task_priority(struct task_t * p_task)
{
    return p_task->priority;
}

static inline void task_save(struct task_t * p_task)
{
    stack_save(p_task->p_stack);
}

static inline void task_load(struct task_t * p_task)
{
    stack_load(p_task->p_stack);
}

#endif
