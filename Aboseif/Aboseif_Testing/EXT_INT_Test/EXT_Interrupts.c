/*
 * EXT_Interrupts.c
 *
 * Created: 2020-02-18 1:40:28 PM
 *  Author: EbrahimOseif
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/


#include "EXT_Interrupts.h"


/************************************************************************/
/*		         TIMER FUNCTIONS' implementation	                    */
/************************************************************************/


/**
 * Input:  
 * 	EXT_INT_EDGE: The edge that will trigger the EXT INT.
								-EXT_INT2_FALLING_EDGE
								-EXT_INT2_RISING_EDGE
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function set the trigger edge.
 * 							
 */

ERROR_STATUS EXT_INT_SetEdge(uint8_t EXT_INT_EDGE){
	
	ERROR_STATUS u8_status = E_OK;
	
	if (EXT_INT2_RISING_EDGE == EXT_INT_EDGE) /* use IS_EQUAL(X,Y) ((X)==(Y)) */
	{
				MCUCSR |= EXT_INT2_EDGE;

	}else if (EXT_INT2_FALLING_EDGE == EXT_INT_EDGE){
				
				MCUCSR &= ~ EXT_INT2_EDGE;
	}else
			u8_status = E_NOK;
	

	/*switch(EXT_INT_EDGE){
		
		/ *case EXT_INT_EDGE_MODE0:
		case EXT_INT_EDGE_MODE1:
		case EXT_INT_EDGE_MODE2:
		case EXT_INT_EDGE_MODE3:
					MCUCR |= EXT_INT_EDGE;
					break;* /
		case EXT_INT2_RISING_EDGE:
					MCUCSR |= EXT_INT2_RISING_EDGE;
					break;
		case EXT_INT2_FALLING_EDGE:
					MCUCSR &= (EXT_INT2_FALLING_EDGE);
					break;
					
		default:
				status = E_NOK;*/
	//}
	return u8_status;
}

/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output:					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function enables EXT INT channel.
 * 							
 */

ERROR_STATUS EXT_INT_Enable(uint8_t EXT_INT_CH){

		ERROR_STATUS u8_status = E_OK;

          switch(EXT_INT_CH){
          	
          	case EXT_INT0:
          		GICR |= EXT_INT0_EN;
          		break;
          	
          	case EXT_INT1:
          		GICR |= EXT_INT1_EN;
          		break;
          	
          	case EXT_INT2:
          		GICR |= EXT_INT2_EN;
				   struct DIO_Cfg_s int2_pin =
				   {
					   GPIOB,
					   BIT2,
					   INPUT
				   };
				  // PORTB_DIR &= ~(1<<2);

				DIO_init(&int2_pin);         	
				break;
          	
          	default:
          			u8_status = E_NOK;
           }
		   
		   	SREG |= (GLOBAL_INT_EN);
	
	return u8_status;
}

/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output:					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function disables EXT INT channel.
 * 							
 */
ERROR_STATUS EXT_INT_Disable(uint8_t EXT_INT_CH){

	ERROR_STATUS u8_status = E_OK;

	switch(EXT_INT_CH){
		
		case EXT_INT0:
			GICR &= ~ EXT_INT0_EN;
			break;
		
		case EXT_INT1:
			GICR &= ~EXT_INT1_EN;
			break;
		
		case EXT_INT2:
			GICR &= ~EXT_INT2_EN;
			GIFR |= EXT_INT2_FLAG;
			break;
		
		default:
				u8_status = E_NOK;
	}
	return u8_status;
}

/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output: state- state of the EXT INT flag					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function disables EXT INT channel.
 * 							
 */	
ERROR_STATUS EXT_INT_isTriggered(uint8_t EXT_INT_CH, uint8_t* state){

	ERROR_STATUS u8_status = E_OK;

	switch(EXT_INT_CH){
		
		case EXT_INT0:
		*state = (GIFR &= EXT_INT0_FLAG);
		break;
		
		case EXT_INT1:
		*state = (GIFR &= EXT_INT1_FLAG);
		break;
		
		case EXT_INT2:
		*state = (GIFR &= EXT_INT2_FLAG);
		break;
		
		default:
				u8_status = E_NOK;
	}
	return u8_status;
}

/* callback implementation */ 


/************************************************************************/
/*						ISRs			        */
/************************************************************************/



