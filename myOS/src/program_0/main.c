/*
 * This file includes all unit tests
 */
#include <scwrapper.h>
#include <minunit.h>

#define COUNT 1000000

volatile int counter;
int tests_run = 0;
int sum = 0; // Shared
int mutex;
int done = 0; // Number of threads that are finished

void thread()
{
        counter += 2;
        terminate();
}

void thread_undo()
{
        counter--;
        terminate();
}

void countgold()
{
        int i; // local to each thread
        for (i = 0; i < COUNT; ++i) {
                semaphoredown(mutex);
                // Critical section
                sum++;
                semaphoreup(mutex);
                yield();
        }
        semaphoredown(mutex);
        done++;
        semaphoreup(mutex);
        terminate();
}

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
        int result = createthread(thread, 0);
        mu_assert("Error, result != ALL_OK", result == ALL_OK);
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

static char *test_semaphores_should_return_correct_handle()
{
        mutex = createsemaphore(1); // First semaphore created will be index 0
        mu_assert("Error, mutex != 0", mutex == 0);
        return 0;
}

static char *test_semaphores_should_perform_correct_increments()
{
        createthread(countgold, 0);
        createthread(countgold, 0);
        int running = 1;
        while (running) {
                yield();
                semaphoredown(mutex);
                running = done < 2;
                semaphoreup(mutex);
        }
        mu_assert("Error, sum != COUNT * 2", sum == COUNT * 2);
        return 0;
}

static char *test_semaphores_should_return_error()
{
        int result = semaphoreup(10);
        mu_assert("Error, result != ERROR", result == ERROR);
        return 0;
}

static char *all_tests()
{
        mu_run_test(test_createprocess_should_return_ALL_OK);
        mu_run_test(test_createprocess_should_return_ERROR);
        mu_run_test(test_create_thread_should_return_ALL_OK);
        mu_run_test(test_yield_should_run_program_1);
        mu_run_test(test_terminate_should_not_print_pang);
        mu_run_test(test_semaphores_should_return_correct_handle);
        mu_run_test(test_semaphores_should_perform_correct_increments);
        mu_run_test(test_semaphores_should_return_error);
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
