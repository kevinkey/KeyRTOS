#include "list.h"

void list_init(struct list_t * p_list)
{
    p_list->p_head = NULL;
    p_list->p_tail = NULL;
}

void list_add(struct list_t * p_list, struct list_item_t * p_item, enum list_add_t add)
{
    switch(add)
    {
        case LIST_ADD_HEAD:
            p_item->p_prev = NULL;
            p_item->p_next = p_list->p_head;

            if(p_item->p_next != NULL)
            {
                p_item->p_next->p_prev = p_item;
            }
            else
            {
                p_list->p_tail = p_item;
            }

            p_list->p_head = p_item;
            break;
        case LIST_ADD_TAIL:
        default:
            p_item->p_prev = p_list->p_tail;
            p_item->p_next = NULL;

            if(p_item->p_prev != NULL)
            {
                p_item->p_prev->p_next = p_item;
            }
            else
            {
                p_list->p_head = p_item;
            }

            p_list->p_tail = p_item;
            break;
    }
}

void list_del(struct list_t * p_list, struct list_item_t * p_item)
{
    if(p_list->p_head == p_item)
    {
        p_list->p_head = p_item->p_next;
    }
    else if(p_item->p_prev != NULL)
    {
        p_item->p_prev->p_next = p_item->p_next;
    }

    if(p_list->p_tail == p_item)
    {
        p_list->p_tail = p_item->p_prev;
    }
    else if(p_item->p_next != NULL)
    {
        p_item->p_next->p_prev = p_item->p_prev;
    }

    p_item->p_next = NULL;
    p_item->p_prev = NULL;
}
