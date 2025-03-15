#include "I2C_LCD_cfg.h"
#include "I2C_LCD.h"

extern I2C_HandleTypeDef hi2c1;

const I2C_LCD_CfgType I2C_LCD_CfgParam[I2C_LCD_MAX] = 
{
    {
        //Configuration parameters for I2C LCD Instance #1
        I2C_LCD_1,  //I2C LCD Module Instance Index
        &hi2c1,     //I2C Hardware Peripheral handle
        0x3f,       //I2C LCD Hardware Device Address
        16,         //I2C LCD Columns Count
        2           //I2C LCD Rows Count
    }
};