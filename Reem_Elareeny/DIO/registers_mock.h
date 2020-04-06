/*
 * registers.h
 *
 * Created: 2/15/2020 11:07:24 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "std_types.h"



/************************************************************************/
/*		                     PORTS REGISTERS		                        */
/************************************************************************/

uint8_t PORTA_DATA;    
uint8_t PORTA_DIR;       
uint8_t PORTA_PIN;	      

uint8_t PORTB_DATA;
uint8_t PORTB_DIR ;
uint8_t PORTB_PIN;
						 
uint8_t PORTC_DATA;
uint8_t PORTC_DIR;
uint8_t PORTC_PIN;
 						 
uint8_t PORTD_DATA;
uint8_t PORTD_DIR;
uint8_t PORTD_PIN;

#endif /* REGISTERS_H_ */