/*
 * car_sm_test.c
 *
 * Created: 3/30/2020 12:40:56 AM
 *  Author: mahmo
 */ 
#include "car_sm_test.h"

extern uint8_t gu8_steeringInitState;
extern uint8_t gu8_steeringSteerCarState;
extern uint8_t gu8_usInitState;
extern uint8_t gu8_UsTriggerState;
extern uint8_t gu8_usGetDistanceState;

ERROR_STATUS car_init_test(sint16_t senario);

void car_sm_test(void)
{	
	const char * u8_testFilePath = "F:/Carier/Embedded/Sprints/CarStaticDesign-Slave/CarStaticDesign/Test/Car_sm_test/tests.txt";
	gstr_testFunPtr_t gstr_testFunPtr[] = {{"car_init_test",car_init_test}};
	uint8_t u8_counter = ZERO;
	testModule(u8_testFilePath,gstr_testFunPtr,1,&u8_counter);
}

ERROR_STATUS car_init_test(sint16_t senario)
{
	/*two stub fun [steering init , us init]->> four test cases*/

	switch(senario)
	{
		case 1:
		/*everything is working fine*/
		gu8_steeringInitState = OK;
		gu8_usInitState = OK;
		break;
		case 2:
		/**/
		gu8_steeringInitState = OK;
		gu8_usInitState = NOK;
		break;
		case 3:
		gu8_steeringInitState = NOK;
		gu8_usInitState = OK;
		break;
		case 4:
		gu8_steeringInitState = NOK;
		gu8_usInitState = NOK;
		break;
	}	
		return Car_SM_Init();

}