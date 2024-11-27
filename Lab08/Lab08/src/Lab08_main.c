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

#define LONG_PRESS 5 // 5Hz = 5 oven cycles / sec

#define Hz 5 // same idea as above

// **** Set any local typedefs here ****

typedef enum
{ // Various states of the oven

    SETUP,
    SELECTOR_CHANGE_PENDING,
    COOKING,
    RESET_PENDING,
    RED_ALERT_EC

} OvenState;

typedef enum
{ // The three cooking operations of the oven

    BAKE,
    TOAST,
    BROIL

} cookingOPS;

typedef struct
{
    OvenState state; // Gets Present State of the Oven

    // add more members to this struct

    uint16_t cooking_time_initial; // Gets Initial Cooking Time ex: 4:05

    uint16_t cooking_time_REM; // Gets Cooking Time after some time has elapsed initially the same as the initial time

    u_int16_t oven_temp; // Temperature of the Oven

    u_int8_t BTN_PRESS_TIME; // How long has the button been pressed for

    uint8_t mode; // Bake, Toast, or Broil?

} OvenData;

// **** Declare any datatypes here ****

static OvenData myoven; // Oven struct that holds all oven info

static uint16_t TIMER_TICK = FALSE; // Timer Tick Flag

static uint16_t free_run_time = 0; // Free Running Counter

static uint8_t button_event_detect = BUTTON_EVENT_NONE; // Button Event Flag

static uint8_t changeTEMP = FALSE; // Flag to let us know if the temperature is being changed

static uint8_t screenINV = FALSE; // Checks if the display is inverted or not?

static uint8_t LED_TIME; // Gets 1/8 Time for the LEDs I fiddled with this a bit to get better results. It's not precise though and can be improved

static uint8_t LEDS_CUR = 0xFF; // Current LED Variable initialized to all 8 LEDs on

static uint16_t free_run_storage; // Stores free running time

static uint8_t numTICKS = 0; // Counts number of ticks necessary to turn off the LEDs

static uint8_t tempSWAP; // When switching between BROIL holds the temperature for the bake or toast mode

// **** Define any module-level, global, or external variables here ****
// Create a local variable to update with ADC readings.

volatile static uint32_t adc_val = 0; // Gets the adc value

volatile uint8_t hasNewADC = FALSE; // Determines whether a new value is available

// **** Put any helper functions here ****

/* This function will update your OLED to reflect the state. */
void updateOvenOLED(OvenData ovenData)
{
    // Update OLED here.

    char oven_OUT[100]; // Gets Final Output of the oven for the OLED depending on the mode

    char topOVEN_ON[10]; // String containing graphics for when the top of the oven is on

    char topOVEN_OFF[10]; // String containing graphics for when the top of the oven is off

    char botOVEN_ON[10]; // String containing graphics for when the bottom of the oven is on

    char botOVEN_OFF[10]; // String containing graphics for when the bottom of the oven is off

    sprintf(topOVEN_ON, "%s%s%s%s%s%s", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON); // Store Oven Top On Graphics

    sprintf(topOVEN_OFF, "%s%s%s%s%s%s", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF); // Store Oven Top OFF Graphics

    sprintf(botOVEN_ON, "%s%s%s%s%s%s", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON); // Store Oven Bottom ON Graphics

    sprintf(botOVEN_OFF, "%s%s%s%s%s%s", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF); // Store Oven Bottom OFF Graphics

    // Time is determined in the following cases by simple division and modulo operations.
    // Since time is btwn 0 - 255 seconds we get the minute via division and second via remainder. EX: 255 / 60 = 4 minutes, 255 % 60 = 15 seconds

    switch (myoven.mode)
    {

    case BAKE: // Time & Temp is configurable, top & bottom heating elements on

        if (!(myoven.state == COOKING || myoven.state == RESET_PENDING))
        { // If were neither cooking or trying to reset the oven were in the intial setup stage for the BAKE

            // As such, display initial temperature

            if (!changeTEMP)
            { // If were not changing the ovens temp

                sprintf(oven_OUT, "|%s| MODE:  BAKE\n|      | >TIME: %d:%02d\n|------| TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_initial / 60,

                        myoven.cooking_time_initial % 60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Indicate we're changing the time
            }
            else
            {

                sprintf(oven_OUT, "|%s| MODE: BAKE\n|      | TIME: %d:%02d\n|------| >TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_initial / 60,

                        myoven.cooking_time_initial % 60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Otherwise indicate to the user we're changing the temperature
            }
        }
        else
        { // Otherwise we just display the time as normal (remaining time) with no selection

            sprintf(oven_OUT, "|%s| MODE: BAKE\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF\n|%s|", topOVEN_ON, myoven.cooking_time_REM / 60,

                    myoven.cooking_time_REM % 60, myoven.oven_temp, DEGREE_SYMBOL, botOVEN_ON); // Output Baking INFO
        }
        break;

    case TOAST: // Time is configurable, only bottom heating elements on, temperature not displayed, no selector

        if (!(myoven.state == COOKING || myoven.state == RESET_PENDING))
        { // If Not cooking or trying to reset the oven we display the intial time

            sprintf(oven_OUT, "|%s| MODE: TOAST\n|      | TIME: %d:%02d\n|------|\n|%s|", topOVEN_OFF, myoven.cooking_time_initial / 60,

                    myoven.cooking_time_initial % 60, botOVEN_ON);
        }
        else
        { // Otherwise display the remaining time

            sprintf(oven_OUT, "|%s| MODE: TOAST\n|      | TIME: %d:%02d\n|------|\n|%s|", topOVEN_OFF, myoven.cooking_time_REM / 60,

                    myoven.cooking_time_REM % 60, botOVEN_ON); // Output TOAST INFO
        }

        break;

    case BROIL: // Temp fixed at 500 degrees, only time is configurable, display temperature

        if (!(myoven.state == COOKING || myoven.state == RESET_PENDING))
        { // If Not cooking or trying to reset the oven we display the intial time

            sprintf(oven_OUT, "|%s| MODE:BROIL\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF \n|%s|", topOVEN_ON, myoven.cooking_time_initial / 60,

                    myoven.cooking_time_initial % 60, const_BROIL_TEMP, DEGREE_SYMBOL, botOVEN_OFF);
        }
        else
        { // Otherwise display remaining time

            sprintf(oven_OUT, "|%s| MODE:BROIL\n|      | TIME: %d:%02d\n|------| TEMP: %d%sF \n|%s|", topOVEN_ON, myoven.cooking_time_REM / 60,

                    myoven.cooking_time_REM % 60, const_BROIL_TEMP, DEGREE_SYMBOL, botOVEN_OFF); // Output BROIL INFO
        }

        break;

        // Default case is excluded since there is no standard mode of operation since its determined by the user
    }

    OledClear(OLED_COLOR_BLACK); // Clear OLED before output

    OledDrawString(oven_OUT); // Draw the desired oven information based on the state & mode

    if (myoven.state == RED_ALERT_EC)
    { // If we're ready to enter, the end of cooking, alert mode

        if (screenINV)
        { // If inverted

            OledDriverSetDisplayNormal(); // Display as normal
        }
        else
        {

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

    switch (myoven.state)
    { // Oven Operates based on one of its 4 possible states plus 1 extra credit state

    case SETUP: // Setup State

        if (hasNewADC)
        { // If the ADC has changed

            uint8_t myADCVAL = (uint8_t)(adc_val & top_8_mask); // Apply bit mask to get the top 8 bits of the read adc value

            if (myoven.mode == BAKE && changeTEMP)
            { // If we're baking and want to change the temperature

                myoven.oven_temp = (myADCVAL + 300); // Add 300 degrees to the adc value 300 + (0 - 255) = (300 - 555 degrees F)
            }
            else
            {

                myoven.cooking_time_initial = (myADCVAL + 1); // Otherwise set the time by adding 1 to the adc value 1 sec - 255 sec = 0:01 - 4:16

                myoven.cooking_time_REM = myoven.cooking_time_initial; // Time remaining will then be the user set initial time
            }

            updateOvenOLED(myoven); // Update the OLED with the new info
        }

        if (button_event_detect & BUTTON_EVENT_3DOWN)
        { // If the 3rd button is down and were in setup head to the selector

            myoven.BTN_PRESS_TIME = free_run_time; // store the free running time as the oven data button time since we will use this to change settings in selector change

            myoven.state = SELECTOR_CHANGE_PENDING; // Switch to selector change pending state
        }

        if (button_event_detect & BUTTON_EVENT_4DOWN)
        { // If we press butoon 4 down

            free_run_storage = free_run_time; // Store free running time

            myoven.state = COOKING; // Switch state to Cooking

            updateOvenOLED(myoven); // Update OLED

            LEDs_Set(0xFF); // Set all 8 LEDS

            LED_TIME = (myoven.cooking_time_initial * Hz) / 12; // Set inital state of LEDS scaled by 5 Hz / 8 Fiddled with for better results
        }

        break; // Exit Setup

    case COOKING: // Oven is in Cooking state

        if (TIMER_TICK)
        { // While a timer tick occurs

            numTICKS++; // Increment the tick counter for the LEDs

            if (numTICKS == LED_TIME && myoven.cooking_time_REM > 0)
            { // If the tick counter is approx 1/8 of the total time and there is time remaining

                LEDS_CUR = LEDS_CUR >> 1; // Shift the Current LED position to turn off the LEDs

                LEDs_Set(LEDS_CUR); // Display the shifted leds

                numTICKS = 0; // reset the tick counter
            }

            if ((free_run_time - free_run_storage) % 5 == 0)
            { // If one 5Hz cycle has passed aka 1 second in ticks

                myoven.cooking_time_REM--; // Decrement the time remaining

                updateOvenOLED(myoven); // and update the OLED
            }

            if (myoven.cooking_time_REM == 0)
            { // When the time hits zero and cooking is finished

                myoven.cooking_time_REM = myoven.cooking_time_initial; // reset the cooking timer to its initial value

                myoven.state = RED_ALERT_EC; // Enter the Extra Credit alert mode

                updateOvenOLED(myoven); // Update the OLED with the flashing graphics

                LEDs_Set(fade_out); // Black out the LEDs
            }
        }

        if (button_event_detect & BUTTON_EVENT_4DOWN)
        { // If the user pressed button 4 down

            myoven.BTN_PRESS_TIME = free_run_time; // store the free run time

            myoven.state = RESET_PENDING; // toaster enters the reset pending state
        }

        break; // Exit Cooking

    case SELECTOR_CHANGE_PENDING: // Were in the selector state where we can swap between modes and change either temp or time depending.

        if (button_event_detect & BUTTON_EVENT_3UP)
        { // If the user has pressed button 3 again and its up

            if ((free_run_time - myoven.BTN_PRESS_TIME) < LONG_PRESS)
            { // If the elapsed time is less than a long press

                myoven.mode += 1; // Move through the oven modes: Bake, Toast, Broil,

                if (myoven.mode > BROIL)
                { // When we hit broil

                    myoven.mode = BAKE; // Reset mode to bake
                }

                if (myoven.mode == BROIL)
                { // If were in the broil state

                    tempSWAP = myoven.oven_temp; // store the previous temperature for either Bake or Toast

                    myoven.oven_temp = const_BROIL_TEMP; // Oven temp is then const 500 degrees
                }
                else if (myoven.mode == BAKE)
                { // If were in Bake mode

                    myoven.oven_temp = tempSWAP; // Restore the initial temperature
                }

                updateOvenOLED(myoven); // Update the OLED

                myoven.state = SETUP; // Return to setup
            }
            else
            { // If were not swapping modes were changing the temperature or Time

                if (myoven.mode == BAKE)
                { // If were in Bake mode

                    if (changeTEMP)
                    { // If currently changing the temperature

                        changeTEMP = FALSE; // set flag to false ie we want to change the Time
                    }
                    else
                    {

                        changeTEMP = TRUE; // Otherwise we want to change the temperature
                    }
                }

                updateOvenOLED(myoven); // Update OLED

                myoven.state = SETUP; // Return to setup
            }
        }

        break; // Exit selector state

    case RESET_PENDING: // The reset pending state

        if (button_event_detect & BUTTON_EVENT_4UP)
        { // If the user presses button 4 and its up

            myoven.state = COOKING; // return to the cooking state
        }

        if (TIMER_TICK)
        { // While there is a timer tick flag

            if ((free_run_time - myoven.BTN_PRESS_TIME) >= LONG_PRESS)
            { // If the user long presses buton 4

                myoven.state = SETUP; // Return to the setup state

                myoven.cooking_time_REM = myoven.cooking_time_initial; // reset the cooking time

                updateOvenOLED(myoven); // Update the OLED

                LEDs_Set(fade_out); // Turn off the LEDS
            }
            else
            { // If we dont want to return to setup or we do nothing just keep doing what was happening in Cooking mode

                numTICKS++; // Increment LED tick counter

                if (numTICKS == LED_TIME && myoven.cooking_time_REM > 0)
                { // If the LED interval has arrived

                    LEDS_CUR = LEDS_CUR >> 1; // Shift LED position

                    LEDs_Set(LEDS_CUR); // Display updated LEDs

                    numTICKS = 0; // Reset LED tick counter
                }

                if ((free_run_time - free_run_storage) % 5 == 0)
                { // If one 5Hz cycle has passed or 1 second in terms of ticks

                    myoven.cooking_time_REM--; // Decrement the remaining time

                    updateOvenOLED(myoven); // Update the OLED
                }

                if (myoven.cooking_time_REM == 0)
                { // When the time hits zero

                    myoven.cooking_time_REM = myoven.cooking_time_initial; // Reset the cooking time

                    myoven.state = RED_ALERT_EC; // Move into the alert mode

                    updateOvenOLED(myoven); // Update the OLED

                    LEDs_Set(fade_out); // Turn off LEDs
                }
            }
        }

        break; // Exit Reset Pending

    case RED_ALERT_EC: // The Extra Credit Alert Phase

        if (TIMER_TICK)
        { // If there is a timer tick flag

            if (screenINV)
            { // If the screen is already inverted

                screenINV = FALSE; // Don't invert it
            }
            else
            {

                screenINV = TRUE; // Otherwise invert it
            }

            updateOvenOLED(myoven); // Update OLED
        }

        if (button_event_detect & BUTTON_EVENT_4UP)
        { // When the user wants to exit the alert mode they can press button 4 again

            screenINV = TRUE; // Display screen as normal

            myoven.state = SETUP; // Return to setup

            updateOvenOLED(myoven); // Update OLED
        }

        break; // Exit the Alert state
    }
}

int main()
{
    BOARD_Init();  // Turn on Board
    ButtonsInit(); // Turn on Buttons
    ADC_Init();    // Turn on POT
    OledInit();    // Turn on OLED

    printf(
        "Welcome to CRUZID's Lab08 (Toaster Oven)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);

    // Initialize state machine (and anything else you need to init) here.

    myoven.BTN_PRESS_TIME = 0; // Button press time initially zero

    myoven.cooking_time_initial = 1; // Cooking time is intially one before adc value

    myoven.cooking_time_REM = 1; // Same as above

    myoven.oven_temp = BAKE_DEF_TEMP; // Default temperature of the oven

    myoven.state = SETUP; // State machine begins in setup state

    myoven.mode = BAKE; // First selectable mode should be bake

    while (1)
    {
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags

        button_event_detect = ButtonsCheckEvents(); // Check for Button Events

        if (button_event_detect != BUTTON_EVENT_NONE || hasNewADC || TIMER_TICK)
        { // If any of the possible events occur (ADC, Button, Timer)

            runOvenSM(); // Run Toaster Machine

            button_event_detect = BUTTON_EVENT_NONE; // Reset Button Event Flag

            hasNewADC = FALSE; // Reset ADC Event Flag

            TIMER_TICK = FALSE; // Reset Timer Event Flag
        }
    };
}

/**
 * This is the interrupt for the Timer2 peripheral. It should check for button
 * events and store them in a module-level variable.
 *
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    if (htim == &htim4)
    { // Event Flags 5Hz Timer That Sets Timer Tick & increments free running time
        // TIM4 interrupt.

        TIMER_TICK = TRUE; // Set Timer Flag To True

        free_run_time++; // Increment Free running counter

        // printf("%d\n", free_run_time);
    }
    else if (htim == &htim3)
    { // 100 Hz Timer that checks for ADC & Button Flags
        // TIM3 interrupt.

        // button_event_detect = ButtonsCheckEvents(); // Checks & gets current button events. Commented out since it seems to be too slow to read a short press
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
    adc_val = HAL_ADC_GetValue(&hadc1);

    // Set the flag to indicate a new value is available.
    hasNewADC = TRUE;

    // Start the next conversion.
    HAL_ADC_Start_IT(&hadc1);
}
