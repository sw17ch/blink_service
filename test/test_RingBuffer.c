#include "unity.h"
#include "RingBuffer.h"

#include <stdint.h>
#include <string.h>

RingBuffer_t rb;
uint8_t backing[5];

// Strip off the last byte so we can safely test for overflow conditions.
#define BACKING_SIZE (sizeof(backing) - 1)

void setUp(void)
{
  memset(&rb, 0, sizeof(rb));
  memset(backing, 0, sizeof(backing));

  RingBuffer_Init(&rb, backing, BACKING_SIZE);
}

void tearDown(void)
{
}

void test_RingBuffer_Init_initializes_a_new_ring_buffer(void)
{
  memset(&rb, 0xAA, sizeof(rb));

  RingBuffer_Init(&rb, backing, BACKING_SIZE);

  TEST_ASSERT_EQUAL(rb.backing, backing);
  TEST_ASSERT_EQUAL(rb.head, 0);
  TEST_ASSERT_EQUAL(rb.tail, 0);
  TEST_ASSERT_EQUAL(rb.len, 0);
}

void test_RingBuffer_Put_stores_valies(void)
{
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'B'));
  TEST_ASSERT_EQUAL('A', rb.backing[0]);
  TEST_ASSERT_EQUAL('B', rb.backing[1]);
}

void test_RingBuffer_Put_is_false_on_overflow(void)
{
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_FALSE(RingBuffer_Put(&rb, 'A')); // overflow
}
