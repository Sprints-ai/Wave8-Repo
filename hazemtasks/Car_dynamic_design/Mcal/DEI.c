/*
 * DEI.c
 *
 * Created: 2/18/2020 11:37:24 PM
 *  Author: Reem
 */ 
#include "DEI.h"
#include "DEI_Cfg.h"

/***************************************************/
/*           Static Globals                        */
/***************************************************/
static volatile void (*gptr_DEI_INT2_CBK)(void)=NULL;

/***************************************************/
/*                  ISRs                           */
/***************************************************/
ISR(INT2_vect)
{
	if(gptr_DEI_INT2_CBK !=NULL)
	gptr_DEI_INT2_CBK();
}

/***************************************************/
/*           Function implementation               */
/***************************************************/
ERROR_STATUS DEI_Init(uint8_t DEI_Channel)
{
	ERROR_STATUS ERR;
	switch (DEI_Channel)
	{
		case _DEI_INT0:
		//SET_BIT(GICR, GICR_INT0_BIT);
		ERR = E_OK;
		break;
		
		case _DEI_INT1:
		//SET_BIT(GICR, GICR_INT1_BIT);
		ERR = E_OK;
		break;
		case _DEI_INT2:
		Set_BIT(GICR,INT2);
		sei();
		gptr_DEI_INT2_CBK = NULL;
		ERR = E_OK;
		break;
		
		default:
		break;
	}
	return ERR;
}
ERROR_STATUS DEI_setMode(uint8_t DEI_Channel,uint8_t DEI_Mode,volatile void (*DEI_CBK)(void))
{
	ERROR_STATUS ERR=E_OK;
	if (DEI_CBK == NULL)
	{
		ERR = E_NULL_PTR;
	}
	else
	{
		switch (DEI_Channel)
		{
			/*case _DEI_INT0:
			ERR = E_OK;
			break;
			
			case _DEI_INT1:
			ERR = E_OK;
			break;*/
			case _DEI_INT2:
			switch(DEI_Mode)
			{
				case DEI_MODE_RISING:
                Set_BIT(MCUCSR,ISC2);
				ERR = E_OK;
				break;	
				case DEI_MODE_FALLING:
			    Clear_BIT(MCUCSR,ISC2);
				ERR = E_OK;
				break;
				default:
				break;
			}
			if (ERR == E_OK)
			{
				gptr_DEI_INT2_CBK = DEI_CBK;
				
			}
			break;			
			default:
			
			break;
		}
	}
	
	return ERR;
}



