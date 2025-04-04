#include "LCD16X2.h"
#include "LCD16X2_cfg.h"
#include "../../Util/Util.h"



void LCD16X2_DATA(uint8_t LCD16X2_Index, unsigned char Data)
{
	if(Data & 1)
		HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D4_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D4_PINx, 1);
	else
		HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D4_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D4_PINx, 0);
	if(Data & 2)
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D5_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D5_PINx, 1);
		else
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D5_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D5_PINx, 0);
	if(Data & 4)
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D6_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D6_PINx, 1);
		else
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D6_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D6_PINx, 0);
	if(Data & 8)
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D7_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D7_PINx, 1);
		else
			HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].D7_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].D7_PINx, 0);
}


void LCD16X2_CMD(uint8_t LCD16X2_Index, unsigned char CMD)
{
	//Select command register
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].RS_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].RS_PINx, 0);
	//Move the command data to LCD
	LCD16X2_DATA(LCD16X2_Index, CMD);
	//Send clock signal to Enable pin
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 1);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay*2);
}


void LCD16X2_Clear(uint8_t LCD16X2_Index)
{
	LCD16X2_CMD(LCD16X2_Index, 0);
	LCD16X2_CMD(LCD16X2_Index, 1);
	DELAY_MS(2);
}


void LCD16X2_Set_Cursor(uint8_t LCD16X2_Index, unsigned char r, unsigned char c)
{
	unsigned char Temp, Low4, High4;
	if(r == 1)
	{
		Temp 	= 0x80 + c -1; //0x80 is used to move the cursor
		High4 	= Temp >> 4;
		Low4 	= Temp & 0x0F;
		LCD16X2_CMD(LCD16X2_Index, High4);
		LCD16X2_CMD(LCD16X2_Index, Low4);
	}
	if(r == 2)
	{
		Temp 	= 0xC0 + c -1; //0x80 is used to move the cursor
		High4 	= Temp >> 4;
		Low4 	= Temp & 0x0F;
		LCD16X2_CMD(LCD16X2_Index, High4);
		LCD16X2_CMD(LCD16X2_Index, Low4);
	}
}


void LCD16X2_Init(uint8_t LCD16X2_Index)
{
	//ACc. to datasheet, you have to wait at least 40ms after power up before interaction
	while(HAL_GetTick() < 50);
	//The init. procedure as described in datasheet
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].RS_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].RS_PINx, 0);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	//Init in 4-bit mode
	LCD16X2_DATA(LCD16X2_Index, 0x00);
	DELAY_MS(150);
	LCD16X2_CMD(LCD16X2_Index, 0x03);
	DELAY_MS(5);
	LCD16X2_CMD(LCD16X2_Index, 0x03);
	DELAY_MS(5);
	LCD16X2_CMD(LCD16X2_Index, 0x03);
	DELAY_US(150);

	LCD16X2_CMD(LCD16X2_Index, 0x02);
	LCD16X2_CMD(LCD16X2_Index, 0x02);
	LCD16X2_CMD(LCD16X2_Index, 0x08);
	LCD16X2_CMD(LCD16X2_Index, 0x00);
	LCD16X2_CMD(LCD16X2_Index, 0x0C);
	LCD16X2_CMD(LCD16X2_Index, 0x00);
	LCD16X2_CMD(LCD16X2_Index, 0x06);
	LCD16X2_CMD(LCD16X2_Index, 0x00);
	LCD16X2_CMD(LCD16X2_Index, 0x01);
}


void LCD16X2_Write_Char(uint8_t LCD16X2_Index, char Data)
{
	char Low4, High4;
	Low4 	= Data & 0x0F;
	High4 	= Data & 0xF0;

	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].RS_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].RS_PINx, 1);

	LCD16X2_DATA(LCD16X2_Index, (High4>>4));
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 1);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay*2);

	LCD16X2_DATA(LCD16X2_Index, Low4);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 1);
	DELAY_US(LCD_Delay);
	HAL_GPIO_WritePin(LCD16X2_CfgParam[LCD16X2_Index].EN_GPIOx, LCD16X2_CfgParam[LCD16X2_Index].EN_PINx, 0);
	DELAY_US(LCD_Delay*2);
}


void LCD16X2_Write_String(uint8_t LCD16X2_Index, char *str)
{
	for(int i = 0 ; str[i] != '\0' ; i++ )
	{
		LCD16X2_Write_Char(LCD16X2_Index, str[i]);
	}
}


void LCD16X2_SL(uint8_t LCD16X2_Index)
{
	LCD16X2_CMD(LCD16X2_Index, 0x01);
	LCD16X2_CMD(LCD16X2_Index, 0x08);
}


void LCD16X2_SR(uint8_t LCD16X2_Index)
{
	LCD16X2_CMD(LCD16X2_Index, 0x01);
	LCD16X2_CMD(LCD16X2_Index, 0x0C);
}
