#include "Inputs.h"
#include "config.h"


// BTNs only Falling edge
// SWs  both edges
// Falling is triggered,
// Rising is unpressed


// BUG: Input is only taken in when switch is pressed first, then button
// BUG: After new values are saved, old delay is activated
 
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    __disable_irq();

//If both button and switch are pressed, read DIP switches to refresh timer values
    if(((GPIO_Pin == Inputs_CfgParam.BTN1_Pin) && (HAL_GPIO_ReadPin(Inputs_CfgParam.SW1_Port, Inputs_CfgParam.SW1_Pin) == GPIO_PIN_RESET)) || 
       ((GPIO_Pin == Inputs_CfgParam.BTN2_Pin) && (HAL_GPIO_ReadPin(Inputs_CfgParam.SW2_Port, Inputs_CfgParam.SW2_Pin) == GPIO_PIN_RESET)) ||
       ((GPIO_Pin == Inputs_CfgParam.SW1_Pin) && (HAL_GPIO_ReadPin(Inputs_CfgParam.BTN1_Port, Inputs_CfgParam.BTN1_Pin) == GPIO_PIN_RESET))|| 
       ((GPIO_Pin == Inputs_CfgParam.SW2_Pin) && (HAL_GPIO_ReadPin(Inputs_CfgParam.BTN2_Port, Inputs_CfgParam.BTN2_Pin) == GPIO_PIN_RESET)))
    {
        ReadDIPSwitch(&Timers_CfgParam.Relay1_Timer, &Timers_CfgParam.Relay2_Timer);
    }
//If switch is pressed, activated relays
    if(GPIO_Pin == Inputs_CfgParam.SW1_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay1_Port, Outputs_CfgParam.Relay1_Pin, GPIO_PIN_SET);
    }
    if(GPIO_Pin == Inputs_CfgParam.SW2_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay2_Port, Outputs_CfgParam.Relay2_Pin, GPIO_PIN_SET);
    }
//If Buttons are pressed, activate relays and set timers
    if(GPIO_Pin == Inputs_CfgParam.BTN1_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay1_Port, Outputs_CfgParam.Relay1_Pin, GPIO_PIN_SET);
        Timers_CfgParam.Relay1_RunningTimer = Timers_CfgParam.Relay1_Timer;

        HAL_GPIO_WritePin(Outputs_CfgParam.TempLED_Port, Outputs_CfgParam.TempLED_Pin, GPIO_PIN_SET);
    }
    if(GPIO_Pin == Inputs_CfgParam.BTN2_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay2_Port, Outputs_CfgParam.Relay2_Pin, GPIO_PIN_SET);
        Timers_CfgParam.Relay2_RunningTimer = Timers_CfgParam.Relay2_Timer;

        HAL_GPIO_WritePin(Outputs_CfgParam.TempLED_Port, Outputs_CfgParam.TempLED_Pin, GPIO_PIN_SET);
    }


    __enable_irq();
}



void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == Inputs_CfgParam.SW1_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay1_Port, Outputs_CfgParam.Relay1_Pin, GPIO_PIN_RESET);
    }
    else if(GPIO_Pin == Inputs_CfgParam.SW2_Pin)
    {
        HAL_GPIO_WritePin(Outputs_CfgParam.Relay2_Port, Outputs_CfgParam.Relay2_Pin, GPIO_PIN_RESET);
    }
}




