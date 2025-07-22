#include "ws2812b_timer.h"
#include "tim.h"

// ============================================================================
// PRIVATE FUNCTION DECLARATIONS
// ============================================================================

static void send_byte_pwm(WS2812B_Timer_Handle_t* handle, uint8_t byte);
static void send_reset_pwm(WS2812B_Timer_Handle_t* handle);
static void set_pwm_duty(WS2812B_Timer_Handle_t* handle, uint8_t duty_percent);

// ============================================================================
// INITIALIZATION
// ============================================================================

void WS2812B_Timer_Init(WS2812B_Timer_Handle_t* handle, TIM_HandleTypeDef* htim, uint32_t channel, uint16_t num_leds) {
    // Initialize handle
    handle->htim = htim;
    handle->channel = channel;
    
    // Validate LED count
    if (num_leds > WS2812B_MAX_LEDS) {
        handle->led_count = WS2812B_MAX_LEDS;
    } else {
        handle->led_count = num_leds;
    }
    
    // Initialize all LEDs to off
    WS2812B_Timer_ClearAll(handle);
    
    // Start timer PWM
    HAL_TIM_PWM_Start(handle->htim, handle->channel);
}

// ============================================================================
// PRIVATE PWM FUNCTIONS
// ============================================================================

static void set_pwm_duty(WS2812B_Timer_Handle_t* handle, uint8_t duty_percent) {
    // Calculate compare value for given duty cycle
    uint32_t compare_value = (WS2812B_TIMER_PERIOD * duty_percent) / 100;
    
    // Set PWM compare value
    __HAL_TIM_SET_COMPARE(handle->htim, handle->channel, compare_value);
}

static void send_byte_pwm(WS2812B_Timer_Handle_t* handle, uint8_t byte) {
    // Send 8 bits using PWM timing for 72MHz clock
    for (int8_t i = 7; i >= 0; i--) {
        // Get current bit (MSB first)
        uint8_t bit = (byte >> i) & 0x01;
        
        if (bit) {
            // Send 1-bit: High for 700ns, Low for 600ns
            set_pwm_duty(handle, WS2812B_PWM_T1H_DUTY);
        } else {
            // Send 0-bit: High for 350ns, Low for 800ns
            set_pwm_duty(handle, WS2812B_PWM_T0H_DUTY);
        }
        
        // Wait for 1.25us (timer period at 1MHz)
        while (__HAL_TIM_GET_FLAG(handle->htim, TIM_FLAG_UPDATE) == RESET);
        __HAL_TIM_CLEAR_FLAG(handle->htim, TIM_FLAG_UPDATE);
    }
}

static void send_reset_pwm(WS2812B_Timer_Handle_t* handle) {
    // Send reset signal (0% duty cycle for 50us)
    set_pwm_duty(handle, 0);
    
    // Wait for 50us (50 timer periods at 1MHz)
    for (int i = 0; i < 50; i++) {
        while (__HAL_TIM_GET_FLAG(handle->htim, TIM_FLAG_UPDATE) == RESET);
        __HAL_TIM_CLEAR_FLAG(handle->htim, TIM_FLAG_UPDATE);
    }
}

// ============================================================================
// CORE LED CONTROL FUNCTIONS
// ============================================================================

void WS2812B_Timer_SetLED(WS2812B_Timer_Handle_t* handle, uint16_t index, RGBColor_t color) {
    // Validate index
    if (index >= handle->led_count) return;
    
    // Clear the specific LED first to ensure no contamination
    RGBColor_t black = {0, 0, 0};
    handle->led_buffer[index] = black;
    
    // Store color in buffer (WS2812B expects GRB order)
    handle->led_buffer[index] = color;
}

void WS2812B_Timer_SetLED_RGB(WS2812B_Timer_Handle_t* handle, uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    RGBColor_t color = {red, green, blue};
    WS2812B_Timer_SetLED(handle, index, color);
}

void WS2812B_Timer_SetAllLEDs(WS2812B_Timer_Handle_t* handle, RGBColor_t color) {
    // Clear the buffer first to ensure no contamination
    WS2812B_Timer_ClearBuffer(handle);
    
    // Set all LEDs to the same color
    for (uint16_t i = 0; i < handle->led_count; i++) {
        handle->led_buffer[i] = color;
    }
}

void WS2812B_Timer_ClearAll(WS2812B_Timer_Handle_t* handle) {
    // Turn off all LEDs
    WS2812B_Timer_ClearBuffer(handle);
}

void WS2812B_Timer_ClearBuffer(WS2812B_Timer_Handle_t* handle) {
    // Clear the entire LED buffer to black
    RGBColor_t black = {0, 0, 0};
    for (uint16_t i = 0; i < handle->led_count; i++) {
        handle->led_buffer[i] = black;
    }
}

void WS2812B_Timer_Update(WS2812B_Timer_Handle_t* handle) {
    // Send all LED data to the strip
    for (uint16_t i = 0; i < handle->led_count; i++) {
        // WS2812B expects GRB order, not RGB
        send_byte_pwm(handle, handle->led_buffer[i].green);
        send_byte_pwm(handle, handle->led_buffer[i].red);
        send_byte_pwm(handle, handle->led_buffer[i].blue);
    }
    
    // Send reset signal
    send_reset_pwm(handle);
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

uint16_t WS2812B_Timer_GetLEDCount(WS2812B_Timer_Handle_t* handle) {
    return handle->led_count;
}

uint16_t WS2812B_Timer_GetMaxLEDs(void) {
    return WS2812B_MAX_LEDS;
}

// ============================================================================
// BRIGHTNESS SCALING
// ============================================================================

RGBColor_t WS2812B_Timer_ScaleBrightness(RGBColor_t color) {
    RGBColor_t scaled_color;
    
    // Handle edge cases first
    if (WS2812B_MAX_BRIGHTNESS == 0) {
        // If brightness is 0, return black
        scaled_color.red = 0;
        scaled_color.green = 0;
        scaled_color.blue = 0;
        return scaled_color;
    }
    
    if (WS2812B_MAX_BRIGHTNESS >= 255) {
        // If brightness is 255 or higher, return original color (no scaling needed)
        return color;
    }
    
    // Scale each color component using integer math with 100x scaling
    // This eliminates floating-point precision issues
    volatile uint32_t temp_red = (uint32_t)color.red * WS2812B_MAX_BRIGHTNESS * 100;
    volatile uint32_t temp_green = (uint32_t)color.green * WS2812B_MAX_BRIGHTNESS * 100;
    volatile uint32_t temp_blue = (uint32_t)color.blue * WS2812B_MAX_BRIGHTNESS * 100;
    
    // Divide by 25500 (255 * 100) for proper scaling
    temp_red = temp_red / 25500;
    temp_green = temp_green / 25500;
    temp_blue = temp_blue / 25500;
    
    // Ensure values don't exceed 255
    scaled_color.red = (temp_red > 255) ? 255 : (uint8_t)temp_red;
    scaled_color.green = (temp_green > 255) ? 255 : (uint8_t)temp_green;
    scaled_color.blue = (temp_blue > 255) ? 255 : (uint8_t)temp_blue;
    
    return scaled_color;
}

// ============================================================================
// PREDEFINED COLORS (AUTOMATICALLY SCALED TO MAX BRIGHTNESS)
// ============================================================================

RGBColor_t WS2812B_Timer_Color_Red(void) {
    RGBColor_t color = {255, 0, 0};  // Full red
    RGBColor_t scaled = WS2812B_Timer_ScaleBrightness(color);
    // Ensure red component is preserved and others are 0
    scaled.green = 0;
    scaled.blue = 0;
    return scaled;
}

RGBColor_t WS2812B_Timer_Color_Green(void) {
    RGBColor_t color = {0, 255, 0};  // Full green
    RGBColor_t scaled = WS2812B_Timer_ScaleBrightness(color);
    // Ensure green component is preserved and others are 0
    scaled.red = 0;
    scaled.blue = 0;
    return scaled;
}

RGBColor_t WS2812B_Timer_Color_Blue(void) {
    RGBColor_t color = {0, 0, 255};  // Full blue
    RGBColor_t scaled = WS2812B_Timer_ScaleBrightness(color);
    // Ensure blue component is preserved and others are 0
    scaled.red = 0;
    scaled.green = 0;
    return scaled;
}

RGBColor_t WS2812B_Timer_Color_White(void) {
    RGBColor_t color = {255, 255, 255};  // Full white
    return WS2812B_Timer_ScaleBrightness(color);
}

RGBColor_t WS2812B_Timer_Color_Black(void) {
    RGBColor_t color = {0, 0, 0};
    return color;  // Black is always black, no scaling needed
}

RGBColor_t WS2812B_Timer_Color_Yellow(void) {
    RGBColor_t color = {255, 255, 0};  // Full yellow
    return WS2812B_Timer_ScaleBrightness(color);
}

RGBColor_t WS2812B_Timer_Color_Purple(void) {
    RGBColor_t color = {255, 0, 255};  // Full purple
    return WS2812B_Timer_ScaleBrightness(color);
}

RGBColor_t WS2812B_Timer_Color_Cyan(void) {
    RGBColor_t color = {0, 255, 255};  // Full cyan
    return WS2812B_Timer_ScaleBrightness(color);
}

// ============================================================================
// TEST FUNCTIONS
// ============================================================================

void WS2812B_Timer_TestIndividualLEDs(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint8_t test_led = 0;
    static uint32_t last_test = 0;
    
    if (HAL_GetTick() - last_test > delay_ms) {
        // Clear all LEDs first
        WS2812B_Timer_ClearAll(handle);
        
        // Light up only the current test LED
        if (test_led < handle->led_count) {
            WS2812B_Timer_SetLED(handle, test_led, WS2812B_Timer_Color_Red());
        }
        
        WS2812B_Timer_Update(handle);
        test_led++;
        if (test_led >= handle->led_count) {
            test_led = 0;  // Loop back to first LED
        }
        last_test = HAL_GetTick();
    }
}

void WS2812B_Timer_TestSolidColor(WS2812B_Timer_Handle_t* handle, RGBColor_t color, uint32_t delay_ms) {
    static uint8_t test_state = 0;
    static uint32_t last_test = 0;
    
    if (HAL_GetTick() - last_test > delay_ms) {
        if (test_state) {
            // Set all LEDs to the specified color
            WS2812B_Timer_SetAllLEDs(handle, color);
        } else {
            // Turn all LEDs off
            WS2812B_Timer_ClearAll(handle);
        }
        
        WS2812B_Timer_Update(handle);
        test_state = !test_state;  // Toggle state
        last_test = HAL_GetTick();
    }
}

void WS2812B_Timer_TestLastLEDColors(WS2812B_Timer_Handle_t* handle, uint32_t delay_ms) {
    static uint8_t color_index = 0;
    static uint32_t last_test = 0;
    
    if (HAL_GetTick() - last_test > delay_ms) {
        // Get the last LED index
        uint16_t last_led_index = handle->led_count - 1;
        
        // Clear all LEDs
        WS2812B_Timer_ClearAll(handle);
        
        // Define color sequence: Red, Green, Blue, White, Yellow, Purple, Cyan
        RGBColor_t colors[] = {
            WS2812B_Timer_Color_Red(),
            WS2812B_Timer_Color_Green(),
            WS2812B_Timer_Color_Blue(),
            WS2812B_Timer_Color_White(),
            WS2812B_Timer_Color_Yellow(),
            WS2812B_Timer_Color_Purple(),
            WS2812B_Timer_Color_Cyan()
        };
        
        // Set last LED to current color
        if (last_led_index < handle->led_count) {
            WS2812B_Timer_SetLED(handle, last_led_index, colors[color_index]);
        }
        
        // Update display
        WS2812B_Timer_Update(handle);
        
        // Move to next color
        color_index = (color_index + 1) % 7;
        last_test = HAL_GetTick();
    }
} 