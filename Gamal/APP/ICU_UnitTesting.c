/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : this file test the ICU driver
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ICU.h"

#define NULL_Ptr ((void*)0)
#define NONE_VALID_INT_CH 3
#define NONE_VALID_TIMER_CH 3
#define NONE_VALID_EDGE_STATE 3
extern uint8_t timer_stub_return_value;
extern uint8_t INT_stub_return_value;

void func(void)
{

}

int main(void) {
	timer_stub_return_value=E_ok;
	INT_stub_return_value=E_ok;
	uint8_t au8_ExpectedOutput=E_ok;
	uint8_t u8_status1=E_ok;
	uint8_t u8_status2=E_ok;
	uint8_t u8_status3=E_ok;
	uint8_t u8_status4=E_ok;
	uint8_t u8_status5=E_ok;
	uint8_t u8_status6=E_ok;
	uint8_t u8_status7=E_ok;
	uint8_t u8_status8=E_ok;
	uint8_t u8_status9=E_ok;
	uint8_t u8_status10=E_ok;
	uint8_t u8_status11=E_ok;
	uint8_t u8_status12=E_ok;
	uint8_t u8_status13=E_ok;
	uint8_t u8_status14=E_ok;
	uint8_t u8_status15=E_ok;
	uint8_t u8_status16=E_ok;
	uint8_t u8_status17=E_ok;
	uint8_t u8_status18=E_ok;
	uint8_t u8_status19=E_ok;
	uint8_t u8_status20=E_ok;
	uint32_t u32_time;
	uint8_t u8_time;
	uint8_t* testcase3=NULL;
	void(*a_ptr)(void)=func;
	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a valid address with a valid data to "Icu_Init"
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	Icu_cfg_s testcase1={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status1 = Icu_Init(&testcase1);
	if(u8_status1==au8_ExpectedOutput)
	{
		printf("test case 1: PASSED\n");
	}
	else
	{
		printf("test case 1: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a valid address with a none-valid data (Timer1) data to "Icu_Init"
	* NOTE THAT: timer1 shouldn't be handled due to hardware limitations
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase2={ICU_CH1,ICU_TIMER_CH1};    //INT1,TIMER1
	u8_status2 = Icu_Init(&testcase2);
	if(u8_status2==au8_ExpectedOutput)
	{
		printf("test case 2: PASSED\n");
	}
	else
	{
		printf("test case 2: FAILED\n");
	}




	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a NULL pointer to "Icu_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status3 = Icu_Init(testcase3);
	if(u8_status3==au8_ExpectedOutput)
	{
		printf("test case 3: PASSED\n");
	}
	else
	{
		printf("test case 3: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a wiled pointer to "Icu_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	* NOTE: this test case has to be commented while testing any other test case since the
	* this test case could cause a Code Crash
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	uint8_t* testcase4;
	u8_status4 = Icu_Init(testcase4);
	if(u8_status4==au8_ExpectedOutput)
	{
		printf("test case 4: PASSED\n");
	}
	else
	{
		printf("test case 4: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a variable address from different data type to "Icu_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	int testcase5={ICU_CH2,ICU_TIMER_CH2};
	u8_status5 = Icu_Init(&testcase5);
	if(u8_status5==au8_ExpectedOutput)
	{
		printf("test case 5: PASSED\n");
	}
	else
	{
		printf("test case 5: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a valid address with a none-valid interrupt number to "Icu_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase6={NONE_VALID_INT_CH,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status6 = Icu_Init(&testcase6);
	if(u8_status6==au8_ExpectedOutput)
	{
		printf("test case 6: PASSED\n");
	}
	else
	{
		printf("test case 6: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_Init
	* Test Case: send a valid address with a none-valid timer number to "Icu_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase7={ICU_CH2,NONE_VALID_TIMER_CH};    /*INT2,TIMER2*/
	u8_status7 = Icu_Init(&testcase7);
	if(u8_status7==au8_ExpectedOutput)
	{
		printf("test case 7: PASSED\n");
	}
	else
	{
		printf("test case 7: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a valid data without initialization to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status8 |= Icu_ReadTime(Timer_0,ICU_RISE_TO_FALL,&u32_time);
	if(u8_status8==au8_ExpectedOutput)
	{
		printf("test case 8: PASSED\n");
	}
	else
	{
		printf("test case 8: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a none-valid data after initialization to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase9={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status9 |= Icu_Init(&testcase9);
	u8_status9 |= Icu_ReadTime(NONE_VALID_TIMER_CH,ICU_RISE_TO_FALL,&u32_time);
	if(u8_status9==au8_ExpectedOutput)
	{
		printf("test case 9: PASSED\n");
	}
	else
	{
		printf("test case 9: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a none-valid data after initialization to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase10={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status10 |= Icu_Init(&testcase10);
	u8_status10 |= Icu_ReadTime(Timer_0,NONE_VALID_EDGE_STATE,&u32_time);
	if(u8_status10==au8_ExpectedOutput)
	{
		printf("test case 10: PASSED\n");
	}
	else
	{
		printf("test case 10: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a none-valid data after initialization (an argument from different
	* data type) to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase11={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status11 |= Icu_Init(&testcase11);
	u8_status11 |= Icu_ReadTime(Timer_2,ICU_RISE_TO_FALL,&u8_time);
	if(u8_status11==au8_ExpectedOutput)
	{
		printf("test case 11: PASSED\n");
	}
	else
	{
		printf("test case 11: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a none-valid data after initialization (the 3rd argument with out
	* the address reference) to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	* NOTE: this test case has to be commented while testing any other test case since the
	* this test case could cause a Code Crash
	************************************************************************************/

	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase12={ICU_CH2,ICU_TIMER_CH2};    //INT2,TIMER2
	u8_status12 |= Icu_Init(&testcase12);
	u8_status12 |= Icu_ReadTime(Timer_0,ICU_RISE_TO_FALL,u32_time);
	if(u8_status12==au8_ExpectedOutput)
	{
		printf("test case 12: PASSED\n");
	}
	else
	{
		printf("test case 12: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send an uninitialized timer channel to "Icu_ReadTime"
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase13={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status13 |= Icu_Init(&testcase13);
	u8_status13 |= Icu_ReadTime(Timer_0,ICU_RISE_TO_FALL,&u32_time);
	if(u8_status13==au8_ExpectedOutput)
	{
		printf("test case 13: PASSED\n");
	}
	else
	{
		printf("test case 13: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: send a valid data after initialization to "Icu_ReadTime"
	* Expected OUTPUT: PASSED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_ok;
	Icu_cfg_s testcase14={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	u8_status14 |= Icu_Init(&testcase14);
	u8_status14 |= Icu_ReadTime(Timer_0,ICU_RISE_TO_FALL,&u32_time);
	if(u8_status14==au8_ExpectedOutput)
	{
		printf("test case 14: PASSED\n");
	}
	else
	{
		printf("test case 14: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: valid calling to "Icu_Init" with E_NOK return from Timer_Module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase15={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	timer_stub_return_value=E_NOk;
	u8_status15 |= Icu_Init(&testcase15);
	timer_stub_return_value=E_ok;
	if(u8_status15==au8_ExpectedOutput)
	{
		printf("test case 15: PASSED\n");
	}
	else
	{
		printf("test case 15: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: valid calling to "Icu_Init" with E_NOK return from INT_Module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Icu_cfg_s testcase16={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	INT_stub_return_value=E_NOk;
	u8_status16 |= Icu_Init(&testcase16);
	INT_stub_return_value=E_ok;
	if(u8_status16==au8_ExpectedOutput)
	{
		printf("test case 16: PASSED\n");
	}
	else
	{
		printf("test case 16: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: call "Rising_EdgeFunc" without initialization
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	Rising_EdgeFunc();
	if(u8_status17==au8_ExpectedOutput)
	{
		printf("test case 17: PASSED\n");
	}
	else
	{
		printf("test case 17: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: valid calling to "Icu_setCallBack" with E_NOK return from Timer_Module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	timer_stub_return_value=E_ok;
	Icu_cfg_s testcase18={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	Icu_Init(&testcase18);
	timer_stub_return_value=E_NOk;
	u8_status18 |= Icu_setCallBack(a_ptr);
	timer_stub_return_value=E_ok;
	if(u8_status18==au8_ExpectedOutput)
	{
		printf("test case 18: PASSED\n");
	}
	else
	{
		printf("test case 18: FAILED\n");
	}


	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: valid calling to "Icu_setCallBack" with E_NOK return from INT_Module
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	INT_stub_return_value=E_ok;
	Icu_cfg_s testcase19={ICU_CH2,ICU_TIMER_CH2};    /*INT2,TIMER2*/
	Icu_Init(&testcase19);
	INT_stub_return_value=E_NOk;
	u8_status19 |= Icu_setCallBack(a_ptr);
	if(u8_status19==au8_ExpectedOutput)
	{
		printf("test case 19: PASSED\n");
	}
	else
	{
		printf("test case 19: FAILED\n");
	}



	/************************************************************************************
	* Target Function: Icu_ReadTime
	* Test Case: call "Icu_setCallBack" with NULL Pointer
	* Expected OUTPUT: FAILED
	* Real OUTPUT:
	************************************************************************************/
	au8_ExpectedOutput=E_NOk;
	u8_status20 |= Icu_setCallBack(NULL_Ptr);
	if(u8_status20==au8_ExpectedOutput)
	{
		printf("test case 20: PASSED\n");
	}
	else
	{
		printf("test case 20: FAILED\n");
	}


	return 0;
}




