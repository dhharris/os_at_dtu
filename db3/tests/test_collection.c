#include <stdlib.h>
#include "../include/shell_lib.h"
#include "../include/tests.h"


int tests_run = 0;


Collection *before_each()
{
        Collection *col = malloc(sizeof(Collection));
        reset(col);
        return col;
}


void after_each(Collection *col)
{
        clear_list(col->head);
        free(col);
}


char *test_reset_should_set_counter_to_zero()
{
        Collection *col = before_each();
        mu_assert("error, counter != 0", col->counter == 0);
        after_each(col);
        return 0;
}


char *test_eval_b_should_increase_counter()
{
        Collection *col = before_each();
        eval_b(col);
        mu_assert("error, counter != 1", col->counter == 1);
        after_each(col);
        return 0;
}


char *test_eval_a_should_increment_counter()
{
        Collection *col = before_each();
        eval_a(col);
        mu_assert("error, col->counter != 1", col->counter == 1);
        after_each(col);
        return 0;
}


char *test_eval_a_should_add_to_linked_list()
{
        Collection *col = before_each();
        eval_a(col);
        mu_assert("error, col->head->value != 0", col->head->value == 0);
        after_each(col);
        return 0;
}


char *test_eval_c_with_small_list_should_remove_tail_node()
{
        Collection *col = before_each();
        eval_a(col);
        eval_c(col);
        mu_assert("error, col->head != NULL", col->head == NULL);
        after_each(col);
        return 0;
}


char *test_eval_c_with_large_list_should_remove_tail_node()
{
        Collection *col = before_each();
        int i;

        for (i = 0; i < 100; ++i)
                eval_a(col);
        eval_c(col);
        mu_assert("error, col->tail->value != 98", col->tail->value == 98);
        after_each(col);
        return 0;
}


char *test_eval_c_should_increment_counter()
{
        Collection *col = before_each();
        eval_c(col);
        mu_assert("error, col->counter != 1", col->counter == 1);
        after_each(col);
        return 0;
}
