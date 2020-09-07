#include "task.h"
#include "irq.h"
#include "system.h"

void task_init(struct task_t * p_task, enum task_priority_t priority)
{
    stack_init(p_task->p_stack);
    p_task->p_event = NULL;
    p_task->priority = priority;
    system_add_task(p_task);
}

void task_wait(struct task_t * p_task, event_t * p_event, time_t timeout)
{
    bool state = irq_disable();

    p_task->p_event = p_event;
    p_task->timeout = time_now() + timeout;

    irq_enable(state);
}

bool task_ready(struct task_t * p_task)
{
    bool ready;

    if(p_task->p_event == NULL)
    {
        ready = true;
    }
    else if(event_status(p_task->p_event))
    {
        ready = true;
    }
    else if(time_now() >= p_task->timeout)
    {
        ready = true;
    }
    else
    {
        ready = false;
    }

    return ready;
}
