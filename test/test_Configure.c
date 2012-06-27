#include "unity.h"
#include "Configure.h"
#include <avr/io.h>
#include "mock_Clock.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Configure_should_setup_timer_and_port(void)
{
    Configure();

    TEST_ASSERT_EQUAL(3    , TCCR0B);
    TEST_ASSERT_EQUAL(1    , TIMSK0);
    TEST_ASSERT_EQUAL(0x20 , DDRB);
    TEST_ASSERT_EQUAL(5    , TCNT0);
}
