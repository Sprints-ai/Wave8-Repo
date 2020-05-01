/*
 * ADC_Driver.c
 *
 * Created: 4/27/2020 12:40:55 AM
 * Author : A_ayman
 */ 


/*
*** Inclusions
*/
#include "MCAL/PORT/PortDriver.h"
#include "HAL/ADC/ADC.h"
#include "SYS_CLK/SysCtr.h"
#include "MCAL/DIO/Dio.h"

/*
***Local Macros
*/

//potentiometer Voltage Range
#define RANGE1  0
#define RANGE2  0.660
#define RANGE3  1.32
#define RANGE4  1.98
#define RANGE5  2.64
#define RANGE6  3.3

int main(void)
{
	SysCtr_init();
	PortDriver_init ();
	ADC_Init();
	uint32_t u32_ADC_Digital_Value;
   float Voltage_Value;
    /* Replace with your application code */
    while (1) 
    {
			  ADC_Start_Conversion(ADC_INDEX0,&u32_ADC_Digital_Value);
			  ADC_Get_Voltage_Reading(ADC_INDEX0,&Voltage_Value);
				
				if (Voltage_Value > RANGE1 && Voltage_Value <= RANGE2)
				{
					DIO_Write(PORTDRIVER_CHANNEL_B4 ,STD_LOW);
					DIO_Write(PORTDRIVER_CHANNEL_B5 ,STD_LOW);
				}
				else if (Voltage_Value > RANGE2 && Voltage_Value <= RANGE3)
				{
					DIO_Write(PORTDRIVER_CHANNEL_B4 ,STD_LOW);
					DIO_Write(PORTDRIVER_CHANNEL_B5 ,STD_HIGH);
				}
				else if (Voltage_Value > RANGE3 && Voltage_Value <= RANGE4)
				{
					DIO_Write(PORTDRIVER_CHANNEL_B4 ,STD_HIGH);
					DIO_Write(PORTDRIVER_CHANNEL_B5 ,LOW);
				}
				else if (Voltage_Value > RANGE4 && Voltage_Value <= RANGE6)
				{
					DIO_Write(PORTDRIVER_CHANNEL_B4 ,STD_HIGH);
					DIO_Write(PORTDRIVER_CHANNEL_B5 ,STD_HIGH);
				}
    }
}

