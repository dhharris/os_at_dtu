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

/* Generates a pseduo random number */
static inline unsigned long rnd(void)
{
        const unsigned long seed = 101;
        static unsigned long memory;

        if ((memory == 0) || (memory == 1) || (memory == -1)) {
                memory = seed;
        }

        memory = (9973 * (~memory)) + ((memory) % 701);
        return memory;
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

static char *test_alloc_with_random_blocks()
{
        struct {
                unsigned long addr;
                unsigned long size;
        } blocks[16];
        register int clock;
        register long total_memory_size = 0;
        register long nallocs = 0;
        register long nfrees = 0;

        /* Reset the information on the blocks */
        for (clock = 0; clock < 16; clock++) {
                blocks[clock].addr = 0;
        }

        clock = 0;

        prints("test_memory_alloc: ");

        int i;
        for (i = 0; i < 10000000; ++i) {
                long addr;

                /* randomize the size of a block. */
                blocks[clock].size = (24 * 1024 * 1024 - total_memory_size) *
                                     (rnd() & (256 * 256 - 1)) /
                                     (256 * 256 * 8);

                /* Sanity check the block size. */
                if ((blocks[clock].size > 0) &&
                    (blocks[clock].size < (24 * 1024 * 1024))) {
                        /* Try to allocate memory. */
                        addr = (unsigned long)alloc(blocks[clock].size);

                        /* Check if it was successful. */
                        mu_assert("Memory block allocate failed!", addr > 0);
                        nallocs++;

                        /* Keep track of how much memory we have allocated... */
                        total_memory_size += blocks[clock].size;
                        /* and the address. */
                        blocks[clock].addr = addr;
                } else {
                        blocks[clock].addr = 0;
                }

                clock = (clock + 1) & 15;

                /* Try to free one block. */
                if (0 != blocks[clock].addr) {
                        if (0 != free((void *)blocks[clock].addr)) {
                                prints("Memory block free failed!\n");
                                break;
                        }
                        nfrees++;
                        total_memory_size -= blocks[clock].size;
                }
        }
        prints("Success\n");
        prints("Total memory size: ");
        printhex(total_memory_size);
        prints("\nTotal allocs: ");
        printhex(nallocs);
        prints("\nTotal frees: ");
        printhex(nfrees);
        prints("\n");

        return 0;
}

static char *test_alloc_with_large_block_should_fail()
{
        uint32_t too_big = 330000000; // Attempt to alloc 33 mb
        mu_assert("Error, alloc result is non-zero", alloc(too_big) == 0);
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
        mu_run_test(test_alloc_with_large_block_should_fail);
        mu_run_test(test_alloc_with_random_blocks);
        return 0;
}

int main(int argc, char *argv[])
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

        while (1)
                ;
}
