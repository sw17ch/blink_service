#include "unity.h"
#include "Blinker_LED.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Blinker_LED_Init(void)
{
  Blinker_LED_t led;

  Blinker_LED_Init(&led, (Port_t)9, 10);

  TEST_ASSERT_EQUAL( 9, (uint64_t)led.port);
  TEST_ASSERT_EQUAL(10, led.pin);
}

void test_Blinker_LED_Toggle(void)
{
  // Doesn't get any tests until Toggle does something more than XOR.
}
