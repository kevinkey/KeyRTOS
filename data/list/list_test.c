#include "list.h"
#include <stdio.h>
#include <stdint.h>

struct test_t
{
    struct list_item_t item;
    uint8_t data;
};

void main(void)
{
    struct list_t list;
    struct test_t pool[16];

    list_init(&list);

    for(uint8_t i = 0u; i < 16; i++)
    {
        pool[i].data = i;
        list_add(&list, (struct list_item_t *)&(pool[i]), LIST_ADD_TAIL);
    }

    LIST_LOOP_EACH(&list)
    {
        struct test_t * p_test = (struct test_t *)p_item;
        printf("%d...", p_test->data);
    }
    printf("\n");

    list_init(&list);

    for(uint8_t i = 0u; i < 16; i++)
    {
        pool[i].data = i;
        list_add(&list, (struct list_item_t *)&(pool[i]), LIST_ADD_HEAD);
    }

    LIST_LOOP_EACH(&list)
    {
        struct test_t * p_test = (struct test_t *)p_item;
        printf("%d...", p_test->data);
    }
    printf("\n");
}
