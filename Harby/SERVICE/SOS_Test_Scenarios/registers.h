/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */


#include "std_types.h"
#include "common_macros.h"

extern uint8_t PORTA_DATA;
extern uint8_t PORTB_DATA;
extern uint8_t PORTC_DATA;
extern uint8_t PORTD_DATA;

extern uint8_t PORTA_DIR;
extern uint8_t PORTB_DIR;
extern uint8_t PORTC_DIR;
extern uint8_t PORTD_DIR;

extern uint8_t PORTA_PIN;
extern uint8_t PORTB_PIN;
extern uint8_t PORTC_PIN;
extern uint8_t PORTD_PIN;

extern uint8_t TIFR;
extern uint8_t TCNT0;
extern uint8_t TCNT2;
extern uint8_t TCCR1A;
extern uint8_t TCCR1B;
extern uint16_t TCNT1;
extern uint16_t ICR1;
extern uint8_t OCR1A;
extern uint8_t OCR1B;
extern uint8_t TCCR0;
extern uint8_t TCCR2;
extern uint8_t TIMSK;


#define		COM1A0		0
#define		COM1A1		0
#define		COM1B1		0
#define		COM1B0		0
#define		FOC1B		0
#define		FOC1A		0
#define		WGM10		0
#define		WGM11		0
#define		WGM12		0
#define		WGM13		0
#define 	CS20		0
#define 	CS21		0
#define 	CS22		0
#define 	CS12		0
#define 	CS10		0
#define 	CS11		0
#define 	CS00		0
#define 	CS01		0
#define 	CS02		0
