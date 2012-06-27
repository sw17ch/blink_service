#include "unity.h"
#include "ProcessTasks.h"

#include "mock_Blinker.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ProcessTasks_should_execute_tasks(void)
{
  ProcessTasks_t process_tasks;

  Blinker_Service_Expect(&process_tasks.blinker);

  ProcessTasks(&process_tasks);
}
