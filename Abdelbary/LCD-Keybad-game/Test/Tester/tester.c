/*
 * testing.c
 *
 * Created: 3/13/2020 9:19:54 AM
 *  Author: mahmo
 */ 

#include "tester.h"
void checkTestCase(sint16_t s16_expected_return , sint16_t s16_fun_return,uint8_t * u8_testCaseNumber)
{
	printf("testCase %3d:	expected_return : %3d	 fun_return: %3d	",*u8_testCaseNumber,s16_expected_return,s16_fun_return);
	/*check on test case*/
	if (s16_fun_return == s16_expected_return)
	printf("Passed.\n");
	else
	printf("Failed.\n");
	u8_testCaseNumber++;
}

void parameter_test(uint8_t* u8_testParamterValues,uint8_t u8_size ,ERROR_STATUS (*callB_fun)(uint8_t), sint16_t ERROR_VALUE,uint8_t * u8_testCaseNumber)
{
	uint8_t u8_counter = 0 ;
	sint16_t s16_expected_return = OK;
	sint16_t s16_fun_return;
	for (;u8_counter < u8_size ;u8_counter++ )
	{
		s16_fun_return = callB_fun(u8_testParamterValues[u8_counter]);
		
		/*check for expected fun status*/
		if(u8_testParamterValues[u8_counter] == u8_testParamterValues[u8_size-ONE])
		s16_expected_return = (ERROR_VALUE);
		
		checkTestCase(s16_expected_return , s16_fun_return,u8_testCaseNumber);

	}
}

void test(void)
{
	#ifdef TMU_TEST
	TMU_Module_run_test();
	#elif  ULTRA_SONIC
	Us_Module_Test();
	#elif  SOS_TEST
	SOS_Module_run_test();
	#elif LCD_TEST
	LCD_Module_run_test();
	#endif
}