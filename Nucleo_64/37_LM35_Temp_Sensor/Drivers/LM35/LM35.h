#ifndef LM35_H_
#define LM35_H_

#define HAL_ADC_MODULE_ENABLED

#include "stm32f1xx_hal.h"

//Number of LM35 Sensors used in project
#define SENSORS_NUM 1

typedef struct
{
    GPIO_TypeDef*   LM35_GPIO;
    ADC_TypeDef*    ADC_Instance;
    uint32_t        ADC_CH;
}LM35_CfgType;


//Prototypes of all functions
void LM35_Init(uint16_t LM35_Instance);
float LM35_Read(uint16_t LM35_Instance, uint8_t *debugValue);

#endif