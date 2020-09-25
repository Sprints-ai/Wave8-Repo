/*
 * std_types.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/************************************************************************/
/*				 		Important values 		                        */
/************************************************************************/

#define NULL	((void *)0)
#define ZERO	(0)

/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/

#define FALSE 	0	/* defines boolean false */
#define TRUE 	1	/* defines boolean true  */


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

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



#endif /* STD_TYPES_H_ */