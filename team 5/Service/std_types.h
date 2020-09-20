/*
 * std_types.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;
typedef char sint8_t;
typedef int sint16_t;
typedef long int sint32_t;
typedef long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;
typedef sint16_t ERROR_STATUS;
typedef		void (*FunPtr)(void);

/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


#define ZERO		(0)
#define ONE			(1)
#define TWO			(2)
#define THREE		(3)
#define FOUR		(4)
#define FIVE		(5)
#define SIX			(6)
#define SEVEN		(7)
#define EIGHT		(8)
#define NINE		(9)
#define TEN			(10)
#define ELEVEN		(11)
#define TWELVE		(12)
#define THIRTEEN	(13)
#define FOURTEEN	(14)
#define FIFTEEN		(15)
#define SIXTEEN		(16)

/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFF	// defines HIGH value for a bit

#define  E_OK 0
#define  E_NOK 1

#define ZERO_VALUE 0 
#define NULL_OPERATOR		'\0'

/************************************************************************/
/*					   bitwise operation		                       */
/************************************************************************/


#define SET_BIT(REG,BIT) REG|=(1<<BIT)

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) REG&=(~(1<<BIT))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* get low of high nibble bit */

#define GET_NIBBLE_LOW(reg) reg & 0b00001111
#define GET_NIBBLE_HIGH(reg) (reg & 0b11110000)>>4



/************************************************************************/
/*                   error handling macros		                       */
/************************************************************************/

#define TMU_module_error -500
#define DIO_module_error -400
#define TIMER_module_error -300
#define  SOS_module_error -200
#define LCD_MODEULE_ERROR -100


#define NULL_PTR_ERROR -1
#define MODULE_UNINTIALIZED -2
#define MULTIPLE_INITIALIZATION -3
#define INVALID__PARAMETER -4
#define MULTIPLE_START -5
#define MULTIPLE_STOP -6
#define FULL_BUFFER -7
#define DEINIT_WITHOUT_INIT -8
#define  STOP_WITHOU_SART -9

#endif /* STD_TYPES_H_ */
