/* Copyright (c) 1997-2017, FenixOS Developers
 * All Rights Reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 */

/*! \file kernel_customization.h This file holds declarations
  for the kernel that you can change and alter. */

/* This file gets included into kernel.h! */

/*! Defines a thread. */
struct thread {
        uint32_t eax;
        uint32_t ebx;
        uint32_t esi;
        uint32_t edi;
        uint32_t ebp;
        uint32_t esp;
        uint32_t eip;
        /* The above members must be the first in the struct. Do not change the
           order. */

        struct process* process;
        /*!< owning process of this thread. Will be 0 if the thread is 
         * unowned, and therefore available for use by a new process. */
        struct thread*  next;
        /*!< can be used to implement linked lists of threads. */

        /* Add more members here if you need. */
};


/*! Process states */
#define PROCESS_NEW 0 // Process has not been set up with a job yet
/* Having PROCESS_NEW as a value of 0 ensures that each process in the
 * processes array will default to this state (because C zeroes out memory
 * that has been declared as a global variable).
 */
#define PROCESS_READY 1 // Process has been set up and is awaiting execution 
#define PROCESS_RUNNING 2 // Process has been chosen for execution
#define PROCESS_BLOCKED 3 // Process is waiting to be unblocked

/*! Defines a process. */
struct process {
        int number_of_threads; /*!< the number of threads this process owns. */
        int state; /*!< Current state of the process */
};

/* You can add more declarations here if you need. */
