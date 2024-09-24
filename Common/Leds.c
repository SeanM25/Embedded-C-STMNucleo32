/**
 * @file    Leds.c
 * @author  Adam Korycki
 * @author  nubby (jlee211@ucsc.edu)
 * @date    15 Nov 2023
 * @brief   File containing LED, Nucleo board-focused functions.
 *
 * This library provides an interface for controlling the LEDs on the UCSC
 * Nucleo I/O Shield development board.
 */

#include <stdio.h>
#include <stdlib.h>
#include <BOARD.h>
#include <Leds.h>
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif  /*  STM32F4 */

/**
 * LEDs_Init() Initializes the LED bar by doing two things:
 *      1) Use the appropriate SFRs to set each LED pin to "output" mode.
 *      2) Use the appropriate SFRs to set each LED pin's output value to 0 (low
 *         voltage). 
 * After calling LEDs_Init(), the other functions in this file can be used to 
 * manipulate the LED bar.
 */
void LEDs_Init(void) {
    // Enable GPIO clocks for ports C and B.
#ifdef STM32F4
    //__HAL_RCC_GPIOC_CLK_ENABLE();
    //__HAL_RCC_GPIOB_CLK_ENABLE();

    //init GOIO output pins for leds
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif  /*  STM32F4 */
    LEDs_Set(0x0); // reset leds
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
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, (newPattern) & 0x1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, (newPattern >> 1) & 0x1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, (newPattern >> 2) & 0x1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, (newPattern >> 3) & 0x1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (newPattern >> 4) & 0x1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (newPattern >> 5) & 0x1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (newPattern >> 6) & 0x1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (newPattern >> 7) & 0x1);
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
    char led_state = 0x00;
#ifdef STM32F4
    led_state += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
    led_state = led_state << 1;
    led_state += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);
#endif  /*  STM32F4 */
    return led_state;
}

