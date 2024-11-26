// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>

// Course library.
#include <BOARD.h>
#include <Timers.h>
#include <Oled.h>
#include <OledDriver.h>
#include "Buttons.h"
#include <Adc.h>
#include "Ascii.h"
#include "Leds.h"

// **** Set any macros or preprocessor directives here ****

#define top_8_mask 0xFF // Gets Top 8 Bits of LEDS, ADC, etc

#define fade_out 0x00 // Zero to do any possible zero operations

#define BAKE_DEF_TEMP 350 // Default Baking Temperature of the oven

#define const_BROIL_TEMP 500 // In BROIL mode the temperature is a constant 500 degrees

#define one_sec 5 // 5Hz = 5 oven cycles / sec

#define Hz 5 // same idea as above


// **** Set any local typedefs here ****

typedef enum { // Various states of the oven

    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING, RED_ALERT_EC

} OvenState;

typedef enum{ // The three cooking operations of the oven

BAKE, TOAST, BROIL

} cookingOPS;

typedef struct{
    OvenState state; // Gets Present State of the Oven

    //add more members to this struct

    uint16_t cooking_time_initial; // Gets Initial Cooking Time ex: 4:05

    uint16_t cooking_time_REM; // Gets Cooking Time after some time has elapsed initially the same as the initial time

    u_int16_t oven_temp; // Temperature of the Oven

    u_int8_t BTN_PRESS_TIME; // How long has the button been pressed for

    uint8_t mode; // Bake, Toast, or Broil?

} OvenData;





// **** Declare any datatypes here ****

static OvenData myoven;

static uint16_t TIMER_TICK = FALSE; // Timer Tick Flag

static uint16_t free_run_time = 0; // Free Running Counter

static uint8_t button_event_detect = BUTTON_EVENT_NONE; // Button Event Flag

static uint8_t changeTEMP = FALSE; // Flag to let us know if the temperature is being changed

static uint8_t screenINV = FALSE; // Checks if the display is inverted or not?

static uint16_t LED_STATE;

static uint16_t LED_MOD;

static uint16_t free_run_storage;

static uint16_t numTICKS;

static uint16_t tempSWAP;



// **** Define any module-level, global, or external variables here ****
// Create a local variable to update with ADC readings.
volatile static uint32_t adc_val = 0;

volatile uint8_t hasNewADC = FALSE;


// **** Put any helper functions here ****




/* This function will update your OLED to reflect the state. */
void updateOvenOLED(OvenData ovenData){
    // Update OLED here.

    //changeTEMP = TRUE;

   // myoven.state = COOKING;

   //myoven.mode = BROIL;

    char oven_OUT [80]; // Gets Final Output of the oven for the OLED depending on the mode

    char topOVEN_ON [8]; // String containing graphics for when the top of the oven is on

    char topOVEN_OFF[8]; // String containing graphics for when the top of the oven is off

    char botOVEN_ON [8]; // String containing graphics for when the bottom of the oven is on

    char botOVEN_OFF [8]; // String containing graphics for when the bottom of the oven is off

    sprintf(topOVEN_ON,"%s%s%s%s%s%s", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON,OVEN_TOP_ON); // Store Oven Top On Graphics

    sprintf(topOVEN_OFF,"%s%s%s%s%s%s", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF); // Store Oven Top OFF Graphics

    sprintf(botOVEN_ON, "%s%s%s%s%s%s", OVEN_BOTTOM_ON,OVEN_BOTTOM_ON,OVEN_BOTTOM_ON,OVEN_BOTTOM_ON,OVEN_BOTTOM_ON,OVEN_BOTTOM_ON); // Store Oven Bottom ON Graphics

    sprintf(botOVEN_OFF, "%s%s%s%s%s%s", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF); // Store Oven Bottom OFF Graphics

    //sprintf()

    // Time is determined in the following cases by simple division and modulo operations. 
    // Since time is btwn 0 - 255 seconds we get the minute via division and second via remainder. EX: 255 / 60 = 4 minutes, 255 % 60 = 15 seconds

    switch(myoven.mode){

        case BAKE: // Time & Temp is configurable, top & bottom heating elements on

    if(!(myoven.state == COOKING || myoven.state == RESET_PENDING)){ // If were neither cooking or trying to reset the oven were in the intial setup stage for the BAKE

    // As such, display initial temperature

        if(!changeTEMP){ // If were not changing the ovens temp

            sprintf(oven_OUT, "|%s| MODE:  BAKE\n|      | >TIME: %d:%02d\n|------| TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_initial/60,  
            
            myoven.cooking_time_initial%60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Indicate we're changing the time
       
        } else{

            sprintf(oven_OUT, "|%s| MODE: BAKE\n|      | TIME: %d:%02d\n|------| >TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_initial/60,  
            
            myoven.cooking_time_initial%60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Otherwise indicate to the user we're changing the temperature

        }
        
    }else{ // Otherwise we just display the time as normal (remaining time) with no selection

        sprintf(oven_OUT, "|%s| MODE: BAKE\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_REM / 60,  
            
            myoven.cooking_time_REM % 60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Output Baking INFO

    }
        break;

        case TOAST: // Time is configurable, only bottom heating elements on, temperature not displayed, no selector

            if(!(myoven.state == COOKING || myoven.state == RESET_PENDING)){ // If Not cooking or trying to reset the oven we display the intial time


                 sprintf(oven_OUT, "|%s| MODE: TOAST\n|      | TIME: %d:%02d\n|------|\n|%s|", topOVEN_OFF, myoven.cooking_time_initial / 60,  
            
            myoven.cooking_time_initial % 60, botOVEN_ON);

            }else{ // Otherwise display the remaining time


                 sprintf(oven_OUT, "|%s| MODE: TOAST\n|      | TIME: %d:%02d\n|------|\n|%s|", topOVEN_OFF, myoven.cooking_time_REM / 60,  
            
            myoven.cooking_time_REM % 60, botOVEN_ON); // Output TOAST INFO

            }

        break;


        case BROIL: // Temp fixed at 500 degrees, only time is configurable, display temperature

            if(!(myoven.state == COOKING || myoven.state == RESET_PENDING)){ // If Not cooking or trying to reset the oven we display the intial time


                sprintf(oven_OUT,"|%s| MODE:BROIL\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF \n|%s|", topOVEN_ON, myoven.cooking_time_initial / 60, 

                myoven.cooking_time_initial % 60, const_BROIL_TEMP, DEGREE_SYMBOL, botOVEN_OFF);


            } else { // Otherwise display remaining time

                sprintf(oven_OUT,"|%s| MODE:BROIL\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF \n|%s|", topOVEN_ON, myoven.cooking_time_REM / 60, 

                myoven.cooking_time_REM % 60, const_BROIL_TEMP, DEGREE_SYMBOL, botOVEN_OFF); // Output BROIL INFO


            }




        break;

        // Default case is excluded since there is no standard mode of operation since its determined by the user
    }

    OledClear(OLED_COLOR_BLACK);

    OledDrawString(oven_OUT);

    if(myoven.state == RED_ALERT_EC){ // If we're ready to enter the end of cooking alert mode

        if(screenINV){ // If inverted

            OledDriverSetDisplayNormal(); // Display as normal
        } else{

            OledDriverSetDisplayInverted(); // Otherwise invert the display
        }

    }

    OledUpdate(); // Output desired OVEN INFO to OLED


}



/* This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.
 */
void runOvenSM(void)
{
    // Write your SM logic here.

    //printf("Hi\n");

switch(myoven.state){

    case SETUP:

    if(hasNewADC){ // If the ADC has changed (Verify Later !!)

        adc_val = (adc_val & top_8_mask); // Apply bit mask to get the top 8 bits

        //printf("%ld\n", adc_val);

        if(myoven.mode == BAKE && changeTEMP){ // If we're baking and want to change the temperature

            myoven.oven_temp = adc_val + 300; // Add 300 degrees to the adc value 300 + (0 - 255) = (300 - 555 degrees F)
            
        } else{

            myoven.cooking_time_initial = adc_val + 1; // Otherwise set the time by adding 1 to the adc value 1 sec - 255 sec = 0:01 - 4:16

            myoven.cooking_time_REM = myoven.cooking_time_initial; // Time remaining will then be the user set initial time
        }

        updateOvenOLED(myoven); // Update the OLED with the new info


    }


    if(button_event_detect & BUTTON_EVENT_3DOWN){ // If the 3rd button is down and were in setup head to the selector

        myoven.BTN_PRESS_TIME = free_run_time; // store the free running time as the oven data button time since we will use this to change settings in selector change

        myoven.state = SELECTOR_CHANGE_PENDING; // Switch to selector change pending state

    }

    if(button_event_detect & BUTTON_EVENT_4DOWN){

        
        free_run_storage = free_run_time; // Store free running time

        updateOvenOLED(myoven); // Update OLED

        LEDs_Set(top_8_mask); // Set all 8 LEDS

        myoven.state = COOKING; // Switch state to Cooking

        LED_STATE = (myoven.cooking_time_initial * Hz) / 8 ; // Set inital state of LEDS

        LED_MOD = (myoven.cooking_time_initial * Hz) % 8 ; // Set initial Remainder of the LEDS

    }

    break;


    case SELECTOR_CHANGE_PENDING:

    if(button_event_detect & BUTTON_EVENT_3UP){

        uint16_t time_elapsed = free_run_time - myoven.BTN_PRESS_TIME;


        if(time_elapsed >= one_sec){


             if(changeTEMP){

                changeTEMP = FALSE;
            } else{

                changeTEMP = TRUE;
            }

             updateOvenOLED(myoven);

            myoven.state = SETUP;

        }else{
            
            if(myoven.mode == BROIL){

                myoven.mode = BAKE;
            } else{

                myoven.mode++;
            }

            if(myoven.mode == BROIL){

                tempSWAP = myoven.oven_temp;

                myoven.oven_temp = const_BROIL_TEMP;

            } else if(myoven.mode == BAKE){

                myoven.oven_temp = tempSWAP;
            }

            updateOvenOLED(myoven);

            myoven.state = SETUP;

        }

    }

    break;







    }

}


int main()
{
    BOARD_Init();
    ButtonsInit();
    ADC_Init();
    OledInit();

    printf(
        "Welcome to CRUZID's Lab08 (Toaster Oven)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );

    // Initialize state machine (and anything else you need to init) here.

    myoven.BTN_PRESS_TIME = 0;

    myoven.cooking_time_initial = 1;

    myoven.cooking_time_REM = 1;

    myoven.oven_temp = BAKE_DEF_TEMP;

    myoven.state = SETUP;

    myoven.mode = BAKE;

    while(1) {
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
       
       //updateOvenOLED(myoven);

        //printf("%d\n", free_run_time);

        if(button_event_detect != BUTTON_EVENT_NONE || hasNewADC || TIMER_TICK){

            runOvenSM();

            button_event_detect = BUTTON_EVENT_NONE;

            hasNewADC = FALSE;

            TIMER_TICK = FALSE;

        }
        



            
    };
}


/**
 * This is the interrupt for the Timer2 peripheral. It should check for button
 * events and store them in a module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    /***************************************************************************
     * Your code goes in between this comment and the following one with 
     * asterisks.
     **************************************************************************/
    if (htim == &htim4) { // Event Flags 5Hz Timer That Sets Timer Tick & increments free running time
        // TIM4 interrupt.

    TIMER_TICK = TRUE; // Set Timer Flag To True

    free_run_time++; // Increment Free running counter

    //printf("%d\n", free_run_time);


    } else if (htim == &htim3) { // 100 Hz Timer that checks for ADC & Button Flags
        // TIM3 interrupt.

        button_event_detect = ButtonsCheckEvents(); // Checks & gets current button events

        
    }
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with 
     * asterisks.
     **************************************************************************/
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
    // Get the result of the current conversion.
    adc_val = HAL_ADC_GetValue (&hadc1);

    // Set the flag to indicate a new value is available.
    hasNewADC = TRUE;

    // Start the next conversion.
    HAL_ADC_Start_IT(&hadc1);
}
