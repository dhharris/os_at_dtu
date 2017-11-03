/*
 * This file includes all unit tests
 */
#include <scwrapper.h>
#include <minunit.h>

int counter;
int tests_run = 0;

void thread(void)
{
        prints("Hello from thread ");
        printhex(counter++);
        prints("\n");
        terminate();
}

char thread_stack[4096];

static char *test_createprocess_should_return_ALL_OK()
{
        int result = createprocess(1);
        mu_assert("error, result != ALL_OK", result == ALL_OK);
        return 0;
}

static char *test_createprocess_should_run_program_1()
{
        // If program 1 is ran then "Pong" will be printed to the screen
        // if we perform a context switch
        yield();
        return 0;
}

static char *all_tests()
{
        mu_run_test(test_createprocess_should_return_ALL_OK);
        mu_run_test(test_createprocess_should_run_program_1);
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
