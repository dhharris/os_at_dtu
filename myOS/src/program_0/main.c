/*! \file \brief The first user program - simply tests the thread creation routine
 *
 */
#include <scwrapper.h>

int counter;

void thread(void)
{
        prints("Hello from thread ");
        printhex(counter++);
        prints("\n");
        terminate();
}

char thread_stack[4096];

int main(int argc, char* argv[])
{
        int i;
        for (i = 0; i < 5; ++i)
                if (ALL_OK != createthread(thread, thread_stack+4096)) {
                        prints("createthread failed!\n");
                        return 1;
                }

        while(1)
                yield();

        return 0;
}
