/*
 * External_INT.c
 *
 * Created: 2/18/2020 12:40:58 PM
 *  Author: Ema
 */ 

#include "External_INT.h"
#include "../Services/BITMATH.h"
#include "interrupt.h"

void (*Ex_INT_CBK_FN[3])(void)={NULL,NULL,NULL};

void External_INT_Init(uint8_t INT_CH,uint8_t EDGE,void(*CBK_FN)(void))
{
	ENABLE_GINT;								 // Enable interrupts by setting I-bit

	switch(INT_CH)
	{
		case EXTERNAL_INT_CH0:
		break;
		case EXTERNAL_INT_CH1:
		break;
		case EXTERNAL_INT_CH2:
		{
			DIO_Cfg_t DIO_cfg_PB2 = {GPIOB,BIT2,INPUT};
			DIO_init(&DIO_cfg_PB2);
			DIO_Write(GPIOB,BIT2,HIGH);
			
			switch(EDGE)
			{
				case EdgeRisiging:
				SET_BIT(MCUCSR,6);			         // Trigger INT2 with the raising edge
				break;

				case EdgeFalling:
				CLR_BIT(MCUCSR,6);				 // Trigger INT2 with the falling edge
				break;
				
				default:
				break;
			}
			
			Ex_INT_CBK_FN[2]=CBK_FN;
		}
		break;
		default:
		break;
	}

}


void External_INT_Enable(uint8_t INT_CH,uint8_t EDGE)
{
	switch(INT_CH)
	{
		case EXTERNAL_INT_CH0:
		break;
		case EXTERNAL_INT_CH1:
		break;
		case EXTERNAL_INT_CH2:
		{
			switch(EDGE)
			{
				case EdgeRisiging:
				SET_BIT(GICR,5);					 // Enable external interrupt pin INT2
				SET_BIT(MCUCSR,6);			         // Trigger INT2 with the raising edge
				break;

				case EdgeFalling:
				SET_BIT(GICR,5);					 // Enable external interrupt pin INT2
				CLR_BIT(MCUCSR,6);				 // Trigger INT2 with the falling edge
				break;
				
				default:
				break;
			}
		}
		break;
		default:
		break;
	}

}


InterruptServiceRoutine(INT2_vect)
{
	if (Ex_INT_CBK_FN[2] != NULL)
	{
		Ex_INT_CBK_FN[2]();
	}
}