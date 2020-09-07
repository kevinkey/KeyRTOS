#include "system.h"
#include "irq.h"
#include "list.h"
#include "time.h"

struct list_t Task_List;
struct task_t * p_Active_Task;

static void schedule_task(void)
{
    LIST_LOOP_EACH(&Task_List, p_i)
    {
        struct task_t * p_task = (struct task_t *)p_i;

        if(task_ready(p_task))
        {
            if((int_t)task_priority(p_task) > (int_t)task_priority(p_Active_Task))
            {
                p_Active_Task = p_task;
            }
        }
    }
}

void system_init(void)
{
    list_init(&Task_List);
}

void system_start(void)
{
    p_Active_Task = (struct task_t *)list_head(&Task_List);
    schedule_task();
    task_load(p_Active_Task);

    irq_enable(true);
}

void system_tick(time_t amount)
{
    bool state = irq_disable();

    task_save(p_Active_Task);
    time_increment(amount);
    schedule_task();
    task_load(p_Active_Task);

    irq_enable(state);
}

void system_add_task(struct task_t * p_task)
{
    bool state = irq_disable();

    list_add(&Task_List, (struct list_item_t *)p_task, LIST_ADD_HEAD);

    irq_enable(state);
}
