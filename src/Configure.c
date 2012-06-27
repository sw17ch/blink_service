#include "Configure.h"
#include "Clock.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static void Configure_Timer0(void);

void Configure(void)
{
  Configure_Timer0();
}

/*
 * Setup Timer 0, which is an 8-bit timer, to divide the bus clock by 64.
 * Preload the timer (TCNT0) with a value of 5 in order to adjust for the
 * remainder in clock division.
 *
 * CLOCK = 16,000,000 Hz
 * DIV = 64
 * TIMER0_COUNTS = 256
 * TIMER0_PRELOAD = 5
 *
 * ((CLOCK / DIV) / (TIMER0_COUNTS - TIMER0_PRELOAD)) = 0.001 seconds
 */

#define TIMER0_PRELOAD (5)
#define RESET_TCNT0() do { TCNT0 = TIMER0_PRELOAD; } while(0)

static void Configure_Timer0(void)
{
  /* disable interrupts */
  cli();

  /* Configure TIMER0 to use the CLK/64 prescaler. */
  TCCR0B = _BV(CS00) | _BV(CS01);

  /* enable the TIMER0 overflow interrupt */
  TIMSK0 = _BV(TOIE0);

  /* confiure PB5 as an output. */
  DDRB |= _BV(DDB5);

  RESET_TCNT0();

  /* enable interrupts. */
  sei();
}

static inline void Timer0_Overflow_Vector()
{
  cli();
  RESET_TCNT0();
  Clock_Tick();
  sei();
}

ISR(TIMER0_OVF_vect)
{
  Timer0_Overflow_Vector();
}

