/*
 * main.c
 *
 *  Created on: Mar 26, 2020
 *      Author: Youssef Harby
 */


#include <stdio.h>
#include "ECUAL/US.h"


/*- PREPROCESSOR MACROS ------------------------------------*/

#define SKIP_LINE		printf("\n")


/*- STATIC GLOBAL VARIABLES --------------------------------*/

static uint16_t gu8_US_GetDistanceFunctionTarget;

/*- APIs PROTOTYPES ----------------------------------------*/

void Us_Init_Tester(void);
void Us_Trigger_Tester(void);
void Us_GetDistance_Tester(uint16_t* Address);


/*- MAIN FUNCTION ------------------------------------------*/

int main(void)
{
//	REMOVE "//" FOR US_INIT FUNCTION TEST SCENARIOS
//
//	//US_INIT_1
//	Us_Init_Tester();
//	SKIP_LINE;
//
//	//US_INIT_2
//	Us_Init_Tester();
//	Us_Init_Tester();
//	SKIP_LINE;
//
//		SKIP_LINE;
//		SKIP_LINE;


//	REMOVE "//" FOR US_TRIGGER FUNCTION TEST SCENARIOS
//
//	//US_TRIGGER_1
//	Us_Init_Tester();
//	Us_Trigger_Tester();
//	SKIP_LINE;
//
//	//US_TRIGGER_2
//	Us_Trigger_Tester();
//	SKIP_LINE;
//
//		SKIP_LINE;
//		SKIP_LINE;


//	REMOVE "//" FOR US_GETDISTANCE FUNCTION TEST SCENARIOS
//
//	//US_GETDISTANCE_1
//	Us_Init_Tester();
//	Us_GetDistance_Tester(&gu8_US_GetDistanceFunctionTarget);
//	SKIP_LINE;
//
//	//US_TRIGGER_2
//	Us_Init_Tester();
//	Us_GetDistance_Tester(NULL);
//	SKIP_LINE;
//
//	//US_TRIGGER_3
//	Us_GetDistance_Tester(&gu8_US_GetDistanceFunctionTarget);
//	SKIP_LINE;

	return 0;
}


/*- APIs IMPLEMENTATION ------------------------------------*/

void Us_Init_Tester(void)
{
	sint8_t as8_ErrorValue = Us_Init();

	if(as8_ErrorValue == US_E_ALREADY_INIT)
	{
		printf("Us Init Error Detected - Us Already Initialized\n");
	}else if(as8_ErrorValue == US_E_OK)
	{
		printf("Us Init Error-Free\n");
	}
}


void Us_Trigger_Tester(void)
{
	sint8_t as8_ErrorValue = Us_Trigger();

	if(as8_ErrorValue == US_E_NOT_INIT)
	{
		printf("Us Trigger Error Detected - Us Not Initialized\n");
	}else if(as8_ErrorValue == US_E_OK)
	{
		printf("Us Trigger Error-Free\n");
	}
}


void Us_GetDistance_Tester(uint16_t* Address)
{
	sint8_t as8_ErrorValue = Us_GetDistance(Address);

	if(as8_ErrorValue == US_E_NOT_INIT)
	{
		printf("Us Get Distance Error Detected - Us Not Initialized\n");
	}else if(as8_ErrorValue == US_E_NULL_POINTER)
	{
		printf("Us Get Distance Error Detected - Null Pointer\n");
	}else if(as8_ErrorValue == US_E_OK)
	{
		printf("Us Get Distance Error-Free\n");
	}
}
