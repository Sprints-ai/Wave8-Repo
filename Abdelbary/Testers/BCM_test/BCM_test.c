/*
 * BCM_test.c
 *
 * Created: 3/24/2020 4:47:20 PM
 *  Author: mahmo
 */ 
#ifdef GCC

#include "BCM_test.h"

#define POINTER_STATE_TEST 2
#define STATE_IDLE					0
#define STATE_SENDING_BYTE			1
#define STATE_SEN_BYTE_COMPLETE		2
#define STATE_FRAM_SEND_COMLETE		3
#define STATE_FINISED				4

/*for reciver*/
#define STATE_RECIVING_HEAEDER		5
#define STAE_RECIVING_FRAME	        7
#define	STATE_FRAM_RECIVE_COMPLETE	6
#define STATE_ERROR					9
#define STATE_CHEAKING_HEADER       11

uint8_t* au8_txState[] = {"STATE_IDLE","STATE_SENDING_BYTE","STATE_SEN_BYTE_COMPLETE","STATE_FRAM_SEND_COMLETE","STATE_FINISED"};
STATIC uint8_t gu8_testCaseNumber;
extern uint8_t gu8_BCM_moduleInitFlag;
typedef void(*BCM_UserNotifier)(ERROR_STATUS status);
extern bcm_taskControlBlock_t g3astr_BCM_Tasks[BCM_MAX_CHANALS][BCM_MAX_MODES];

extern void BCM_spiSentCBF(void);
void bcm_SenderNotifier(ERROR_STATUS value)
{
	
}
ERROR_STATUS BCM_structPointerParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	gstr_BCM_cfg_t bcm_cfg={BCM_SPI_CHANAL,BCM_SENDER};
	gstr_BCM_cfg_t* pstr_sp_cfg[POINTER_STATE_TEST] = {&bcm_cfg,NULL};
	s16_fun_status = BCM_init(pstr_sp_cfg[s16_paramter] );
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

ERROR_STATUS BCM_chanalParamTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	gstr_BCM_cfg_t bcm_cfg={s16_paramter,BCM_SENDER};
	s16_fun_status =  BCM_init(&bcm_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

ERROR_STATUS BCM_modeParamTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	gstr_BCM_cfg_t bcm_cfg={BCM_SPI_CHANAL,s16_paramter};
	s16_fun_status =  BCM_init(&bcm_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

void BCM_init_normally(void)
{
	gstr_BCM_cfg_t bcm_cfg={BCM_SPI_CHANAL,BCM_SENDER};
	BCM_init(&bcm_cfg);
}

ERROR_STATUS BCM_setupStructPointerParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,bcm_SenderNotifier,ZERO,BCM_SPI_CHANAL,BCM_SENDER};
	gstr_BCM_Task_cfg_t* pstr_sp_cfg[POINTER_STATE_TEST] = {&gstr_BCM_SenderTask_cfg,NULL};
	
	BCM_init_normally();
	s16_fun_status = BCM_setup(pstr_sp_cfg[s16_paramter]);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;

}

ERROR_STATUS BCM_setupBufferParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	uint8_t* pstr_cfg[POINTER_STATE_TEST] = {&buffer,NULL};
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {pstr_cfg[s16_paramter],&lock,bcm_SenderNotifier,ZERO,BCM_SPI_CHANAL,BCM_SENDER};
	gu8_BCM_moduleInitFlag = TRUE;
	//BCM_init_normally();

	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

ERROR_STATUS BCM_setupLockParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	uint8_t* pstr_cfg[POINTER_STATE_TEST] = {&lock,NULL};
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,pstr_cfg[s16_paramter],bcm_SenderNotifier,ZERO,BCM_SPI_CHANAL,BCM_SENDER};
	gu8_BCM_moduleInitFlag = TRUE;
	//BCM_init_normally();
	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}


ERROR_STATUS BCM_CBFParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	BCM_UserNotifier pstr_cfg[POINTER_STATE_TEST] = {bcm_SenderNotifier,NULL};
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,pstr_cfg[s16_paramter],s16_paramter,BCM_SPI_CHANAL,BCM_SENDER};
	gu8_BCM_moduleInitFlag = TRUE;
	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

ERROR_STATUS BCM_setupSizeParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,bcm_SenderNotifier,s16_paramter,BCM_SPI_CHANAL,BCM_SENDER};
	gu8_BCM_moduleInitFlag = TRUE;
	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}
ERROR_STATUS BCM_setupChanalParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,bcm_SenderNotifier,ZERO,s16_paramter,BCM_SENDER};
	gu8_BCM_moduleInitFlag = TRUE;
	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}

ERROR_STATUS BCM_setupModeParamterTest(sint16_t s16_paramter)
{
	sint16_t s16_fun_status;
	uint8_t buffer;
	uint8_t lock;
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,bcm_SenderNotifier,ZERO,BCM_SPI_CHANAL,s16_paramter};
	gu8_BCM_moduleInitFlag = TRUE;
	s16_fun_status = BCM_setup(&gstr_BCM_SenderTask_cfg);
	gu8_BCM_moduleInitFlag = FALSE;
	return s16_fun_status;
}
void BCM_Module_Test()
{

	gu8_testCaseNumber = ZERO;
	printf("\n\n\t=========================SPI_Module_TEST=======================\n\n");
	printf("\n\t\t-----------------BCM_init_TEST-------------\n");
	BCM_init_test();
	printf("\n\t\t-----------------BCM_setup_TEST------------\n");
	BCM_setup_test();
	printf("\n\t\t---------------BCM_RX_dispatcher_TEST-------\n");
	BCM_RX_dispatcher_test();
	printf("\n\t\t---------------BCM_TX_dispatcher_TEST-------\n");
	BCM_TX_dispatcher_test();
	printf("\n\n\t=========================ENDED================================\n\n");
}

void BCM_init_test( )
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;
	
	sint16_t as16_BCM_strPointer [][TEST_PARAMTER_AND_RET_VALUE]	= {{ZERO,OK},{ONE,(BCM_MODULE_ERR+NULL_PTR_ERROR)}};
	sint16_t as16_BCM_Mode		 [][TEST_PARAMTER_AND_RET_VALUE]	= {{BCM_SENDER,OK},{(BCM_RECIVER,OK)}};
	sint16_t as16_BCM_Chanal	 [][TEST_PARAMTER_AND_RET_VALUE]	= {{BCM_SPI_CHANAL,OK},{BCM_UART_CHANAL,OK},{BCM_I2C_CHANAL,OK}};
	
	parameter_test2(as16_BCM_strPointer,2,BCM_structPointerParamterTest,ZERO,ZERO,ZERO,ZERO,FALSE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_Mode,4,BCM_modeParamTest,20,30,2,(BCM_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_Chanal,4,BCM_chanalParamTest,10,15,2,(BCM_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
}
void BCM_setup_test()
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;
	
	sint16_t as16_BCM_strPointer	 [][TEST_PARAMTER_AND_RET_VALUE]	= {{ZERO,OK},{ONE,(BCM_MODULE_ERR+NULL_PTR_ERROR)}};
	sint16_t as16_BCM_BufferPointer  [][TEST_PARAMTER_AND_RET_VALUE]	= {{ZERO,OK},{ONE,(BCM_MODULE_ERR+NULL_PTR_ERROR)}};
	sint16_t as16_BCM_LockPointer    [][TEST_PARAMTER_AND_RET_VALUE]    = {{ZERO,OK},{ONE,(BCM_MODULE_ERR+NULL_PTR_ERROR)}};
	sint16_t as16_BCM_CBFPointer     [][TEST_PARAMTER_AND_RET_VALUE]    = {{ZERO,OK},{ONE,(BCM_MODULE_ERR+NULL_PTR_ERROR)}};
	sint16_t as16_BCM_BufferSize	 [][TEST_PARAMTER_AND_RET_VALUE]	= {{10,OK},{(20,OK)}};
	sint16_t as16_BCM_Mode	    	 [][TEST_PARAMTER_AND_RET_VALUE]	= {{BCM_SENDER,OK},{(BCM_RECIVER,OK)}};
	sint16_t as16_BCM_Chanal	     [][TEST_PARAMTER_AND_RET_VALUE]	= {{BCM_SPI_CHANAL,OK},{BCM_UART_CHANAL,OK},{BCM_I2C_CHANAL,OK}};
	
	
	parameter_test2(as16_BCM_strPointer,2,BCM_setupStructPointerParamterTest,ZERO,ZERO,ZERO,ZERO,FALSE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_BufferPointer,2,BCM_setupBufferParamterTest,ZERO,ZERO,ZERO,ZERO,FALSE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_LockPointer,2,BCM_setupLockParamterTest,ZERO,ZERO,ZERO,ZERO,FALSE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_CBFPointer,2,BCM_CBFParamterTest,ZERO,ZERO,ZERO,ZERO,FALSE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_BufferSize,2,BCM_setupSizeParamterTest,100,200,50,(BCM_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_Mode,2,BCM_setupModeParamterTest,5,9,2,(BCM_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(as16_BCM_Chanal,2,BCM_setupChanalParamterTest,5,9,2,(BCM_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	//gstr_BCM_Task_cfg_t 
	
	//BCM_setup()
}
void BCM_RX_dispatcher_test(void)
{
	
}
void BCM_TX_dispatcher_test(void)
{
	BCM_init_normally();
	uint8_t buffer;
	uint8_t lock;
	gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {&buffer,&lock,bcm_SenderNotifier,10,BCM_SPI_CHANAL,BCM_SENDER};
	BCM_setup(&gstr_BCM_SenderTask_cfg);
	uint8_t curretnState = STATE_IDLE;

	for (int i = 0 ; i <50 ; i++)
	{
		uint8_t x =  g3astr_BCM_Tasks[BCM_SPI_CHANAL][BCM_SENDER].u8_taskStatus;
		printf("%s\n",au8_txState[x]);
		BCM_TX_dispatcher();
		if (g3astr_BCM_Tasks[BCM_SPI_CHANAL][BCM_SENDER].u8_taskStatus == STATE_SENDING_BYTE)
		{
			BCM_spiSentCBF();
		}
		//BCM_spiSentCBF();
	}
}


#endif