#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "../Common/std_types.h"

/********************************************************
 * General Registers
 *******************************************************/
#define MCUCR	*((reg_type8_t)(0X55))
#define MCUCSR	*((reg_type8_t)(0X54))
#define GICR	*((reg_type8_t)(0X5B))
#define GIFR	*((reg_type8_t)(0X5A))

/********************************************************
 * PORTx registers
 *******************************************************/

#define PORTA_DATA 	*((reg_type8_t)(0X3B))
#define PORTA_DIR  	*((reg_type8_t)(0X3A))
#define PORTA_PIN	*((reg_type8_t)(0X39))

#define PORTB_DATA 	*((reg_type8_t)(0X38))
#define PORTB_DIR  	*((reg_type8_t)(0X37))
#define PORTB_PIN	*((reg_type8_t)(0X36))

#define PORTC_DATA 	*((reg_type8_t)(0X35))
#define PORTC_DIR  	*((reg_type8_t)(0X34))
#define PORTC_PIN	*((reg_type8_t)(0X33))


#define PORTD_DATA 	*((reg_type8_t)(0X32))
#define PORTD_DIR  	*((reg_type8_t)(0X31))
#define PORTD_PIN	*((reg_type8_t)(0X30))


/*********************************************************
 * General Timer registers
 ********************************************************/
#define TIMSK		*((reg_type8_t)(0X59))
#define TIFR		*((reg_type8_t)(0X58))


/*********************************************************
 * Timer 0 Registers
 *********************************************************/

#define TCCR0		*((reg_type8_t)(0X53))
#define TCNT0		*((reg_type8_t)(0X52))
#define OCR0		*((reg_type8_t)(0X5C))


/**********************************************************
 * Timer 1 Registers
 *********************************************************/

#define TCCR1A		*((reg_type8_t)(0X4F))
#define TCCR1B		*((reg_type8_t)(0X4E))
#define TCCR1		*((reg_type16_t)(0X4E))
#define TCNT1H		*((reg_type8_t)(0X4D))
#define TCNT1L		*((reg_type8_t)(0X4C))
#define TCNT1		*((reg_type16_t)(0X4C))
#define OCR1AH		*((reg_type8_t)(0X4B))
#define OCR1AL		*((reg_type8_t)(0X4A))
#define OCR1A		*((reg_type16_t)(0X4A))
#define OCR1BH		*((reg_type8_t)(0X49))
#define OCR1BL		*((reg_type8_t)(0X48))
#define OCR1B		*((reg_type16_t)(0X48))
#define ICR1H		*((reg_type8_t)(0X47))
#define ICR1L		*((reg_type8_t)(0X46))
#define ICR1		*((reg_type16_t)(0X46))


/**********************************************************
 * Timer 2 Registers
 **********************************************************/
#define TCCR2		*((reg_type8_t)(0X45))
#define TCNT2		*((reg_type8_t)(0X44))
#define OCR2		*((reg_type8_t)(0X43))


/************************************************************
 * interrupts vector table
 ***********************************************************/
#define RESET_ *((reg_type8_t)(0X000))
#define INT0_ *((reg_type8_t)(0X002))
#define INT1_ *((reg_type8_t)(0X004))
#define INT2_ *((reg_type8_t)(0X006))
#define TIMER2_COMP_ *((reg_type8_t)(0X008))
#define TIMER2_OVF_ *((reg_type8_t)(0X00A))
#define TIMER1_CAPT_ *((reg_type8_t)(0X00C))
#define TIMER1_COMPA_ *((reg_type8_t)(0X00E))
#define TIMER1_COMPB_ *((reg_type8_t)(0X010))
#define TIMER1_OVF_ *((reg_type8_t)(0X012))
#define TIMER0_COMP_ *((reg_type8_t)(0X014))
#define TIMER0_OVF_ *((reg_type8_t)(0X016))
#define SPI_STC_ *((reg_type8_t)(0X018))   /*serial transfer complete*/
#define USART_RXC_ *((reg_type8_t)(0X01A))
#define USART_UDRE_ *((reg_type8_t)(0X01C))
#define USART_TXC_ *((reg_type8_t)(0X01E))
#define ADC_ *((reg_type8_t)(0X020))
#define EE_RDY_ *((reg_type8_t)(0X022))
#define ANA_COMP_ *((reg_type8_t)(0X024))
#define TWI_ *((reg_type8_t)(0X026))
#define SPM_RDY_ *((reg_type8_t)(0X028))

/************************************************************
 * UART registers
 ***********************************************************/
#define UCSRA *((reg_type8_t)(0X2B))
#define UCSRB *((reg_type8_t)(0X2A))
#define UBRRL *((reg_type8_t)(0X29))
#define UCSRC *((reg_type8_t)(0X40))
#define UBRRH *((reg_type8_t)(0X40))
#define UDR *((reg_type8_t)(0X2C))

/************************************************************
 * SPI registers
 ***********************************************************/
#define  SPCR  *((reg_type8_t)0x2D)
#define  SPSR  *((reg_type8_t)0x2E)
#define  SPDR  *((reg_type8_t)0x2F)




/************************************************************
 * Registers bits definitions
 ***********************************************************/
/*============Timer general registers bits definitions============*/

/*==================TIMSK======================*/
#define TOIE0 0	    // defines BIT0 in a TIMSK register
#define OCIE0 1	    // defines BIT1 in a TIMSK register
#define TOIE1 2	    // defines BIT2 in a TIMSK register
#define OCIE1B 3	// defines BIT3 in a TIMSK register
#define OCIE1A 4	// defines BIT4 in a TIMSK register
#define TICIE1 5	// defines BIT5 in a TIMSK register
#define TOIE2 6	    // defines BIT6 in a TIMSK register
#define OCIE2 7	   // defines BIT7 in a TIMSK register

/*===================TIFR=====================*/
#define TOV0 0	  // defines BIT0 in a TIMSK register
#define OCF0 1	  // defines BIT1 in a TIMSK register
#define TOV1 2	  // defines BIT2 in a TIMSK register
#define OCF1B 3	  // defines BIT3 in a TIMSK register
#define OCF1A 4	  // defines BIT4 in a TIMSK register
#define ICF1 5	  // defines BIT5 in a TIMSK register
#define TOV2 6	  // defines BIT6 in a TIMSK register
#define OCF2 7	  // defines BIT7 in a TIMSK register



/*==============TIMER0 Registers Bits Definitions=================*/

/*==================TCCR0======================*/
#define CS00 0	 // defines BIT0 in a TCCR0 register
#define CS01 1	 // defines BIT1 in a TCCR0 register
#define CS02 2	 // defines BIT2 in a TCCR0 register
#define WGM01 3	 // defines BIT3 in a TCCR0 register
#define COM00 4	 // defines BIT4 in a TCCR0 register
#define COM01 5	 // defines BIT5 in a TCCR0 register
#define WGM00 6	 // defines BIT6 in a TCCR0 register
#define FOC0 7	 // defines BIT7 in a TCCR0 register

/*========TIMER0 Registers Bits Definitions======*/

/*==================TCCR1A======================*/
#define WGM10 0	     // defines BIT0 in a TCCR1A register
#define WGM11 1	     // defines BIT1 in a TTCCR1A register
#define FOC1B 2	     // defines BIT2 in a TCCR1A register
#define FOC1A 3	     // defines BIT3 in a TCCR1A register
#define COM1B0 4	 // defines BIT4 in a TCCR1A register
#define COM1B1 5	 // defines BIT5 in a TCCR1A register
#define COM1A0 6	 // defines BIT6 in a TCCR1A register
#define COM1A1 7	 // defines BIT7 in a TCCR1A register

/*==================TCCR1B======================*/
#define CS10 0	     // defines BIT0 in a TCCR1B register
#define CS11 1	     // defines BIT1 in a TCCR1B register
#define CS12 2	     // defines BIT2 in a TCCR1B register
#define WGM12 3	     // defines BIT3 in a TCCR1B register
#define WGM13 4	     // defines BIT4 in a TCCR1B register
/*reserved bit*/	 // defines BIT5 in a TCCR1B register
#define ICES1 6	     // defines BIT6 in a TCCR1B register
#define ICNC1 7	     // defines BIT7 in a TCCR1B register


/*===========================TIMER2 Registers Bits Definitions===============================*/

/*==================TCCR2======================*/
#define CS20 0	 // defines BIT0 in a TCCR2 register
#define CS21 1	 // defines BIT1 in a TCCR2 register
#define CS22 2	 // defines BIT2 in a TCCR2 register
#define WGM21 3	 // defines BIT3 in a TCCR2 register
#define COM20 4	 // defines BIT4 in a TCCR2 register
#define COM21 5	 // defines BIT5 in a TCCR2 register
#define WGM20 6	 // defines BIT6 in a TCCR2 register
#define FOC2 7	 // defines BIT7 in a TCCR2 register


/*============Interrupts registers bits definitions============*/
/*MCUCR register*/

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define SM0 4
#define SM1 5
#define SM2 6
#define SE 7

/*MCUCSR*/
#define PORF 0
#define EXTRF 1
#define BORF 2
#define WDRF 3
#define JTRF 4
/*reserved bit(bit5)*/
#define ISC2 6
#define JTD 7

/*GICR*/
#define IVCE 0
#define IVSEL 1
/*reserved bit(bit2)*/
/*reserved bit(bit3)*/
/*reserved bit(bit4)*/
#define INT2 5
#define INT0 6
#define INT1 7

/*GIFR*/
/*reserved bit(bit0)*/
/*reserved bit(bit1)*/
/*reserved bit(bit2)*/
/*reserved bit(bit3)*/
/*reserved bit(bit4)*/
#define INTF2 5
#define INTF0 6
#define INTF1 7



/****************************************************************************************/


#endif /* REGISTERS_H_ */

