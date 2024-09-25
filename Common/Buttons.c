/**
 * Library for interracting with buttons on the UCSC Nucleo I/O shield.
 *
 * @file    Buttons.h
 * @author  nubby (jlee211@ucsc.edu)
 *
 * @date    24 Sep 2024
 */
#include "Buttons.h"

// These masks are used for checking if the buttons have been the same value 
// over all 4 tracked timesteps.
#define BUTTON1_STATE_MASK 0x11111
#define BUTTON2_STATE_MASK 0x22222
#define BUTTON3_STATE_MASK 0x44444
#define BUTTON4_STATE_MASK 0x88888

#define BUTTON1_DOWN_EVENT_MASK   0x01111
#define BUTTON1_UP_EVENT_MASK     0x10000
#define BUTTON2_DOWN_EVENT_MASK   0x02222
#define BUTTON2_UP_EVENT_MASK     0x20000
#define BUTTON3_DOWN_EVENT_MASK   0x04444
#define BUTTON3_UP_EVENT_MASK     0x40000
#define BUTTON4_DOWN_EVENT_MASK   0x08888
#define BUTTON4_UP_EVENT_MASK     0x80000

// Mask for the position of each button
#define BUTTON1_POS_MASK (1<<0)
#define BUTTON2_POS_MASK (1<<1)
#define BUTTON3_POS_MASK (1<<2)
#define BUTTON4_POS_MASK (1<<3)

void Buttons_Init(void)
{
    // Enable pins PC4, PC5, PC6, and PD2 as inputs for buttons 1, 2, 3, and 4,
    // respectively.
    //
    // Each of these pins is also accessible via pin headers.
    //
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Configure GPIO pins : GP_IN0_Pin GP_IN1_Pin GP_IN2_Pin */
    GPIO_InitStruct.Pin = GP_IN0_Pin|GP_IN1_Pin|GP_IN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pin : PD2 */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
 * BUTTON_STATES()
 * TODO(nubby): Convert this to a macro.
 *
 * @returns (uint8_t) A nibble (LSBs) representing the current state of each
 *                    button: "0" == "UP"; "1" == "DOWN".
 */
uint8_t BUTTON_STATES(void)
{
  uint8_t b_state = 0;
  b_state += !HAL_GPIO_ReadPin(GPIOC, GP_IN0_Pin);
  b_state = b_state << 1;
  b_state += !HAL_GPIO_ReadPin(GPIOC, GP_IN1_Pin);
  b_state = b_state << 1;
  b_state += !HAL_GPIO_ReadPin(GPIOC, GP_IN2_Pin);
  b_state = b_state << 1;
  b_state += !HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);
  return b_state;
}

uint8_t Buttons_CheckEvents(void)
{
    // The states of all buttons are tracked over the last 4 samples. Only 
    // once a button is read as the same value over all 4 states does the 
    // estimated button state change.
    static uint16_t buttonSamples = 0;

    // Holds The Last Events for all four buttons.
    // An event only occurs if the last event is not the same.
    // We make the assumption that upon the first call no buttons are pressed.
    // A Button Up event means the bit is low

    static uint8_t LastButtonEvents = 0;

    uint8_t event = BUTTON_EVENT_NONE;

    // Append the current button state to our button state time vector. We do 
    // this before checking for transitions as it simplifies things.
    uint32_t buttonSampleCheck = (((uint32_t) buttonSamples) << 4) |
                                     BUTTON_STATES();

    // Button 1 - From pressed to released
    if (((buttonSampleCheck & BUTTON1_STATE_MASK) == BUTTON1_UP_EVENT_MASK)
            &&(LastButtonEvents & BUTTON1_POS_MASK)
    ) {
        event |= BUTTON_EVENT_1UP;
        LastButtonEvents &= ~BUTTON1_POS_MASK;
    }// Button 1 - From released to pressed
    else if (
        ((buttonSampleCheck & BUTTON1_STATE_MASK) == BUTTON1_DOWN_EVENT_MASK)
            &&!(LastButtonEvents & BUTTON1_POS_MASK)
    ) {
        event |= BUTTON_EVENT_1DOWN;
        LastButtonEvents |= BUTTON1_POS_MASK;
    }

    // Button 2 - From pressed to released
    if (((buttonSampleCheck & BUTTON2_STATE_MASK) == BUTTON2_UP_EVENT_MASK)
            &&(LastButtonEvents & BUTTON2_POS_MASK)
    ) {
        event |= BUTTON_EVENT_2UP;
        LastButtonEvents &= ~BUTTON2_POS_MASK;
    }// Button 2 - From released to pressed
    else if (
        ((buttonSampleCheck & BUTTON2_STATE_MASK) == BUTTON2_DOWN_EVENT_MASK)
            &&!(LastButtonEvents & BUTTON2_POS_MASK)
    ) {
        event |= BUTTON_EVENT_2DOWN;
        LastButtonEvents |= BUTTON2_POS_MASK;
    }

    // Button 3 - From pressed to released
    if (((buttonSampleCheck & BUTTON3_STATE_MASK) == BUTTON3_UP_EVENT_MASK)
            &&(LastButtonEvents & BUTTON3_POS_MASK)) {
        event |= BUTTON_EVENT_3UP;
        LastButtonEvents &= ~BUTTON3_POS_MASK;
    }// Button 3 - From released to pressed
    else if (
        ((buttonSampleCheck & BUTTON3_STATE_MASK) == BUTTON3_DOWN_EVENT_MASK)
            &&!(LastButtonEvents & BUTTON3_POS_MASK)
    ) {
        event |= BUTTON_EVENT_3DOWN;
        LastButtonEvents |= BUTTON3_POS_MASK;
    }

    // Button 4 - From pressed to released
    if (((buttonSampleCheck & BUTTON4_STATE_MASK) == BUTTON4_UP_EVENT_MASK)
            &&(LastButtonEvents & BUTTON4_POS_MASK)
    ) {
        event |= BUTTON_EVENT_4UP;
        LastButtonEvents &= ~BUTTON4_POS_MASK;
    }// Button 4 - From released to pressed
    else if (
        ((buttonSampleCheck & BUTTON4_STATE_MASK) == BUTTON4_DOWN_EVENT_MASK)
            &&!(LastButtonEvents & BUTTON4_POS_MASK)
    ) {
        event |= BUTTON_EVENT_4DOWN;
        LastButtonEvents |= BUTTON4_POS_MASK;
    }

    // And be sure to record the new button state samples.
    buttonSamples = (uint16_t) buttonSampleCheck;

    return event;
}
