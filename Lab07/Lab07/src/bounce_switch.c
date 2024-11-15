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

# define left 0

#define right 1

#define testtime 30
// **** Declare any datatypes here ****


struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

//static struct Timer T1 = {FALSE, testtime};

static struct Timer T1;



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

   char current_led = 0x01;

    char left_led = 0x01;

   char right_led = 0x80;

    char state = -1;

   // T1.event = FALSE;


    while (1){

        if(T1.event == TRUE){

 //printf("%d\n", current_led);

 LEDs_Set(current_led);

            if(current_led == left_led){

                state = right;

            }

            if(current_led == right_led){

                state = left;

            }
            

            if(state == right){

                current_led <<= 1;

               }

               if(state == left){

                current_led >>= 1;

               }


            }

           T1.event = FALSE;


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

u_int8_t switch_state = SWITCH_STATES();

u_int8_t count = 0;   

__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);

/*

T1.timeRemaining--;

if(T1.timeRemaining == 0){

    T1.event = TRUE;

    T1.timeRemaining = testtime;

}
*/

T1.timeRemaining--;

if(T1.timeRemaining <= 0){

    T1.event = TRUE;

if(switch_state & SW5_STATE()){


        count |= 1;

}

if(switch_state & SW6_STATE()){


        count |= 1;

}

T1.timeRemaining = ((SWITCH_STATES() + 1) * count);

}



    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
