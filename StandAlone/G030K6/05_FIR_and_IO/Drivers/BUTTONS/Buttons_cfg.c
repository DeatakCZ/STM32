#include "Buttons.h"

const BTN_CfgType BTN_CfgParam[BTN_UNITS] = 
{
    {
        //Button 1 configuration
        GPIOB,
        GPIO_PIN_2,
        GPIO_NOPULL,
        BTNS_FILTER_ORDER
    },
    {
        //Button 2 configuration
        GPIOA,
        GPIO_PIN_8,
        GPIO_NOPULL,
        BTNS_FILTER_ORDER
    },
    {
        //Button 3 configuration
        GPIOA,
        GPIO_PIN_9,
        GPIO_NOPULL,
        BTNS_FILTER_ORDER
    },
    {
        //Button 4 configuration
        GPIOC,
        GPIO_PIN_6,
        GPIO_NOPULL,
        BTNS_FILTER_ORDER
    }
};

uint8_t Filters_Buffers[BTN_UNITS][BTNS_FILTER_ORDER+1] = {0};