#include "IL9225.h"
#include "IL9225_cfg.h"

void IL9225_setUp(uint8_t IL9225_Index)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    uint8_t i = 0;

    for( i = 0 ; i < DISPLAY_NUM ; i++ )
    {
        //Configure LED GPIO Pins
        if( ( IL9225_CfgParam[i].CS_GPIOx || IL9225_CfgParam[i].RS_GPIOx || IL9225_CfgParam[i].SCL_GPIOx || IL9225_CfgParam[i].RST_GPIOx || IL9225_CfgParam[i].SDI_GPIOx ) == GPIOA)
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
        }
        else if( ( IL9225_CfgParam[i].CS_GPIOx || IL9225_CfgParam[i].RS_GPIOx || IL9225_CfgParam[i].SCL_GPIOx || IL9225_CfgParam[i].RST_GPIOx || IL9225_CfgParam[i].SDI_GPIOx ) == GPIOB)
        {
            __HAL_RCC_GPIOB_CLK_ENABLE();
        }
        else if( ( IL9225_CfgParam[i].CS_GPIOx || IL9225_CfgParam[i].RS_GPIOx || IL9225_CfgParam[i].SCL_GPIOx || IL9225_CfgParam[i].RST_GPIOx || IL9225_CfgParam[i].SDI_GPIOx ) == GPIOC)
        {
            __HAL_RCC_GPIOC_CLK_ENABLE();
        }
        else if( ( IL9225_CfgParam[i].CS_GPIOx || IL9225_CfgParam[i].RS_GPIOx || IL9225_CfgParam[i].SCL_GPIOx || IL9225_CfgParam[i].RST_GPIOx || IL9225_CfgParam[i].SDI_GPIOx ) == GPIOD)
        {
            __HAL_RCC_GPIOD_CLK_ENABLE();
        }
        else if( ( IL9225_CfgParam[i].CS_GPIOx || IL9225_CfgParam[i].RS_GPIOx || IL9225_CfgParam[i].SCL_GPIOx || IL9225_CfgParam[i].RST_GPIOx || IL9225_CfgParam[i].SDI_GPIOx ) == GPIOE)
        {
            __HAL_RCC_GPIOE_CLK_ENABLE();
        }

        GPIO_InitStruct.Pin = IL9225_CfgParam[i].CS_PINx;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(IL9225_CfgParam[i].IL9225_GPIOx, &GPIO_InitStruct);
    }
}

void Init(uint8_t IL9225_Index)
{
//    RIM[1:0] ->
//
//Start byte:
// 1 2 3 4 5 6 7  8 
// x x x x x x RS R/W
// R/W | RS | Function
//  0  | 0  | Write an index to IR register
//  1  | 0  | Read an internal status
//  0  | 1  | Write to control registers or the internal GRAM by WDR register
//  1  | 1  | Read from the internal GRAM by RDR register

}