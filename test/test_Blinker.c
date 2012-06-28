#include "unity.h"
#include "Blinker.h"

#include "mock_Alarm.h"
#include "mock_Blinker_LED.h"

#include <string.h>
#include <avr/io.h>

Blinker_t blinker;

void setUp(void) { memset(&blinker, 0, sizeof(blinker)); }
void tearDown(void) { }

void test_Blinker_Init(void)
{
  Blinker_LED_Init_Expect(&blinker.led, &PORTB, PORTB5);
  Alarm_Init_Expect(&blinker.alarm, 500);
  Alarm_Start_Expect(&blinker.alarm);

  Blinker_Init(&blinker);
}

void test_Blinker_should_toggle_light_if_alarm_is_expired(void)
{
  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, true);
  Blinker_LED_Toggle_Expect(&blinker.led);
  Alarm_Reset_Expect(&blinker.alarm);

  Blinker_Service(&blinker);
}

void test_Blinker_should_not_toggle_if_alarm_has_not_expired(void)
{
  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, false);

  Blinker_Service(&blinker);
}
