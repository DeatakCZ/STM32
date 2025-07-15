#ifndef CONFIG_H
#define CONFIG_H

#include "stm32g0xx_hal.h"
#include "stdint.h"

#define DIP_DELAY 100           // ms delay per bit on DIP switch - 100 / 200





typedef struct
{
    // Latch Port & Pin
    GPIO_TypeDef *Latch_Port; 
    uint16_t Latch_Pin;
    // Data Port & Pin
    GPIO_TypeDef *Data_Port; 
    uint16_t Data_Pin;
    // Clock Port & Pin
    GPIO_TypeDef *Clock_Port;
    uint16_t Clock_Pin;
}DIP_CfgType;

typedef struct
{
    // BTN2 Port & Pin
    GPIO_TypeDef *BTN2_Port;
    uint16_t BTN2_Pin;
    //BTN1 Port & Pin
    GPIO_TypeDef *BTN1_Port;
    uint16_t BTN1_Pin;
    // SW1 Port & Pin
    GPIO_TypeDef *SW1_Port;
    uint16_t SW1_Pin;
    // SW2 Port & Pin
    GPIO_TypeDef *SW2_Port;
    uint16_t SW2_Pin;
}Inputs_CfgType;

typedef struct
{   
    // Relay1 Port & Pin
    GPIO_TypeDef *Relay1_Port;
    uint16_t Relay1_Pin;
    // Relay2 Port & Pin
    GPIO_TypeDef *Relay2_Port;
    uint16_t Relay2_Pin;
    // Temp LED Port & Pin
    GPIO_TypeDef *TempLED_Port;
    uint16_t TempLED_Pin;
}Outputs_CfgType;
    
typedef struct
{
    //Timer presets for relays activation
    uint16_t Relay1_Timer;
    uint16_t Relay2_Timer;

    //Timers for tracking running time/delay
    uint16_t Relay1_RunningTimer;
    uint16_t Relay2_RunningTimer;
}Timers_CfgType;

extern const DIP_CfgType DIP_CfgParam;
extern const Inputs_CfgType Inputs_CfgParam;
extern const Outputs_CfgType Outputs_CfgParam;
extern Timers_CfgType Timers_CfgParam;

void HAL_IncTick(void);

#endif