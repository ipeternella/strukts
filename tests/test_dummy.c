#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_runner.h"

void test_adding_1_plus_1_should_be_2()
{
    assert(1 + 1 == 2);
}

void test_adding_1_plus_2_should_be_3()
{
    assert(1 + 2 == 3);
}

// static -> only 'visible' to this file
static UnitTest tests[] = {test_adding_1_plus_1_should_be_2, test_adding_1_plus_2_should_be_3, NULL};

int main()
{
    run(tests);

    return EXIT_SUCCESS;
}