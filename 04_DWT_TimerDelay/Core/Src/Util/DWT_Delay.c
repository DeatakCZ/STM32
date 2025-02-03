/*
 * DWT_Delay.c
 *
 *  Created on: Feb 3, 2025
 *      Author: PanTalir
 */

#include "DWT_Delay.h"


uint32_t DWT_Delay_Init(void)
{
	//Disable TRC
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; 	//~0x01000000;
	//Enable TRC
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;		// 0x01000000;

	//Disable clock cycle counter
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;				//~0x00000001;
	//Enable clock cycle counter
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;				// 0x00000001;

	//Reset the clock cycle counter
	DWT->CYCCNT = 0;

	// 3 no operation instructions = nop
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");

	//Check if clock cycle counter has started
	if (DWT->CYCCNT)
	{
		return 0;	//Clock cycle has started
	}
	else
	{
		return 1;	//CLock cycle counter not started
	}
}
