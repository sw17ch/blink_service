#include "unity.h"
#include "mock_Blinker_LED.h"
#include "mock_Alarm.h"
#include "Blinker.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_Blinker_should_toggle_light_if_alarm_is_expired(void)

{

  Blinker_t blinker = { { 0, 0 } };



  Alarm_IsExpired_CMockExpectAndReturn(19, &blinker.alarm, 1);

  Blinker_LED_Toggle_CMockExpect(20, &blinker.led);

}
