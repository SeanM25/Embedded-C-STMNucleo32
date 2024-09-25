// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course library.
#include "BOARD.h"


// **** Set any macros or preprocessor directives here ****


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef struct {
    OvenState state;
    //add more members to this struct
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****


// **** Put any helper functions here ****


/* This function will update your OLED to reflect the state. */
void updateOvenOLED(OvenData ovenData){
    //update OLED here
}

/* This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.
 */
void runOvenSM(void)
{
    //write your SM logic here.
}


int main()
{
    BOARD_Init();

    printf(
        "Welcome to CRUZID's Lab07 (Toaster Oven).  Compiled on %s %s.",
        __TIME__,
        __DATE__
    );

    //initialize state machine (and anything else you need to init) here

    while(1) {
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
    };
}


/**
 * This is where IRQs are handled.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    /***************************************************************************
     * Your code goes in between this comment and the following one with 
     * asterisks.
     **************************************************************************/
    if (htim == &htim4) {
      // TIM4 interrupt.
    } else if (htim = &htim3) {
      // TIM3 interrupt.
    }
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
}
