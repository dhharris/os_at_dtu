#include <unistd.h>
#include <string.h>
#include "../include/tests.h"

// Including io.h and unistd.h causes errors, so restating fn prototype
int write_int(int filedes, int d);

char *test_write_int_should_write_correct_bytes()
{
        int fds[2];
        char buf[2] = {0};
        pipe(fds);

        // Write to the pipe
        write_int(fds[1], 0);
        close(fds[1]);

        // Read from the pipe into buf
        read(fds[0], buf, 2);
        close(fds[0]);

        mu_assert("Error, strcmp(buf, \"0\") != 0", strcmp(buf, "0") == 0);
        return 0;
}

char *test_write_int_with_many_digits_should_write_correct_bytes()
{
        int fds[2];
        char buf[4] = {0};
        pipe(fds);

        // Write to the pipe
        write_int(fds[1], 100);
        close(fds[1]);

        // Read from the pipe into buf
        read(fds[0], buf, 4);
        close(fds[0]);

        mu_assert("Error, strcmp(buf, \"100\") != 0", strcmp(buf, "100") == 0);
        return 0;
}
