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

//#define time_T1 2000

#define left 0

#define right 1

#define test 2000

#define test2 3000

// **** Declare any datatypes here ****

struct Timer {
  uint8_t event;
  int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

static struct Timer T1 = {FALSE,test};

static struct Timer T2 = {FALSE,test2};


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

    int state = -1;

    while (1){

        

        if(T1.event == TRUE){

            printf("It's Working !\n");


            LEDs_Set(0x01);

            T1.event = FALSE;

           // T1.event = FALSE;
  
   }

         if(T2.event == TRUE){

           T2.event = FALSE;

            printf("It's Working Again !\n");

            LEDs_Set(0x2);

             T2.event = FALSE;

           // T1.event = FALSE;
  
   }



      //T1.event = FALSE;

     // T2.event = FALSE;


    }

    //while(1);
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

    //printf("Call\n");

    /*
    u_int8_t switch_count_right = 0x0;

    u_int8_t switch_count_left = 0x0;

    u_int8_t switch_pres_state = SWITCH_STATES(); // Switches are either 0, 1, 2, 3 depending on which are on at a given time no need to waste space

    // = 0 neither on

    // = 1 right switch on

    // = 2 left switch on

    // = 3 both on

    T1.timeRemaining--;

    if(T1.timeRemaining <= 0){

        T1.event = TRUE;

    
    if(switch_pres_state & SW5_STATE()){

        switch_count_left |= 1;
        

    }

      if(switch_pres_state & SW6_STATE()){

        switch_count_left |= 1;
        

    }

        T1.timeRemaining = switch_count_left;

        //printf("%d\n", T1.event);
    }
   
*/

//TIM1->SR &= ~TIM_SR_UIF;

//__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);

//int bob = &htim2;

//printf("%d\n",bob);

T1.timeRemaining--;

//if(T1.timeRemaining <= 0){

if(T1.timeRemaining == 0){

 T1.event = TRUE;

 T1.timeRemaining = test;

}
//}

T2.timeRemaining--;

if(T2.timeRemaining <= 0){

if(T2.timeRemaining == 0){

 T2.event = TRUE;

 T2.timeRemaining = test2;

}
}




    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
    }
}
