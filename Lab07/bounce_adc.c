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
#include <Oled.h>
#include <OledDriver.h>

// User libraries


// **** Set macros and preprocessor directives ****

#define winSIZE 3 // Size of Window

#define adcMAX 4095.0 // Max value from adc

#define adcMIN 0 // Min value from adc

#define hund 100

// **** Declare any datatypes here ****

struct AdcResult{ // Given adc struct

uint8_t event; // event member

uint16_t voltage; // voltage member

};

// **** Define global, module-level, or external variables here ****
volatile uint16_t adc_val = 0; // Given intial ADC val
volatile uint8_t hasNewADC = FALSE; // Given inital code

static struct AdcResult myADC; // Global struct to read ADC val
// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init(); // Turn on board
    ADC_Init(); // Turn on adc
    OledInit(); // Turn on OLED screen
    
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
    //uint32_t loopCount = 0;

   myADC.event = TRUE;

char* result [50]; // string to store results from Adc and percentage

    while (1)
    {

        if(myADC.event){

           int percentage = (myADC.voltage / adcMAX) * hund; // Get Percentage of ADC value

          //printf("ADC: %d Percentage: %d\n", myADC.voltage, percentage); // Print results on the terminal

         sprintf(result, "ADC: %d Percentage: %d%%", myADC.voltage, percentage); // Gets results and stores in a string for OLED screen
            
            OledClear(OLED_COLOR_BLACK); // Clear OLED

            OledDrawString(result); // Display results

            OledUpdate(); // Output to OLED screen
        }

        myADC.event = FALSE; // rest event flag

        /* Given intial code
        if (hasNewADC) //Wait until the ISR signals that we have something new to report
        {
            hasNewADC = FALSE; //Reset the flag so that we don't recycle the same measurement
            
           // printf("%09ld: ADC: %d\r\n", loopCount, adc_val); //Prints the elapsed time in timer ticks and the ADC value
            loopCount++;
        }
        */
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

    adc_val = HAL_ADC_GetValue (&hadc1); // Get the result of the current conversion

    if(adc_val - myADC.voltage >= winSIZE || myADC.voltage - adc_val >= winSIZE){ // If outside the window

        myADC.event = TRUE; // execute an event

    }

    if(adc_val + winSIZE >= adcMAX){ // If near max value


        myADC.voltage = adcMAX; // voltage = max threshold


    } else if(adc_val - winSIZE <= adcMIN){ // If near min value

            myADC.voltage = adcMIN; // voltage = min adv value
    } else{

        myADC.voltage =  adc_val; // otherwise voltage is current adc reading

    }

    HAL_ADC_Start_IT(&hadc1); //Start the next conversion

}

