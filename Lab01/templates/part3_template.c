/*
 * @file    part3.c
 * @author  Roronoa Zoro (rorozoro3@ucsc.edu)
 * @brief   Hello, OLED!
 * 
 * @date    January 1, 1970
 */

#include <stdio.h>
#include <stdlib.h>

#include <BOARD.h>
#include <Oled.h>

/*
 *
 */
int main(void) {
    BOARD_Init();

    /***************************************************************************
     * Your code goes in between this comment and the following one with       *
     * asterisks.                                                              *
     **************************************************************************/

    /***************************************************************************
     * Your code goes in between this comment and the preceding one with       *
     * asterisks.                                                              *
     **************************************************************************/

    BOARD_End();    // Handles cleanup of the system;
    while(1);       // if embedded, we should never exit.
}

