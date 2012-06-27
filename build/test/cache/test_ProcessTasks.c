#include "unity.h"
#include "mock_Blinker.h"
#include "ProcessTasks.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_ProcessTasks_should_execute_tasks(void)

{

  ProcessTasks_t process_tasks;



  Blinker_Service_CMockExpect(18, &process_tasks.blinker);



  ProcessTasks(&process_tasks);

}
