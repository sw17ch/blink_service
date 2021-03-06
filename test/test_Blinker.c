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
  Alarm_Init_Expect(&blinker.alarm, DEFAULT_BLINKER_INTERVAL);
  Alarm_Start_Expect(&blinker.alarm);

  Blinker_Init(&blinker);

  TEST_ASSERT_EQUAL(DEFAULT_BLINKER_INTERVAL, blinker.interval);
  TEST_ASSERT_EQUAL(false, blinker.reinit_alarm);
}

void test_Blinker_Service_should_toggle_light_if_alarm_is_expired(void)
{
  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, true);
  Blinker_LED_Toggle_Expect(&blinker.led);
  Alarm_Reset_Expect(&blinker.alarm);

  Blinker_Service(&blinker);
}

void test_Blinker_Service_should_not_toggle_if_alarm_has_not_expired(void)
{
  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, false);

  Blinker_Service(&blinker);
}

void test_Blinker_Service_should_reinit_alarm_if_interval_updated(void)
{
  blinker.interval = 62;
  blinker.reinit_alarm = true;

  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, true);
  Blinker_LED_Toggle_Expect(&blinker.led);
  Alarm_Init_Expect(&blinker.alarm, 62);

  Blinker_Service(&blinker);
  
  TEST_ASSERT_EQUAL(false, blinker.reinit_alarm);
}

void test_Blinker_UpdateInterval_should_change_the_interval(void)
{
  blinker.interval = 45;

  Blinker_UpdateInterval(&blinker, 67);

  TEST_ASSERT_EQUAL(67, blinker.interval);
  TEST_ASSERT_EQUAL(true, blinker.reinit_alarm);
}
