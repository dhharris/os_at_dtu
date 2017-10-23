/* Copyright (c) 1997-2017, FenixOS Developers
 * All Rights Reserved.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 */

/*! \file kernel_customization.c This file holds definitions
  for the kernel that you can change and alter. */

#include <stdint.h>
#include <instruction_wrappers.h>
#include <sysdefines.h>

#include "kernel.h"


// Return the next available ready thread
struct thread *yield()
{
        int i, index = current_thread - threads;

        /* Search upper half of array */
        for (i = index + 1; i < MAX_THREADS; ++i)
                if (threads[i].process)
                        return &threads[i];

        /* Search lower half of array */
        for (i = 0; i < index; ++i)
                if (threads[i].process)
                        return &threads[i];
        return current_thread; // None found
}


// Terminate thread t. If t is an unused thread this syscall is a NOP
void terminate(struct thread *t)
{
        struct process *p = t->process;
        if (p) {
                /* Terminate process if it has no more threads */
                if (!--p->number_of_threads) {
                        p->state = PROCESS_NEW;
                        p->number_of_threads = 0;
                }
                t->process = 0;
        }
}

// Assigns thread t to the next available process
// Returns ALL_OK on success, ERROR on failure
int assign_to_process(struct thread *t)
{
        int i;
        struct process *p = 0;

        for (i = 0; i < MAX_PROCESSES; ++i)
                if (processes[i].state == PROCESS_NEW) {
                        p = &processes[i];
                        break;
                }
        if (!p)
                return ERROR; // Unable to find a new process

        t->process = p;
        p->state = PROCESS_READY; // p gets promoted to READY state
        p->number_of_threads++;
        return ALL_OK;
}


// Finds an available thread that isn't being used
// Returns 0 if not found
struct thread *get_new_thread()
{
        int i;
        for (i = 0; i < MAX_THREADS; ++i)
                if (!threads[i].process)
                        return &threads[i];
        return 0;
}


void kernel_late_init(void)
{
        /* Set up the first thread. For now we do not set up a process. That is
           for you to do later. */
        threads[0].eip = executable_table[0];
        assign_to_process(&threads[0]);

        /* Go to user space. */
        go_to_user_space();
}

void handle_system_call(void)
{
        switch (current_thread->eax) {
                case SYSCALL_VERSION:
                        {
                                current_thread->eax = 0x00010000;
                                break;
                        }
                case SYSCALL_PRINTS:
                        {
                                kprints((char *) current_thread->edi);
                                current_thread->eax = ALL_OK;
                                break;
                        }

                case SYSCALL_CREATEPROCESS:
                        {
                                /* Find a new thread */
                                struct thread *t = get_new_thread();

                                if (t) {
                                        int index = current_thread->edi;
                                        t->eip =
                                                executable_table[index];
                                        current_thread->eax =
                                                assign_to_process(t);
                                } else {
                                        current_thread->eax = ERROR;
                                }
                                break;
                        }
                case SYSCALL_TERMINATE:
                        {
                                terminate(current_thread);
                                break;
                        }
                case SYSCALL_YIELD:
                        {
                                current_thread->eax = ALL_OK;
                                current_thread = yield();
                                // TODO: Change process state?
                                break;
                        }
                default:
                        {
                                /* Unrecognized system call. Not good. */
                                current_thread->eax = ERROR_ILLEGAL_SYSCALL;
                        }
        }

        go_to_user_space();
}

/* Add more definitions here if you need. */