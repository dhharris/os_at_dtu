/*
 * This file includes all unit tests
 */
#include <scwrapper.h>
#include <minunit.h>

#define COUNT 10000000

volatile int counter;
int tests_run = 0;
int sum = 0; // Shared
int mutex;

void thread()
{
        while (1) {
                counter++;
                yield();
        }
}

void thread_undo()
{
        counter--;
        terminate(); // Whoops, we only run this once!
}

void countgold()
{
        int i; // local to each thread
        for (i = 0; i < COUNT; ++i) {
                semaphoredown(mutex);
                // Critical section
                sum++;
                semaphoreup(mutex);
        }
        terminate();
}

char thread_stack[4096];

static char *test_createprocess_should_return_ALL_OK()
{
        int result = createprocess(1);
        mu_assert("error, result != ALL_OK", result == ALL_OK);
        return 0;
}

static char *test_createprocess_should_return_ERROR()
{
        int result = createprocess(1000);
        mu_assert("error, result != ERROR", result == ERROR);
        return 0;
}

static char *test_create_thread_should_return_ALL_OK()
{
        int result = createthread(thread, thread_stack + 4096);
        mu_assert("Error, result != ALL_OK", result == ALL_OK);
        return 0;
}

static char *test_yield_should_add_to_counter_each_time()
{
        int first = counter;
        yield(); // Context switch so the thread we created is ran
        yield(); // Do it again
        int second = counter;
        mu_assert("Error, second != first + 2", second == first + 2);
        return 0;
}

static char *test_yield_should_run_program_1()
{
        // If program 1 is ran then "Pong" will be printed to the screen
        // if we perform a context switch
        yield();
        prints("test_yield: Verify that 'Pong' is printed above\n");
        return 0;
}

static char *test_terminate_should_not_print_pang()
{
        createprocess(2);
        yield();
        prints("test_terminate: Verify that program2 does not print 'Pang'\n");
        return 0;
}

static char *test_terminate_with_thread_should_increment_counter()
{
        int first = counter;
        createthread(thread_undo, thread_stack + 4096);
        yield(); // Context switch so the thread we created is ran
        yield(); // Do it again
        int second = counter;
        // Now it should only be incremented by 1
        mu_assert("Error, second != first + 1", second == first + 1);
        return 0;
}

static char *test_semaphores_should_perform_correct_increments()
{
        mutex = createsemaphore(1);
        createthread(countgold, thread_stack + 4096);
        createthread(countgold, thread_stack + 4096);
        yield();
        mu_assert("Error, sum != COUNT * 2", sum == COUNT * 2);
        return 0;
}

static char *all_tests()
{
        mu_run_test(test_createprocess_should_return_ALL_OK);
        mu_run_test(test_createprocess_should_return_ERROR);
        mu_run_test(test_create_thread_should_return_ALL_OK);
        mu_run_test(test_yield_should_run_program_1);
        mu_run_test(test_yield_should_add_to_counter_each_time);
        mu_run_test(test_terminate_should_not_print_pang);
        mu_run_test(test_terminate_with_thread_should_increment_counter);
        mu_run_test(test_semaphores_should_perform_correct_increments);
        return 0;
}

int main(int argc, char* argv[])
{
        char *result = all_tests();
        if (result != 0) {
                prints(result);
                prints("\n");
        } else {
                prints("ALL TESTS PASSED\n");
        }
        prints("Tests run: ");
        printhex(tests_run);
        prints("\n");

        while (1);
}
