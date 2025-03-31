#include "LEDs.h"

const LED_CfgType LED_CfgParam[LED_UNITS] = 
{
    {
        //LED 1 Conf.
        GPIOA,
        GPIO_PIN_6
    },
    {
        //LED 2 Conf.
        GPIOA,
        GPIO_PIN_7
    },
    {
        //LED 3 Conf.
        GPIOB,
        GPIO_PIN_0
    },
    {
        //LED 4 Conf.
        GPIOB,
        GPIO_PIN_1
    }
};