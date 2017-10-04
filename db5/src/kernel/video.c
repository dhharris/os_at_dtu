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

/* Index of the current screen position */
int index = 0;

// Helper function to print a char to the VGA screen
// Prints the character and then moves the screen pointer
void kprintc(char c)
{
        (*screen_pointer)[index++].character = c;
        if (c == '\n') // Move to next row
                // We know we are at the start of a row if index % ncols == 0
                while (index % MAX_COLS)
                        index++;
}

/**
 * Print a C string to the VGA screen
 */
void kprints(const char *string)
{
        /* Implement me! */
}

/**
 * Writes a 32 bit unsigned value in hex to the VGA screen
 */
void kprinthex(const register uint32_t value)
{
        /* Implement me! */
}
