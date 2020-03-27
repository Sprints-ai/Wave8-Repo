/*
 * std_types.h
 *
 *  *  Author: EbrahimOseif
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL		((void *)0)
#define	ZERO		0
#define NULL_CHAR	'\0'
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;


typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;


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
/*						Function Status Macros                          */
/************************************************************************/
typedef sint8_t ERROR_STATUS;
#define E_OK	1
#define E_NOK	0
/************************************************************************/
/*				 HELP MACROS                               */
/************************************************************************/

#define GetBit(Reg, BitNo)      ( (Reg >> BitNo) & 1   )
#define ClearBit(Reg, BitNo)    (  Reg &= ~ (1<<BitNo) )
#define SetBit(Reg, BitNo)      (  Reg |=   (1<<BitNo) )
#define ToggelBit(Reg, BitNo)   (  Reg ^=   (1<<BitNo) )


#endif /* STD_TYPES_H_ */