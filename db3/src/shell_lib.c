#include <stdio.h>
#include <stdlib.h>
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
                printf("%d", head->value);
                if (head->next)
                        putchar(',');
                head = head->next;
        }
        putchar('\n');
}


void reset(Collection *col)
{
        col->head = col->tail = NULL;
        col->counter = 0;
}


void eval_a(Collection *col)
{
        if (!col->head) {
                col->head = malloc(sizeof(node_t));
                col->head->value = col->counter;
                col->head->next = NULL;
                col->tail = col->head;
        } else {
                col->tail->next = malloc(sizeof(node_t));
                col->tail = col->tail->next;
                col->tail->value = col->counter;
                col->tail->next = NULL;
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
                col->head = col->tail = NULL;
        } else {
                while (p->next != col->tail)
                        p = p->next;
                // Now p points to node before tail
                free(col->tail);
                col->tail = p;
                col->tail->next = NULL;
        }
        eval_b(col);
}


int parse_character(Collection *col, char c)
{
        switch (c) {
                case 'a': eval_a(col);
                          break;
                case 'b': eval_b(col);
                          break;
                case 'c': eval_c(col);
                          break;
                default:
                          print_list(col->head);
                          return 1;
        }
        return 0;
}
