#include "list.h"
#include <stdint.h>
#include "test.h"

struct test_t
{
    struct list_item_t item;
    uint8_t data;
};

int main(void)
{
    struct list_t list;
    struct test_t pool[16];

    list_init(&list);

    for(uint8_t i = 0u; i < 16; i++)
    {
        pool[i].data = i;
        list_add(&list, (struct list_item_t *)&(pool[i]), LIST_ADD_TAIL);
    }

    uint8_t count = 0u;
    LIST_LOOP_EACH(&list, p_i)
    {
        struct test_t * p_test = (struct test_t *)p_i;
        TEST_EQUAL(p_test->data, count);
        count++;
    }

    list_init(&list);

    for(uint8_t i = 0u; i < 16; i++)
    {
        pool[i].data = i;
        list_add(&list, (struct list_item_t *)&(pool[i]), LIST_ADD_HEAD);
    }

    count = 15u;
    LIST_LOOP_EACH(&list, p_i)
    {
        struct test_t * p_test = (struct test_t *)p_i;
        TEST_EQUAL(p_test->data, count);
        count--;
    }

    exit(EXIT_SUCCESS);
}
