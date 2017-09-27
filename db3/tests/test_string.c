#include "../include/string.h"
#include "../include/tests.h"

char *test_strlen_should_return_correct_length()
{
        const char *test_str = "test";
        mu_assert("Error, strlen(test_str) != 4", strlen(test_str) == 4);
        return 0;
}
