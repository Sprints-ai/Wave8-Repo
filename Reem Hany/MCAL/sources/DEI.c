/*
 * DEI.c
 *
 * Created: 2/18/2020 11:37:24 PM
 *  Author: Reem
 */ 
#include "../includes/DEI.h"
#include "../includes/DEI_Cfg.h"

/***************************************************/
/*           Static Globals                        */
/***************************************************/
static volatile void (*gptr_DEI_INT2_CBK)(void)=NULL;

/***************************************************/
/*                  ISRs                           */
/***************************************************/
_ISR__(INT2_vect)
{
	if(gptr_DEI_INT2_CBK !=NULL)
	gptr_DEI_INT2_CBK();
}

/***************************************************/
/*           Function implementation               */
/***************************************************/

/*
 * Fun----------: ERROR_STATUS DEI_Init(uint8_t DEI_Ch);
 * Input--------: digital external interrupt channel
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: initializes the DEI_Channel 
*/
ERROR_STATUS DEI_Init(uint8_t DEI_Channel)
{
	ERROR_STATUS ERR;
	switch (DEI_Channel)
	{
		case _DEI_INT0:
		SET_BIT(GICR, GICR_INT0_BIT);
		ERR = E_OK;
		break;
		
		case _DEI_INT1:
		SET_BIT(GICR, GICR_INT1_BIT);
		ERR = E_OK;
		break;
		
		case _DEI_INT2:
		GICR	 |=0X20;
		
		gptr_DEI_INT2_CBK = NULL;
		ERR = E_OK;
		break;
		
		default:
		ERR = E_INVALID_PARAMETER;
		break;
	}
	return ERR;
}

/*
 * Fun----------: ERROR_STATUS DEI_Init(uint8_t DEI_Ch);
 * Input--------: digital external interrupt channel,DEI MODE, Call back function
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: assign the DEI mode and DEI call back function
*/
ERROR_STATUS DEI_setMode(uint8_t DEI_Channel,uint8_t DEI_Mode,void (*DEI_CBK)(void))
{
	ERROR_STATUS ERR;
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
				SET_BIT(MCUCSR,MCUCSR_INT2_BIT);
				ERR = E_OK;
				break;
				
				case DEI_MODE_FALLING:
				CLR_BIT(MCUCSR,MCUCSR_INT2_BIT);
				ERR = E_OK;
				break;
				
				default:
				ERR = E_INVALID_PARAMETER;
				break;
			}
			if (ERR == E_OK)
			{
				gptr_DEI_INT2_CBK = DEI_CBK;
				EN_GLOBAL_INT;
			}
			break;
			
			default:
			ERR = E_INVALID_PARAMETER;
			break;
		}
	}
	
	return ERR;
}



