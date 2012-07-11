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

  TEST_ASSERT_EQUAL(backing, rb.backing);
  TEST_ASSERT_EQUAL(BACKING_SIZE, rb.backing_size);
  TEST_ASSERT_EQUAL(0, rb.head);
  TEST_ASSERT_EQUAL(0, rb.tail);
  TEST_ASSERT_EQUAL(0, rb.len);
}

void test_RingBuffer_Put_stores_values(void)
{
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'B'));
  TEST_ASSERT_EQUAL('A', rb.backing[0]);
  TEST_ASSERT_EQUAL('B', rb.backing[1]);
}

void test_RingBuffer_Put_adjusts_len(void)
{
  TEST_ASSERT_EQUAL(0, rb.len);
  RingBuffer_Put(&rb, 'A');
  TEST_ASSERT_EQUAL(1, rb.len);
  RingBuffer_Put(&rb, 'B');
  TEST_ASSERT_EQUAL(2, rb.len);
}

void test_RingBuffer_Put_is_handles_overflows(void)
{
  uint8_t expected_backing[] = {'A','B','C','D', 0};

  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'A'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'B'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'C'));
  TEST_ASSERT_TRUE(RingBuffer_Put(&rb, 'D'));
  TEST_ASSERT_FALSE(RingBuffer_Put(&rb, 'E')); // overflow, should be false

  TEST_ASSERT_EQUAL_MEMORY(expected_backing, backing, sizeof(expected_backing));

}

void test_RingBuffer_Get_is_true_when_data_is_valid(void)
{
  uint8_t val = 0;

  RingBuffer_Put(&rb, 'A');

  TEST_ASSERT_TRUE(RingBuffer_Get(&rb, &val));
  TEST_ASSERT_EQUAL('A', val);

  RingBuffer_Put(&rb, 'B');

  TEST_ASSERT_TRUE(RingBuffer_Get(&rb, &val));
  TEST_ASSERT_EQUAL('B', val);
}

void test_RingBuffer_Get_is_false_when_data_is_invalid(void)
{
  uint8_t val = 0;
  TEST_ASSERT_FALSE(RingBuffer_Get(&rb, &val));

  RingBuffer_Put(&rb, 'A');
  TEST_ASSERT_TRUE(RingBuffer_Get(&rb, &val));
  TEST_ASSERT_FALSE(RingBuffer_Get(&rb, &val));
}

void test_RingBuffer_Get_can_wrap_around(void)
{
  uint8_t val = 0;

  // Fill the buffer.
  RingBuffer_Put(&rb, 'A');
  RingBuffer_Put(&rb, 'B');
  RingBuffer_Put(&rb, 'C');
  RingBuffer_Put(&rb, 'D');

  // Pull something out.
  RingBuffer_Get(&rb, &val);
  TEST_ASSERT_EQUAL('A', val);

  // Put two more things in. Second should fail.
  RingBuffer_Put(&rb, 'E');
  TEST_ASSERT_FALSE(RingBuffer_Put(&rb, 'X'));

  // Pull everything out.
  RingBuffer_Get(&rb, &val);
  TEST_ASSERT_EQUAL('B', val);
  RingBuffer_Get(&rb, &val);
  TEST_ASSERT_EQUAL('C', val);
  RingBuffer_Get(&rb, &val);
  TEST_ASSERT_EQUAL('D', val);
  RingBuffer_Get(&rb, &val);
  TEST_ASSERT_EQUAL('E', val);
}

void test_RingBuffer_Reset_puts_the_ring_buffer_at_its_original_state(void)
{
  RingBuffer_Put(&rb, 'A');
  RingBuffer_Reset(&rb);

  TEST_ASSERT_EQUAL(0, rb.len);
  TEST_ASSERT_EQUAL(0, rb.head);
  TEST_ASSERT_EQUAL(0, rb.tail);
}
