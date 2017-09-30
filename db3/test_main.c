#include <stdio.h>
#include <stdlib.h>
#include "include/tests.h"

int tests_run = 0;

static char *all_tests()
{
        mu_run_test(test_eval_b_should_increase_counter);
        mu_run_test(test_reset_should_set_counter_to_zero);
        mu_run_test(test_eval_a_should_add_to_linked_list);
        mu_run_test(test_eval_a_should_increment_counter);
        mu_run_test(test_eval_c_should_increment_counter);
        mu_run_test(test_eval_c_with_small_list_should_remove_tail_node);
        mu_run_test(test_eval_c_with_large_list_should_remove_tail_node);

        mu_run_test(test_sinit_should_set_correct_size);
        mu_run_test(test_sdestroy_should_set_size_to_zero);
        mu_run_test(test_spush_should_add_to_stack);
        mu_run_test(test_spush_with_full_stack_should_double_size);
        mu_run_test(test_spop_should_return_top_element);
        mu_run_test(test_spop_should_remove_top_element);

        mu_run_test(test_strlen_should_return_correct_length);

        mu_run_test(
                test_write_int_with_many_digits_should_write_correct_bytes
        );
        mu_run_test(test_write_int_should_write_correct_bytes);
        mu_run_test(
                test_write_int_with_negative_number_should_write_correct_bytes
        );
        mu_run_test(test_getchar_should_read_correct_character);
        mu_run_test(test_getchar_should_return_EOF_on_error);
        mu_run_test(test_putchar_should_write_correct_character);

        return 0;
}

int main(int argc, char **argv)
{
        char *result = all_tests();
        if (result) {
                printf("%s\n", result);
        }
        else
                printf("ALL TESTS PASSED\n");
        printf("Tests run: %d\n", tests_run);
        return result != 0;
}
