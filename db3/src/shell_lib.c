#include "../include/io.h"
#include "../include/mem.h"
#include "../include/shell_lib.h"


void clear_list(node_t *head)
{
        if (!head)
                return;
        clear_list(head->next);
        free(head);
}


void print_list(node_t *head)
{
        while (head) {
                write_int(STDOUT_FILENO, head->value);
                if (head->next)
                        putchar(',');
                head = head->next;
        }
        putchar('\n');
}


void reset(Collection *col)
{
        col->head = col->tail = 0;
        col->counter = 0;
}


void eval_a(Collection *col)
{
        if (!col->head) {
                col->head = malloc(sizeof(node_t));
                col->head->value = col->counter;
                col->head->next = 0;
                col->tail = col->head;
        } else {
                col->tail->next = malloc(sizeof(node_t));
                col->tail = col->tail->next;
                col->tail->value = col->counter;
                col->tail->next = 0;
        }
        eval_b(col);
}


void eval_b(Collection *col)
{
        ++(col->counter);
}


void eval_c(Collection *col)
{
        node_t *p = col->head;
        if (p == col->tail) {
                // One or no nodes
                free(col->head);
                col->head = col->tail = 0;
        } else {
                while (p->next != col->tail)
                        p = p->next;
                // Now p points to node before tail
                free(col->tail);
                col->tail = p;
                col->tail->next = 0;
        }
        eval_b(col);
}

