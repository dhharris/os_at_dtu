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
int syscall_read(char *dest, int len);
int write_char(char c);

int syscall_write(char *dest, int len);

#endif /* IO_H_ */
