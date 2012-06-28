#include <string.h>
#include <stdbool.h>

#include "unity.h"
#include "Alarm.h"

#include "mock_Clock.h"

Alarm_t a;

void setUp(void) { memset(&a, 0, sizeof(a)); }
void tearDown(void) {}

void test_breadcrumbs(void)
{
  TEST_ASSERT_EQUAL(4, sizeof(Clock_Val_t)); // if this breaks, check the rest
}

void test_Alarm_Init(void)
{
  Alarm_Init(&a, 1000);

  TEST_ASSERT_EQUAL(1000, a.duration);
  TEST_ASSERT_EQUAL(false, a.started);
}

void test_Alarm_Start(void)
{
  Clock_Get_ExpectAndReturn(12345);

  Alarm_Start(&a);

  TEST_ASSERT_EQUAL(12345, a.started_at);
  TEST_ASSERT_EQUAL(true, a.started);
}

void test_Alarm_Reset_when_never_started(void)
{
  Alarm_Init(&a, 1000);

  Clock_Get_ExpectAndReturn(12345);

  Alarm_Reset(&a);
}

void test_Alarm_Reset_when_started(void)
{
  Alarm_Init(&a, 1000);
  Clock_Get_ExpectAndReturn(12345);
  Alarm_Start(&a);

  Alarm_Reset(&a);

  TEST_ASSERT_EQUAL(13345, a.started_at);
}

void test_Alarm_IsExpired_is_false_when_duration_has_not_passed(void)
{
  Alarm_Init(&a, 10);
  Clock_Get_ExpectAndReturn(10);
  Alarm_Start(&a);
  Clock_Get_ExpectAndReturn(15);

  TEST_ASSERT_FALSE(Alarm_IsExpired(&a));
}

void test_Alarm_IsExpired_is_true_when_duration_has_passed(void)
{
  Alarm_Init(&a, 10);
  Clock_Get_ExpectAndReturn(10);
  Alarm_Start(&a);
  Clock_Get_ExpectAndReturn(20);

  TEST_ASSERT_TRUE(Alarm_IsExpired(&a));
}

void test_Alarm_IsExpired_handles_rollover(void)
{
  Alarm_Init(&a, 10);
  Clock_Get_ExpectAndReturn(UINT32_MAX - 1);
  Alarm_Start(&a);
  Clock_Get_ExpectAndReturn(9);

  TEST_ASSERT_TRUE(Alarm_IsExpired(&a));

  Alarm_Init(&a, 10);
  Clock_Get_ExpectAndReturn(UINT32_MAX - 1);
  Alarm_Start(&a);
  Clock_Get_ExpectAndReturn(4);

  TEST_ASSERT_FALSE(Alarm_IsExpired(&a));
}
