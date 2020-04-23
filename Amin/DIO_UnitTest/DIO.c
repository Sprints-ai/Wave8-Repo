/*
 * DIO.c
 *
 * Created: 2/15/2020 4:50:16 PM
 *  Author: Ahmed Amin
 */
#include "DIO.h"

 /*Describtion: this function initialize the gpio direction for specific direction  */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
    ERROR_STATUS retval=E_OK;
    if(DIO_info!=NULL){
	 switch(DIO_info->GPIO){
		 case GPIOA:
		 if(DIO_info->dir){
		 PORTA_DIR|=DIO_info->pins;}
		 else {
			 PORTA_DIR&=~(DIO_info->pins);
		 }
		 retval=E_OK;
		 break;

		 case GPIOB:
		 if(DIO_info->dir){
		 PORTB_DIR|=DIO_info->pins;}
		 else {
			 PORTB_DIR&=~(DIO_info->pins);
		 }
		 retval=E_OK;
		 break;

		 case GPIOC:
		 if(DIO_info->dir){
		 PORTC_DIR|=DIO_info->pins;}
		 else {
			 PORTC_DIR&=~(DIO_info->pins);
		 }
		 retval=E_OK;
		 break;

		 case GPIOD:
		 if(DIO_info->dir){
		 PORTD_DIR|=(DIO_info->pins);}
		 else {
			 PORTD_DIR&=~(DIO_info->pins);
		 }
		 retval=E_OK;
		 break;

		 default:
            retval=E_NOK;
	 }
    }
    else{
     retval=NULL_PTR_ERROR;
     }
	 return retval;
 }

  /*Describtion: this function write the gpio pin  */
 ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value){
	 ERROR_STATUS retval=E_OK;
	switch(GPIO){
		case GPIOA:
		if(value){
		PORTA_DATA|=pins;}
		else {
			PORTA_DATA&=~(pins);
		}
	     retval=E_OK;
		 return retval;
		 break;
		case GPIOB:
		if(value){
		PORTB_DATA|=pins;}
		else {
			PORTB_DATA&=~(pins);
		}
	     retval=E_OK;
		 return retval;
		 break;
		case GPIOC:
		if(value){
		PORTC_DATA|=pins;}
		else {
			PORTC_DATA&=~(pins);
		}
		 retval=E_OK;
		 return retval;
		break;
		case GPIOD:
		if(value){
		PORTD_DATA|=pins;}
		else {
			PORTD_DATA&=~(pins);
		}
	     retval=E_OK;
		 return retval;
		break;
		default:
            retval=E_NOK;
	}
	 return retval;
 }


 /*Describtion: this function read the state of gpio pin  */
ERROR_STATUS DIO_Read (uint8 GPIO,uint8 pins, uint8 *data){
	ERROR_STATUS retval=E_OK;
	if(data!=NULL){
	switch(GPIO){
		case GPIOA:
		if((PORTA_PIN&=pins)){
			return 1;
			}else{
		   retval=E_OK;
		 return retval;
		}
		break;
		case GPIOB:
		if((PORTB_PIN&=pins)){
			return 1;
			}else{
		  retval=E_OK;
		 return retval;
		}
		break;
		case GPIOC:
		if((PORTC_PIN&=pins)){
			return 1;
			}else{
		  retval=E_OK;
		 return retval;
		}
		break;
		case GPIOD:
		if((PORTD_PIN&=pins)){
			return 1;
			}else{
		 retval=E_OK;
		 return retval;
		}
		break;
		default:
            retval=E_NOK;
	}
	}
	else{
        retval=NULL_PTR_ERROR;
	}
	    return retval;
}

 /*Describtion: this function toggle the gpio pin */
ERROR_STATUS DIO_Toggle (uint8 GPIO, uint8 pins){
	ERROR_STATUS retval=E_OK;
	switch(GPIO){
		case GPIOA:
		PORTA_DATA^=pins;
	   retval=E_OK;
		 return retval;
		break;
		case GPIOB:
		PORTB_DATA^=pins;
		 retval=E_OK;
		 return retval;
		break;
		case GPIOC:
		PORTC_DATA^=pins;
		 retval=E_OK;
		 return retval;
		break;
		case GPIOD:
		PORTD_DATA^=pins;
		 retval=E_OK;
		 return retval;
		break;
		default:
            retval=E_NOK;
	}
	return retval;
}
