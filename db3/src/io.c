#include "../include/io.h"
#include "../include/stack.h"

int read(int filedes, void *buf, unsigned int nbyte)
{

        // At -O3 GCC was optimizing dest and nbyte away.
        //  Volatile is to prevent that.
        volatile int bytes_read = 0;
        volatile unsigned int _nbyte = nbyte;
        volatile int _filedes = filedes;
        volatile void *_buf = buf;

        // Read system call:
        //  eax contains the system call number, 3 for read
        //  ebx contains the file descriptor to read from, 0 for stdin
        //  ecx contains the location to read into
        //  edx contains the number of bytes to read
        __asm__ ("int $0x80"
                        : "=a" (bytes_read)
                        : "a" (0x03),
                        "b" (_filedes),
                        "c" (_buf),
                        "d" (_nbyte)
                        :
                );

        return bytes_read;
}


int write(int filedes, const void *buf, unsigned int nbyte)
{

        // At -O3 GCC was optimizing these away.  Added volatile
        //  to prevent that from happening
        volatile int bytes_written = 0;
        volatile unsigned int _nbyte = nbyte;
        volatile int _filedes = filedes;
        volatile const void *_buf = buf;

        // Write system call:
        //  eax contains the system call number, 4 for write
        //  ebx contains the fd to write to, 1 for stdout, 2 for stderr
        //  ecx contains the location of bytes to write
        //  edx contains the number of bytes to write
        __asm__ ("int $0x80"
                        : "=a" (bytes_written)
                        : "a" (0x04),
                        "b" (_filedes),
                        "c" (_buf),
                        "d" (_nbyte)
                        :
                );
        return bytes_written;
}

// Helper function to print out a single char
int write_char(int filedes, char c)
{
        return write(filedes, &c, 1);
}

// Helper function to print out an integer
int write_int(int filedes, int d)
{
        if (d == 0)
                return write_char(filedes, '0');

        char str[11] = {0}; // Largest integer value is usually 10 digits long
        Stack s;
        sinit(&s, 10);

        while (d > 0) {
                spush(&s, d % 10);
                d /= 10;
        }

        int i = 0;
        while (!sisempty(&s))
                str[i++] = spop(&s) + '0';
        str[i] = 0; // Make sure str is null terminated
        sdestroy(&s);

        return write(filedes, str, i + 1);
}
