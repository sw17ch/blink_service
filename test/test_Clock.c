#include "unity.h"
#include "Clock.h"

void setUp(void) {}
void tearDown(void) {}

void test_Clock_Tick(void)
{
  Clock_Set(0);
  Clock_Tick();
  TEST_ASSERT_EQUAL(1, Clock_Get());
  Clock_Tick();
  TEST_ASSERT_EQUAL(2, Clock_Get());
  Clock_Set(10);
  Clock_Tick();
  TEST_ASSERT_EQUAL(11, Clock_Get());
}

void test_Clock_Reset(void)
{
  Clock_Set(10);
  Clock_Reset();

  TEST_ASSERT_EQUAL(0, Clock_Get());
}

void test_Clock_Get(void)
{
  Clock_Set(12);
  TEST_ASSERT_EQUAL(12, Clock_Get());
}

void test_Clock_Set(void)
{
  Clock_Set(12);
  TEST_ASSERT_EQUAL(12, Clock_Get());
  Clock_Set(20);
  TEST_ASSERT_EQUAL(20, Clock_Get());
}
