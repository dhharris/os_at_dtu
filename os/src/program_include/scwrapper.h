/* Copyright (c) 1997-2017, FenixOS Developers
   All Rights Reserved.

   This file is subject to the terms and conditions defined in
   file 'LICENSE', which is part of this source code package.
 */

/*! \file scwrapper.h
 *  This file contains C wrapper functions for system calls.
 *  The wrappers are used by user programs to perform system
 *  calls from C.
 */

#ifndef _SCWRAPPER_H_
#define _SCWRAPPER_H_

/* Include the constants that identifies system calls. */

#include <sysdefines.h>
#include <stdint.h>

/*! Wrapper for the system call that returns the version of the kernel. */
static inline int32_t
version(void)
{
 int32_t return_value;

 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t"
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_VERSION) :
                 "cc", "%ecx", "%edx");
 return return_value;
}


/*! Wrapper for the system call that prints a string.
 * @param string Pointer to the string to be printed.
 * */
static inline int32_t
prints(const char* const string)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_PRINTS), "D" (string) :
                 "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that prints a hexadecimal value.
 * @param value hexadecimal value to be printed.
 */
static inline int32_t
printhex(const uint32_t value)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t"
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_PRINTHEX), "D" (value) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that allocates a memory block
 *  @param length integer holding the number of bytes to allocate
 */
static inline void *
alloc(int32_t length)
{
 void * return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_ALLOCATE), "D" (length) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that frees a memory block.
 *  @param address address to the memory block to free.
 */
static inline int32_t
free(void * address)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_FREE), "D" (address) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that returns the number of memory pages used. */
static inline int32_t
memory_pages_used(void)
{
 int32_t return_value;

 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t"
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_MEMORY_PAGES_USED) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that terminates threads and processes. */
static inline void
terminate(void)
{
 __asm volatile("sysenter" :
                 :
                 "a" (SYSCALL_TERMINATE) :
                 "cc", "%ecx", "%edx");
}

/*! Wrapper for the system call that creates processes.
 * @param executable integer identifying the program which should be loaded 
 *  and run as a process.
 */
static inline int32_t
createprocess(const int executable)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_CREATEPROCESS), "D" (executable) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that will temporarily move the calling thread 
    from the running to the ready state. The system call does not take any 
    parameters and returns ALL_OK. */
static inline int32_t
yield(void)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                 "1: \n\t" :
                 "=a" (return_value) :
                 "a" (SYSCALL_YIELD) :
                 "cc", "%ecx", "%edx");
 return return_value;
}

/*! Wrapper for the system call that creates a thread. */
static inline int32_t
createthread(void (*thread)(void), void* stack)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t"  :
                "=a" (return_value) :
                "a" (SYSCALL_CREATETHREAD), "D" (thread), "S" (stack) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that creates a semaphore. */
static inline int32_t
createsemaphore(int32_t initial_count)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t"  :
                "=a" (return_value) :
                "a" (SYSCALL_CREATESEMAPHORE), "D" (initial_count) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that performs a down operation on a 
    semaphore. */
static inline int32_t
semaphoredown(int32_t semaphore_handle)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value) :
                "a" (SYSCALL_SEMAPHOREDOWN), "D" (semaphore_handle) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that performs an up operation on a 
    semaphore */
static inline int32_t
semaphoreup(int32_t semaphore_handle)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value) :
                "a" (SYSCALL_SEMAPHOREUP), "D" (semaphore_handle) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that allocates a port. */
static inline int32_t
allocateport(int32_t id)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value) :
                "a" (SYSCALL_ALLOCATEPORT), "D" (id) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that finds a port given an owning process and
    port identity. */
static inline int32_t
findport(int32_t id, int32_t process)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value) :
                "a" (SYSCALL_FINDPORT), "D" (id), "S" (process) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that sends a message to a port. */
static inline int32_t
send(int32_t port, const struct message* const message)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value) :
                "a" (SYSCALL_SEND), "D" (port), "S" (message) :
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

/*! Wrapper for the system call that receives a message from a port. */
static inline int32_t
receive(int32_t               port, 
        struct message* const message,
        int32_t* const        sender)
{
 int32_t return_value;
 __asm volatile("mov $1f, %%edx \n\t" 
                "mov %%esp, %%ecx   \n\t" 
                "sysenter         \n\t" 
                "1: \n\t" :
                "=a" (return_value), "=D" (*sender) :
                "a" (SYSCALL_RECEIVE), "D" (port), "S" (message):
                "cc", "%ecx", "%edx", "memory");
 return return_value;
}

#endif /* _SCWRAPPER_H_ */
