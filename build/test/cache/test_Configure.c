#include "unity.h"
#include "mock_Clock.h"
#include "Configure.h"


void setUp(void)

{

}



void tearDown(void)

{

}



void test_Configure_should_setup_timer_and_port(void)

{

    Configure();



    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((TCCR0B)), (((void *)0)), (_U_UINT)18, UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((TIMSK0)), (((void *)0)), (_U_UINT)19, UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0x20)), (_U_SINT)((DDRB)), (((void *)0)), (_U_UINT)20, UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((TCNT0)), (((void *)0)), (_U_UINT)21, UNITY_DISPLAY_STYLE_INT);

}
