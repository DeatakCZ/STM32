#ifndef WS2812B_TIMER_H
#define WS2812B_TIMER_H

#include "main.h"
#include "stm32f1xx_hal_tim.h"
#include <stdint.h>

/**
 * @brief Timer-based WS2812B LED Library
 * 
 * This library uses Timer PWM to generate precise WS2812B protocol timing
 * for reliable LED control.
 */

// ============================================================================
// CONSTANTS AND DEFINITIONS
// ============================================================================

// WS2812B Protocol Timing (in nanoseconds)
#define WS2812B_T0H_NS    350    // 0-bit high time
#define WS2812B_T0L_NS    800    // 0-bit low time
#define WS2812B_T1H_NS    700    // 1-bit high time
#define WS2812B_T1L_NS    600    // 1-bit low time
#define WS2812B_RESET_NS  50000  // Reset time (50us)

// Timer configuration for 72MHz system clock
#define WS2812B_TIMER_PRESCALER    0    // No prescaler
#define WS2812B_TIMER_PERIOD        72   // 72MHz / 72 = 1MHz (1us per count)
#define WS2812B_TIMER_FREQ          1000000  // 1MHz timer frequency

// PWM duty cycles for WS2812B protocol (calculated for 72MHz clock)
#define WS2812B_PWM_T0H_DUTY        28   // 28% duty cycle for 0-bit high (350ns/1250ns)
#define WS2812B_PWM_T1H_DUTY        56   // 56% duty cycle for 1-bit high (700ns/1250ns)

// Maximum number of LEDs
#define WS2812B_MAX_LEDS      32

// Configurable brightness (0-255, default 64 = 25%)
#define WS2812B_MAX_BRIGHTNESS 128

// Color structure for RGB values
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGBColor_t;

// WS2812B handle structure
typedef struct {
    TIM_HandleTypeDef* htim;
    uint32_t channel;
    uint16_t led_count;
    RGBColor_t led_buffer[WS2812B_MAX_LEDS];
} WS2812B_Timer_Handle_t;

// ============================================================================
// FUNCTION DECLARATIONS
// ============================================================================

// Initialization
void WS2812B_Timer_Init(WS2812B_Timer_Handle_t* handle, TIM_HandleTypeDef* htim, uint32_t channel, uint16_t num_leds);

// Core functions
void WS2812B_Timer_SetLED(WS2812B_Timer_Handle_t* handle, uint16_t index, RGBColor_t color);
void WS2812B_Timer_SetLED_RGB(WS2812B_Timer_Handle_t* handle, uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
void WS2812B_Timer_SetAllLEDs(WS2812B_Timer_Handle_t* handle, RGBColor_t color);
void WS2812B_Timer_ClearAll(WS2812B_Timer_Handle_t* handle);
void WS2812B_Timer_ClearBuffer(WS2812B_Timer_Handle_t* handle);
void WS2812B_Timer_Update(WS2812B_Timer_Handle_t* handle);

// Utility functions
uint16_t WS2812B_Timer_GetLEDCount(WS2812B_Timer_Handle_t* handle);
uint16_t WS2812B_Timer_GetMaxLEDs(void);

// Brightness scaling function
RGBColor_t WS2812B_Timer_ScaleBrightness(RGBColor_t color);

// Test functions
void WS2812B_Timer_TestIndividualLEDs(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Timer_TestSolidColor(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms);
void WS2812B_Timer_TestLastLEDColors(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);

// Predefined colors (automatically scaled to WS2812B_MAX_BRIGHTNESS)
RGBColor_t WS2812B_Timer_Color_Red(void);
RGBColor_t WS2812B_Timer_Color_Green(void);
RGBColor_t WS2812B_Timer_Color_Blue(void);
RGBColor_t WS2812B_Timer_Color_White(void);
RGBColor_t WS2812B_Timer_Color_Black(void);
RGBColor_t WS2812B_Timer_Color_Yellow(void);
RGBColor_t WS2812B_Timer_Color_Purple(void);
RGBColor_t WS2812B_Timer_Color_Cyan(void);

#endif // WS2812B_TIMER_H 