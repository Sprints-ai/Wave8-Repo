/*****************************************************************************/
/*					SysCtr_Lcfg.c												 */	
/*****************************************************************************/
#include "SysCtr_Cfg.h"
#include "SysCtr_Lcfg.h"
#include "SysCtr_Types.h"
#include "../std_types.h"

// Clock Gates Control //
/*
SysCtr_Cfg_t SysCtr_EnableCfgArr[NUM_OF_PRIPHERALS] =
{
//   SystemControl_ClkGateFunction_t ,   SystemControl_ClkGateModuleID_t	//
{	General_Purpose_Timer_32_Bit	  ,	General_Purpose_Timer_32_Bit_Timer0	},
{	General_Purpose_Input_Output	  ,	General_Purpose_Input_Output_PORT_A },
{	General_Purpose_Input_Output	  ,	General_Purpose_Input_Output_PORT_B }

};*/


uint8_t SysCtr_EnableArr[NUM_OF_PRIPHERALS] =
{
//Inter_Integrated_Circuit_I2C_0,
	//General_Purpose_Timer_32_Bit_Timer0,
	General_Purpose_Input_Output_PORT_A	,	
  Analog_to_Digital_Converter_ADC_0	,
	General_Purpose_Input_Output_PORT_D,
	General_Purpose_Input_Output_PORT_E

};

/*#include <stdio.h>
void main (){
	printf("%d \n %d",(General_Purpose_Input_Output_PORT_A/0x10),General_Purpose_Input_Output_PORT_A%16);
}*/
