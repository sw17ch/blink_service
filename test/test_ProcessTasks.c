#include "unity.h"
#include "ProcessTasks.h"

#include "mock_Blinker.h"
#include "mock_Echo.h"
#include "mock_Serial.h"

ProcessTasks_t process_tasks;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ProcessTasks_Init_should_init_tasks(void)
{
	Serial_Init_Expect(&process_tasks.serial);

	Blinker_Init_Expect(&process_tasks.blinker);
	Echo_Init_Expect(&process_tasks.echo);

	ProcessTasks_Init(&process_tasks);
}

void test_ProcessTasks_should_execute_tasks(void)
{
  ProcessTasks_t process_tasks;

  Blinker_Service_Expect(&process_tasks.blinker);
	Echo_Service_Expect(&process_tasks.echo, &process_tasks.serial);

  ProcessTasks(&process_tasks);
}
