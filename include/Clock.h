#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

typedef uint32_t Clock_Val_t;

/**
 * Increments the clock. Should only be called by the timer interrupt.
 */
void Clock_Tick(void);

/**
 * Reset the clock to zero.
 */
void Clock_Reset(void);

/**
 * Get the current value of the clock.
 */
Clock_Val_t Clock_Get(void);

/**
 * Set the value of the clock. Should not be used in normal operation.
 */
void Clock_Set(Clock_Val_t clock_to_set);

#endif /* CLOCK_G */
