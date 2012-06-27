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
  Blinker_t blinker = { { 0, 0 } };

  Alarm_IsExpired_ExpectAndReturn(&blinker.alarm, true);
  Blinker_LED_Toggle_Expect(&blinker.led);
}
