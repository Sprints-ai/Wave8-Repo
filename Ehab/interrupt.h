/*
 * interrupt.h
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */

#include "registers.h"

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define INT0  				0x40
#define INT1				0x80
#define INT2				0x20

#define INT0_LOW_LEVEL			0x00
#define INT0_ANY_LOGICAL_CHANGE	0x01
#define INT0_FALLING_EDGE		0x02
#define INT0_RISING_EDGE		0x03

#define INT1_LOW_LEVEL			0x00
#define INT1_ANY_LOGICAL_CHANGE	0x04
#define INT1_FALLING_EDGE		0x08
#define INT1_RISING_EDGE		0x0C

#define INT2_FALLING_EDGE	0x00
#define INT2_RISING_EDGE	0x40

#define ENABLE_GINT			(SREG|=(1<<7))
#define DISABLE_GINT		(SREG&=~(1<<7))


/* defining the vector numbers to recognizable names*/
#define INT0_vect			__vector_1			//External interrupt 0 vector
#define INT1_vect			__vector_2			//External interrupt 1 vector
#define INT2_vect			__vector_3			//External interrupt 2 vector
#define TIMER2_COMP_vect	__vector_4			//Timer2 compare match vector
#define TIMER2_OVF_vect		__vector_5			//Timer2 overflow vector
#define TIMER1_CAPT_vect	__vector_6			//Timer1 input capture vector
#define TIMER1_COMPA_vect	__vector_7			//Timer1 compare match A vector
#define TIMER1_COMPB_vect	__vector_8			//Timer1 compare match B vector
#define TIMER1_OVF_vect		__vector_9			//Timer1 overflow vector
#define TIMER0_COMP_vect	__vector_10			//Timer0 compare match vector
#define TIMER0_OVF_vect		__vector_11			//Timer0 overflow vector
#define SPI_STC_vect		__vector_12
#define USART_RXC_vect		__vector_13
#define USART_UDRE_vect		__vector_14
#define USART_TXC_vect		__vector_15
#define ADC_vect			__vector_16
#define EE_RDY_vect			__vector_17
#define ANA_COMP_vect		__vector_18
#define TWI_vect			__vector_19
#define SPM_RDY_vect		__vector_20

/**
 * Description: Initializing the external interrupt
 * @param u8_INTno: number of the external interrupt required to be initialized
 *              and takes the following values:
 * 				- 0x40 -> INT0
 * 				- 0x80 -> INT1
 * 				- 0x20 -> INT2
 * @param u8_sense: set the sense of the external interrupt
 */
void EXTI_Init(uint8_t u8_INTNo , uint8_t u8_sense);

/**
 * Description: De-Initializing the external interrupt
 */
void EXTI_DEInit(void);

/* Defining the interrupt service routine function to be a signal function */
#define InterruptServiceRoutine(vector_num) void vector_num(void) __attribute__((signal));\
												void vector_num(void)
												
/* #define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::) */

#endif /* INTERRUPT_H_ */
