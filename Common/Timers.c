/**
 * @file    Timers.c
 * @author  Adam Korycki
 * @author  nubby (jlee211@ucsc.edu)
 *
 * @date 29 Sep 2023
 */

#include <stdlib.h>
#include <stdint.h>
#include "Timers.h"

// Boolean defines for TRUE, FALSE, SUCCESS and ERROR
#ifndef FALSE
#define FALSE ((int8_t) 0)
#define TRUE ((int8_t) 1)
#endif
#ifndef ERROR
#define ERROR ((int8_t) -1)
#define SUCCESS ((int8_t) 1)
#endif

static uint8_t init_status = FALSE;

static uint32_t us; //microsecond count
static uint32_t ms; //millisecond count

/**
 * @function Timers_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Initializes and starts the timer (TIM2) peripheral
 */
char Timers_Init(void) {
    if (init_status == FALSE) { // if TIM2 module has not been initialized
#ifdef STM32F4
        TIM_ClockConfigTypeDef sClockSourceConfig = {0};
        TIM_MasterConfigTypeDef sMasterConfig = {0};

        // Get the system clock freq in MHz.
        uint32_t system_clock_freq = Timers_GetSystemClockFreq() / 1000000;
        htim2.Instance = TIM2;
        // Set the clock prescaler for 1 MHz timer clock.
        htim2.Init.Prescaler = system_clock_freq - 1; 
        htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
        // Trigger an interrupt every 1ms.
        htim2.Init.Period = 1024; 
        htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
        if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
        {
          return ERROR;
          //Error_Handler();
        }
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
        {
          return ERROR;
          //Error_Handler();
        }
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
        {
          return ERROR;
          //Error_Handler();
        }
        HAL_TIM_Base_Start_IT(&htim2); // start interrupt
#endif  /*  STM32F4 */
        init_status = TRUE;
    }
    return SUCCESS;
}

/**
 * @function Timers_GetMilliSeconds(void)
 * @param None
 * @return current millisecond count
 * @brief ^
 * @author Adam Korycki, 2023.09.29 */
uint32_t Timers_GetMilliSeconds(void) {
    return ms;
}

/**
 * @function Timers_GetMicroSeconds(void)
 * @param None
 * @return current microsecond count
 * @brief ^
 * @author Adam Korycki, 2023.09.29 */
uint32_t Timers_GetMicroSeconds(void) {
#ifdef STM32F4
    return us + TIM2->CNT; // (ms*1000) + (current value of 1Mhz counter)
#else
    return 0;
#endif  /*  STM32F4 */
}

/**
 * @function Timers_GetSystemClockFreq(void)
 * @param None
 * @return frequnecy of system clock in hz
 * @brief ^
 * @author Adam Korycki, 2023.09.29 */
uint32_t Timers_GetSystemClockFreq(void) {
#ifdef STM32F4
    return HAL_RCC_GetSysClockFreq();
#else
    return 0;
#endif  /*  STM32F4 */
}

/* NOTE: You will need to define your own timer callback following this formula:
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
      if (htim == &htim2) {
        // 1ms has passed, define actions here!
      }
  }
 *
 */

//#define Timers_TEST
#ifdef Timers_TEST // Timers TEST HARNESS
//SUCCESS - printed microsecond and millisecond values are are around 100 ms apart

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Timers.h"


int main(void) {
    BOARD_Init();
    Timers_Init();

    uint32_t init_ms = Timers_GetMilliSeconds();
    uint32_t init_us = Timers_GetMicroSeconds();
    while(TRUE) {
        printf("ms: %011d\r\nus: %011d\r\n\r\n", Timers_GetMilliSeconds()-init_ms, Timers_GetMicroSeconds()-init_us);
#ifdef STM32F4
        // TODO(nubby): Add a dummy timer function to `Timers.h`.
        // sleep(0.001)
        HAL_Delay(1);
#endif  /*  STM32F4 */
    }
}
#endif
