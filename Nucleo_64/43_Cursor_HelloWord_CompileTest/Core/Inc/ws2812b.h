#ifndef WS2812B_H
#define WS2812B_H

#include "main.h"
#include <stdint.h>

/**
 * @brief WS2812B LED Library (C Version)
 * 
 * This library provides a clean interface for controlling WS2812B RGB LEDs
 * using GPIO pin output with precise timing for the protocol.
 */

// ============================================================================
// CONSTANTS AND DEFINITIONS
// ============================================================================

// WS2812B Protocol Timing (in CPU cycles at 72MHz)
// WS2812B requires: T0H: 350ns, T0L: 800ns, T1H: 700ns, T1L: 600ns
// Using more conservative timing for better compatibility
#define WS2812B_T0H_CYCLES    30    // 0-bit high time (~420ns at 72MHz)
#define WS2812B_T0L_CYCLES    70    // 0-bit low time (~970ns at 72MHz)
#define WS2812B_T1H_CYCLES    70    // 1-bit high time (~970ns at 72MHz)
#define WS2812B_T1L_CYCLES    30    // 1-bit low time (~420ns at 72MHz)
#define WS2812B_RESET_CYCLES  4000  // Reset time (~55us at 72MHz)

// Maximum number of LEDs (adjust based on available RAM)
#define WS2812B_MAX_LEDS      32    // Maximum LEDs per strip

// Color structure for RGB values
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGBColor_t;

// WS2812B handle structure
typedef struct {
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
    uint16_t led_count;
    RGBColor_t led_buffer[WS2812B_MAX_LEDS];
} WS2812B_Handle_t;

// ============================================================================
// FUNCTION DECLARATIONS
// ============================================================================

// Initialization
void WS2812B_Init(WS2812B_Handle_t* handle, GPIO_TypeDef* port, uint16_t pin, uint16_t num_leds);

// Core functions
void WS2812B_SetLED(WS2812B_Handle_t* handle, uint16_t index, RGBColor_t color);
void WS2812B_SetLED_RGB(WS2812B_Handle_t* handle, uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
void WS2812B_SetAllLEDs(WS2812B_Handle_t* handle, RGBColor_t color);
void WS2812B_ClearAll(WS2812B_Handle_t* handle);
void WS2812B_Update(WS2812B_Handle_t* handle);

// Utility functions
uint16_t WS2812B_GetLEDCount(WS2812B_Handle_t* handle);
uint16_t WS2812B_GetMaxLEDs(void);
void WS2812B_SetBrightness(WS2812B_Handle_t* handle, uint16_t index, uint8_t brightness);
void WS2812B_SetAllBrightness(WS2812B_Handle_t* handle, uint8_t brightness);

// Animation helpers
void WS2812B_FadeIn(WS2812B_Handle_t* handle, RGBColor_t color, uint16_t duration_ms);
void WS2812B_FadeOut(WS2812B_Handle_t* handle, uint16_t duration_ms);
void WS2812B_Rainbow(WS2812B_Handle_t* handle, uint16_t start_index, uint16_t length);
void WS2812B_Chase(WS2812B_Handle_t* handle, RGBColor_t color, uint16_t delay_ms);

// Predefined colors
RGBColor_t WS2812B_Color_Red(void);
RGBColor_t WS2812B_Color_Green(void);
RGBColor_t WS2812B_Color_Blue(void);
RGBColor_t WS2812B_Color_White(void);
RGBColor_t WS2812B_Color_Black(void);
RGBColor_t WS2812B_Color_Yellow(void);
RGBColor_t WS2812B_Color_Purple(void);
RGBColor_t WS2812B_Color_Cyan(void);

#endif // WS2812B_H 