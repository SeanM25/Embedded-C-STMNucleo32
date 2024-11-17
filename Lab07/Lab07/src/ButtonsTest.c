/**
 * @file    ButtonsTest.c
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
#include "stm32f4xx_hal.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

static uint8_t buttonsWorking;

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init();
    Timers_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 4 (ButtonsTest). Compiled on %s %s.\n",
        __TIME__,
        __DATE__
    );
    
   // printf("Please press some buttons!\n");

   // Test Harness for Buttons

   // What follows below is the intial state of each of the buttons which is blank since nothing has been pressed

   char * button_1 = ":------"; 

   char * button_2 = ":------";

   char * button_3 = ":------";

   char * button_4 = ":------";

   while(1){

    if(buttonsWorking != BUTTON_EVENT_NONE){ // If a button event is detected

    if(buttonsWorking & BUTTON_EVENT_1DOWN){  // And the Button 1 is down 

        button_1 = "Down"; // Button 1 displays down
    }

    if(buttonsWorking & BUTTON_EVENT_1UP){

        button_1 = "Up"; // Otherwise Button 1 displays up
    }


    if(buttonsWorking & BUTTON_EVENT_2DOWN){ // If button 2 down

        button_2 = "Down"; // Display down
    }

    if(buttonsWorking & BUTTON_EVENT_2UP){

        button_2 = "Up"; // Otherwise button 2 up
    }


    if(buttonsWorking & BUTTON_EVENT_3DOWN){ // If button 3 down

        button_3 = "Down"; // Display down
    }

    if(buttonsWorking & BUTTON_EVENT_3UP){

        button_3 = "Up"; // Otherwise button 3 is up
    }

    if(buttonsWorking & BUTTON_EVENT_4DOWN){ // If button 4 is down

        button_4 = "Down"; // Display Down
    }

    if(buttonsWorking & BUTTON_EVENT_4UP){

        button_4 = "Up"; // Otherwise Display button 4 up
    }

    }

        buttonsWorking = BUTTON_EVENT_NONE; // Reset button event flag

        printf("Event 1:%s 2:%s 3:%s 4:%s\n", button_1, button_2, button_3, button_4); // Print test harness specified in manual

   }


    
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/

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

__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE); // Clear the flag

buttonsWorking = Buttons_CheckEvents(); // Call button event checker




    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
