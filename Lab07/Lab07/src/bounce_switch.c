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

struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

#define time_T1 2000

#define left 0

#define right 1


// **** Declare function prototypes ****

static struct Timer T1;


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

    char right_wing_led = 0x80;
    
    char left_wing_led = 0x01;

    char current_led = 0x01;

    int pres_state = -1;
    
    T1.event = FALSE;

    while (1){

        //HAL_Delay(0);

        if(T1.event){

            if(current_led == left_wing_led){

                pres_state = right;

            } else if (current_led == right_wing_led){

                pres_state = left;
            }
            
                if(pres_state == right && current_led <= right_wing_led){

                LEDs_Set(current_led);

                current_led >>= 1;
            }

            if(pres_state == left && current_led >= left_wing_led){

                      LEDs_Set(current_led);

                current_led <<= 1;


            T1.event = FALSE;

        


    }
}
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

    
    u_int8_t switch_count = 0x0;

    u_int8_t switch_pres_state = SWITCH_STATES(); // Switches are either 0, 1, 2, 3 depending on which are on at a given time no need to waste space

    if(switch_pres_state & SW5_STATE()){

        switch_count |= SW5_STATE();


    }

     if(switch_pres_state & SW6_STATE()){

        switch_count |= SW6_STATE();


    }


        T1.event = TRUE;
        
        T1.timeRemaining = switch_count;




    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
