// TODO(nubby): Convert this into an interrupt-driven ADC module.
/*
 * @file   Adc.c
 * @author Adam Korycki
 *
 * @date 16 Sep 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Adc.h"

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

/**
 * ADC_Init(void)
 *
 * @brief Initializes the ADC subsystem with an interrupt; selects ADC Pin4 by 
 *        default.
 * 
 * @return SUCCESS or ERROR
 */
char ADC_Init(void) {
	if (init_status == FALSE) { // if ADC has not been initialized
#ifdef STM32F4
    ADC_ChannelConfTypeDef sConfig = {0};

    /** Configure the global features of the ADC (Clock, Resolution, Data
     * Alignment and number of conversion).
    */
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
      //Error_Handler();
      return ERROR;
    }

    /** Configure for the selected ADC regular channel its corresponding rank in
     * the sequencer and its sample time.
    */
    sConfig.Channel = POT;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      //Error_Handler();
      return ERROR;
    }
#endif  /*  STM32F4 */
    init_status = TRUE;
  }
	return SUCCESS;
}

/**
 * ADC_End(void)
 *
 * @brief Disables the A/D subsystem and release the pins used
 */
void ADC_End(void){
#ifdef STM32F4
  /*
	HAL_ADC_Stop(&hadc1);
  */
  HAL_ADC_Stop_IT(&hadc1);
	HAL_ADC_DeInit(&hadc1);
#endif  /*  STM32F4 */
}

/*
*/

//#define ADC_TEST
#ifdef ADC_TEST //ADC TEST HARNESS
// SUCCESS - printed analog values for each channel are correct

#include <stdio.h>
#include "BOARD.h"
#include "ADC.h"


struct ADC_result {
  uint32_t event;
  int16_t voltage;
};

static struct ADC_result adc_result = {FALSE, 0};


int main(void) {
  // Initialize.
	BOARD_Init();
	if (!ADC_Init()) {
    return ERROR;
  }

  while(1<2) {
    if (adc_result.event) {
      printf("Potentiometer reading: %d\r\n", (int)adc_result.voltage);
      adc_result.event = FALSE;
      HAL_ADC_Start_IT(&hadc1);
    }
    HAL_Delay(200);
    /*
			printf("POT   = %d\r\n", ADC_Read(POT));
			printf("ADC_0 = %d\r\n", ADC_Read(ADC_0));
			printf("ADC_1 = %d\r\n", ADC_Read(ADC_1));
			printf("ADC_2 = %d\r\n", ADC_Read(ADC_2));
			printf("ADC_3 = %d\r\n", ADC_Read(ADC_3));
			printf("ADC_4 = %d\r\n", ADC_Read(ADC_4));
			printf("ADC_5 = %d\r\n\r\n", ADC_Read(ADC_5));
//#ifdef STM32F4
      // TODO(nubby): Add a dummy timer function to `timers.h`.
      // sleep(0.5)
			HAL_Delay(500);
      */
//#endif  /*  STM32F4 */
  }
}


/**
 * HAL_ADC_ConvCpltCallback()
 *
 * @brief Callback to reading ADC data on change. This is required for an
 *        interrupt-driven ADC.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
  if (hadc == &hadc1) {
    adc_result.voltage = HAL_ADC_GetValue(&hadc1);
    adc_result.event = TRUE;
  }
}

#endif
