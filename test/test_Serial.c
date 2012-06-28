#include "unity.h"
#include "Serial.h"

#include <string.h>

Serial_t serial;

void setUp(void) {memset(&serial, 0, sizeof(serial));}
void tearDown(void) {}

void test_Serial_Init(void)
{
  Serial_Init(&serial, 70);
  TEST_ASSERT_EQUAL(70, serial.port);
}
