/*
 * DIO.c
 *
 * Created: 17/02/2020 11:33:51 ص
 *  Author: TOSHIBA
 */ 
#include "DIO.h"

extern u8_ERROR_STATUS_t DIO_init (gstr_DIO_Cfg_t *pstr_DIOCfg){
	if (pstr_DIOCfg!=NULL){
	switch (pstr_DIOCfg->u8_GPIO){
		
		case GPIOA :
		switch (pstr_DIOCfg->u8_dir){
			case INPUT:
			PORTA_DIR&=~(pstr_DIOCfg->u8_pins);
			break;
			case OUTPUT:
			PORTA_DIR|=	pstr_DIOCfg->u8_pins;
			break;
		}
		break;
		
		case GPIOB :
		switch (pstr_DIOCfg->u8_dir){
			case INPUT:
			PORTB_DIR&=~(pstr_DIOCfg->u8_pins);
			break;
			case OUTPUT:
			PORTB_DIR|=	(pstr_DIOCfg->u8_pins);
			break;
		}
		
		break;
		
		case GPIOC :
		switch (pstr_DIOCfg->u8_dir)
		{
			case INPUT:
			PORTC_DIR&=~(pstr_DIOCfg->u8_pins);
			break;
			case OUTPUT:
			PORTC_DIR|=	(pstr_DIOCfg->u8_pins);
			break;
		}
		
		break;
		
		case GPIOD :
		switch (pstr_DIOCfg->u8_dir){
			case INPUT:
			PORTD_DIR&=~(pstr_DIOCfg->u8_pins);
			break;
			case OUTPUT:
			PORTD_DIR|=(pstr_DIOCfg->u8_pins);
			break;
		}
		break;
			default:
			return E_NOK;
	}
	return  E_OK;
}
else 
return E_NOK;

}
extern u8_ERROR_STATUS_t DIO_Write (uint8_t u8_GPIO, uint8_t u8_pins, uint8_t u8_value){
	switch (u8_GPIO){
		case GPIOA :
		
		PORTA_DATA=((PORTA_DATA)&~(u8_pins))|((u8_value)& (u8_pins));
		/*PORTA_DATA=u8_value;*/
		
		/*switch(u8_value){
			
			case HIGH:
			PORTA_DATA|=u8_pins;
			break;
			case LOW :
			PORTA_DATA&=(~u8_pins);
			break;
		}*/
		break;
		
		case GPIOB :
		PORTB_DATA=((PORTB_DATA)&~(u8_pins))|((u8_value)& (u8_pins));
		/*switch(u8_value){
			
			case HIGH:
			PORTB_DATA|=u8_pins;
			break;
			case LOW :
			PORTB_DATA&=(~u8_pins);
			break;
		}*/
		break;
		
		case GPIOC :
		PORTC_DATA=((PORTC_DATA)&~(u8_pins))|((u8_value)& (u8_pins));
		/*switch(u8_value){
			
			case HIGH:
			PORTC_DATA|=u8_pins;
			break;
			case LOW :
			PORTC_DATA&=(~u8_pins);
			break;
		}*/
		break;
		
		case GPIOD :
		PORTD_DATA=((PORTD_DATA)&~(u8_pins))|((u8_value)&(u8_pins));
		/*switch(u8_value){
			
			case HIGH:
			PORTD_DATA|=u8_pins;
			break;
			case LOW :
			PORTD_DATA&=(~u8_pins);
			break;
		}
		break;*/
			default:
			return E_NOK;
	}
	return E_OK;
}

extern u8_ERROR_STATUS_t DIO_Read (uint8_t u8_GPIO,uint8_t u8_pins, uint8_t *pu8_data){
	switch (u8_GPIO){
		
		case GPIOA :
		*pu8_data=u8_pins & PORTA_PIN;
		break;
		
		case GPIOB :
		*pu8_data=u8_pins&PORTB_PIN;
		break;
		
		case GPIOC :
		*pu8_data=(u8_pins &PORTC_PIN);
		break;
		
		case GPIOD :
		*pu8_data=u8_pins &PORTD_PIN;
		break;
			default:
			return E_NOK;
	}
	
	return E_NOK;

}

extern u8_ERROR_STATUS_t DIO_Toggle (uint8_t u8_GPIO, uint8_t u8_pins){
	
	switch (u8_GPIO){
		
		case GPIOA :
		PORTA_DATA^=u8_pins;
		break;
		
		case GPIOB :
		PORTB_DATA^=u8_pins;
		
		case GPIOC :
		PORTC_DATA^=u8_pins;

		break;
		
		case GPIOD :
		PORTD_DATA^=u8_pins;

		break;
		default:
       return E_NOK;
	}
	return E_OK;
}
	


