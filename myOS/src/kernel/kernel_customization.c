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

unsigned long memory_pages_used;

// Return the next available ready thread
struct thread *next_thread()
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

/* Free the page frame at index if this process is allowed to do so */
void free_page_frame(int index)
{
        if (page_frame_table[index].owner == current_thread->process
                        && page_frame_table[index].free_is_allowed) {
                page_frame_table[index].owner = 0;
                memory_pages_used -= 1;
        }
}

void destroysemaphore(int index)
{
        semaphores[index].in_use = 0;
}

void yield()
{
        current_thread->process->state = PROCESS_READY;
        current_thread = next_thread();
        current_thread->process->state = PROCESS_RUNNING;
}


// Terminate thread t. If t is an unused thread this syscall is a NOP
void terminate(struct thread *t)
{
        struct process *p = t->process;
        int i;

        if (p) {
                /* Terminate process if it has no more threads */
                if (!(--p->number_of_threads)) {
                        p->state = PROCESS_NEW;

                        // Remove any semaphores the process is using
                        for (i = 0; i < MAX_SEMAPHORES; ++i)
                                if (semaphores[i].owner == p)
                                        destroysemaphore(i);
                        // Free up memory used by the process
                        for (i = 0; i < MAX_NUMBER_OF_FRAMES; ++i)
                                free_page_frame(i); // only will free if owned
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

int is_valid_exe(int index)
{
        return index >= 0 && index < EXECUTABLE_TABLE_SIZE;
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

int createsemaphore(int max)
{
        int i;

        for (i = 0; i < MAX_SEMAPHORES; ++i) {
                if (!semaphores[i].in_use) {
                        struct semaphore *sem = &semaphores[i];
                        sem->in_use = 1;
                        sem->owner = current_thread->process;
                        sem->count = sem->max = max;
                        return i;
                }
        }
        return ERROR; // Free semaphore not found
}

void semaphoreup(int index)
{
        struct semaphore *sem = &semaphores[index];

        // Only threads of the owning process can use the semaphore
        if (sem->owner != current_thread->process) {
                current_thread->eax = ERROR;
        } else if (sem->count >= sem->max) {
                yield(); // Block until we can increment
        } else {
                sem->count++;
                current_thread->eax = ALL_OK;
        }
}

void semaphoredown(int index)
{
        struct semaphore *sem = &semaphores[index];

        // Only threads of the owning process can use the semaphore
        if (sem->owner != current_thread->process) {
                current_thread->eax = ERROR;
        } else if (sem->count <= 0) {
                yield(); // Block until we can decrement
        } else {
                sem->count--;
                current_thread->eax = ALL_OK;
        }
}

void *malloc(uint32_t nbytes)
{
        uint32_t npages = (nbytes + 4095) >> 12;

        /* Find first available memory block */
        uint32_t start, end;
        start = end = 0;

        for (start = 0; start + npages < MAX_NUMBER_OF_FRAMES; ++start) {
                for (end = start; end < start + npages; ++end)
                        if (page_frame_table[end].owner)
                                break; // Not available
                if (end == start + npages)
                        break; // We found a valid block
                else
                        start = end + 1;
        }
        if (start + npages >= MAX_NUMBER_OF_FRAMES)
                return 0;

        /* Set memory metadata */
        uint32_t i;

        for (i = start; i < end; ++i) {
                page_frame_table[i].owner = current_thread->process;
                page_frame_table[i].start = start;
                page_frame_table[i].free_is_allowed = 1;
        }
        memory_pages_used += npages;

        return (void*)&page_frame_table[start];
}


void free(void *p)
{
        if (!p)
                return;
        int start = ((struct page_frame*)p)->start;
        int i;
        for (i = start; i < MAX_NUMBER_OF_FRAMES; ++i) {
                if (page_frame_table[i].start == start)
                        free_page_frame(i);
                else
                        break; // Past end of memory or invalid address
        }
}

void kernel_late_init(void)
{
        /* Set up the first thread. For now we do not set up a process. That is
           for you to do later. */
        threads[0].eip = executable_table[0];
        assign_to_process(&threads[0]);
        threads[0].process->state = PROCESS_RUNNING;

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
                case SYSCALL_PRINTHEX:
                        {
                                kprinthex((int) current_thread->edi);
                                current_thread->eax = ALL_OK;
                                break;
                        }
                case SYSCALL_CREATEPROCESS:
                        {
                                /* Find a new thread */
                                struct thread *t = get_new_thread();
                                int index = current_thread->edi;

                                if (t && is_valid_exe(index)) {
                                        t->eip =
                                                executable_table[index];
                                        current_thread->eax =
                                                assign_to_process(t);
                                } else {
                                        current_thread->eax = ERROR;
                                }
                                break;
                        }
                case SYSCALL_CREATETHREAD:
                        {
                                /* Set up new thread associated with the
                                 * current thread's process
                                 */
                                struct thread *t = get_new_thread();
                                if (!t) {
                                        current_thread->eax = ERROR;
                                        break;
                                }
                                t->process = current_thread->process;
                                t->process->number_of_threads++;
                                t->eip = current_thread->edi;
                                t->esp = current_thread->esi;
                                current_thread->eax = ALL_OK;
                                break;
                        }
                case SYSCALL_TERMINATE:
                        {
                                terminate(current_thread);
                                yield();
                                break;
                        }
                case SYSCALL_YIELD:
                        {
                                yield();
                                current_thread->eax = ALL_OK;
                                break;
                        }
                case SYSCALL_CREATESEMAPHORE:
                        {
                                int count = current_thread->edi;
                                current_thread->eax =
                                        createsemaphore(count);
                                break;
                        }
                case SYSCALL_SEMAPHOREUP:
                        {
                                semaphoreup(current_thread->edi);
                                break;
                        }
                case SYSCALL_SEMAPHOREDOWN:
                        {
                                semaphoredown(current_thread->edi);
                                break;
                        }
                case SYSCALL_ALLOCATE:
                        {
                                int nbytes = current_thread->edi;
                                current_thread->eax = (uint32_t)malloc(nbytes);
                                break;
                        }
                case SYSCALL_FREE:
                        {
                                free((void*)current_thread->edi);
                                // Invalid free is a no-op, so always ALL_OK
                                current_thread->eax = ALL_OK;
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
