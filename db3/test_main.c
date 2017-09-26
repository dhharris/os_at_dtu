#include <stdio.h>
#include "include/tests.h"

static char *all_tests()
{
        mu_run_test(test_eval_b_should_increase_counter);
        mu_run_test(test_reset_should_set_counter_to_zero);
        mu_run_test(test_eval_a_should_add_to_linked_list);
        mu_run_test(test_eval_a_should_increment_counter);
        mu_run_test(test_eval_c_should_increment_counter);
        mu_run_test(test_eval_c_with_small_list_should_remove_tail_node);
        mu_run_test(test_eval_c_with_large_list_should_remove_tail_node);
        return 0;
}

int main(int argc, char **argv)
{
        char *result = all_tests();
        if (result)
                printf("%s\n", result);
        else
                printf("ALL TESTS PASSED\n");
        printf("Tests ran: %d\n", tests_run);
        return result != 0;
}
