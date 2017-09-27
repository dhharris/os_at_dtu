#include "../include/string.h"

unsigned long strlen(const char *s)
{
        unsigned long len = 0;

        while(*s) {
                ++len;
                ++s;
        }
        return len;
}
