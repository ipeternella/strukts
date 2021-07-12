/**
 * @file test_runner.h
 *
 * @brief Test running functions and utilities.
 */

#ifndef __STRUKTS_TEST_RUNNER_H
#define __STRUKTS_TEST_RUNNER_H

/**
 * Typedef of a fn pointer that represents a unit test.
 */
typedef void (*UnitTest)(void);

/**
 * Runs an array of unit tests. Accepts an array of UnitTest functions due to
 * array decaying.
 */
void run(UnitTest *tests);

#endif /* ifndef __STRUKTS_TEST_RUNNER_H */