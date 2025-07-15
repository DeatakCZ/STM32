#ifndef CONFIG_H
#define CONFIG_H

#include "stm32g0xx_hal.h"


#define DIP_DELAY 100           // ms delay per bit on DIP switch - 100 / 200

typedef struct
{
    GPIO_TypeDef *Latch_Port; 
    uint16_t Latch_Pin;
    GPIO_TypeDef *Data_Port; 
    uint16_t Data_Pin;
    GPIO_TypeDef *Clock_Port;
    uint16_t Clock_Pin;
} DIP_CfgType;

extern const DIP_CfgType DIP_CfgParam;

#endif