/**
 * @file    bounce_adc.c
 * @author
 * @date
 */

// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course libraries.
#include <BOARD.h>
#include <Adc.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init();
    ADC_Init();

    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 3 (bounce_adc)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );

    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    while (1);
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new
 * ADC reading is available in the ADC buffer SFRs, ADC1BUF0 - ADC1BUF7.
 * 
 * It should not be called, and should communicate with main code only by using
 * module-level variables.
 */
void HAL_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (hadc == &hadc1) {
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    

    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
