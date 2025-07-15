#include "DIPs.h"
#include "config.h"




void LatchData(void)
{
	HAL_GPIO_WritePin(DIP_CfgParam.Latch_Port, DIP_CfgParam.Latch_Pin, GPIO_PIN_RESET);
	asm("NOP");
	asm("NOP");
	//HAL_Delay(1);			// needs 24ns at 4,5V
	HAL_GPIO_WritePin(DIP_CfgParam.Latch_Port, DIP_CfgParam.Latch_Pin, GPIO_PIN_SET);
	asm("NOP");
	asm("NOP");
	//HAL_Delay(1);
}


void TickClock(void)
{
	HAL_GPIO_WritePin(DIP_CfgParam.Clock_Port, DIP_CfgParam.Clock_Pin, GPIO_PIN_SET);
	asm("NOP");
	asm("NOP");
	//HAL_Delay(1);			
	HAL_GPIO_WritePin(DIP_CfgParam.Clock_Port, DIP_CfgParam.Clock_Pin, GPIO_PIN_RESET);
	asm("NOP");
	asm("NOP");
	//HAL_Delay(1);
}


void CalculateDelay(uint8_t DIP1, uint8_t DIP2, uint16_t* Timer1, uint16_t* Timer2)
{
	*Timer1 = 0;
	*Timer2 = 0;

	*Timer1 = (DIP1 * DIP_DELAY)+1;
	*Timer2 = (DIP2 * DIP_DELAY)+1;
}


void ReadDIPSwitch(uint16_t* Timer1, uint16_t* Timer2)
{
	LatchData();

	uint8_t DIP1 = 0x00;
	uint8_t DIP2 = 0x00;

	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		if(i < 4)
		{
			DIP1 = DIP1 << 1;
			if(HAL_GPIO_ReadPin(DIP_CfgParam.Data_Port, DIP_CfgParam.Data_Pin) == 1)
			{
				DIP1 |= 0x01;
			}
			else
			{
				asm("NOP");
				asm("NOP");
			}
		}
		else if(i>=4)
		{
			DIP2 = DIP2 << 1;
			if(HAL_GPIO_ReadPin(DIP_CfgParam.Data_Port, DIP_CfgParam.Data_Pin) == 1)
			{
				DIP2 |= 0x01;
			}
			else
			{
				asm("NOP");
				asm("NOP");
			}
		}

		TickClock();
	}

	CalculateDelay(DIP1, DIP2, Timer1, Timer2);
}