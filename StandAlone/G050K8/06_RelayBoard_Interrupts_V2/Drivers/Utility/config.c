#include "config.h"
#include "main.h"

const DIP_CfgType DIP_CfgParam = 
{
    //Latch Port & Pin
    DIP_LATCH_GPIO_Port,
    DIP_LATCH_Pin,

    //Data Port & Pin
    DIP_DATA_GPIO_Port,
    DIP_DATA_Pin,

    //Clock Port & Pin
    DIP_CLOCK_GPIO_Port,
    DIP_CLOCK_Pin
};

const Inputs_CfgType Inputs_CfgParam =
{
    //BTN2 Port & Pin
    BTN_2_GPIO_Port,
    BTN_2_Pin,
    //BTN1 Port & Pin
    BTN_1_GPIO_Port,
    BTN_1_Pin,
    //SW1 Port & Pin
    SW_1_GPIO_Port,
    SW_1_Pin,
    //SW2 Port & Pin
    SW_2_GPIO_Port,
    SW_2_Pin
};

const Outputs_CfgType Outputs_CfgParam =
{
    //Relay1 Port & Pin
    RELAY_1_GPIO_Port,
    RELAY_1_Pin,
    
    //Relay2 Port & Pin
    RELAY_2_GPIO_Port,
    RELAY_2_Pin,

    //Temp LED Port & Pin
    TEMP_LED_GPIO_Port,
    TEMP_LED_Pin
};

Timers_CfgType Timers_CfgParam =
{
    0,
    0,
    0,
    0
};


// what is wanted behaviour?
// When button is pressed, relay is activated 
// Or When Button is pressed timer is started, therefore relay could be switched off before button is let go

void HAL_IncTick(void)
{
if(Timers_CfgParam.Relay1_RunningTimer > 0)
    {
        Timers_CfgParam.Relay1_RunningTimer--;
        if(Timers_CfgParam.Relay1_RunningTimer == 0 && HAL_GPIO_ReadPin(Inputs_CfgParam.SW1_Port, Inputs_CfgParam.SW1_Pin) == GPIO_PIN_SET)
        {
            HAL_GPIO_WritePin(Outputs_CfgParam.Relay1_Port, Outputs_CfgParam.Relay1_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(Outputs_CfgParam.TempLED_Port, Outputs_CfgParam.TempLED_Pin, GPIO_PIN_RESET);
        }
    }

    if(Timers_CfgParam.Relay2_RunningTimer > 0)
    {
        Timers_CfgParam.Relay2_RunningTimer--;
        if(Timers_CfgParam.Relay2_RunningTimer == 0 && HAL_GPIO_ReadPin(Inputs_CfgParam.SW2_Port, Inputs_CfgParam.SW2_Pin) == GPIO_PIN_SET)
        {
            HAL_GPIO_WritePin(Outputs_CfgParam.Relay2_Port, Outputs_CfgParam.Relay2_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(Outputs_CfgParam.TempLED_Port, Outputs_CfgParam.TempLED_Pin, GPIO_PIN_RESET);
        }
    }
}