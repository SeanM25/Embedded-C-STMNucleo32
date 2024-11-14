/**
 * @file    Leds.c
 * @author
 * @date
 *
 * This library provides an interface for controlling the LEDs on the UCSC
 * Nucleo I/O Shield development board.
 */

#include <stdio.h>
#include <stdlib.h>
#include <BOARD.h>
#include <Leds_Lab07.h>
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif  /*  STM32F4 */

#define LED8 0x80

#define LED7 0x40

#define LED6 0x20

#define LED5 0x10

#define LED4 0x08

#define LED3 0x04

#define LED2 0x02

#define LED1 0x01


volatile char light_conf = 0; // Global char to return the light config in LedGet() made volitile to protect against possible unexpected changes


/**
 * LEDs_Init() Initializes the LED bar by doing three things:
 *      1) Enables usage of the GPIO clocks for needed ports.
 *      2) Use the appropriate SFRs to set each LED pin to "output" mode.
 *      3) Use the appropriate SFRs to set each LED pin's output value to 0 (low
 *         voltage). 
 * After calling LEDs_Init(), the other functions in this file can be used to 
 * manipulate the LED bar.
 */
void LEDs_Init(void) {
    // Enable GPIO clocks for ports C and B.
#ifdef STM32F4
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Init GOIO output pins for LEDs.
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif  /*  STM32F4 */
    LEDs_Set(0x0); // Reset LEDs.
}

/**
 * LEDs_Set() controls the output on the LED bar.  Input values are 8-bit 
 * patterns, where each bit describes the desired state of the corresponding 
 * LED. So, for example, LEDs_Set(0x80) should  leave the first LED on, and the
 * last 7 LEDs off. LEDs_Set(0x1F) should turn off the first three LEDs and turn
 * on the remaining five LEDs. 
 *
 * @param newPattern:  An 8-bit value describing the desired output on the LED
 * bar. 
 *
 * LEDs_Set should not change any LED pins to inputs.
 */
void LEDs_Set(char newPattern) {
#ifdef STM32F4
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/

    light_conf = newPattern;


// Perform bitwise and on each of the LED positions to see if they should be turned on or not

    int res_LED1 = newPattern & LED1; 
    int res_LED2 = newPattern & LED2;
    int res_LED3 = newPattern & LED3;
    int res_LED4 = newPattern & LED4;
    int res_LED5 = newPattern & LED5;
    int res_LED6 = newPattern & LED6;
    int res_LED7 = newPattern & LED7;
    int res_LED8 = newPattern & LED8;

    if(res_LED1 == 0){ // If LED 1 should be off

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 1); // Otherwise turn it on

    }

        if(res_LED2 == 0){ // If LED 2 should be off 

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 1); // else turn on

    }

        if(res_LED3 == 0){ // If LED 3 should be off

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 1); // otherwise turn it on

    }

        if(res_LED4 == 0){ // If LED 4 should be off

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, 1); // Otherwise turn it on

    }

        if(res_LED5 == 0){ // If LED 5 should be off

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1); // Otherwise turn it on

    }

            if(res_LED6 == 0){ // If LED 6 should be off

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1); // Otherwise turn it on

    }

            if(res_LED7 == 0){ // If LED 7 should be off

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1); // Else turn on

    }

            if(res_LED8 == 0){ // If LED 8 should be off

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0); // Keep it off

   } else{

       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // else turn it on

    }


    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
#endif  /*  STM32F4 */
}

/**
 * LEDs_Get() returns the current state of the LED bar.  Return values are 8-bit
 * patterns, where each bit describes the current state of the corresponding
 * LED. So, for example, if the LED bar's LED's are
 *
 * [ON OFF ON OFF   OFF ON OFF ON],
 *
 * LEDs_Get() should return 0xA5.
 * 
 * @return char:  An 8-bit value describing the current output on the LED bar.  
 * 
 * LEDs_Get() should not change the state of the LEDs, or any SFRs.
 */
char LEDs_Get(void) {
    char led_state = 0x00; // LED state initialized to 0
#ifdef STM32F4
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/

led_state = light_conf; // LED state equals present light config as determined by Set

    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
#endif  /*  STM32F4 */
    return led_state; // Return LED state
}

