/*
 * ARM_STD_t.h
 *
 * Created: 4/3/2020 2:23:35 PM
 *  Author: A_ayman
 */ 


#ifndef ARM_STD_T_H_
#define ARM_STD_T_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef signed char sint8_t;
typedef signed int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;
typedef volatile uint32_t* const reg_type32_t;
typedef unsigned char ERROR_STATUS ;


/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFFFFFFFF	// defines HIGH value for a bit

#define ZERO 0
#define ONE 1



#define E_OK 0
#define E_NOK 1


#endif /* ARM_STD_T_H_ */
