#include "minunit.h"

/* Collection tests */
char *test_eval_b_should_increase_counter();
char *test_reset_should_set_counter_to_zero();
char *test_eval_a_should_add_to_linked_list();
char *test_eval_a_should_increment_counter();
char *test_eval_c_should_increment_counter();
char *test_eval_c_with_small_list_should_remove_tail_node();
char *test_eval_c_with_large_list_should_remove_tail_node();

/* Stack tests */
char *test_sinit_should_set_correct_size();
char *test_sdestroy_should_set_size_to_zero();
char *test_spush_should_add_to_stack();
char *test_spush_with_full_stack_should_double_size();
char *test_spop_should_return_top_element();
char *test_spop_should_remove_top_element();

/* String tests */
char *test_strlen_should_return_correct_length();

/* io tests */
char *test_write_int_should_write_correct_bytes();
char *test_write_int_with_many_digits_should_write_correct_bytes();
