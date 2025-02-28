/*
 * LCD16X2_cfg.h
 *
 *  Created on: Feb 25, 2025
 *      Author: PanTalir
 */

#ifndef LCD16X2_CFG_H_
#define LCD16X2_CFG_H_

#include "main.h"
#include "LCD16X2.h"

typedef struct
{
	//LCD Instance
	uint8_t LCD16X2_Instance;


	//LCD Pin: D4
	GPIO_TypeDef * D4_GPIOx;
	uint16_t D4_PINx;

	//LCD Pin: D5
	GPIO_TypeDef * D5_GPIOx;
	uint16_t D5_PINx;

	//LCD Pin: D6
	GPIO_TypeDef * D6_GPIOx;
	uint16_t D6_PINx;

	//LCD Pin: D7
	GPIO_TypeDef * D7_GPIOx;
	uint16_t D7_PINx;

	//LCD Pin: EN
	GPIO_TypeDef * EN_GPIOx;
	uint16_t EN_PINx;

	//LCD Pin: RS
	GPIO_TypeDef * RS_GPIOx;
	uint16_t RS_PINx;
}LCD16X2_CfgType;

extern const LCD16X2_CfgType LCD16X2_CfgParam[LCD16X2_MAX];

#endif /* LCD16X2_CFG_H_ */
