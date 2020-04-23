
#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "std_types.h"


uint8 MCUCR;
uint8 MCUCSR;
uint8 GICR;
uint8 GIFR;
uint8 SREG;
/*
 * PORTx registers
 */

uint8 PORTA_DATA;
uint8 PORTA_DIR;
uint8 PORTA_PIN;

uint8 PORTB_DATA;
uint8 PORTB_DIR;
uint8 PORTB_PIN;

uint8 PORTC_DATA;
uint8 PORTC_DIR;
uint8 PORTC_PIN;


uint8 PORTD_DATA;
uint8 PORTD_DIR;
uint8 PORTD_PIN;


/*
 * General Timer registers
 */
uint8 TIMSK;
uint8 TIFR;


/*
 * Timer 0 Registers
 */

uint8 TCCR0;
uint8 TCNT0;
uint8 OCR0;


/*
 * Timer 1 Registers
 */



///REMEBER TO CHECK FOR A B AND NONE
uint8 TCCR1A;
uint8 TCCR1B;
uint8 TCCR1;
uint8 TCNT1H;
uint8 TCNT1L;
uint8 TCNT1;
uint8 OCR1AH;
uint8 OCR1AL;
uint8 OCR1A;
uint8 OCR1BH;
uint8 OCR1BL;
uint8 OCR1B;
uint8 ICR1H;
uint8 ICR1L;
uint8 ICR1;


/*
 * Timer 2 Registers
 */
uint8 TCCR2;
uint8 TCNT2;
uint8 OCR2;
uint8 ASSR;

/*
 *Timer Counter Interrupt flag Registers
 */
/*uint8 TOV0=0;
uint8 OCF0=1;
uint8 TOV1=2;
uint8 OCF1B=3;
uint8 OCF1A=4;
uint8 ICF1=5;
uint8 TOV2=6;
uint8 OCF2=7;*/

#endif /* REGISTERS_H_ */
