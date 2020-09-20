/*
 * SOS.h
 *
 * Created: 3/11/2020 10:54:33 AM
 *  Author: MENA
 */ 


#ifndef SOS_H_
#define SOS_H_




/************************************************************************/
/*							 INCLUDES							        */
/************************************************************************/

#include "std_types.h"
#include "registers.h"


/************************************************************************/
/*							 DEFINES							        */
/************************************************************************/

#define PERIODIC 0 
#define  ONESHOT 1

#define SOS_TIMER_CH0 0
#define SOS_TIMER_CH1 1
#define SOS_TIMER_CH2 2


#define SOS_BUFFER_SIZE 100


#define reselution_one_mili 1


/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/

typedef struct SOS_Cfg_s{
	
	uint8_t Timer_channel ;
	uint8_t SOS_Reselution ;
	
	
	}SOS_Cfg_s;
	
	
typedef struct SOS_tsak_s{
	
	uint8_t Task_ID;
	void (* Ptr_FunctionCall)(void) ; 
	uint16_t delay_time ;
	uint8_t SOS_mode ;/* periodic or one shot*/
	uint16_t N_OVFs ;
	uint8_t Priority ;
	
	}SOS_tsak_s;
	
	




/************************************************************************/
/*				    SOS FUNCTIONS' PROTOTYPES				        */
/************************************************************************/


/**
 * Input: Pointer to a structure contains the information needed to initialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */


ERROR_STATUS SOS_Init (SOS_Cfg_s *SOS_Cfg);




/**
 * Input: Pointer to a structure contains the information needed to deinitialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: DeInitiates the module.
 * 							
 */


ERROR_STATUS SOS_DeInit (SOS_Cfg_s *SOS_Cfg);


/**
 * Input: Pointer to a structure contains the information needed to start the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: start the module.
 * 							
 */


ERROR_STATUS SOS_Create_Task (SOS_tsak_s *SOS_task);


/**
 * Input: Pointer to a structure contains the information needed to stop the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: stop the module.
 * 							
 */


ERROR_STATUS SOS_Remove_Task (SOS_tsak_s *SOS_task);


/**
 * Input: void. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Run the basic logic code to calculate the timing
 * and call the user function depends on the timeout event for each software timer object.
 * 							
 */


ERROR_STATUS SOS_Run (void);




#endif /* SOS_H_ */