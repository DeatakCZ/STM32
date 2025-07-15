/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LM35_Pin GPIO_PIN_3
#define LM35_GPIO_Port GPIOA
#define TIM_DATA_Pin GPIO_PIN_0
#define TIM_DATA_GPIO_Port GPIOB
#define TIM_LATCH_Pin GPIO_PIN_1
#define TIM_LATCH_GPIO_Port GPIOB
#define TIM_CLOCK_Pin GPIO_PIN_2
#define TIM_CLOCK_GPIO_Port GPIOB
#define RELAY2_Pin GPIO_PIN_11
#define RELAY2_GPIO_Port GPIOA
#define RELAY1_Pin GPIO_PIN_12
#define RELAY1_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_3
#define BUTTON2_GPIO_Port GPIOB
#define BUTTON1_Pin GPIO_PIN_4
#define BUTTON1_GPIO_Port GPIOB
#define SWITCH1_Pin GPIO_PIN_5
#define SWITCH1_GPIO_Port GPIOB
#define SWITCH2_Pin GPIO_PIN_6
#define SWITCH2_GPIO_Port GPIOB
#define TEMP_LED_Pin GPIO_PIN_7
#define TEMP_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
