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
#include "stm32f4xx_hal.h"

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

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
        "Welcome to CRUZID's Lab07, Part 1 (bouce_timers)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );
    
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
    while (1) {
        // Poll "Timer A".
        // React to "Timer A" events.
        // Clear "Timer A" event flag.
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


    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
