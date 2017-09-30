#include <unistd.h>
#include <string.h>
#include "../include/tests.h"

#define EOF -1
// Including io.h and unistd.h causes errors, so restating fn prototype
int write_int(int filedes, int d);
int putchar(int c);
int getchar();

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

char *test_write_int_with_negative_number_should_write_correct_bytes()
{
        int fds[2];
        char buf[3] = {0};
        pipe(fds);

        // Write to the pipe
        write_int(fds[1], -1);
        close(fds[1]);

        // Read from the pipe into buf
        read(fds[0], buf, 3);
        close(fds[0]);

        mu_assert("Error, strcmp(buf, \"-1\") != 0", strcmp(buf, "-1") == 0);
        return 0;
}

char *test_getchar_should_read_correct_character()
{
        int fds[2];
        pipe(fds);

        // Write to the pipe
        write(fds[1], "c", 1);
        close(fds[1]);

        // Direct stdin to the read end of the pipe
        dup2(fds[0], STDIN_FILENO);
        char result = getchar();
        close(fds[0]);

        mu_assert("Error, result != 'c'", result == 'c');
        return 0;
}

char *test_getchar_should_return_EOF_on_error()
{
        int fds[2];
        pipe(fds);
        close(fds[1]); // Nothing in the pipe

        // Direct stdin to the read end of the pipe
        dup2(fds[0], STDIN_FILENO);
        char result = getchar();
        close(fds[0]);

        mu_assert("Error, result != EOF", result == EOF);
        return 0;
}

char *test_putchar_should_write_correct_character()
{
        char buf[1];
        int fds[2];
        int saved_stdout = dup(STDOUT_FILENO);
        pipe(fds);

        // Direct stdout to write end of pipe
        dup2(fds[1], STDOUT_FILENO);

        // Write to the pipe
        putchar('c');
        close(fds[1]);

        // Read from the pipe into buf
        read(fds[0], buf, 1);
        close(fds[0]);

        // Restore stdout
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);

        mu_assert("Error, buf[0] != 'c'", buf[0] == 'c');
        return 0;
}
