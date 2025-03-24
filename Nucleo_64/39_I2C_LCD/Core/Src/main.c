/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "../../I2C_LCD/I2C_LCD.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MyI2C_LCD I2C_LCD_1
#define SPEED 400

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t HeartChar[] = {0x00, 0x0a, 0x15, 0x11, 0x11, 0x0a, 0x04, 0x00};
uint8_t SmileChar[] = {0x00, 0x0a, 0x0a, 0x00, 0x1f, 0x11, 0x09, 0x06};
uint8_t Flower1Char[] =     {0x13, 0x1e, 0x0e, 0x0f, 0x1b, 0x04, 0x15, 0x0e};
uint8_t Flower1InvChar[] =  {0x0c, 0x01, 0x11, 0x10, 0x04, 0x1b, 0x0a, 0x11};
uint8_t Flower2Char[] =     {0x19, 0x0f, 0x0e, 0x1e, 0x17, 0x04, 0x15, 0x0e};
uint8_t Flower2InvChar[] =  {0x06, 0x10, 0x11, 0x01, 0x08, 0x1b, 0x0a, 0x11};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Dance(uint8_t rounds, uint8_t mode)
{

  uint8_t i = 0, o = 0;

  for( int c = 0 ; c < rounds ; c++)
  {
    if(mode)
    {
      I2C_LCD_ShiftLeft(MyI2C_LCD);
      HAL_Delay(SPEED/2);
      I2C_LCD_ShiftLeft(MyI2C_LCD);
      HAL_Delay(SPEED);
      I2C_LCD_ShiftRight(MyI2C_LCD);
      HAL_Delay(SPEED/2);
      I2C_LCD_ShiftRight(MyI2C_LCD);
      HAL_Delay(SPEED);
    }  


    for (int p = 0; p < 4 ; p++)
    {
      I2C_LCD_SetCursor(MyI2C_LCD, 12, 1);
      switch(i)
      {
        case 0:
        if(!o)
        {
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 2);
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 3);
          o = 1;
        }
        else
        {
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 4);
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 5);
          i = 1;
          o = 0;
        }
        break;
      case 1:
        if(!o)
        {
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 3);
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 2);
          o = 1;
        }
        else
        {
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 5);
          I2C_LCD_PrintCustomChar(MyI2C_LCD, 4);
          i = 1;
          o = 0;
        }
      } 
      HAL_Delay(SPEED);
    }
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  I2C_LCD_Init(MyI2C_LCD);

  I2C_LCD_CreateCustomChar(MyI2C_LCD, 0, HeartChar);
  I2C_LCD_CreateCustomChar(MyI2C_LCD, 1, SmileChar);
  I2C_LCD_CreateCustomChar(MyI2C_LCD, 2, Flower1Char);
  I2C_LCD_CreateCustomChar(MyI2C_LCD, 3, Flower2Char);
  I2C_LCD_CreateCustomChar(MyI2C_LCD, 4, Flower1InvChar);
  I2C_LCD_CreateCustomChar(MyI2C_LCD, 5, Flower2InvChar);

  I2C_LCD_SetCursor(MyI2C_LCD, 0, 0);
  I2C_LCD_WriteString(MyI2C_LCD, " !Hello World!");
  I2C_LCD_SetCursor(MyI2C_LCD, 0, 1);
  I2C_LCD_WriteString(MyI2C_LCD, " !I2C_LCD!");

  HAL_Delay(SPEED*2);


  I2C_LCD_PrintCustomChar(MyI2C_LCD, 0);
  I2C_LCD_PrintCustomChar(MyI2C_LCD, 1);
  I2C_LCD_PrintCustomChar(MyI2C_LCD, 2);
  I2C_LCD_PrintCustomChar(MyI2C_LCD, 3);

  HAL_Delay(SPEED*2);



  I2C_LCD_NoBacklight(MyI2C_LCD);   HAL_Delay(SPEED*2);
  I2C_LCD_Backlight(MyI2C_LCD);     HAL_Delay(SPEED*2);
  Dance(1,1);
  I2C_LCD_Cursor(MyI2C_LCD);        HAL_Delay(SPEED*2);
  I2C_LCD_Blink(MyI2C_LCD);         HAL_Delay(SPEED*2);
  I2C_LCD_NoBlink(MyI2C_LCD);       HAL_Delay(SPEED*2);
  I2C_LCD_NoCursor(MyI2C_LCD);      HAL_Delay(SPEED*2);
  I2C_LCD_NoDisplay(MyI2C_LCD);     HAL_Delay(SPEED*2);
  I2C_LCD_Display(MyI2C_LCD);       HAL_Delay(SPEED*2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    Dance(1, 0);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
