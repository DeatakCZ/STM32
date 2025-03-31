#ifndef BUTTONS_H_
#define BUTTONS_H_

#define HAL_GPIO_MODULE_ENABLED

#include "stm32g0xx_hal.h"


//Number of button units used
#define BTN_UNITS       2

#define BTN_PRESSED     1
#define BTN_RELEASED    0

#define BTNS_FILTER_ORDER 8

typedef struct
{
    GPIO_TypeDef *  BTN_GPIO;
    /*
    GPIO A
    GPIO B
    ...
    */
    uint16_t         BTN_PIN;
    /*
    GPIO_PIN_1
    GPIO_PIN_2
    */
    uint16_t          PULL_MODE;
    /*
    GPIO_PULLUP
    GPIO_PULLDOWN
    GPIO_NOPULL
    */
    uint16_t Filter_Order;
    /*
    0
    1
    ...
    N
    */
}BTN_CfgType;

//////////Prototype of all functions//////////
void BTNs_Init(uint8_t* BTN_States);
void BTN_Main(void);
void BTN_Read(uint16_t au16_Instance, uint8_t* BTN_State);

#endif