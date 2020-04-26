/*Mock registers.c*/

#include "../../Infrastructure/std_types.h"
/*
 * General Registers
 */
uint8_t MCUCR;
uint8_t MCUCSR;
uint8_t GICR;
uint8_t GIFR;
uint8_t SREG;
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
 * General Timer registers
 */
uint8_t TIMSK;
uint8_t TIFR;

/*
 * Timer 0 Registers
 */

uint8_t TCCR0;
uint8_t TCNT0;
uint8_t OCR0;
/*
 * Timer 1 Registers
 */

uint8_t TCCR1A	;
uint8_t TCCR1B	;
uint16_t TCCR1	;

uint8_t TCNT1H	;
uint8_t TCNT1L	;
uint16_t TCNT1	;


uint8_t OCR1AH	;
uint8_t OCR1AL	;
uint8_t OCR1A	;

uint8_t OCR1BH	;
uint8_t OCR1BL	;
uint8_t OCR1B	;

uint8_t ICR1H	;
uint8_t ICR1L	;
uint16_t ICR1	;


/*
 * Timer 2 Registers
 */
uint8_t TCCR2	;
uint8_t TCNT2	;
uint8_t OCR2	;
uint8_t ASSR  ;
