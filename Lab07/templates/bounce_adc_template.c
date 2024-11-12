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
volatile uint16_t adc_val = 0;
volatile uint8_t hasNewADC = FALSE;
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
    uint32_t loopCount = 0;
    while (1)
    {
        if (hasNewADC) //Wait until the ISR signals that we have something new to report
        {
            hasNewADC = FALSE; //Reset the flag so that we don't recycle the same measurement
            printf("%09d: ADC: %d\r\n", loopCount, adc_val); //Prints the elapsed time in timer ticks and the ADC value
            loopCount++;
        }
    }
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new
 * ADC reading is available in the ADC buffer
 * 
 * It should not be called, and should communicate with main code only by using
 * module-level variables.
 */
void ADC_IRQHandler(void)
{
    adc_val = HAL_ADC_GetValue (&hadc1); //Get the result of the current conversion
    hasNewADC = TRUE; //Set the flag to indicate a new value is available
    HAL_ADC_Start_IT(&hadc1); //Start the next conversion
}

