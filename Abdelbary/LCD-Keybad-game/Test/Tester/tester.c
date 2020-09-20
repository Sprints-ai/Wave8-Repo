/*
 * testing.c
 *
 * Created: 3/13/2020 9:19:54 AM
 *  Author: mahmo
 */ 

#ifdef GCC


#include "tester.h"
void checkTestCase(sint16_t s16_expected_return , sint16_t s16_fun_return,uint8_t * u8_testCaseNumber)
{
	printf("testCase %3d:	expected_return : %3d	 fun_return: %3d	",*u8_testCaseNumber,s16_expected_return,s16_fun_return);
	/*check on test case*/
	if (s16_fun_return == s16_expected_return)
	printf("Passed.\n");
	else
	printf("Failed.\n");
	(*u8_testCaseNumber)++;
}
void compareValue(sint16_t s16_expected_value , sint16_t s16_return_value,uint8_t * u8_testCaseNumber)
{
	printf("	    %3:   expected_return : %3d	 fun_return: %3d	",s16_expected_value,s16_return_value);
	/*check on test case*/
	if (s16_return_value == s16_expected_value)
	printf("Passed.\n");
	else
	printf("Failed.\n");
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






void parameter_test2(sint16_t s16_testParamter[][TEST_PARAMTER_AND_RET_VALUE],uint8_t u8_size ,ERROR_STATUS (*callB_fun)(sint16_t),sint16_t s16_startValue,
sint16_t s16_endValue,sint16_t s16_Step, sint16_t ERROR_VALUE ,uint8_t u8_useSamplesFlag,uint8_t * u8_testCaseNumber)
{
	uint8_t u8_counter = 0 ;
	sint16_t s16_expected_return = OK;
	sint16_t s16_fun_return;
	for (;u8_counter < u8_size ;u8_counter++ )
	{
		s16_fun_return = callB_fun(s16_testParamter[u8_counter][TEST_PARAMTER]);
		/*check for expected fun status*/
		s16_expected_return = s16_testParamter[u8_counter][EXPECTED_RETURN];
		
		checkTestCase(s16_expected_return , s16_fun_return,u8_testCaseNumber);
	}
	
	if (u8_useSamplesFlag == TRUE)
	{
		sint16_t s16_paramterValue = s16_startValue;
		s16_expected_return = ERROR_VALUE;
		
		for (;s16_paramterValue <= s16_endValue ;s16_paramterValue+=s16_Step )
		{
			s16_fun_return = callB_fun(s16_paramterValue);
			checkTestCase(s16_expected_return , s16_fun_return,u8_testCaseNumber);
		}

		
	}
}
void test(void)
{
	#ifdef TMU_TEST
	TMU_Module_run_test();
	#elif  ULTRA_SONIC
	Us_Module_Test();
	#elif  BCM_TEST
	BCM_Module_Test();
	#elif  SOS_TEST
	SOS_Module_run_test();
	#elif  SPI_TEST
	SPI_Module_Test();
	#endif
}
#endif