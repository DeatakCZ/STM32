#ifndef INPUTS_H
#define INPUTS_H

#include "stm32g0xx_hal.h"

void HAL_GPIO_EXTI_Rising_Callback(uint16_t);
void HAL_GPIO_EXTI_Falling_Callback(uint16_t);



#endif