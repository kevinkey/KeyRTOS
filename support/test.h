#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>

#define TEST_EQUAL(value, expect)                                               \
    if(value != expect)                                                         \
    {                                                                           \
        fprintf(stderr,                                                         \
                "\"" #value "\" does not equal \"" #expect "\", "               \
                "expected %d got %d on line %d\n",                              \
                expect,                                                         \
                value,                                                          \
                __LINE__);                                                      \
        exit(EXIT_FAILURE);                                                     \
    }

#endif
