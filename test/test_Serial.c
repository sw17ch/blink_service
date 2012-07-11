#include "unity.h"
#include "Serial.h"
#include "Serial_Callbacks.h"

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "mock_RingBuffer.h"
#include "mock_UART.h"

Serial_t serial;
int32_t forever_call_count = 0;

void setUp(void)
{
	memset(&serial, 0, sizeof(serial));
	forever_call_count = 0;
}
void tearDown(void) {}

static bool RingBuffer_Get_Short_Stub(RingBuffer_t * rb, uint8_t * byte, int32_t numcalls);
static bool RingBuffer_Get_Forever_Stub(RingBuffer_t * rb, uint8_t * byte, int32_t numcalls);

void test_Serial_Init(void)
{
	RingBuffer_Init_Expect(&serial.rb, serial.rb_backing, RING_BUFFER_BACKING_SIZE);
	UART_Init_Expect(Serial_Callbacks_RX, &serial, Serial_Callbacks_TX, &serial);
  Serial_Init(&serial);
}

void test_Serial_Put_sticks_bytes_in_the_ring_buffer_and_kicks_uart(void)
{
	uint8_t buf[] = {1,2,3};

	RingBuffer_Put_ExpectAndReturn(&serial.rb, 1, true);
	RingBuffer_Put_ExpectAndReturn(&serial.rb, 2, true);
	RingBuffer_Put_ExpectAndReturn(&serial.rb, 3, true);

	UART_Wakeup_Expect();

	Serial_Put(&serial, buf, sizeof(buf));
}

void test_Serial_Put_returns_bytes_unsent_and_only_calls_wakeup_if_some_bytes_were_put(void)
{
	uint8_t buf[] = {1,2,3};

	RingBuffer_Put_ExpectAndReturn(&serial.rb, 1, false);
	TEST_ASSERT_EQUAL(3, Serial_Put(&serial, buf, 3));

	RingBuffer_Put_ExpectAndReturn(&serial.rb, 1, true);
	RingBuffer_Put_ExpectAndReturn(&serial.rb, 2, false);
	UART_Wakeup_Expect();
	TEST_ASSERT_EQUAL(2, Serial_Put(&serial, buf, 3));

	RingBuffer_Put_ExpectAndReturn(&serial.rb, 1, true);
	RingBuffer_Put_ExpectAndReturn(&serial.rb, 2, true);
	RingBuffer_Put_ExpectAndReturn(&serial.rb, 3, true);
	UART_Wakeup_Expect();
	TEST_ASSERT_EQUAL(0, Serial_Put(&serial, buf, 3));
}

void test_Serial_Get_retrieves_bytes(void)
{
	uint8_t buf[4];

	RingBuffer_Get_StubWithCallback(RingBuffer_Get_Short_Stub);

	TEST_ASSERT_EQUAL(1, Serial_Get(&serial, buf, sizeof(buf)));
}

void test_Serial_Get_retrieves_at_most_len_bytes(void)
{
	uint8_t buf[4];

	RingBuffer_Get_StubWithCallback(RingBuffer_Get_Forever_Stub);

	TEST_ASSERT_EQUAL(4, Serial_Get(&serial, buf, sizeof(buf)));
	TEST_ASSERT_EQUAL(4, forever_call_count);
}

void test_Serial_Callbacks_RX_counts_overflows(void)
{
	TEST_IGNORE_MESSAGE("implement me");
}

// Callback stubs.

static bool RingBuffer_Get_Short_Stub(RingBuffer_t * rb, uint8_t * byte, int32_t numcalls)
{
	TEST_ASSERT_EQUAL(&serial.rb, rb);

	switch(numcalls)
	{
		case 0:
			*byte = 'A';
			return true;
		default:
			return false;
	}
}

static bool RingBuffer_Get_Forever_Stub(RingBuffer_t * rb, uint8_t * byte, int32_t numcalls)
{
	TEST_ASSERT_EQUAL(&serial.rb, rb);
	forever_call_count++;

	*byte = 'X';
	return true;
}
