/*
 * testing.c
 *
 * Created: 3/13/2020 9:19:54 AM
 *  Author: mahmo
 */ 

#ifdef GCC


#include "tester.h"

ERROR_STATUS dummy(sint16_t x)
{
	return OK;
}
ERROR_STATUS dummy2(sint16_t x)
{
	return -102;
}
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


/************************test automation**********************************/

int testModule(const char * u8_filePath,gstr_testFunPtr_t gstr_testFunPtr[],uint8_t u8_CBF_arraySize,uint8_t* u8_testCaseCounter)
{
	FILE * filePtr = fopen(u8_filePath, "rt");
	uint8_t  au8_paramterType[MAX_PARAMTER_SIZE];
	uint8_t  au8_Paramter[MAX_PARAMTER_SIZE];
	uint8_t  u8_useRangeFlag = FALSE;
	sint16_t u8_rangStartVal = ZERO;
	sint16_t u8_rangeEndVal  = ZERO;
	sint16_t u8_rangeStep	 = ZERO;
	sint16_t u8_rangeErrVal  = ZERO;
	sint16_t u8_testCounts   = ZERO;
	CBF      testCBF = NULL;
	
	sint16_t testParam [MAX_TEST][TEST_PARAMTER_AND_RET_VALUE];

	if(filePtr == NULL)
	{
		printf("file %s not found",u8_filePath);
	}
	else
	{
		uint8_t u8_tempLineBuffer[MAX_LINE_SIZE];
		while(!feof(filePtr))
		{
			if (fgets(u8_tempLineBuffer,MAX_LINE_SIZE,filePtr) && strcmp(u8_tempLineBuffer,"\n") != ZERO) 
			{
				sscanf(u8_tempLineBuffer, "%40s : %40[^;]s;", au8_paramterType, au8_Paramter);
				
				//printf("<<%s>><<%s>>\n",  tmpstr1,tmpstr2);
				if (strcmp(au8_paramterType,"MOD")== ZERO)
				{
					PrintHeader(au8_Paramter,TEST_PANAR_HEADER);
				}
				
				
				else if(strcmp(au8_paramterType,"FUN")== ZERO)
				{
					PrintHeader(au8_Paramter,TEST_PANAR_FUN_NAME);
				}
				
				
				else if(strcmp(au8_paramterType,"TESTFUN")== ZERO)
				{
					uint8_t u8_counter = ZERO;
					for (;u8_counter < u8_CBF_arraySize ; u8_counter++)
						if (strcmp(au8_Paramter,gstr_testFunPtr[u8_counter].pu8_funName)==0)
							testCBF = gstr_testFunPtr[u8_counter].testFunCallback_t;
						
					if(testCBF == NULL)
						printf("Unrecongized parameter : \"%s\"\n", au8_Paramter);
				}
				
				
				else if (strcmp(au8_paramterType,"C")== ZERO) {
					
					sscanf(au8_Paramter, "[%d,%d]", &testParam[u8_testCounts][TEST_CBF_NAME], &testParam[u8_testCounts][TEST_CBF_ADD]);
					u8_testCounts++;
				}
				
				
				else if (strcmp(au8_paramterType,"R")== ZERO) {
					
					sscanf(au8_Paramter, "[%d,%d,%d,%d]" , &u8_rangStartVal,&u8_rangeEndVal,&u8_rangeStep,&u8_rangeErrVal);
					
					u8_useRangeFlag = TRUE;
					
				}
				else if (strcmp(au8_paramterType,"END")== ZERO) {
					if (testCBF == NULL)
						printf("CBF IS NULL\n");
					else if(u8_useRangeFlag == TRUE && u8_rangStartVal > u8_rangeEndVal)
						printf("RANGE START > RANGE END\n");
					else if(u8_testCaseCounter == NULL)
							printf("u8_testCaseCounter IS NULL\n");
					else /*everything is ok*/
						{
							parameter_test2(testParam,u8_testCounts,testCBF,u8_rangStartVal,u8_rangeEndVal,u8_rangeStep,u8_rangeErrVal,u8_useRangeFlag,u8_testCaseCounter);
							u8_testCounts = ZERO;
						}				
				}
				else{
					printf("Unrecongized parameter : \"%s\"\n", au8_paramterType);
				}
			}
		}
		fclose(filePtr);		
	}
	

}

void PrintHeader(uint8_t* u8_buffer,uint8_t u8_type)
{
		uint8_t u8_padlen = (TOTAL_PAD - strlen(u8_buffer))>>ONE;
		switch(u8_type)
		{
			case TEST_PANAR_HEADER:
				printf("\n\n\t=========================%*s%s%*s=======================\n\n",u8_padlen, "", u8_buffer, u8_padlen, "");
			break;
			case TEST_PANAR_FOOTER:
				printf("\n\n\t=========================ENDED================================\n\n");
			break;
			case TEST_PANAR_FUN_NAME:
				printf("\n\t\t-----------------%*s%s%*s---------------\n\n",u8_padlen, "", u8_buffer, u8_padlen, "");
			break;
			default:
				printf("\n\t\t-----------------UNKNOWN-PARAMTER-TO-PRINT-HEADE-FUN----------\n\n");
			break;
		}
}
void test(void)
{
/*
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
	#elif CAR_SM_TEST
	car_sm_test();
	#elif DUMMY_TEST
	uint8_t* u8_testFilePath = "F:/Carier/Embedded/Sprints/CarStaticDesign-Slave/CarStaticDesign/Test/Tester/tests.txt";
	gstr_testFunPtr_t gstr_testFunPtr[] = {{"dummy",dummy},{"dummy2",dummy2}};
	uint8_t u8_counter = ZERO;
	testModule(u8_testFilePath,gstr_testFunPtr,2,&u8_counter);
	#endif
	*/
	
}
#endif