#ifndef DIPS_H_
#define DIPS_H_

#include "stdint.h"
#include "stm32g0xx_hal.h"
#include "config.h"

void LatchData( void );
void TickClock( void );

void ReadDIPSwitch( uint16_t*, uint16_t* );


#endif