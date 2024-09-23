/*
 * Future-fitted interface from PIC32 to STM32 architectures. 
 *
 * File:            BOARD.c
 * Author:          nubby 
 * Contributors:    Adam Korycki, Max Dunne
 *
 * Created on July 29, 2024. 
 */


#ifdef STM32F4
#include <BOARD.h>
#include <Leds.h>
#else
#include <stdlib.h>
#include "BOARD.h"
#endif  /*  STM32F4  */

static void Board_GPIO_Init(void);
static void USART2_UART_Init(void);

static uint8_t init_status = FALSE;

/**
 * @function  SystemClock_Config(void)
 * @param     None
 * @return    None
 * @brief     Initialize onboard RC oscillators and bus clocks.
 */
void SystemClock_Config();

/**
 * @function  Error_Handler(void)
 * @param     None
 * @return    None
 * @brief     Configurable handler for error debugging.
 */
void Error_Handler();


/* minimum GPIO pin assocations for NUCLEO64*/
#define B1_Pin GPIO_PIN_13 // onboard blue push button
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2 // USB-UART (USART2)
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

/* define UART2 handler and setup printf() functionality */
#ifdef STM32F4
UART_HandleTypeDef huart2;
#endif  /* STM32F4 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
#ifdef STM32F4
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif  /* STM32F4 */


/**
 * @function BOARD_Init(void)
 * @param None
 * @return None
 * @brief Set the clocks up for the board, initializes the serial port and sets the leds to low.
 * @author Adam Korycki, 2023.09.03  */
void BOARD_Init() {
  if (init_status == FALSE) { // if Board has not been initialized
#ifdef STM32F4
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();
#endif  /* STM32F4 */
    /* configure GPIO/analog pins */
    Board_GPIO_Init();
    /* Configure usb-UART2 @ 115200 baud */
    USART2_UART_Init();
#ifdef STM32F4
    LEDs_Init();
#endif  /*  STM32F4 */
    init_status = TRUE;
  }
}

/**
 * @function BOARD_End(void)
 * @param None
 * @return None
 * @brief Shuts down all peripherals; turns all pins into input.
 * @author nubby, 2024.07.29  */
void BOARD_End()
{
#ifdef STM32F4
	// TODO(nubby):
    // kill off all interrupts except serial and clear their flags

    // kill off all interrupts except A/D and clear their flags

    // set all ports to be digital inputs
#else
    exit(0);
#endif
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
#ifdef STM32F4
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
#endif  /* STM32F4 */
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART2_UART_Init(void)
{

#ifdef STM32F4
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
#endif  /* STM32F4 */
}

static void Board_GPIO_Init(void)
{
#ifdef STM32F4
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin (blue push button)*/
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
#endif  /* STM32F4 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
#ifdef STM32F4
  __disable_irq();
#endif  /* STM32F4 */
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

