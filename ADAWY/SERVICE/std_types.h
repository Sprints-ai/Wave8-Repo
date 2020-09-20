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
typedef unsigned  int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;
typedef sint16_t ERROR_STATUS;

/************************************************************************/
/*				 		defining Microcontroller clock                      */
/************************************************************************/
#define F_CPU 16000000.0

/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFF	// defines HIGH value for a bit

/************************************************************************/
/*						 ERROR_STATUS defines                               */
/************************************************************************/
#define E_OK 0 // OK
#define E_NOK 1 // NOT OK

#define E_NULL_PTR                            -1
#define E_UNINITIALIZED_MODULE                -2
#define E_MULTIPLE_INITIALIZION               -3
#define E_STOP_WITHOUT_START                  -4 
#define E_INVALID_PARAMETER                   -5
#define E_MULTIPLE_START                      -6 
#define E_MULTIPLE_STOP                       -7
#define E_FULL_BUFFER                         -8

#endif /* STD_TYPES_H_ */