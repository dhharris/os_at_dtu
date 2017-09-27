/*
 * io.h
 *
 *  Created on: Aug 28, 2014
 */

#ifndef IO_H_
#define IO_H_
/**
 * These functions wrap the linux read and write system calls for
 *  stdin and stdout respectively.  There is also one helper
 *  function to print out a single char.
 *
 * If you need or want to add more function to the interface, feel
 *  free to do so and add the definitions to this file.  It may
 *  be beneficial to add a helper to print out integers for example
 *  */

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2


int read(int fildes, void *buf, unsigned int nbyte);
int write(int filedes, const void *buf, unsigned int nbyte);

int write_char(int filedes, char c);
int write_int(int filedes, int n);


#endif /* IO_H_ */
