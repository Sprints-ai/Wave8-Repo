#ifndef STD_TYPES_H_
#define STD_TYPES_H_

//#include "registers.h"
#include "common_macros.h"


#define NULL	((void *)0)

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64_t;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8* const reg_type8_t;
typedef volatile uint16* const reg_type16_t;

#define bool uint8
#define ERROR_STATUS signed char


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

#define ZERO 0
#define ONE 1
#define E_OK 1
#define E_NOK 0
#define NULL_PTR_ERROR -1
#define INVALID_ARGUMENT -2

#endif
