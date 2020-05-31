/************************************************************************************************************************/
/******************** vedio link: https://drive.google.com/open?id=1YXdfyEE5xQ4vB4Dgye2VWZwWltReiQ2H ********************/
/************************************************************************************************************************/

#include "SYSTEM_PERIPHERAL/SYSTEM_CONTROL/SYSCTR.h"
#include "SYSTEM_PERIPHERAL/PortDriver/PortDriver.h"
#include "SYSTEM_PERIPHERAL/DIO/Dio.h"
#include "SYSTEM_PERIPHERAL/ADC/ADC.h"

#define DISTANCE_INITIAL_VALUE      0x00u
#define MAX_DISTANCE                ((int16_t)0x05)
#define MAX_RANGE                   ((uint16_t)0xFFFu)
int main (void)
{
	Adc_ValueGroupType DataBuffer; /*ADC conversion data buffer*/
	
	uint16_t  au8_Distance = DISTANCE_INITIAL_VALUE;
	
	SysCtr_init(); /*init system colck control (GPIOE and ADC)*/
	
	PortDriver_init(); /*init Port driver (O/P DIO E4,E5 and I/P ADC E2)*/
	
	Adc_Init(&ADC_Cfg); /*init ADC module*/
	
	Adc_SetupResultBuffer(ADC_SEQUENCER_3_MODULE0, &DataBuffer); /*setup Conversion Data Buffer*/
	
	while(1)
	{
		  Adc_StartGroupConversion(ADC_SEQUENCER_3_MODULE0); /*Start ADC Conversion*/
		  
		  if (ADC_COMPLETED == (Adc_GetGroupStatus(ADC_SEQUENCER_3_MODULE0))) /*Check Convesrion Complete Flag*/
		  {
		  	  Adc_ReadGroup(ADC_SEQUENCER_3_MODULE0, &DataBuffer); /*Read Conversion Data*/
		  	  Adc_StopGroupConversion(ADC_SEQUENCER_3_MODULE0); /*Stop ADC Conversion*/
		  }
		  
			au8_Distance = (DataBuffer * MAX_DISTANCE) / MAX_RANGE ;
		  
			if (0 == au8_Distance)
			{
				DIO_Write(PORTDRIVER_CHANNEL_E4, STD_LOW);
				DIO_Write(PORTDRIVER_CHANNEL_E5, STD_LOW);
			}
			else if (1 == au8_Distance)
	    {
	    	DIO_Write(PORTDRIVER_CHANNEL_E4, STD_HIGH);
     	  DIO_Write(PORTDRIVER_CHANNEL_E5, STD_LOW);
      }
			else if (2 == au8_Distance)
			{
		 	  DIO_Write(PORTDRIVER_CHANNEL_E4, STD_LOW);
        DIO_Write(PORTDRIVER_CHANNEL_E5, STD_HIGH);
      }
			else if (3 == au8_Distance)
      {
      	DIO_Write(PORTDRIVER_CHANNEL_E4, STD_HIGH);
        DIO_Write(PORTDRIVER_CHANNEL_E5, STD_HIGH);
      }
			else
			{
				DIO_Write(PORTDRIVER_CHANNEL_E4, STD_LOW);
				DIO_Write(PORTDRIVER_CHANNEL_E5, STD_LOW);
			}
		}
}
