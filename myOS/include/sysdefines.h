/* Copyright (c) 1997-2017, FenixOS Developers
   All Rights Reserved.

   This file is subject to the terms and conditions defined in
   file 'LICENSE', which is part of this source code package.
 */

/*! \file sysdefines.h
 *  This file defines constants and data types used by system calls.
 *
 */

#ifndef _SYSDEFINES_H_
#define _SYSDEFINES_H_

/* Constant declarations. */

/*! Return code when system call returns normally. */
#define ALL_OK                  (0)
/*! Return code when system call returns with an error. */
#define ERROR                   (-1)
/*! Return code when system call is unknown. */
#define ERROR_ILLEGAL_SYSCALL   (-2)

/*! System call that returns the version of the kernel. */
#define SYSCALL_VERSION         (0)
/*! System call that prints a string. */
#define SYSCALL_PRINTS          (1)
/*! System call that prints a hexadecimal value. */
#define SYSCALL_PRINTHEX        (2)

/*! System call that allocates a memory block. The length of the requested
    memory block is passed in edi. The system call returns the address or an
    error code. */
#define SYSCALL_ALLOCATE        (4)

/*! System call that frees a memory block allocated through the allocate
    system call. The address of the memory block is passed in edi. The
    system call returns  ALL_OK if successful or an error code if
    unsuccessful. */
#define SYSCALL_FREE            (5)

/*! System call that terminates the currently running
 *  thread. It takes no parameters. Terminates the process
 *  when there are no threads left. */
#define SYSCALL_TERMINATE       (6)

/*! System call that creates a new process with one single
 *  thread. The program used is the executable whose index is
 *  passed in edi. */
#define SYSCALL_CREATEPROCESS   (7)

/*! System call that will temporarily move the calling thread from the running
    to the ready state. The system call does not take any parameters and returns
    ALL_OK.*/
#define SYSCALL_YIELD           (8)

/*! Creates a new thread in the process of the calling thread. The value of 
    eip register of the new thread is passed in the edi registe. The value of 
    the esp register of the new thread is passed in esi. The other registers
    are undefinied.

    The system call returns in eax ALL_OK if successful or an error code if 
    unsuccessful.
   */
#define SYSCALL_CREATETHREAD    (16)

/*! Creates a new semaphore and returns if successful the handle of the
    semaphore in the eax register. The initial value of the semaphore count
    value is passed in the edi register.
   
    If unsuccessful the system call returns an error code in eax. */
#define SYSCALL_CREATESEMAPHORE (17)

/*! Performs a semaphore down operation. The handle of the semaphore is passed
    in the edi register.

    The system call returns in eax ALL_OK if successful or an error code if 
    unsuccessful.
   */
#define SYSCALL_SEMAPHOREDOWN   (18)

/*! Performs an semaphore up operation. The handle of the semaphore is passed
    in the edi register.

    The system call returns in eax ALL_OK if successful or an error code if 
    unsuccessful.
   */
#define SYSCALL_SEMAPHOREUP     (19)

/*! Returns the number of memory pages used in user space in register eax
 */
#define SYSCALL_MEMORY_PAGES_USED (72)

/*! System call that allocates a port. The identity number of the port
    is passed in edi. The system call returns, in eax, a handle to the
    port or an error code if unsuccessful.
 */
#define SYSCALL_ALLOCATEPORT    (20)

/*! System call that finds a port. The identity number of the port is
    passed in edi. The owning process identity is passed in esi. The
    system call returns, in eax, a handle to the port or an error code
    if unsuccessful.
 */
#define SYSCALL_FINDPORT        (21)

/*! System call that sends a message. The handle of the destination
    port is passed in edi. A pointer to the message is passed in
    esi. The system call returns, in eax, ALL_OK if successful or an
    error code if unsuccessful.
   */
#define SYSCALL_SEND            (22)

/*! System call that receives a message. The handle of the port on
    which to receive is passed in edi. Register esi holds a pointer to
    a buffer that will hold the received message.

    The system call returns, in eax, ALL_OK if successful or an error
    code if unsuccessful. Register edi holds the identity of process
    from which the message was received.
   */
#define SYSCALL_RECEIVE         (23)

/* Type declarations. */

/*! Describes a message. */
struct message
{
 int32_t int_0;
 int32_t int_1;
 int32_t int_2;
 int32_t int_3;
 int32_t int_4;
 int32_t int_5;
 int32_t int_6;
 int32_t int_7;
};

#endif
