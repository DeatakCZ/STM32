#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

/////////_GPIO DIRECT ACCESS MACRO'S_//////////////////////////////////
#define GPIO_SET_PIN(port, pin) 	((port)->BSRR = (pin))
#define GPIO_CLEAR_PIN(port, pin) 	((port)->BSRR = (pin << 16u))
#define GPIO_TOGGLE_PIN(port, pin) 	((port)->ODR  ^= (pin))
#define GPIO_READ_PIN(port, pin) 	((port)->IDR & (pin))
///////////////////////////////////////////////////////////////////////

/////////_SYSTICK TIMER DELAY MACRO_///////////////////////////////////
#define SYSTICK_LOAD (SystemCoreClock/1000000U)
#define SYSTICK_DELAY_CALIB (SYSTICK_LOAD >> 1)

#define DELAY_US(us) \
    do { \
         uint32_t start = SysTick->VAL; \
         uint32_t ticks = (us * SYSTICK_LOAD)-SYSTICK_DELAY_CALIB;  \
         while((start - SysTick->VAL) < ticks); \
    } while (0)

#define DELAY_MS(ms) \
    do { \
        for (uint32_t i = 0; i < ms; ++i) { \
            DELAY_US(1000); \
        } \
    } while (0)
///////////////////////////////////////////////////////////////////////


#endif /* UTIL_UTIL_H_ */
