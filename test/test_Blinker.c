#include "unity.h"
#include "Blinker.h"

#include "mock_Alarm.h"
#include "mock_Blinker_LED.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Blinker_should_toggle_light_if_alarm_is_expired(void)
{
  Blinker_t blinker;

  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, true);
  Blinker_LED_Toggle_Expect(&blinker.led);

  Blinker_Service(&blinker);
}

void test_Blinker_should_not_toggle_if_alarm_has_not_expired(void)
{
  Blinker_t blinker;

  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, false);

  Blinker_Service(&blinker);
}
