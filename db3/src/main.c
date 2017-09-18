#include <stdio.h>
#include <stdlib.h>
#include "shell_lib.h"


int main()
{
        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        Collection *col = malloc(sizeof(Collection));
        reset(col);

        while ((linelen = getline(&line, &linecap, stdin)) > 0) {
                line[linelen - 1] = 0; // Remove newline character
                char *p = line;
                int status = 0;

                while (*p && !status)
                        status = parse_character(col, *p++);
                if (status)
                        break;
        }

        clear_list(col->head);
        free(col);
        free(line);
        return 0;
}
