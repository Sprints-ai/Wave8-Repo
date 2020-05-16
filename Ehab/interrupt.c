/*
 * interrupt.c
 *
 * Created: 1/29/2020 7:02:09 PM
 *  Author: ahmed
 */ 


#include "interrupt.h"

void (*EXTI_CBK[3])(void) = {NULL,NULL,NULL};

void EXTI_Init(uint8_t u8_INTNo , uint8_t u8_sense , void(*CBK_FN)(void))
{
	GICR |= u8_INTNo;
	
	switch (u8_INTNo)
	{
		case INT0:
		{
			//PORTD_DIR |= 0x04;
			switch(u8_sense)
			{
				case INT0_LOW_LEVEL:
				MCUCR &= !(INT0_RISING_EDGE);
				break;
				
				default:
				MCUCR |= u8_sense;
				break;
			}
			EXTI_CBK[0] = CBK_FN;
		}
		break;
		
		case INT1:
		{
			//PORTD_DIR &= ~0x08;
			switch(u8_sense)
			{
				case INT1_LOW_LEVEL:
				MCUCR &= !(INT1_RISING_EDGE);
				break;
				
				default:
				MCUCR|=u8_sense;
			}
			EXTI_CBK[1] = CBK_FN;
			
		}
		break;
		
		case INT2:
		{
			//PORTB_DIR &= ~0x04;
			switch(u8_sense)
			{
				case INT2_FALLING_EDGE:
				MCUCSR &= !(INT2_RISING_EDGE);
				break;
				
				case INT2_RISING_EDGE:
				MCUCSR |= INT2_RISING_EDGE;
				break;
			}
			EXTI_CBK[2] = CBK_FN;
		}
		break;
	}
}

InterruptServiceRoutine(INT0_vect)
{
	if (EXTI_CBK[0] != NULL)
	{
		EXTI_CBK[0]();
	}
		UDR = 1;
}

InterruptServiceRoutine(INT1_vect)
{
	if (EXTI_CBK[1] != NULL)
	{
		EXTI_CBK[1]();
	}

}

InterruptServiceRoutine(INT2_vect)
{	
	if (EXTI_CBK[2] != NULL)
	{
		EXTI_CBK[2]();
	}
}