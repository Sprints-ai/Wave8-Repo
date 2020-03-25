/*
 * SPI_test.c
 *
 * Created: 3/24/2020 10:58:25 PM
 *  Author: mahmo
 */ 

#ifdef GCC

#include "SPI_test.h"
STATIC uint8_t gu8_testCaseNumber;


ERROR_STATUS spi_modeParamTest(sint16_t s16_paramter)
{
		gstrSPI_spi_satus_t gstr_sp_cfg;
		gstr_sp_cfg.spi_mod			 = s16_paramter;
		gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
		gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
		gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
		gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
		gstr_sp_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
		return SPI_init(&gstr_sp_cfg);
}
ERROR_STATUS spi_oprationModParamTest(sint16_t s16_paramter)
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod			 = SPI_MASTER_MOD;
	gstr_sp_cfg.spi_opration_mod	 = s16_paramter;
	gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	gstr_sp_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
	return SPI_init(&gstr_sp_cfg);
}
ERROR_STATUS spi_PrescalerParamterTest(sint16_t s16_paramter)
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod			 = SPI_MASTER_MOD;
	gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
	gstr_sp_cfg.spi_prescaler		 = s16_paramter;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	gstr_sp_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
	return SPI_init(&gstr_sp_cfg);
}

ERROR_STATUS spi_speedParamterTest(sint16_t s16_paramter)
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod			 = s16_paramter;
	gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
	gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	gstr_sp_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
	return SPI_init(&gstr_sp_cfg);
}

ERROR_STATUS spi_SamplingModeTest(sint16_t s16_paramter)
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod			 = SPI_MASTER_MOD;
	gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
	gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = s16_paramter;
	gstr_sp_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
	return SPI_init(&gstr_sp_cfg);
}

ERROR_STATUS spi_dataOrderParamterTest(sint16_t s16_paramter)
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod			 = SPI_MASTER_MOD;
	gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
	gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	gstr_sp_cfg.spi_data_order	 = s16_paramter;
	return SPI_init(&gstr_sp_cfg);
}

STATIC ERROR_STATUS SPI_initNorm()
{
	gstrSPI_spi_satus_t gstr_sp_cfg;
	gstr_sp_cfg.spi_mod				 = SPI_MASTER_MOD;
	gstr_sp_cfg.spi_opration_mod	 = SPI_INT_MOD;
	gstr_sp_cfg.spi_prescaler		 = SPI_PRESCALER_128;
	gstr_sp_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
	gstr_sp_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	gstr_sp_cfg.spi_data_order		 = SPI_DATA_ORDER_LSB;
	return SPI_init(&gstr_sp_cfg);
	
}

void SPI_init_test()
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return = OK;
	
	sint16_t au8_SPI_Mode [][TEST_PARAMTER_AND_RET_VALUE]			= {{SPI_SLAVE_MOD,OK},{(SPI_MASTER_MOD,OK)},{0x03,(SPI_MODULE_ERR+INVALAD_PARAMETER)},{0x04,(SPI_MODULE_ERR+INVALAD_PARAMETER)}};
	sint16_t au8_SPI_operationMode [][TEST_PARAMTER_AND_RET_VALUE]	= {{SPI_INT_MOD,OK},{SPI_NORMAL_MOD,OK},{0x05,(SPI_MODULE_ERR+INVALAD_PARAMETER)},{0x01,(SPI_MODULE_ERR+INVALAD_PARAMETER)}};
	sint16_t au8_SPI_prescaler [][TEST_PARAMTER_AND_RET_VALUE]		= {{SPI_PRESCALER_4,OK},{SPI_PRESCALER_16,OK},{SPI_PRESCALER_64,OK},{SPI_PRESCALER_128,OK}};
	sint16_t au8_SPI_speed [][TEST_PARAMTER_AND_RET_VALUE]			= {{SPI_NORMAL_SPEED,OK},{SPI_DOBULE_SPEED,OK}};
	sint16_t au8_SPI_sampling [][TEST_PARAMTER_AND_RET_VALUE]		= {{SPI_SAMPLING_MOD_0,OK},{SPI_SAMPLING_MOD_1,OK},{SPI_SAMPLING_MOD_2,OK},{SPI_SAMPLING_MOD_3,OK}};
	sint16_t au8_SPI_dataOrder [][TEST_PARAMTER_AND_RET_VALUE]		= {{SPI_DATA_ORDER_LSB,OK},{SPI_DATA_ORDER_MSB,OK}}; 
	
	parameter_test2(au8_SPI_Mode,4,spi_modeParamTest,20,30,2,(SPI_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(au8_SPI_Mode,4,spi_oprationModParamTest,10,15,2,(SPI_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(au8_SPI_Mode,4,spi_speedParamterTest,5,10,5,(SPI_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(au8_SPI_Mode,4,spi_SamplingModeTest,20,30,2,(SPI_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);
	parameter_test2(au8_SPI_Mode,4,spi_dataOrderParamterTest,3,7,2,(SPI_MODULE_ERR+INVALAD_PARAMETER),TRUE,&gu8_testCaseNumber);

}
void spi_enable_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return;
	
	/*enable with init normal mode*/
	SPI_initNorm();
	s16_fun_return = spi_enable();
	s16_expected_return = OK;
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	spi_Deinit();
	
	/*enable without initalize*/
	s16_fun_return = spi_enable();
	s16_expected_return = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	
}
void SPI_sendData_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return;
		
	/*send with init normal mode*/
	SPI_initNorm();
	spi_enable();
	s16_fun_return = SPI_sendData(ONE);
	s16_expected_return = OK;
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	spi_Deinit();
		
	/*send without initalize*/
	s16_fun_return = SPI_sendData(ONE);
	s16_expected_return = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	
	/*send without enable*/
	SPI_initNorm();
	spi_enable();
	s16_fun_return = SPI_sendData(ONE);
	s16_expected_return =  (SPI_MODULE_ERR+MODULE_NOT_EN);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	spi_Deinit();
}

void SPI_getData_test(void)
{
	sint16_t s16_fun_return;
	sint16_t s16_expected_return;
	uint8_t	 u8_data;
	/*send with init normal mode*/
	SPI_initNorm();
	spi_enable();
	s16_fun_return = SPI_getData(&u8_data);
	s16_expected_return = OK;
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	spi_Deinit();
	
	/*send without initalize*/
	s16_fun_return = SPI_getData(&u8_data);
	s16_expected_return = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	
	/*send without enable*/
	SPI_initNorm();
	spi_enable();
	s16_fun_return = SPI_getData(&u8_data);
	s16_expected_return =  (SPI_MODULE_ERR+MODULE_NOT_EN);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	spi_Deinit();
}

void SPI_Deinit_test(void)
{
	/*init then deinit*/
	sint16_t s16_fun_return;
	sint16_t s16_expected_return;
	uint8_t	 u8_data;
	/*init then deinit*/
	SPI_initNorm();
	spi_enable();
	s16_fun_return = spi_Deinit();
	s16_expected_return = OK;
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);
	
	/*deinit without init*/
	s16_fun_return = spi_Deinit();
	s16_expected_return = (SPI_MODULE_ERR+MODULE_NOT_INITALIZED);
	checkTestCase(s16_expected_return , s16_fun_return,&gu8_testCaseNumber);

}

void SPI_Module_Test()
{
	gu8_testCaseNumber = ZERO;
	printf("\n\n\t=========================SPI_Module_TEST=======================\n\n");
	printf("\n\t\t-----------------SPI_Init_TEST-------------\n");
	SPI_init_test();
	printf("\n\t\t-----------------SPI_DeInit_TEST-----------\n");
	SPI_Deinit_test();
	printf("\n\t\t-----------------SPI_Enable_TEST-----------\n");
	spi_enable_test();
	printf("\n\t\t-----------------SPI_sendData_TEST---------\n");
	SPI_sendData_test();
	printf("\n\t\t-----------------SPI_getData_TEST----------\n");
	SPI_getData_test();
	printf("\n\n\t=========================ENDED================================\n\n");
}


#endif