/**
 * @file    bounce_switch.c
 * @author
 * @date
 */

// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course libraries.
#include <BOARD.h>
#include <Timers.h>

#include "Buttons.h"
#include "Leds_Lab07.h"
#include "stm32f4xx_hal.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

#define TIME_1 2000

struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

struct Timer Timer1 = {FALSE, TIME_1};




// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init();
    Timers_Init();
    LEDs_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 2 (bounce_switch)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );
    
    printf("Please press some buttons!\n");
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
    while (1){

           printf("%d\n", Timer1.event);
        
        if(Timer1.event == 1){

            printf("AAA\n");

           // Timer1.event = FALSE;


        }

       //printf("%d\n", Timer1.event);
    }
}

/**
 * This is the interrupt for the Timer2 peripheral. It should check for button
 * events and store them in a module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim == &htim2) {
    /***************************************************************************
     * Your code goes in between this comment and the following one with 
     * asterisks.
     **************************************************************************/

Timer1.timeRemaining--;

if(Timer1.timeRemaining == 0){


    //printf("Yay!\n");

    Timer1.event = TRUE;

   Timer1.timeRemaining = TIME_1;
}





    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
