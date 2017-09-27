#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/tests.h"
#include "../include/stack.h"


Stack *stack_before_each()
{
        Stack *s = malloc(sizeof(Stack));
        sinit(s, 10);
        return s;
}

void stack_after_each(Stack *s)
{
        sdestroy(s);
        free(s);
}

char *test_sinit_should_set_correct_size()
{
        Stack s;
        sinit(&s, 10);
        mu_assert("Error, s.size != 10", s.size == 10);
        sdestroy(&s);
        return 0;
}

char *test_sdestroy_should_set_size_to_zero()
{
        Stack s;
        sinit(&s, 10);
        sdestroy(&s);
        mu_assert("Error, s.size != 0", s.size == 0);
        return 0;
}

char *test_spush_should_add_to_stack()
{
        Stack *s = stack_before_each();
        spush(s, 1);
        mu_assert("Error, s->contents[0] != 1", s->contents[0] == 1);
        stack_after_each(s);
        return 0;
}

char *test_spush_with_full_stack_should_double_size()
{
        Stack *s = stack_before_each();
        int i;
        for (i = 0; i < 11; ++i)
                spush(s, 1);
        mu_assert("Error, s->size != 20", s->size == 20);
        stack_after_each(s);
        return 0;
}

char *test_spop_should_return_top_element()
{
        Stack *s = stack_before_each();
        spush(s, 1);
        spush(s, 2);
        int elem = spop(s);
        mu_assert("Error, elem != 2", elem == 2);
        stack_after_each(s);
        return 0;
}

char *test_spop_should_remove_top_element()
{
        Stack *s = stack_before_each();
        spush(s, 1);
        spush(s, 2);
        spop(s);
        mu_assert("Error, s->contents[0] != 1", s->contents[0] == 1);
        stack_after_each(s);
        return 0;
}
