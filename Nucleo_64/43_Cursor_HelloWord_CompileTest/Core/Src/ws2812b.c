#include "ws2812b.h"
#include "gpio.h"

// ============================================================================
// PRIVATE FUNCTION DECLARATIONS
// ============================================================================

static void delay_cycles(uint32_t cycles);
static void send_byte(WS2812B_Handle_t* handle, uint8_t byte);
static void send_reset(WS2812B_Handle_t* handle);

// ============================================================================
// INITIALIZATION
// ============================================================================

void WS2812B_Init(WS2812B_Handle_t* handle, GPIO_TypeDef* port, uint16_t pin, uint16_t num_leds) {
    // Initialize handle
    handle->gpio_port = port;
    handle->gpio_pin = pin;
    
    // Validate LED count
    if (num_leds > WS2812B_MAX_LEDS) {
        handle->led_count = WS2812B_MAX_LEDS;
    } else {
        handle->led_count = num_leds;
    }
    
    // Initialize all LEDs to off
    WS2812B_ClearAll(handle);
}

// ============================================================================
// PRIVATE TIMING FUNCTIONS
// ============================================================================

static void delay_cycles(uint32_t cycles) {
    // Simple cycle-accurate delay using loop
    for (volatile uint32_t i = 0; i < cycles; i++) {
        __NOP(); // No operation instruction
    }
}

static void send_byte(WS2812B_Handle_t* handle, uint8_t byte) {
    // Send 8 bits with precise timing
    for (int8_t i = 7; i >= 0; i--) {
        // Get current bit (MSB first)
        uint8_t bit = (byte >> i) & 0x01;
        
        // Set pin high
        HAL_GPIO_WritePin(handle->gpio_port, handle->gpio_pin, GPIO_PIN_SET);
        
        if (bit) {
            // Send 1-bit: longer high time
            delay_cycles(WS2812B_T1H_CYCLES);
            HAL_GPIO_WritePin(handle->gpio_port, handle->gpio_pin, GPIO_PIN_RESET);
            delay_cycles(WS2812B_T1L_CYCLES);
        } else {
            // Send 0-bit: shorter high time
            delay_cycles(WS2812B_T0H_CYCLES);
            HAL_GPIO_WritePin(handle->gpio_port, handle->gpio_pin, GPIO_PIN_RESET);
            delay_cycles(WS2812B_T0L_CYCLES);
        }
    }
}

static void send_reset(WS2812B_Handle_t* handle) {
    // Send reset signal (low for at least 50us)
    HAL_GPIO_WritePin(handle->gpio_port, handle->gpio_pin, GPIO_PIN_RESET);
    delay_cycles(WS2812B_RESET_CYCLES);
}

// ============================================================================
// CORE LED CONTROL FUNCTIONS
// ============================================================================

void WS2812B_SetLED(WS2812B_Handle_t* handle, uint16_t index, RGBColor_t color) {
    // Validate index
    if (index >= handle->led_count) return;
    
    // Store color in buffer (WS2812B expects GRB order)
    handle->led_buffer[index] = color;
}

void WS2812B_SetLED_RGB(WS2812B_Handle_t* handle, uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    RGBColor_t color = {red, green, blue};
    WS2812B_SetLED(handle, index, color);
}

void WS2812B_SetAllLEDs(WS2812B_Handle_t* handle, RGBColor_t color) {
    // Set all LEDs to the same color
    for (uint16_t i = 0; i < handle->led_count; i++) {
        handle->led_buffer[i] = color;
    }
}

void WS2812B_ClearAll(WS2812B_Handle_t* handle) {
    // Turn off all LEDs
    RGBColor_t black = {0, 0, 0};
    WS2812B_SetAllLEDs(handle, black);
}

void WS2812B_Update(WS2812B_Handle_t* handle) {
    // Send all LED data to the strip
    for (uint16_t i = 0; i < handle->led_count; i++) {
        // WS2812B expects GRB order, not RGB
        send_byte(handle, handle->led_buffer[i].green);
        send_byte(handle, handle->led_buffer[i].red);
        send_byte(handle, handle->led_buffer[i].blue);
    }
    
    // Send reset signal
    send_reset(handle);
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

uint16_t WS2812B_GetLEDCount(WS2812B_Handle_t* handle) {
    return handle->led_count;
}

uint16_t WS2812B_GetMaxLEDs(void) {
    return WS2812B_MAX_LEDS;
}

void WS2812B_SetBrightness(WS2812B_Handle_t* handle, uint16_t index, uint8_t brightness) {
    // Validate index
    if (index >= handle->led_count) return;
    
    // Scale RGB values by brightness (0-255)
    uint8_t scale = brightness;
    handle->led_buffer[index].red = (handle->led_buffer[index].red * scale) / 255;
    handle->led_buffer[index].green = (handle->led_buffer[index].green * scale) / 255;
    handle->led_buffer[index].blue = (handle->led_buffer[index].blue * scale) / 255;
}

void WS2812B_SetAllBrightness(WS2812B_Handle_t* handle, uint8_t brightness) {
    // Apply brightness to all LEDs
    for (uint16_t i = 0; i < handle->led_count; i++) {
        WS2812B_SetBrightness(handle, i, brightness);
    }
}

// ============================================================================
// PREDEFINED COLORS
// ============================================================================

RGBColor_t WS2812B_Color_Red(void) {
    RGBColor_t color = {255, 0, 0};
    return color;
}

RGBColor_t WS2812B_Color_Green(void) {
    RGBColor_t color = {0, 255, 0};
    return color;
}

RGBColor_t WS2812B_Color_Blue(void) {
    RGBColor_t color = {0, 0, 255};
    return color;
}

RGBColor_t WS2812B_Color_White(void) {
    RGBColor_t color = {255, 255, 255};
    return color;
}

RGBColor_t WS2812B_Color_Black(void) {
    RGBColor_t color = {0, 0, 0};
    return color;
}

RGBColor_t WS2812B_Color_Yellow(void) {
    RGBColor_t color = {255, 255, 0};
    return color;
}

RGBColor_t WS2812B_Color_Purple(void) {
    RGBColor_t color = {255, 0, 255};
    return color;
}

RGBColor_t WS2812B_Color_Cyan(void) {
    RGBColor_t color = {0, 255, 255};
    return color;
}

// ============================================================================
// ANIMATION HELPER FUNCTIONS
// ============================================================================

void WS2812B_FadeIn(WS2812B_Handle_t* handle, RGBColor_t color, uint16_t duration_ms) {
    // Fade in from black to specified color
    uint16_t steps = duration_ms / 10; // 10ms per step
    
    for (uint16_t step = 0; step <= steps; step++) {
        uint8_t brightness = (step * 255) / steps;
        
        for (uint16_t i = 0; i < handle->led_count; i++) {
            RGBColor_t fade_color = {
                (uint8_t)((color.red * brightness) / 255),
                (uint8_t)((color.green * brightness) / 255),
                (uint8_t)((color.blue * brightness) / 255)
            };
            WS2812B_SetLED(handle, i, fade_color);
        }
        
        WS2812B_Update(handle);
        HAL_Delay(10);
    }
}

void WS2812B_FadeOut(WS2812B_Handle_t* handle, uint16_t duration_ms) {
    // Fade out to black
    uint16_t steps = duration_ms / 10; // 10ms per step
    
    for (uint16_t step = steps; step > 0; step--) {
        uint8_t brightness = (step * 255) / steps;
        
        for (uint16_t i = 0; i < handle->led_count; i++) {
            RGBColor_t fade_color = {
                (uint8_t)((handle->led_buffer[i].red * brightness) / 255),
                (uint8_t)((handle->led_buffer[i].green * brightness) / 255),
                (uint8_t)((handle->led_buffer[i].blue * brightness) / 255)
            };
            WS2812B_SetLED(handle, i, fade_color);
        }
        
        WS2812B_Update(handle);
        HAL_Delay(10);
    }
    
    WS2812B_ClearAll(handle);
    WS2812B_Update(handle);
}

void WS2812B_Rainbow(WS2812B_Handle_t* handle, uint16_t start_index, uint16_t length) {
    // Create rainbow effect across specified LEDs
    for (uint16_t i = 0; i < length && (start_index + i) < handle->led_count; i++) {
        uint8_t hue = (i * 255) / length;
        
        // Simple HSV to RGB conversion
        uint8_t sector = hue / 43;
        uint8_t offset = hue % 43;
        uint8_t p = 0;
        uint8_t q = (255 * (43 - offset)) / 43;
        uint8_t t = (255 * offset) / 43;
        
        RGBColor_t color;
        switch (sector) {
            case 0: color = (RGBColor_t){255, t, p}; break;      // Red to Yellow
            case 1: color = (RGBColor_t){q, 255, p}; break;      // Yellow to Green
            case 2: color = (RGBColor_t){p, 255, t}; break;      // Green to Cyan
            case 3: color = (RGBColor_t){p, q, 255}; break;      // Cyan to Blue
            case 4: color = (RGBColor_t){t, p, 255}; break;      // Blue to Magenta
            case 5: color = (RGBColor_t){255, p, q}; break;      // Magenta to Red
        }
        
        WS2812B_SetLED(handle, start_index + i, color);
    }
}

void WS2812B_Chase(WS2812B_Handle_t* handle, RGBColor_t color, uint16_t delay_ms) {
    // Chase animation - moving light across the strip
    for (uint16_t pos = 0; pos < handle->led_count; pos++) {
        // Clear all LEDs
        WS2812B_ClearAll(handle);
        
        // Set current position
        WS2812B_SetLED(handle, pos, color);
        
        // Update and wait
        WS2812B_Update(handle);
        HAL_Delay(delay_ms);
    }
} 