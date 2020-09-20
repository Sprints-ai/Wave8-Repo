/*
 * DIO_TEST.c
 *
 * Created: 2/17/2020 4:14:39 PM
 *  Author: Hazem
 */ 

#include "car_sm.h"
#include "..\servicelayer\SOS.h"
#include "..\ECUAL\LCD.h"


#ifndef GCC
void sys_init(void);
int main(void)
{ 
sys_init();

SOS_Start_Timer(40,Car_SM_Update,PERIODIC,2);
SOS_Start_Timer(40,Us_mainfunc,PERIODIC,1);
SOS_Start_Timer(500,LCD_Mainfunc,PERIODIC,3);
	while(1)
  {
	
	 SOS_Dispatch(); 
	 
/*
	Car_SM_Update();
   softwareDelayMs(100);*/
}

}

void sys_init(void)
{
	LCD_init();
	Car_SM_Init();
	SOS_Init(&gstr_OSCONFIG);
	
}

#endif
#ifdef GCC


#include "../Testers/Tester/tester.h"


ERROR_STATUS dummy(sint16_t x)
{
	return E_OK;
}
ERROR_STATUS dummy2(sint16_t x)
{
	return -102;
}
int main(void)
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
	#elif CAR_SM_TEST
	car_sm_test();
	#elif DUMMY_TEST
	uint8_t* u8_testFilePath = "C:/Users/hazem/Downloads/Car_static_arch-FirstDelviry/Testers/Tester/tests.txt";
	gstr_testFunPtr_t gstr_testFunPtr[] = {{"dummy",dummy},{"dummy2",dummy2}};
	uint8_t u8_counter = ZERO;
	testModule(u8_testFilePath,gstr_testFunPtr,2,&u8_counter);
	#endif
	return 0;
}
#endif