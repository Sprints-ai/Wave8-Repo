#include "gpio.h"
void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction){
	switch(u8_port){
		case GPIOA: 
		PORTA_DIR=u8_direction;
		break;
		case GPIOB: 
		PORTB_DIR=u8_direction;
		break;
		case GPIOC: 
		PORTC_DIR=u8_direction;
		break;
		case GPIOD: 
		PORTD_DIR=u8_direction;
		break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value){
	switch(u8_port){
		case GPIOA: 
		PORTA_DATA=u8_value;
		break;
		case GPIOB: 
		PORTB_DATA=u8_value;
		break;
		case GPIOC: 
		PORTC_DATA=u8_value;
		break;
		case GPIOD: 
		PORTD_DATA=u8_value;
		break;
	}
	
}

void gpioPortToggle(uint8_t u8_port){
	switch(u8_port){
		case GPIOA: 
		PORTA_DATA^=0xFF;
		break;
		case GPIOB: 
		PORTB_DATA^=0xFF;
		break;
		case GPIOC: 
		PORTC_DATA^=0xFF;
		break;
		case GPIOD: 
		PORTD_DATA^=0xFF;
		break;
	}
}

 uint8_t gpioPortRead(uint8_t u8_port){
	switch(u8_port){
		case GPIOA: 
		return PORTA_PIN;
		break;
		case GPIOB: 
		return PORTB_PIN;
		break;
		case GPIOC: 
		return PORTC_PIN;
		break;
		case GPIOD: 
		return PORTD_PIN;
		break;
	} 
	return 0;
	 
 }
 void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction){
	 
	 switch(u8_port){
		case GPIOA: 
		if(u8_direction){
		PORTA_DIR|=u8_pins;}
		else {
			PORTA_DIR&=~(u8_pins);
		}
		break;
		case GPIOB: 
		if(u8_direction){
		PORTB_DIR|=u8_pins;}
		else {
			PORTB_DIR&=~(u8_pins);
		}
		break;
		case GPIOC: 
		if(u8_direction){
		PORTC_DIR|=u8_pins;}
		else {
			PORTC_DIR&=~(u8_pins);
		}
		break;
		case GPIOD: 
		if(u8_direction){
		PORTD_DIR|=u8_pins;}
		else {
			PORTD_DIR&=~(u8_pins);
		}
		break;
	}
}
 void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value){
	 switch(u8_port){
		case GPIOA: 
		if(u8_value){
		PORTA_DATA|=u8_pins;}
		else {
			PORTA_DATA&=~(u8_pins);
		}
		break;
		case GPIOB: 
		if(u8_value){
		PORTB_DATA|=u8_pins;}
		else {
			PORTB_DATA&=~(u8_pins);
		}
		break;
		case GPIOC: 
		if(u8_value){
		PORTC_DATA|=u8_pins;}
		else {
			PORTC_DATA&=~(u8_pins);
		}
		break;
		case GPIOD: 
		if(u8_value){
		PORTD_DATA|=u8_pins;}
		else {
			PORTD_DATA&=~(u8_pins);
		}
		break;
	}
	 
 }
 void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins){
	  switch(u8_port){
		case GPIOA: 
		PORTA_DATA^=u8_pins;
		break;
		case GPIOB: 
		PORTB_DATA^=u8_pins;
		break;
		case GPIOC: 
		PORTC_DATA^=u8_pins;
		break;
		case GPIOD: 
		PORTD_DATA^=u8_pins;
		break;
	}
 }

 uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin,uint8_t*readpin){
	   switch(u8_port){
		case GPIOA: 
		if((PORTA_PIN&=u8_pin)){
			*readpin=1;
			return 1;
		}else{
			*readpin=0;
			return 0;
		}
		break;
		case GPIOB: 
		if((PORTB_PIN&=u8_pin)){
			*readpin=1;
			return 1;
		}else{
			*readpin=0;
			return 0;
		}
		break;
		case GPIOC: 
		if((PORTC_PIN&=u8_pin)){
			*readpin=1;
			return 1;
		}else{
			*readpin=0;
			return 0;
		}
		break;
		case GPIOD: 
		if((PORTD_PIN&=u8_pin)){
			*readpin=1;
			return 1;
		}else{
			*readpin=0;
			return 0;
		}
		break;
	}
	return 0;
 }



