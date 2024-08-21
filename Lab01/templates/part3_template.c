/*
 * Hello, OLED!
 *
 * File:    part3.c
 * Author:  Roronoa Zoro (rorozoro3ucsc.edu)
 * 
 * Created on January 1, 1970.
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
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

