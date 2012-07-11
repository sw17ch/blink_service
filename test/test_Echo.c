#include "unity.h"
#include "Echo.h"

#include <string.h>

#include "mock_Serial.h"

Echo_t echo;
Serial_t serial;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Breadcrumbs(void)
{
	TEST_ASSERT_EQUAL(16, sizeof(echo.buffer));
}

void test_Echo_Init_should_clear_buffer(void)
{
 	uint8_t expected_buffer[ECHO_BUFFER_SIZE] = { 0 };

	memset(echo.buffer, 9, sizeof(echo.buffer));

	Echo_Init(&echo);

	TEST_ASSERT_EQUAL_MEMORY(expected_buffer, echo.buffer, sizeof(expected_buffer));
}

void test_Echo_Service_should_get_then_put(void)
{
	Serial_Get_ExpectAndReturn(&serial, echo.buffer, sizeof(echo.buffer), 9);
	Serial_Put_ExpectAndReturn(&serial, echo.buffer, 9, 0);

	Echo_Service(&echo, &serial);
}
