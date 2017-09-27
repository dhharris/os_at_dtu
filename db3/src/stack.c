#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

void sinit(Stack *s, int size)
{
        s->contents = malloc(sizeof(int) * size);
        s->size = size;
        s->top = -1; // Empty
}

void sdestroy(Stack *s)
{
        free(s->contents);
        s->contents = NULL;
        s->size = 0;
        s->top = -1; // Empty
}

int sisempty(Stack *s)
{
        return s->top < 0;
}


int sisfull(Stack *s)
{
        return s->top >= s->size - 1;
}

void spush(Stack *s, int element)
{
        if (sisfull(s)) {
                /* Double the size of the contents of the stack and copy
                 * everything over
                 */
                int *new_contents = malloc(sizeof(int) * s->size * 2);
                int i;

                for (i = 0; i < s->size; ++i)
                        new_contents[i] = s->contents[i];
                free(s->contents);
                s->contents = new_contents;
                s->size *= 2;
        }
        s->contents[++s->top] = element;
}

int spop(Stack *s)
{
        if (sisempty(s)) {
                fprintf(stderr, "Error: cannot pop from empty stack");
                sdestroy(s);
                exit(1);
        }
        return s->contents[s->top--];
}
