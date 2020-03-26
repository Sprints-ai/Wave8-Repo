/*
 * Errors.h
 *
 * Created: 2/25/2020 10:40:12 AM
 *  Author: ahmed
 */


#ifndef ERRORS_H_
#define ERRORS_H_

/***********************************************/
/***************** MODULE NUBERS *****************/
/***********************************************/

#define SOS_MODULE 1
#define BCM_MODULE 2
#define TIMER_MODULE 3
/*
*** ERRORS NUBERS
*/
/*BCM*/
#define NO_ERROR                          0
#define ERROR_NULL_POINTER					   1
#define ERROR_INVALID_PARAMETER				2
#define  ERROR_BCM_NOT_INITIALIZED	      14
#define ERROR_BCM_ALREADY_INITIALIZED	   13
/*TMU*/
#define ERROR_STOP_WITHOUT_START			   5
#define ERROR_MULTIPLE_START				   6
#define ERROR_FULL_BUFFER					   7
#define ERROR_NOT_FULL_BUFFER				   8
#define ERROR_EMPTY_BUFFER					   9
#define ERROR_NOT_EMPTY_BUFFER			   10
#define  ERROR_SOS_NOT_INITIALIZED	      11
#define ERROR_SOS_ALREADY_INITIALIZED		12
#define ERROR_SOS_DELETING_BEFORE_CREATING        4
#define ERROR_TIMER_NOT_INITIALIZED  3


#endif /* ERRORS_H_ */
