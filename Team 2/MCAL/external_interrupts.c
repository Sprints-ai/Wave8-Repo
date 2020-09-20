/*
 ============================================================================
 Name        : interrupt.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */
#include "external_interrupts.h"

#define NULL_Ptr ((void*)0)
#define CLEAR 0
#define ONE 1


volatile uint8_t g8_state;
volatile uint8_t g8_interrupt_zero_flag=CLEAR;
volatile uint8_t g8_echo_flag=CLEAR;

/************************INT0*****************************************/
ERROR_STATUS INT0_Init(EN_Edge_t en_edge_selection)
{
	uint8_t u8_status;

	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (ONE<<INT0);                 /* Enable external interrupt pin INT0*/
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOD,
			DIO_stru_init.pins=BIT2,
			DIO_stru_init.dir=INPUT,
	};
	u8_status |= DIO_init (&DIO_stru_init);
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
		MCUCR &= ~(ONE<<ISC00) & ~(ONE<<ISC01);		/* Trigger INT0 with the low level*/
		u8_status |= E_ok;
		break;

	case ANY_CHANGE:
		MCUCR |= (ONE<<ISC10);  					 /* Trigger INT0 with the any change*/
		u8_status |= E_ok;
		break;

	case FALLING_EDGE:
		MCUCR |= (ONE<<ISC00);  					 /* Trigger INT0 with the falling edge*/
		u8_status |= E_ok;
		break;

	case RISIGING_EDGE:
		MCUCR |= (ONE<<ISC00) | (ONE<<ISC01);  		 /* Trigger INT0 with the raising edge*/
		u8_status |= E_ok;
		break;

	default:
		u8_status |= E_NOk;
		break;
	}
	sei();                             			 /*Enable interrupts by setting I-bit*/

	if(u8_status == E_ok)
	{
		u8_status=E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}


ERROR_STATUS INT0_DeInit(void)
{
	uint8_t u8_status;
	cli();                             			 /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(ONE<<INT0);                		 /* Disable external interrupt pin INT0*/
	MCUCR &= ~(ONE<<ISC00) & ~(ONE<<ISC01);
	u8_status |= E_ok;
	return u8_status;
}

/****************************INT1*******************************************/
ERROR_STATUS INT1_Init(EN_Edge_t en_edge_selection)
{
	uint8_t u8_status;
cli();                            		 	 /*Disable interrupts by clearing I-bit*/
	GICR  |= (ONE<<INT1);                 	/* Enable external interrupt pin INT1*/
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOD,
			DIO_stru_init.pins=BIT3,
			DIO_stru_init.dir=INPUT,
	};
	u8_status |= DIO_init (&DIO_stru_init);
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
		MCUCR &= ~(ONE<<ISC10) & ~(ONE<<ISC11);	 /* Trigger INT0 with the low level*/
		u8_status |= E_ok;
		break;

	case ANY_CHANGE:
		MCUCR |= (ONE<<ISC10);                /* Trigger INT0 with the any change*/
		u8_status |= E_ok;
		break;

	case FALLING_EDGE:
		MCUCR |= (ONE<<ISC11);                /* Trigger INT0 with the falling edge*/
		u8_status |= E_ok;
		break;

	case RISIGING_EDGE:
		MCUCR |= (ONE<<ISC10) | (ONE<<ISC11);   /* Trigger INT0 with the raising edge*/
		u8_status |= E_ok;
		break;

	default:
		u8_status |= E_NOk;
		break;
	}
	sei();                              /*Enable interrupts by setting I-bit*/

	if(u8_status == E_ok)
	{
		u8_status = E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}

ERROR_STATUS INT1_DeInit(void)
{
	uint8_t u8_status;
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(ONE<<INT1);                 /* Disable external interrupt pin INT0*/
	MCUCR &= ~(ONE<<ISC10) & ~(ONE<<ISC11);
	u8_status |= E_ok;
	return u8_status;
}

/****************************INT2*******************************************/
ERROR_STATUS INT2_Init(EN_Edge_t en_edge_selection)
{
	uint8_t u8_status;
	cli();                              /*Disable interrupts by clearing I-bit*/
	GICR  |= (ONE<<INT2);                 /* Enable external interrupt pin INT1*/
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOB,
			DIO_stru_init.pins=BIT2,
			DIO_stru_init.dir=INPUT,
	};
	u8_status |= DIO_init (&DIO_stru_init);
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
										/*this case is not exist*/
		u8_status |= E_NOk;
		break;

	case ANY_CHANGE:
										/*this case is not exist*/
		u8_status |= E_NOk;
		break;

	case FALLING_EDGE:
		MCUCSR &= ~(ONE<<ISC2);            /*nothing to do*/
		u8_status |= E_ok;
		break;

	case RISIGING_EDGE:
		MCUCSR |= (ONE<<ISC2);            /* Trigger INT0 with the raising edge*/
		u8_status|= E_ok;
		break;

	default:
		u8_status |= E_NOk;
		break;
	}
	sei();                              /*Enable interrupts by setting I-bit*/

	if(u8_status == E_ok)
	{
		u8_status=E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}

	return u8_status;
}

ERROR_STATUS INT2_DeInit(void)
{
	uint8_t u8_status;
	cli();                               /*Disable interrupts by clearing I-bit*/
	GICR  &= ~(ONE<<INT2);                 /* Disable external interrupt pin INT0*/
	MCUCSR &= ~(ONE<<ISC2);
	u8_status |= E_ok;
	return u8_status;
}

ERROR_STATUS INT2_SetEdge(EN_Edge_t en_edge_selection)
{
	uint8_t u8_status;
	/*I have to check first if it is enabled or not*/
	switch(en_edge_selection)
	{
	case LOW_LEVEL:
		                                /*this case is not exist*/
		break;

	case ANY_CHANGE:
		                                /*this case is not exist*/
		break;

	case FALLING_EDGE:
		MCUCSR &= ~(ONE<<ISC2);
		break;

	case RISIGING_EDGE:
		MCUCSR |= (ONE<<ISC2);            /* Trigger INT0 with the raising edge*/
		break;

	default:
		u8_status |= E_NOk;
		break;
	}

	if(u8_status == E_ok)
	{
		u8_status=E_ok;
	}
	else
	{
		u8_status = E_NOk;
	}
	return u8_status;
}
/***************************************************************************/


/********************************ISRS***************************************/

ISR(INT2_vect)
{
	if(g_callBackPtr != NULL_Ptr)
	{
		// Call the Call Back function in the application after the edge is detected
		(*g_callBackPtr)(); // another method to call the function using pointer to function g_callBackPtr();
	}

}

/******************************************************************************/
