/*
 * SOS.c
 *
 * Created: 3/11/2020 10:48:50 AM
 *  Author: MENA
 */ 




#include "Timer.h"
#include "SOS.h"




static void ISR_flag_func(void);
static void Remove_task(SOS_tsak_s *SOS_task);




static uint8_t g_u8_timer_CH ;
static uint8_t g_u8_SOS_reselution ;

static SOS_tsak_s *Buffer[SOS_BUFFER_SIZE] = { NULL };

static uint8_t g_u8_NO_ELEMNT_BUFFER = ZERO_VALUE ;

static uint8_t g_u8_ISR_flag = FALSE ;
static uint8_t g_u8_SOS_initialzation = FALSE ;
static uint8_t g_u8_first_call_start = FALSE ;





void sort() {

	/* Sort the given array number, of length n */
	SOS_tsak_s * temp ;
	uint8_t au8_iterator_j , au8_iterator_i, au8_iterator_x , au8_iterator_y;

	for ( au8_iterator_x = 0 ;  au8_iterator_x < SOS_BUFFER_SIZE  ; au8_iterator_x++){

		if(Buffer[au8_iterator_x]==NULL){
			au8_iterator_y = au8_iterator_x ;
			au8_iterator_y++ ;
			while(Buffer[au8_iterator_y]==NULL ) {
				au8_iterator_y++;
				if(au8_iterator_y==SOS_BUFFER_SIZE){
					au8_iterator_x = SOS_BUFFER_SIZE;
					break ;
				}
				
			}
			Buffer[au8_iterator_x] = Buffer[au8_iterator_y] ;
			Buffer[au8_iterator_y] = NULL ;
		}
	}
	

	for (au8_iterator_i = 1; au8_iterator_i < SOS_BUFFER_SIZE -1; au8_iterator_i++) {

		for (au8_iterator_j = 0 ; au8_iterator_j < SOS_BUFFER_SIZE - au8_iterator_i; au8_iterator_j++) {

			if(Buffer[au8_iterator_j] == NULL || Buffer[au8_iterator_j+1] == NULL)
			break ;
			else if (Buffer[au8_iterator_j]->Priority > Buffer[au8_iterator_j + 1]->Priority) {
				
				temp = Buffer[au8_iterator_j];
				Buffer[au8_iterator_j] = Buffer[au8_iterator_j + 1];
				Buffer[au8_iterator_j + 1] = temp;
			}
		}
	}
	
	
}





/**
 * Input: Pointer to a structure contains the information needed to initialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 */


ERROR_STATUS SOS_Init (SOS_Cfg_s *SOS_Cfg){
	
	
	if (SOS_Cfg == NULL)
		return SOS_module_error +NULL_PTR_ERROR ;
	
	/* check if the module is initialized before */
	
	
	if (g_u8_SOS_initialzation== FALSE )
		g_u8_SOS_initialzation = TRUE ;
	else
		return SOS_module_error + MULTIPLE_INITIALIZATION ;
	
	Timer_cfg_s timer_SOS_cfg ;
	g_u8_timer_CH = SOS_Cfg->Timer_channel;
	
	
	/* check for available range of resolution */
	
	if (SOS_Cfg->SOS_Reselution<1 || SOS_Cfg->SOS_Reselution>17)
	{
		return SOS_module_error + INVALID__PARAMETER ;
	}
	
	/* set resolution to global to be used in start function */
	
	g_u8_SOS_reselution = SOS_Cfg->SOS_Reselution ;
	
	/*		 switch on timer channel		*/
	
	switch(SOS_Cfg->Timer_channel){
		
		case SOS_TIMER_CH0 :
		
			timer_SOS_cfg.Timer_CH_NO = SOS_TIMER_CH0;
			timer_SOS_cfg.Timer_Mode = TIMER_MODE ;
			timer_SOS_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_SOS_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_SOS_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_SOS_cfg);
			
		
			break;
		case SOS_TIMER_CH1 :
		
			timer_SOS_cfg.Timer_CH_NO = SOS_TIMER_CH1;
			timer_SOS_cfg.Timer_Mode = TIMER_MODE ;
			timer_SOS_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_SOS_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_SOS_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_SOS_cfg);
		
			break;
		case SOS_TIMER_CH2 :
			timer_SOS_cfg.Timer_CH_NO = SOS_TIMER_CH2;
			timer_SOS_cfg.Timer_Mode = TIMER_MODE ;
			timer_SOS_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
			timer_SOS_cfg.Timer_Prescaler = TIMER_PRESCALER_64;
			timer_SOS_cfg.Timer_Cbk_ptr = ISR_flag_func ;
			
			/*		initialize timer		 */
			
			Timer_Init(&timer_SOS_cfg);
		
			break;
		default:
		/*  invalid timer channel */
		
			return SOS_module_error + INVALID__PARAMETER ;
		break;
		
	}
	
	return E_OK ;
}



/**
 * Input: Pointer to a structure contains the information needed to de-initialize the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: DeInitiates the module.
 * 							
 */


ERROR_STATUS SOS_DeInit (SOS_Cfg_s *SOS_Cfg){
	
	/* check for null pointer error */
	if (SOS_Cfg == NULL)
	return SOS_module_error +NULL_PTR_ERROR ;
	
	
	/* check if the SOS initialized before de-init or not */
	if (g_u8_SOS_initialzation!= TRUE)
	{
		return SOS_module_error + DEINIT_WITHOUT_INIT ;
	}
	/*stop timer */
	
	Timer_Stop(g_u8_timer_CH);
	
	/*free all the buffer */
	
	return E_OK ;
}



/**
 * Input: Pointer to a structure contains the information needed to start the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: start the module.
 * 							
 */


ERROR_STATUS SOS_Create_Task (SOS_tsak_s *SOS_task){
	
	uint8_t count ;
	
	/* check for null pointer error */
	
	if (SOS_task == NULL)
		return SOS_module_error +NULL_PTR_ERROR ;
	
	if (SOS_task->Ptr_FunctionCall == NULL)
		return SOS_module_error +NULL_PTR_ERROR ;
	
	/*check if the buffer is full */
	
	if (SOS_task->SOS_mode!=PERIODIC && SOS_task->SOS_mode!=ONESHOT)
		return SOS_module_error + INVALID__PARAMETER ;
	
	/* set the user struct in the internal struct   */
		
	SOS_task-> N_OVFs = SOS_task-> delay_time ;
		
	if (g_u8_NO_ELEMNT_BUFFER<SOS_BUFFER_SIZE)
	{	
		for( count = ZERO_VALUE ; count < SOS_BUFFER_SIZE ; count++)
		{
		if (Buffer[count] == NULL)
		{
			/*		 set struct in buffer		 */
			
			Buffer[count] = SOS_task ;
			
			
			/* increment the no of element in the buffer */
			
			g_u8_NO_ELEMNT_BUFFER++;
			break;
			
		}
		}
		
		if (g_u8_first_call_start == FALSE )
		{
			Timer_Start(g_u8_timer_CH ,250);
			
			g_u8_first_call_start++;
			
		}
	}else
	
	
		return SOS_module_error + FULL_BUFFER ;
		
	sort() ;
	
	return E_OK ;
	
}



/**
 * Input: Pointer to a structure contains the information needed to stop the SOS. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: stop the module.
 * 							
 */



ERROR_STATUS SOS_Remove_Task (SOS_tsak_s *SOS_task){

	if (g_u8_first_call_start!=1)
	{
		return STOP_WITHOU_SART + SOS_module_error ;
	}
	
	Remove_task(SOS_task);
	
	return E_OK ;
	
}







void Remove_task(SOS_tsak_s *SOS_task){
	
		uint8_t count ;
		
		for (count = ZERO_VALUE ; count<SOS_BUFFER_SIZE ; count++)
		{
			if (Buffer[count]!=NULL&& SOS_task->Task_ID==Buffer[count]->Task_ID)
			{
				Buffer[count] = NULL ;
			}
		}
	
}



/**
 * Input: void. 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Run the basic logic code to calculate the timing
 * and call the user function depends on the timeout event for each software timer object.
 * 							
 */


ERROR_STATUS SOS_Run (void){
	uint8_t count ;
	
	
	if (g_u8_ISR_flag == TRUE)
	{
		
		
 		for (count = ZERO_VALUE ; count<SOS_BUFFER_SIZE ; count++)
 		{
			
			 
  			if (Buffer[count]!=NULL)
  			{
 				
  				Buffer[count] ->N_OVFs-- ;
  				if ( Buffer[count] ->N_OVFs == ZERO_VALUE)
  				{
 						 
  					Buffer[count]-> Ptr_FunctionCall();
 			
  					if (Buffer[count]->SOS_mode == ONESHOT)
 					 Buffer[count] = NULL ;
  					else 
  					Buffer[count]->N_OVFs=Buffer[count]->delay_time ;
  					
  					
  				}
  			}
 		}
		g_u8_ISR_flag = FALSE ;
	}
	return E_OK ;
	
}


 void ISR_flag_func(void){
//	counter++
// if counter == 50 { 
	g_u8_ISR_flag = TRUE ;
//}	
	
}