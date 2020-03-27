/*
 * DIO.c
 *
 *	Created: 2020-02-17 11:02:45 AM
 *  Author: EbrahimOseif
 */ 


/************************************************************************/
/*				 INCLUDES										        */
/************************************************************************/


#include "DIO.h"





/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/


/************************************************************************/
/*		         TIMER FUNCTIONS' implementation				        */
/************************************************************************/


/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
	
	ERROR_STATUS u8_status = E_OK;
	
	if (DIO_info == NULL)
	{
		u8_status = E_NOK;
	}else{
			if (!(DIO_info->GPIO >= GPIOA && DIO_info->GPIO <= GPIOD))
			{
				u8_status = E_NOK;
			}else
			{
			switch(DIO_info->GPIO){
				
				case 0:
				if ( DIO_info->dir == INPUT )
				{
					PORTA_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
				}
				else{
					PORTA_DIR |= DIO_info->pins;
				}
				
				break;
				
				case 1:
				if ( DIO_info->dir == INPUT )
				{
					PORTB_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
				}
				else{
					PORTB_DIR |= DIO_info->pins;
				}
				
				break;
				
				case 2:
				if ( DIO_info->dir == INPUT )
				{
					PORTC_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
				}
				else{
					PORTC_DIR |= DIO_info->pins;
				}
				
				break;
				
				case 3:
				if ( DIO_info->dir == INPUT )
				{
					PORTD_DIR &= ~(DIO_info->pins); //clear the bits to be inputs
				}
				else{
					PORTD_DIR |= DIO_info->pins;
				}
				
				break;
				
				default:
				u8_status = E_NOK;
			}	
		}/* END OF ELSE */
		
	}/* END OF outer ELSE */
	
	return u8_status;
}


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t u8_pins, uint8_t u8_value){
	
		ERROR_STATUS u8_status = E_OK;
		
			if (!(GPIO >= GPIOA && GPIO <= GPIOD) /*|| !(u8_pins >=0 && u8_pins <=7)*/)
			{
				u8_status = E_NOK;
				
			}else{
				
	       switch(GPIO){
		      
		      case GPIOA:

		               if(u8_value == LOW)
		               {
			               PORTA_DATA &= ~(u8_pins);
		               }
		               else
		               {
			               PORTA_DATA |= (u8_pins /*& u8_value*/);
		               }
		               break;

		      case GPIOB:
			  
		               if(u8_value == LOW)
		               {
			               PORTB_DATA &= ~(u8_pins);
		               }
		               else
		               {
			               PORTB_DATA |= (u8_pins /*& u8_value*/);
		               }
		               break;
			  
		      case GPIOC:
			  
		               if(u8_value == LOW)
		               {
			               PORTC_DATA &= ~(u8_pins);
		               }
		               else
		               {
			               PORTC_DATA |= (u8_pins /*& u8_value*/);
		               }
		               break;

		      case GPIOD:
			  
		               if(u8_value == LOW)
		               {
			               PORTD_DATA &= ~(u8_pins);
		               }
		               else
		               {
			               PORTD_DATA |= (u8_pins /*& u8_value*/);
		               }
		               break;

		      default:
					u8_status = E_NOK;
	      }
	  
	 } /* end of else */
	return u8_status;	
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t u8_pins, uint8_t *data){
	
	
	ERROR_STATUS u8_status = E_OK;
		
		if (!(GPIO >= GPIOA && GPIO <= GPIOD) /* || !(u8_pins >=0 && u8_pins <=7)*/)
		{
			u8_status = E_NOK;
			
		}else{
			
		switch(GPIO){
			
			case GPIOA:
					*data =	 (PORTA_PIN & u8_pins ) ;
					break;
			
			case GPIOB:
					*data =	 (PORTB_PIN & u8_pins ) ;
					break;
			
			case GPIOC:
					*data =	 (PORTC_PIN & u8_pins ) ;
					break;
			case GPIOD:
					*data =	(PORTD_PIN & u8_pins ) ;
					break;
			default: 
			   u8_status = E_NOK;
		}
		
		if(*data != LOW)
		{
			*data = HIGH;
		}
		
	} /*end of else */
		return u8_status;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*    				- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t u8_pins){
	
	ERROR_STATUS u8_status = E_OK;
		
		if (!(GPIO >= GPIOA && GPIO <= GPIOD)  /* || !(u8_pins >=0 && u8_pins <=7) */)
		{
			u8_status = E_NOK;
			
			}
			else{
	
	             switch(GPIO){
	             	
	             	case GPIOA:
	             			PORTA_DATA ^= u8_pins;
	             			break;
	             	
	             	case GPIOB:
	             			PORTB_DATA ^= u8_pins;
	             			break;
	             	
	             	case GPIOC:
	             			PORTC_DATA ^= u8_pins;
	             			break;
	             	
	             	case GPIOD:
	             			PORTD_DATA ^= u8_pins;
	             			break;
	             	default: 
	             			u8_status = E_NOK;
	             }
			}/*end of else */
				 
	return u8_status;
}
