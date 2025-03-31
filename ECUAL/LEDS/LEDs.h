#ifndef LEDS_H
#define LEDS_H_

#define HAL_GPIO_MODULE_ENABLED

#include "stm32g0xx.h.h"

//Number of LEDs
#define LED_UNITS   2


typedef struct 
{
    GPIO_TypeDef *  LED_GPIO;
    /* 
    GPIOA
    GPIOB
    ...
    */
   uint16_t         LED_PIN;
   /*
   GPIO_PIN_1
   GPIO_PIN_2
   ...
   */
}LED_CfgType;


//////////Prototypes of all functions//////////

void LEDs_Init(void);
void LED_ON(uint16_t au16_Instance);
void LED_OFF(uint16_t au16_Instance);

#endif