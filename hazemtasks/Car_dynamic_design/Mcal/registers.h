/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "..\Common\std_types.h"

#define F_CPU 16000000UL
/*
 * General Registers
 */
#define MCUCR	*((reg_type8_t )0x55)	
#define MCUCSR	*((reg_type8_t )0x54)	
#define GICR	*((reg_type8_t )0x5B)	
#define GIFR	*((reg_type8_t )0x5A)	

#define INT0  6
#define INT1  7
#define INT2  5

#define ISC2  6
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3


/*
 * PORTx registers
 */

#define PORTA_DATA 	*((reg_type8_t)0x3B)
#define PORTA_DIR  	*((reg_type8_t)0x3A)
#define PORTA_PIN	*((reg_type8_t)0x39)

#define PORTB_DATA 	*((reg_type8_t)0x38)
#define PORTB_DIR  	*((reg_type8_t)0x37)
#define PORTB_PIN	*((reg_type8_t)0x36)

#define PORTC_DATA 	*((reg_type8_t)0x35)
#define PORTC_DIR  	*((reg_type8_t)0x34)
#define PORTC_PIN	*((reg_type8_t)0x33)


#define PORTD_DATA 	*((reg_type8_t)0x32)
#define PORTD_DIR  	*((reg_type8_t)0x31)
#define PORTD_PIN	*((reg_type8_t)0x30)


/*
 * General Timer registers
 */
#define TIMSK		*((reg_type8_t)0x59)
#define TIFR		*((reg_type8_t)0x58)


/*
 * Timer 0 Registers
 */

#define TCCR0		*((reg_type8_t)0x53)
#define TCNT0		*((reg_type8_t)0x52)
#define OCR0		*((reg_type8_t)0x5c)

/**
 * TCCR0 bits
 */

#define CS00	(0x01)
#define CS01	(0x02)
#define CS02	(0x04)
#define WGM01	(0x08)
#define COM00	(0x10)
#define COM01	(0x20)
#define WGM00	(0x40)
#define FOC0	(0x80)


/*
 * Timer 1 Registers
 */

#define TCCR1A	    *((reg_type8_t)0x4F)	
#define TCCR1B		*((reg_type8_t)0x4E)
#define TCCR1		*((reg_type16_t)0x4F)
#define TCNT1H		*((reg_type8_t)0x4D)
#define TCNT1L		*((reg_type8_t)0x4C)
#define TCNT1		*((reg_type16_t)0x4C)
#define OCR1AH		*((reg_type8_t)0x4B)
#define OCR1AL		*((reg_type8_t)0x4A)
#define OCR1A		*((reg_type16_t)0x4A)
#define OCR1BH		*((reg_type8_t)0x49)
#define OCR1BL		*((reg_type8_t)0x48)
#define OCR1B		*((reg_type16_t)0x48)
#define ICR1H		*((reg_type8_t)0x47)
#define ICR1L		*((reg_type8_t)0x46)
#define ICR1		*((reg_type16_t)0x46)
/**
 * TCCR1A bits
 */

#define WGM10	(0x01)
#define WGM11	(0x02)
#define FOC1B	(0x04)
#define FOC1A	(0x08)
#define COM1B0	(0x10)
#define COM1B1	(0x20)
#define COM1A0	(0x40)
#define COM1A1	(0x80)


/**
 * TCCR1B bits
 */

#define CS10	(0x01)
#define CS11	(0x02)
#define CS12	(0x04)
#define WGM12	(0x08)
#define WGM13	(0x10)
#define RESER	(0x20)
#define ICES1	(0x40)
#define ICNC1	(0x80)

/*
 * Timer 2 Registers
 */
#define TCCR2		*((reg_type8_t)0x45)
#define TCNT2		*((reg_type8_t)0x44)
#define OCR2		*((reg_type8_t)0x43)

/**
 * TCCR2 bits
 */

#define CS20	(0x01)
#define CS21	(0x02)
#define CS22	(0x04)
#define WGM21	(0x08)
#define COM20	(0x10)
#define COM21	(0x20)
#define WGM20	(0x40)
#define FOC2	(0x80)

#define  TOIE0 0x01
#define  TOIE1 0x04
#define  TOIE2 0x40
#define  OCIE0 1

#define  TOV0 0
#define  TOV1 2
#define  TOV2 6






#endif /* REGISTERS_H_ */
