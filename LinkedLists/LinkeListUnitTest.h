#ifndef AIVUNIT_H
#define AIVUNIT_H
#include <stdio.h>
#include <stdlib.h>


#define AIVUNIT_INT_EQ(expected, actual)\
if (expected != actual) \
{ \
    printf("%s: expected %d but was %d\n", __FUNCTION__, expected, actual);        /* __FUNCTION__ prende il nome della funzione */ \
    exit(-1); \
} \

#define AIVUNIT_IS_TRUE(actual)\
if (!(actual)) \
{ \
    printf("%s: expected %s but was %s\n", __FUNCTION__, "true", "false"); \
    exit(-1); \
} \

#define AIVUNIT_TEST(name) void name()

#define AIVUNIT_RUNNER(...) \
int main() \
{ \
    void (* tests[])() = { __VA_ARGS__ };     /* __VA_ARGS__ prende l'argomento che gli passiamo, che saranno i nomi delle funzioni*/ \
    int count = sizeof(tests) / sizeof(void*); \
    for (int i = 0; i < count; i++) \
    { \
        tests[i](); \
    } \
    printf("All tests passed: %d", count); \
} \

#endif //AIVUNIT_H



























































