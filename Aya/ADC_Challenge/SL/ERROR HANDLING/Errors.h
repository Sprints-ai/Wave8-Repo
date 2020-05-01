/*
 * Error.h
 *
 * Created: 3/26/2020 2:57:24 PM
 *  Author: A_ayman
 */ 


#ifndef ERROR_H_
#define ERROR_H_


/*
*** Module Number
*/ 

#define ADC_MODULE 0



/*
*** Error Types
*/


#define NO_ERROR                               0
#define ERROR_INVALID_CHANNEL_PARAMETER		  1
#define ERROR_INVALID_SAMPLE_SEQUENCER			  2 
#define ERROR_INVALID_INPUT_SOURCE             3 
#define ERROR_INVALID_MUX_VALUE	       	     4
#define ERROR_NOT_INITIALIZED		              5
#define ERROR_ALREADY_INITIALIZED	           6
#define ERROR_READ_WITHOUT_INITIALIZATION		  7
 #define ERROR_INVALID_MODULE_NUMBER           8
#define ERROR_CHANNEL_NOT_INITIALIZED		     9 
#define ERROR_NULL_POINTER                     10


#endif /* ERROR_H_ */

