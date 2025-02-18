/*
 * Timer_Delay.h
 *
 *  Created on: Feb 3, 2025
 *      Author: PanTalir
 */

#ifndef SRC_UTIL_TIMER_DELAY_H_
#define SRC_UTIL_TIMER_DELAY_H_

#include "stm32f1xx_hal.h"


void TimerDelay_Init(void);
void delay_us(uint16_t au16_us);
void delay_ms(uint16_t au16_ms);


#endif /* SRC_UTIL_TIMER_DELAY_H_ */
