#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list_item_t
{
    struct list_item_t * p_prev;
    struct list_item_t * p_next;
};

struct list_t
{
    struct list_item_t * p_head;
    struct list_item_t * p_tail;
};

enum list_add_t
{
    LIST_ADD_HEAD,
    LIST_ADD_TAIL,
};

void list_init(struct list_t * p_list);
void list_add(struct list_t * p_list, struct list_item_t * p_item, enum list_add_t add);
void list_del(struct list_t * p_list, struct list_item_t * p_item);

#define LIST_LOOP_EACH(p_list)                                                  \
    for(struct list_item_t * p_item = (p_list)->p_head;                         \
        p_item != NULL;                                                         \
        p_item = p_item->p_next)

#endif
