
#ifndef MOCK_REGISTERS_H_
#define MOCK_REGISTERS_H_
#include "std_types.h"

/*
 * General Registers
 */
/*
 * General Registers
 */
extern uint8_t MCUCR ;
extern uint8_t MCUCSR ;
extern uint8_t GICR  ;
extern uint8_t GIFR	;
extern uint8_t SREG	 ;
/*
 * PORTx registers
 */

extern uint8_t PORTA_DATA	 ;
extern uint8_t PORTA_DIR ;
extern uint8_t PORTA_PIN ;

extern uint8_t PORTB_DATA ;

extern uint8_t PORTB_DIR;
extern uint8_t PORTB_PIN;

extern uint8_t PORTC_DATA;
extern uint8_t PORTC_DIR ;
extern uint8_t PORTC_PIN ;


extern uint8_t PORTD_DATA	 ;
extern uint8_t PORTD_DIR ;
extern uint8_t PORTD_PIN ;


/*
 * General Timer registers
 */
extern uint8_t TIMSK		;
extern uint8_t TIFR		;

/*
 * Timer 0 Registers
 */

extern uint8_t TCCR0	;
extern uint8_t TCNT0	;
extern uint8_t OCR0;
#define TOV0      0
#define OCF0      1
#define TOV1      2
#define OCF1B     3
#define OCF1A     4
#define ICF1      5
#define TOV2      6
#define OCF2      7
/***************************************************/
/* OCF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0<<TIFRReg */
/***************************************************/
/*
 * Timer 1 Registers
 */

extern uint8_t TCCR1A	;
extern uint8_t TCCR1B	;
extern uint16_t TCCR1	;

extern uint8_t TCNT1H	;
extern uint8_t TCNT1L	;
extern uint16_t TCNT1	;


extern uint8_t OCR1AH	;
extern uint8_t OCR1AL	;
extern uint8_t OCR1A	;

extern uint8_t OCR1BH	;
extern uint8_t OCR1BL	;
extern uint8_t OCR1B;

extern uint8_t ICR1H;
extern uint8_t ICR1L;
extern uint16_t ICR1;


/*
 * Timer 2 Registers
 */
extern uint8_t TCCR2;
extern uint8_t TCNT2;
extern uint8_t OCR2	;
extern uint8_t ASSR ;


#endif /* MOCK_REGISTERS_H_ */
