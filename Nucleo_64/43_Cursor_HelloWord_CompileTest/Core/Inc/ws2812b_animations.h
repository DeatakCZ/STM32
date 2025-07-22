#ifndef WS2812B_ANIMATIONS_H
#define WS2812B_ANIMATIONS_H

#include "ws2812b_timer.h"

// ============================================================================
// ANIMATION FUNCTIONS
// ============================================================================

// Basic animations
void WS2812B_Animation_Rainbow(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Animation_Chase(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms);
void WS2812B_Animation_Fade(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms);
void WS2812B_Animation_Breath(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms);

// Advanced animations
void WS2812B_Animation_Fire(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Animation_Wave(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Animation_Sparkle(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Animation_KnightRider(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);
void WS2812B_Animation_LinearFlow(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms);

// Demo functions
void WS2812B_Animation_Demo(WS2812B_Timer_Handle_t* handle);
void WS2812B_Animation_BrightnessTest(WS2812B_Timer_Handle_t* handle);

// Color wheel and utility functions
RGBColor_t WS2812B_Animation_ColorWheel(uint8_t position);
uint8_t WS2812B_Animation_ScaleBrightness(uint8_t color, uint8_t brightness);

#endif // WS2812B_ANIMATIONS_H 