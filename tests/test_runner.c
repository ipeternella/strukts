#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_runner.h"

void run(UnitTest *tests)
{
    // tests lists always end with a final NULL element
    for (int i = 0; tests[i] != NULL; i++)
    {
        tests[i]();
    }
}