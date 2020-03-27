/*
 * EXT_Interrupts.h
 *
 * Created: 2020-02-18 1:40:00 PM
 *  Author: EbrahimOseif
 */ 

#ifndef EXT_INTERRUPTS_H_
#define EXT_INTERRUPTS_H_


/************************************************************************/
/*				 INCLUDES										        */
/************************************************************************/


#include "registers.h"
#include "std_types.h"
#include "interrupt.h"
#include "DIO.h"


/************************************************************************/
/*				 DEFINES											      */
/************************************************************************/

#define GLOBAL_INT_EN			0x80
#define INT_CHANNELS_NUMBER		3

#define EXT_INT0				0
#define EXT_INT1				1
#define EXT_INT2				2

#define EXT_INT0_EN				0x40
#define EXT_INT1_EN				0x80
#define EXT_INT2_EN				0x20

#define EXT_INT0_FLAG			0x40
#define EXT_INT1_FLAG			0x80
#define EXT_INT2_FLAG			0x20

#define EXT_INT_EDGE_MODE0		0x00
#define EXT_INT_EDGE_MODE1		0x01
#define EXT_INT_EDGE_MODE2		0x02
#define EXT_INT_EDGE_MODE3		0x03

#define EXT_INT2_EDGE			0x40
#define EXT_INT2_FALLING_EDGE	0
#define EXT_INT2_RISING_EDGE	1


/************************************************************************/
/*		         TIMER FUNCTIONS' PROTOTYPES		                    */
/************************************************************************/

/**
 * Input:  
 * 	EXT_INT_EDGE: The edge that will trigger the EXT INT.
								-EXT_INT2_FALLING_EDGE
								-EXT_INT2_RISING_EDGE
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function set the trigger edge.
 * 							
 */
	ERROR_STATUS EXT_INT_SetEdge(uint8_t EXT_INT_EDGE);

/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output:					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function enables EXT INT channel.
 * 							
 */
	ERROR_STATUS EXT_INT_Enable(uint8_t EXT_INT_CH);
	
	
/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output:					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function disables EXT INT channel.
 * 							
 */
	ERROR_STATUS EXT_INT_Disable(uint8_t  EXT_INT_CH);
	
/**
 * Input:  
 * 	EXT_INT_CH: The EXT INT Channel 
							-EXT_INT0
							-EXT_INT1
							-EXT_INT2
 * Output: state- state of the EXT INT flag					 
 * In/Out:					 
 * Return: The error status of the function.			
 * Description: This function disables EXT INT channel.
 * 							
 */	
	
	ERROR_STATUS EXT_INT_isTriggered(uint8_t EXT_INT_CH, uint8_t* state);


#endif /* EXT_INTERRUPTS_H_ */