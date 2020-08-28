/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */
#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "std_types.h"

/*
 * General Registers
 */
uint8_t MCUCR;
uint8_t MCUCSR;
uint8_t GICR;
uint8_t GIFR;

/*
 * PORTx registers
 */

uint8_t PORTA_DATA;
uint8_t PORTA_DIR;
uint8_t PORTA_PIN;

uint8_t PORTB_DATA;
uint8_t PORTB_DIR;
uint8_t PORTB_PIN;

uint8_t PORTC_DATA;
uint8_t PORTC_DIR;
uint8_t PORTC_PIN;

uint8_t PORTD_DATA;
uint8_t PORTD_DIR;
uint8_t PORTD_PIN;


/*
*** USART REGISTERS
*/
uint8_t UDR	;
uint8_t UCSRA;
uint8_t UCSRB;
uint8_t UCSRC;
uint8_t UBRRL;
uint8_t UBRRH;
uint8_t UBRR;
uint8_t SPDR;

#endif /* REGISTERS_H_ */
