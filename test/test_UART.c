#include "unity.h"
#include "UART.h"

void setUp(void) {}
void tearDown(void) {}

void test_Breadcrumbs(void)
{
  // Not much to do here. UART probably won't have much to test ever.
  TEST_ASSERT_EQUAL(1, UART_COUNT);
}
