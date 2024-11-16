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

# define left 0 // Constant for moving LEDs left

#define right 1 // Same as above but right

#define testtime 30 // Test variable used to make sure the LEDs were moving back and forth properly

// **** Declare any datatypes here ****


struct Timer { // Given timer struct with members event and time remaining
  uint8_t event;
  int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

//static struct Timer Timer1 = {FALSE, testtime}; // Test struct used to test LED oscillation logic

static struct Timer Timer1; // Timer 1 struct



// **** Declare function prototypes ****


int main(void)
{
    BOARD_Init(); // Board On
    Timers_Init(); // Timers On
    LEDs_Init(); // LEDs On
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

   char current_led = 0x01; // Current LED pos set initially to the first led

    char left_led = 0x01; // left most led in our 8 LED array

   char right_led = 0x80; // Right most LED in array

    char state = -1; // State variable for switching logic

   // Timer1.event = FALSE;


    while (1){ // Run Indefinitely in an Embedded context

        if(Timer1.event == TRUE){ // If there's an Timer event

 //printf("%d\n", current_led); // Used to test LED swirching without using the lights

 LEDs_Set(current_led); // Turn on current LED

            if(current_led == left_led){ // If LED at left most position

                state = right; // We want to go right

            }

            if(current_led == right_led){ // If LED at right most position

                state = left; // Want to go left

            }
            

            if(state == right){ // If were going right

                current_led <<= 1; // Shift LED position right by one each time

               }

               if(state == left){ // If going left

                current_led >>= 1; // Shift LED position left by 1 each time

               }


            }

           Timer1.event = FALSE; // Clear event flag


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

u_int8_t switch_state = SWITCH_STATES() + 1; // Present state of the LEDs incremented by 1 so it doesn't return 0

u_int8_t count = 0; // Counting variable initilazed to 0

uint8_t num = 5; // A constant number which gave me good switching results

__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE); // Clear interrupt flag

/*

Timer1.timeRemaining--; // Test Code for LED oscillation

if(Timer1.timeRemaining == 0){

    Timer1.event = TRUE;

    Timer1.timeRemaining = testtime;

}
*/

Timer1.timeRemaining--; // Decrement Timer1

if(Timer1.timeRemaining <= 0){ // If time = 0

    Timer1.event = TRUE; // Trigger Timer1 event

if(switch_state & SW5_STATE()){ // If one switch is on


        count ^= 1; // XOR count variable by 1 for time remaining

}

if((switch_state & SW6_STATE()) || (switch_state & SW5_STATE())){ // If either or both switches are on


        count ^= 3; // Increase count for faster oscillation

}

//printf("%d\n", count); // Test code for counting

Timer1.timeRemaining = (num - ((switch_state) * count)); // timeRemaining is more or less based on the switches return value

}



    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
