#include "include/shell_lib.h"
#include "include/io.h"
#include "include/mem.h"


/**
 * Execute the command given by c
 * Returns whether the program should keep running
 */
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
                          return 0;
        }
        return 1;
}


int main()
{
        Collection col;
        reset(&col);

        int running = 1;
        char c;

        while (running && (c = getchar())!= EOF)
                running = parse_character(&col, c);

        clear_list(col.head);
        return 0;
}
