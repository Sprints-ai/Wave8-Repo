/*
 * SOS_test.c
 *
 * Created: 2/25/2020 3:23:35 PM
 *  Author: mahmo
 */ 
#include "SOS_test.h"
#define ERROR__TIMER_CH					3
#define TIMER_CHS_TESTS					4
#define TIMER_TICK_TEST					4
#define ERROR_TIMER_RESLUTION			(SOS_MAX_TIMER_RESLUTION+1)
#define FUN_STATUS_COUNT				2
#define POINTER_STATE_TESTS					2



#define ERROR_ID						SOS_OBJ_BUFFER_SIZE+ONE
#define ID_PARAMTER_TESTS				6
#define LAP_TIME_PARAMTER_TESTS			4
#define TYPES_PARAMTER_TESTS			3
#define ERROR_LAP_TIME					SOS_MAX_LAP_TIME+ONE
#define ERROR_TYPE_PARAMTER				ON_SHOT+ONE

					
#define invald_ID                      200
volatile uint16_t timer0_MS_flag;
static uint8_t gu8_testCaseNumber;
/*
static sint16_t sau16_fun_status [FUN_STATUS_COUNT] = {OK,NOK};
*/



void sos_stub_comsumer_fun(void)
{
	
}



ERROR_STATUS SOS_createTask_Id_rapper(uint8_t Id)
{
	return SOS_createTask(Id,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
}


ERROR_STATUS SOS_createTask_lapTime_rapper(uint8_t lap_time)
{
	static uint8_t Id = ZERO;
	sint16_t s16_fun_status =  SOS_createTask(Id,sos_stub_comsumer_fun,lap_time,PERIODIC,ONE);
	Id++;
	return s16_fun_status;
}

ERROR_STATUS SOS_createTask_callBFun_rapper(uint8_t CBF_indx)
{
	static uint8_t Id = ZERO;
	void (*fun_pointers_parameter[POINTER_STATE_TESTS])(void)= {sos_stub_comsumer_fun,NULL};
	sint16_t s16_fun_status =  SOS_createTask(Id,fun_pointers_parameter[CBF_indx],ONE,PERIODIC,ONE);
	Id++;
	return s16_fun_status;
}

ERROR_STATUS SOS_createTask_types_rapper(uint8_t type)
{
	static uint8_t Id = ZERO;
	sint16_t s16_fun_status =  SOS_createTask(Id,sos_stub_comsumer_fun,ONE,type,ONE);
	Id++;
	return s16_fun_status;
}
ERROR_STATUS SOS_init_timerCh_rapper(uint8_t parm)
{
	SOS_linkCfg.timer_ch = parm;
	SOS_linkCfg.tick_reslution = ONE;
	sint16_t s16_fun_status =  SOS_Init(&SOS_linkCfg);
	SOS_Deinit();
	return s16_fun_status;
}

ERROR_STATUS SOS_init_struct_rapper(uint8_t parm)
{
	gstr_SOS_cfg_t *cfg_struct_pointer[POINTER_STATE_TESTS] = {&SOS_linkCfg,NULL};

	sint16_t s16_fun_status =  SOS_Init(cfg_struct_pointer[parm]);
	SOS_Deinit();
	return s16_fun_status;
}
ERROR_STATUS SOS_init_timeReslution_rapper(uint8_t parm)
{
	SOS_linkCfg.timer_ch = ZERO;
	SOS_linkCfg.tick_reslution = parm;
	sint16_t s16_fun_status =  SOS_Init(&SOS_linkCfg);
	SOS_Deinit();
	return s16_fun_status;
}




void    SOS_Init_test()
{
	/*
	*	SOS_INIT has one parameter and call one fun
	*   test each element of the struct,one stub fun and struct pointer 4 test parameters needed
	*/
	/*note we are not handling the stub fun error return as it is not implemented*/
	/*test parameter for SOS_cfg struct->timer_chanal parameter and SOS_cfg structe->tick time*/
	
	sint16_t s16_expected_return = OK;
	sint16_t s16_fun_return;
	uint8_t au8_Timer_ch [TIMER_CHS_TESTS] = { SOS_TIMER_CH0,SOS_TIMER_CH1,SOS_TIMER_CH2,ERROR__TIMER_CH};
	uint8_t au8_Tick_reslution [TIMER_TICK_TEST] = { 1,3,SOS_MAX_TIMER_RESLUTION,ERROR_TIMER_RESLUTION};
	uint8_t str_SOS_cfg_pointer[POINTER_STATE_TESTS] = {0,1};
		
	
	parameter_test(au8_Timer_ch,TIMER_CHS_TESTS,SOS_init_timerCh_rapper,(SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER),&gu8_testCaseNumber);
	parameter_test(au8_Tick_reslution,TIMER_TICK_TEST,SOS_init_timeReslution_rapper,(SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER),&gu8_testCaseNumber);
	parameter_test(str_SOS_cfg_pointer,POINTER_STATE_TESTS,SOS_init_struct_rapper,(SOS_MODULE_ERROR_NUM+NULL_PTR_ERROR),&gu8_testCaseNumber);

	/*last test case reinitialize the module*/
	SOS_Init(&SOS_linkCfg);
	s16_fun_return = SOS_Init(&SOS_linkCfg);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MULTIPLE_INITALIZATION);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
}




void SOS_createTask_test(void)
{
	uint8_t au8_task_Ids [ID_PARAMTER_TESTS] = { 1,2,3,4,SOS_OBJ_BUFFER_SIZE,ERROR_ID};
	uint8_t au8_lap_time [LAP_TIME_PARAMTER_TESTS] = {1,2,SOS_MAX_LAP_TIME,ERROR_LAP_TIME};
	uint8_t au8_CBF_state_indx[POINTER_STATE_TESTS] = {0,1};
	uint8_t au8_types[TYPES_PARAMTER_TESTS] = {PERIODIC,ONE,ERROR_TYPE_PARAMTER};
		
	sint16_t s16_expected_return = OK;
	sint16_t s16_fun_return;

	
	/*
	*	test scenario 1 
	*	module initalized with tick reslution of 1 ms and timer ch 0 
	*	-test all  parameters with initialized module
	*/
	
	SOS_Init(&SOS_linkCfg);
	parameter_test(au8_task_Ids,ID_PARAMTER_TESTS,SOS_createTask_Id_rapper,(SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER),&gu8_testCaseNumber);
	SOS_Deinit();
	SOS_Init(&SOS_linkCfg);
	parameter_test(au8_lap_time,LAP_TIME_PARAMTER_TESTS,SOS_createTask_lapTime_rapper,(SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER),&gu8_testCaseNumber);
	SOS_Deinit();
	SOS_Init(&SOS_linkCfg);	
	parameter_test(au8_CBF_state_indx,POINTER_STATE_TESTS,SOS_createTask_callBFun_rapper,(SOS_MODULE_ERROR_NUM+NULL_PTR_ERROR),&gu8_testCaseNumber);
	SOS_Deinit();
	SOS_Init(&SOS_linkCfg);
	parameter_test(au8_types,TYPES_PARAMTER_TESTS,SOS_createTask_types_rapper,(SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER),&gu8_testCaseNumber);
	SOS_Deinit();
	
	
	/*
	*	scenario 1.1
	*	call start with same id
	*/
	SOS_Init(&SOS_linkCfg);
	SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);	
	s16_fun_return = SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();

	/*
	*	test scenario 2
	*	start SOS with no SOS_int
	*/
	s16_fun_return = SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);

	/*	Test scenario 3
	*	start SOS after SOS_deinit
	*/
	SOS_Init(&SOS_linkCfg);
	SOS_Deinit();
	s16_fun_return = SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
}

void SOS_deletTask_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;	
	
	/* scenario one stop without init*/
	s16_fun_return = SOS_deletTask(ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	/*-scenario two stop without start*/
	SOS_Init(&SOS_linkCfg);
	s16_fun_return = SOS_deletTask(ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	
	/*-scenario three stop invalid ID*/
	SOS_Init(&SOS_linkCfg);
	s16_fun_return =SOS_deletTask(invald_ID);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	/*-scenario four stop same id twice*/
	SOS_Init(&SOS_linkCfg);
	SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
	SOS_deletTask(ONE);
	s16_fun_return = SOS_deletTask(ONE);
	s16_expected_return = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	/*-scenario five stop an existing id*/
	SOS_Init(&SOS_linkCfg);
	SOS_createTask(ONE,sos_stub_comsumer_fun,ONE,PERIODIC,ONE);
	s16_fun_return = SOS_deletTask(ONE);
	s16_expected_return = (OK);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
}

void SOS_dispatcher_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;
	/*test case 1 calling dispatcher without init SOS*/
	s16_fun_return = SOS_run();
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);

	
	
	/*test case 2 calling dispatcher without anyTasks*/
	SOS_Init(&SOS_linkCfg);
	s16_fun_return = SOS_run();
	s16_expected_return = (OK);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	
	/*test case 3 calling dispatcher with buffer full*/
	SOS_Init(&SOS_linkCfg);
	for(uint8_t u8_counter = 0 ; u8_counter <SOS_OBJ_BUFFER_SIZE ; u8_counter++)
	{
		SOS_createTask(u8_counter,sos_stub_comsumer_fun,u8_counter+1,PERIODIC,ONE);
	}
	s16_fun_return = SOS_run();
	s16_expected_return = (OK);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	SOS_Deinit();
	
}


void SOS_DeInit_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;

	/*test case 1 normal*/
	SOS_Init(&SOS_linkCfg);
	s16_fun_return = SOS_Deinit();
	s16_expected_return = (OK);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	
	/*test case 2 nok*/
	s16_fun_return = SOS_Deinit();
	s16_expected_return = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
}

void SOS_Module_run_test(void)
{
	printf("\n\n\t=========================SOS_Module_TEST=======================\n\n");
	printf("\n\t\t-----------------SOS_Init_TEST-------------\n");
	SOS_Init_test();
	printf("\n\t\t-----------------SOS_DeInit_TEST-----------\n");
	SOS_DeInit_test();
	printf("\n\t\t-----------------SOS_createTask_TEST------------\n");
	SOS_createTask_test();
	printf("\n\t\t-----------------SOS_deletTask_TEST-------------\n");
	SOS_deletTask_test();
	printf("\n\t\t-----------------SOS_Dispatcher_TEST-------\n");
	SOS_dispatcher_test();
	printf("\n\n\t=========================ENDED================================\n\n");

}