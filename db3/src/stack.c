#include "../include/stack.h"
#include "../include/io.h"
#include "../include/mem.h"

void sinit(Stack *s, int size)
{
        s->contents = malloc(sizeof(int) * size);
        s->size = size;
        s->top = -1; // Empty
}

void sdestroy(Stack *s)
{
        free(s->contents);
        s->contents = 0;
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
                write(STDERR_FILENO, "Err: cannot pop from empty stack\n", 34);
                return s->top;
        }
        return s->contents[s->top--];
}
