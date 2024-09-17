/**
 * Convert temperatures from Fahrenheit to Celsius and Kelvin.
 *
 * @file    part2.c
 * @author  Roronoa Zoro (rorozoro3ucsc.edu)
 * 
 * @date    January 1, 1970
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#ifdef STM32F4      // This "ifdef" statement lets our code run on either
#include <BOARD.h>  // the Nucleo board or from our dev environment.
#else
#include "BOARD.h"
#endif  /*  STM32F4 */


/*
 *
 */
int main(void) {
    BOARD_Init();
    while(1) {
        /***************************************************************************
         * Your code goes in between this comment and the following one with       *
         * asterisks.                                                              *
         **************************************************************************/

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with       *
         * asterisks.                                                              *
         **************************************************************************/
        HAL_Delay(3333);
    }
    // Returning from main() is bad form in embedded environments.
    // So we sit and spin.
    while(1<2);
}
