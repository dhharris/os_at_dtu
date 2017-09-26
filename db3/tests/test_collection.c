#include <stdlib.h>
#include "../include/shell_lib.h"
#include "../include/tests.h"


Collection *collection_before_each()
{
        Collection *col = malloc(sizeof(Collection));
        reset(col);
        return col;
}


void collection_after_each(Collection *col)
{
        clear_list(col->head);
        free(col);
}


char *test_reset_should_set_counter_to_zero()
{
        Collection *col = collection_before_each();
        mu_assert("error, counter != 0", col->counter == 0);
        collection_after_each(col);
        return 0;
}


char *test_eval_b_should_increase_counter()
{
        Collection *col = collection_before_each();
        eval_b(col);
        mu_assert("error, counter != 1", col->counter == 1);
        collection_after_each(col);
        return 0;
}


char *test_eval_a_should_increment_counter()
{
        Collection *col = collection_before_each();
        eval_a(col);
        mu_assert("error, col->counter != 1", col->counter == 1);
        collection_after_each(col);
        return 0;
}


char *test_eval_a_should_add_to_linked_list()
{
        Collection *col = collection_before_each();
        eval_a(col);
        mu_assert("error, col->head->value != 0", col->head->value == 0);
        collection_after_each(col);
        return 0;
}


char *test_eval_c_with_small_list_should_remove_tail_node()
{
        Collection *col = collection_before_each();
        eval_a(col);
        eval_c(col);
        mu_assert("error, col->head != NULL", col->head == NULL);
        collection_after_each(col);
        return 0;
}


char *test_eval_c_with_large_list_should_remove_tail_node()
{
        Collection *col = collection_before_each();
        int i;

        for (i = 0; i < 100; ++i)
                eval_a(col);
        eval_c(col);
        mu_assert("error, col->tail->value != 98", col->tail->value == 98);
        collection_after_each(col);
        return 0;
}


char *test_eval_c_should_increment_counter()
{
        Collection *col = collection_before_each();
        eval_c(col);
        mu_assert("error, col->counter != 1", col->counter == 1);
        collection_after_each(col);
        return 0;
}
