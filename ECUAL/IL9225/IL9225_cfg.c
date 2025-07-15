#include "IL9225.h"

const IL9225_CfgType IL9225_CfgParam[DISPLAY_NUM] = 
{
    //OLED DISPLAY #1 DRIVEN BY IL9225
    {
        GPIOA,
        GPIO_PIN_1,     //CS - Chip select
        GPIOA,
        GPIO_PIN_1,     //RS - Register select
        GPIOA,
        GPIO_PIN_1,     //SCL - Clock
        GPIOA,
        GPIO_PIN_1,     //RST - Reset
        GPIOA,
        GPIO_PIN_1     //SDI - Serial data Input

    }

}