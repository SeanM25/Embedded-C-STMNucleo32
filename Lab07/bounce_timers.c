/**
 * @file    bounce_timers.c
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

// Declare Constants for each Timer of 2, 3, & 5 seconds respectively time in ms

#define TIMER_A_CountD 2000
#define TIMER_B_CountD 3000
#define TIMER_C_CountD 5000

// **** Declare any datatypes here ****
struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

// Declare Timer A, TimerB, and TimerC variables each initialized to false and the appropriate time

struct Timer Timer_A = {FALSE, TIMER_A_CountD};
struct Timer Timer_B = {FALSE, TIMER_B_CountD};
struct Timer Timer_C = {FALSE, TIMER_C_CountD};




int main(void)
{
    BOARD_Init();
    Timers_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 1 (bouce_timers)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );

    LEDs_Init();
    
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
    while (1) {
        // Poll "Timer A".
        // React to "Timer A" events.
        // Clear "Timer A" event flag.

        if(Timer_A.event){ // If a Timer A event is ready to execute

               printf("A\n"); // Print A

               LEDs_Set(0x01); // Turn on LED1

               //Timer_A.event = FALSE;  // Event A is False after exec
        }

        Timer_A.event = FALSE;

        if(Timer_B.event){

               printf("B\n"); // Print B

               LEDs_Set(0x02); // Turn on LED 2

               //Timer_B.event = FALSE; // B event false after exec 
        }

         Timer_B.event = FALSE; // B event false after exec 


        if(Timer_C.event){

              printf("C\n");

              LEDs_Set(0x04); // Turn on LED 3

               //Timer_C.event = FALSE; // C False after Exec
        }

         Timer_C.event = FALSE; // C False after Exec


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

      // Update "Timer A".
      // If "Timer A" has counted down, generate "Timer A" event.

      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);


      if(Timer_A.timeRemaining > 0){ // Countdown from 2 sec to 0 only to avoid errors


      Timer_A.timeRemaining--; // Decrement TimerA

      }

      if(Timer_A.timeRemaining == 0){ // When Timer A hits 0

            Timer_A.event = TRUE; // Triger Timer A event

            Timer_A.timeRemaining = TIMER_A_CountD; // reset Timer A's clock

      }

      if(Timer_B.timeRemaining > 0){ // Countdown from 3 sec to 0 only to avoid errors


      Timer_B.timeRemaining--; // Decrement TimerB

      }

      if(Timer_B.timeRemaining == 0){ // When Timer B hits 0

            Timer_B.event = TRUE; // Trigger Timer B event

            Timer_B.timeRemaining = TIMER_B_CountD; // reset Timer B's clock

      }

      if(Timer_C.timeRemaining > 0){ // Countdown from 5 sec to 0 only to avoid erros

      Timer_C.timeRemaining--; // Decrement TimerC

      }

      if(Timer_C.timeRemaining == 0){ // When Timer C is 0

            Timer_C.event = TRUE; // Trigger C event

            Timer_C.timeRemaining = TIMER_C_CountD; // Reset Timer C clock

      }


    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
