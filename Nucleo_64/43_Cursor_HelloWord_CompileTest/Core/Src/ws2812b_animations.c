#include "ws2812b_animations.h"
#include <stdlib.h>

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

RGBColor_t WS2812B_Animation_ColorWheel(uint8_t position) {
    // Position must be 0-255
    position = 255 - position;
    
    RGBColor_t color = {0, 0, 0};
    
    if (position < 85) {
        color.red = 255 - position * 3;
        color.green = position * 3;
        color.blue = 0;
    } else if (position < 170) {
        position -= 85;
        color.red = 0;
        color.green = 255 - position * 3;
        color.blue = position * 3;
    } else {
        position -= 170;
        color.red = position * 3;
        color.green = 0;
        color.blue = 255 - position * 3;
    }
    
    // Scale to max brightness
    return WS2812B_Timer_ScaleBrightness(color);
}

uint8_t WS2812B_Animation_ScaleBrightness(uint8_t color, uint8_t brightness) {
    return (color * brightness) / 255;
}

// ============================================================================
// BASIC ANIMATIONS
// ============================================================================

void WS2812B_Animation_Rainbow(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint8_t offset = 0;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create rainbow effect flowing along the linear strip
        for (uint16_t i = 0; i < handle->led_count; i++) {
            // Create smooth gradient across the line
            uint8_t color_pos = (i * 32 + offset) % 256;  // 32 steps per LED for smooth transition
            RGBColor_t color = WS2812B_Animation_ColorWheel(color_pos);
            WS2812B_Timer_SetLED(handle, i, color);
        }
        
        WS2812B_Timer_Update(handle);
        offset = (offset + 2) % 256;  // Slower movement for linear strip
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_Chase(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms) {
    static uint16_t position = 0;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Clear all LEDs
        WS2812B_Timer_ClearAll(handle);
        
        // Light up current position
        if (position < handle->led_count) {
            WS2812B_Timer_SetLED(handle, position, color);
        }
        
        WS2812B_Timer_Update(handle);
        
        // Move to next position
        position = (position + 1) % handle->led_count;
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_Fade(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms) {
    static uint8_t brightness = 0;
    static uint8_t direction = 1;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create faded color
        RGBColor_t faded_color;
        faded_color.red = WS2812B_Animation_ScaleBrightness(color.red, brightness);
        faded_color.green = WS2812B_Animation_ScaleBrightness(color.green, brightness);
        faded_color.blue = WS2812B_Animation_ScaleBrightness(color.blue, brightness);
        
        // Set all LEDs to faded color
        WS2812B_Timer_SetAllLEDs(handle, faded_color);
        WS2812B_Timer_Update(handle);
        
        // Update brightness
        if (direction) {
            brightness++;
            if (brightness >= 255) direction = 0;
        } else {
            brightness--;
            if (brightness == 0) direction = 1;
        }
        
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_Breath(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms) {
    static uint8_t brightness = 0;
    static uint8_t direction = 1;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create breathing effect with smooth brightness change
        RGBColor_t breath_color;
        breath_color.red = WS2812B_Animation_ScaleBrightness(color.red, brightness);
        breath_color.green = WS2812B_Animation_ScaleBrightness(color.green, brightness);
        breath_color.blue = WS2812B_Animation_ScaleBrightness(color.blue, brightness);
        
        // Set all LEDs to breathing color
        WS2812B_Timer_SetAllLEDs(handle, breath_color);
        WS2812B_Timer_Update(handle);
        
        // Update brightness with slower change
        if (direction) {
            brightness += 2;
            if (brightness >= 255) {
                brightness = 255;
                direction = 0;
            }
        } else {
            brightness -= 2;
            if (brightness == 0) {
                brightness = 0;
                direction = 1;
            }
        }
        
        last_update = HAL_GetTick();
    }
}

// ============================================================================
// ADVANCED ANIMATIONS
// ============================================================================

void WS2812B_Animation_Fire(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create fire effect flowing along the linear strip
        for (uint16_t i = 0; i < handle->led_count; i++) {
            // Create fire gradient - hotter at the start, cooler at the end
            uint8_t heat_factor = 255 - (i * 32);  // 255, 223, 191, 159, 127, 95, 63, 31
            if (heat_factor < 64) heat_factor = 64;  // Minimum brightness
            
            uint8_t red = 128 + (heat_factor / 2);  // 128-255 based on position
            uint8_t green = heat_factor / 4;        // 0-63 based on position
            uint8_t blue = 0;                       // No blue in fire
            
            // Add some randomness for flicker effect
            red += (rand() % 32) - 16;  // ±16 random variation
            if (red > 255) red = 255;
            if (red < 128) red = 128;
            
            RGBColor_t fire_color = {red, green, blue};
            fire_color = WS2812B_Timer_ScaleBrightness(fire_color);
            
            WS2812B_Timer_SetLED(handle, i, fire_color);
        }
        
        WS2812B_Timer_Update(handle);
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_Wave(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint8_t offset = 0;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create wave effect flowing along the linear strip
        for (uint16_t i = 0; i < handle->led_count; i++) {
            // Create wave pattern that flows along the line
            uint8_t wave_pos = (i * 36 + offset) % 256;  // 36 steps per LED for smooth wave
            uint8_t brightness = 64 + (wave_pos * 191) / 255;  // 64-255 brightness
            
            RGBColor_t wave_color = {brightness, brightness, brightness};
            wave_color = WS2812B_Timer_ScaleBrightness(wave_color);
            
            WS2812B_Timer_SetLED(handle, i, wave_color);
        }
        
        WS2812B_Timer_Update(handle);
        offset = (offset + 3) % 256;  // Slower movement for linear strip
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_Sparkle(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Clear all LEDs
        WS2812B_Timer_ClearAll(handle);
        
        // Add random sparkles
        for (uint8_t i = 0; i < 3; i++) {  // 3 sparkles at a time
            uint16_t pos = rand() % handle->led_count;
            RGBColor_t sparkle_color = WS2812B_Timer_Color_White();
            WS2812B_Timer_SetLED(handle, pos, sparkle_color);
        }
        
        WS2812B_Timer_Update(handle);
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_KnightRider(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint16_t position = 0;
    static uint8_t direction = 1;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Clear all LEDs
        WS2812B_Timer_ClearAll(handle);
        
        // Create Knight Rider effect with tail - perfect for linear strip
        for (int8_t i = -1; i <= 1; i++) {  // Shorter tail for 8 LEDs
            int16_t led_pos = position + i;
            if (led_pos >= 0 && led_pos < handle->led_count) {
                // Calculate brightness based on distance from center
                uint8_t brightness = 128 - (abs(i) * 64);  // 128, 64, 0
                if (brightness > 0) {
                    RGBColor_t rider_color = {brightness, 0, 0};  // Red
                    rider_color = WS2812B_Timer_ScaleBrightness(rider_color);
                    WS2812B_Timer_SetLED(handle, led_pos, rider_color);
                }
            }
        }
        
        WS2812B_Timer_Update(handle);
        
        // Update position - slower for linear strip
        if (direction) {
            position++;
            if (position >= handle->led_count - 1) direction = 0;
        } else {
            position--;
            if (position == 0) direction = 1;
        }
        
        last_update = HAL_GetTick();
    }
}

void WS2812B_Animation_LinearFlow(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint8_t offset = 0;
    static uint32_t last_update = 0;
    
    if (HAL_GetTick() - last_update > delay_ms) {
        // Create flowing effect along the linear strip
        for (uint16_t i = 0; i < handle->led_count; i++) {
            // Create flowing gradient that moves along the line
            uint8_t flow_pos = (i * 8 + offset) % 256;
            
            // Create smooth color transition
            RGBColor_t flow_color;
            if (flow_pos < 128) {
                // First half: blue to green
                flow_color.red = 0;
                flow_color.green = flow_pos * 2;
                flow_color.blue = 255 - flow_pos * 2;
            } else {
                // Second half: green to red
                flow_pos -= 128;
                flow_color.red = flow_pos * 2;
                flow_color.green = 255 - flow_pos * 2;
                flow_color.blue = 0;
            }
            
            flow_color = WS2812B_Timer_ScaleBrightness(flow_color);
            WS2812B_Timer_SetLED(handle, i, flow_color);
        }
        
        WS2812B_Timer_Update(handle);
        offset = (offset + 4) % 256;  // Smooth flow speed
        last_update = HAL_GetTick();
    }
}

// ============================================================================
// DEMO FUNCTIONS
// ============================================================================

void WS2812B_Animation_Demo(WS2812B_Timer_Handle_t* handle) {
    // ============================================================================
    // WS2812B LINEAR STRIP ANIMATION DEMO
    // ============================================================================
    // Optimized for 8 LEDs in a line - each animation runs for about 4 seconds
    // All animations flow smoothly along the linear strip
    
    // 1. Linear Flow - smooth color gradient flowing along the line
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_LinearFlow(handle, 100);
        HAL_Delay(100);
    }
    
    // 2. Knight Rider - red light moving back and forth (perfect for linear strip)
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_KnightRider(handle, 100);
        HAL_Delay(100);
    }
    
    // 3. Rainbow - flowing rainbow colors along the line
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Rainbow(handle, 100);
        HAL_Delay(100);
    }
    
    // 4. Fire - fire effect flowing from start to end of strip
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Fire(handle, 100);
        HAL_Delay(100);
    }
    
    // 5. Wave - white wave pattern flowing along the line
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Wave(handle, 100);
        HAL_Delay(100);
    }
    
    // 6. Chase - green light moving from LED to LED
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Chase(handle, WS2812B_Timer_Color_Green(), 100);
        HAL_Delay(100);
    }
    
    // 7. Breathing Blue - all LEDs breathing together
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Breath(handle, WS2812B_Timer_Color_Blue(), 100);
        HAL_Delay(100);
    }
    
    // 8. Sparkle - random white sparkles along the strip
    for (int i = 0; i < 40; i++) {
        WS2812B_Animation_Sparkle(handle, 100);
        HAL_Delay(100);
    }
}

void WS2812B_Animation_BrightnessTest(WS2812B_Timer_Handle_t* handle) {
    // ============================================================================
    // WS2812B BRIGHTNESS DEBUG TEST
    // ============================================================================
    // Simple test to verify brightness control is working
    
    // Test 1: All LEDs red at controlled brightness
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    WS2812B_Timer_SetAllLEDs(handle, WS2812B_Timer_Color_Red());
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 2: All LEDs green at controlled brightness
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    WS2812B_Timer_SetAllLEDs(handle, WS2812B_Timer_Color_Green());
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 3: All LEDs blue at controlled brightness
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    WS2812B_Timer_SetAllLEDs(handle, WS2812B_Timer_Color_Blue());
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 4: All LEDs white at controlled brightness
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    WS2812B_Timer_SetAllLEDs(handle, WS2812B_Timer_Color_White());
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 5: Turn all off
    WS2812B_Timer_ClearAll(handle);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 6: Manual brightness test - very dim red
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    RGBColor_t dim_red = {16, 0, 0};  // Very dim red (16/255 = 6%)
    WS2812B_Timer_SetAllLEDs(handle, dim_red);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 7: Manual brightness test - medium red
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    RGBColor_t medium_red = {64, 0, 0};  // Medium red (64/255 = 25%)
    WS2812B_Timer_SetAllLEDs(handle, medium_red);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 8: Manual brightness test - bright red
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    RGBColor_t bright_red = {128, 0, 0};  // Bright red (128/255 = 50%)
    WS2812B_Timer_SetAllLEDs(handle, bright_red);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 9: Test scaling function directly
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    RGBColor_t full_red = {255, 0, 0};  // Full red (255)
    RGBColor_t scaled_red = WS2812B_Timer_ScaleBrightness(full_red);
    WS2812B_Timer_SetAllLEDs(handle, scaled_red);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    
    // Test 10: Test scaling function with full white
    WS2812B_Timer_ClearBuffer(handle);  // Clear buffer first
    RGBColor_t full_white = {255, 255, 255};  // Full white (255,255,255)
    RGBColor_t scaled_white = WS2812B_Timer_ScaleBrightness(full_white);
    WS2812B_Timer_SetAllLEDs(handle, scaled_white);
    WS2812B_Timer_Update(handle);
    HAL_Delay(3000);
    

}