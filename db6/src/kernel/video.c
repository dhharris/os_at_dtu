/* Copyright (c) 1997-2017, FenixOS Developers
   All Rights Reserved.

   This file is subject to the terms and conditions defined in
   file 'LICENSE', which is part of this source code package.
   */

/*! \file video.c This file holds implementations of functions
  presenting output to the VGA screen. */
#include <stdint.h>

/* Max dimensions of the VGA screen */
#define MAX_COLS (80)
#define MAX_ROWS (25)

typedef struct {
        unsigned char character; /*!< The character part of the byte tuple
                                   used for each screen position. */
        unsigned char attribute; /*!< The attribute part of the byte tuple
                                   used for each screen position. */
} screen_position; /*!< Defines a VGA text mode screen position. */

typedef struct {
        /*!< The VGA screen. It is organized as a two dimensional array. */
        screen_position positions[MAX_ROWS][MAX_COLS];
} screen; /*!< Defines a VGA text mode screen. */

/*! points to the VGA screen. */
static screen* const screen_pointer = (screen*) 0xB8000;

/* Coordinates of the current screen position */
int posx = 0;
int posy = 0;

/* Array of possible hex characters */
static char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};


// Helper function to convert unsigned integer to hex string and store the
// result in buf. Assume that buf has enough space to hold the string.
// Returns the length of buf
int uitohex(uint32_t n, char *buf)
{

        int len, i;
        len = 0;

        do {
                buf[len++] = hex[n & 0xF];
                n >>= 4;
        } while (n);

        // Reverse the order
        for (i = 0; i < len / 2; ++i) {
                buf[i] ^= buf[len - i - 1];
                buf[len - i - 1] ^= buf[i];
                buf[i] ^= buf[len - i - 1];
        }

        buf[len] = '\0'; // Null terminate
        return len;
}

// Helper function to determine whether a character can be printed
int isprint(int c)
{
        return c >= 32 && c <= 126;
}


// Helper function to move all characters on the screen up one row
void scroll_screen()
{
        int x, y;
        for (y = 0; y < MAX_ROWS; ++y)
                for (x = 0; x < MAX_COLS; ++x)
                         screen_pointer->positions[y][x].character =
                                 screen_pointer->positions[y + 1][x].character;
}

// Helper function to print a char to the VGA screen
// Prints the character and then moves the screen pointer
void kprintc(char c)
{
        if (isprint(c))
                screen_pointer->positions[posy][posx++].character = c;

        // Move to next row if we are at the end or newline character is drawn
        if (posx >= MAX_COLS || c == '\n') {
                posx = 0;
                posy++;
        }
        // Implement terminal scrolling, i.e. in the case that the screen
        // fills up, move all rows up one row and discard the upper most,
        // leaving a blank row at the bottom ready to be filled up with chars
        if (posy >= MAX_ROWS) {
                scroll_screen();
                posy = MAX_ROWS - 1;
        }
}

/**
 * Print a C string to the VGA screen
 */
void kprints(const char *string)
{
        int i = 0;
        while (string[i])
                kprintc(string[i++]);
}


/**
 * Writes a 32 bit unsigned value in hex to the VGA screen
 */
void kprinthex(const register uint32_t value)
{
        /* Implement me! */
        char buf[9]; // enough for 32 bit integer
        uitohex(value, buf);
        kprints("0x");
        kprints(buf);
}
