#ifndef IL9225_H_
#define IL9225_H_

#include "main.h"
#include "IL9225.h"



typedef struct 
{   
    //CS - Chip select
    GPIO_TypeDef* CS_GPIOx;
    uint16_t CS_PINx;

    //RS - Register select
    GPIO_TypeDef* RS_GPIOx;
    uint16_t RS_PINx;

    //SCL - Clock
    GPIO_TypeDef* SCL_GPIOx;
    uint16_t SCL_PINx;

    //RST - Reset
    GPIO_TypeDef* RST_GPIOx;
    uint16_t RST_PINx;

    //SDI - Serial data Input
    GPIO_TypeDef* SDI_GPIOx;
    uint16_t SDI_PINx;
    
}IL9225_CfgType;

extern const IL9225_CfgType IL9225_CfgParam[DISPLAY_NUM];

#endif /* IL9225_H_ */