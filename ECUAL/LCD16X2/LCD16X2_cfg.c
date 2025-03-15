#include "LCD16X2_cfg.h"
#include "LCD16X2.h"

const LCD16X2_CfgType LCD16X2_CfgParam[LCD16X2_MAX] = 
{
	{
		LCD16X2_1,				//Instance number
		GPIOA, GPIO_PIN_7,		//D4
		GPIOA, GPIO_PIN_8,		//D5
		GPIOA, GPIO_PIN_9,		//D6
		GPIOA, GPIO_PIN_10,		//D7
		GPIOA, GPIO_PIN_11,		//EN
		GPIOA, GPIO_PIN_12,		//RS
	}
};
