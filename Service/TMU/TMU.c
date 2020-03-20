/*
 * TMU.c
 *
 * Created: 24/02/2020 02:56:11 م
 *  Author: TOSHIBA
 */ 
/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "TMU.h"
//#include "TMU_PbCfg.h"


#include "stdio.h"

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/			
							
#define TUM_UNINIT       (0)				
#define TMU_INIT         (1)				
#define TUM_BUFFER_EMPTY (0)
#define CONSUMER_START_COUNT (1)
#define TMU_ISR_START_COUNT (1)
#define ZERO                  0	
#define MAX_TIMER_CH_NU       (3)	
#define NULL_ID              256
#define START_TMU_ISR         1
#define STOP_TMU_ISR         0	
#define TCNT_INITIAL_COUNT 6
#define TCNT_NUMBER_OF_COUNT 250
#define CONSUMER_MODE_PROTECTIN 2  
#define ONE                     1
typedef struct {void (*P_Consumer)(void);
	uint8_t u8_Perudicity ;
	uint8_t u8_ConsumerTime;
	uint8_t u8_ConsumerCount ;
	uint16_t u8_consumerId;
} str_CONSUMER;
	
	
static str_CONSUMER astr_ConsumerBufferArr[TMU_DUFFER_MAX_SIZE]={0};
static strTMU_Cfg_t strTMU_Control;			
static uint8_t TMU_BufferSize= TUM_BUFFER_EMPTY;
static uint8_t u8_TMU_Status=TUM_UNINIT;
static uint8_t volatile TMU_ISR_Flag=START_TMU_ISR; 

static void TMU_ISR_(void);
 
/*
 * @param: input:  strTMU_Cfg_t  *
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the TMU   
 */
u8_ERROR_STATUS_t TMU_Init (const strTMU_Cfg_t * ConfigPtr )
 {
	
	u8_ERROR_STATUS_t u8_TUM_ErrorStatus=E_OK;
	
	uint8_t u8_BufferIndex = ZERO;
	
	      if (ConfigPtr != NULL)
			 {
				if( u8_TMU_Status==TUM_UNINIT){
			
					 strTMU_Control.u8_TimerID = ConfigPtr->u8_TimerID;
					 
					 strTMU_Control.u8_TMU_reslution = ConfigPtr->u8_TMU_reslution;
					 
						 if(strTMU_Control.u8_TimerID < MAX_TIMER_CH_NU )
						 {
			
                         gstrTimerConfig_t TMU_TimerCfg={strTMU_Control.u8_TimerID, TIMER_MODE,TIMER_PRESCALER_64,TIMER_MODE_INT,TMU_ISR_};
	    
		                 Timer_Init(&TMU_TimerCfg);
		 
						while ( u8_BufferIndex< TMU_DUFFER_MAX_SIZE )
						{
					 
						astr_ConsumerBufferArr[u8_BufferIndex].u8_consumerId=NULL_ID ;
						u8_BufferIndex ++;
						 }
	 
						Timer_Start(TMU_TimerCfg.u8_TimerCh,TCNT_NUMBER_OF_COUNT);
           
		                 u8_TMU_Status = TMU_INIT;
						 
						}
		
					else
						u8_TUM_ErrorStatus= ERROR_INVALIDE_PARAMETAR+ MODULE_ERROR_NUMBER  ;
						}
			else 
				u8_TUM_ErrorStatus= ERROR_MULTIPLE_INIT+ MODULE_ERROR_NUMBER  ;
		}
		else 
			u8_TUM_ErrorStatus= ERROR_NULL_PTR+ MODULE_ERROR_NUMBER ;
	 
	return  u8_TUM_ErrorStatus;
	
	}
/*
 * @param: input:  u8_consumerTime  :Delay Time 
 * @param: input:  u8_consumerMode  : Consumer Mode that takes one of (ONE_SHOT,PERIODIC)
 * @param: input:  u8_ConsumerId    : Consumer Id 
 * @param: input:  void(*consumerPointer)(void) : Pointer to function 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Creates consumer with predetermined time    
 */

u8_ERROR_STATUS_t TMU_Start_Timer(uint8_t u8_consumerTime ,uint8_t u8_consumerMode,uint8_t u8_ConsumerId,void(*consumerPointer)(void) ){
		u8_ERROR_STATUS_t u8_TUM_ErrorStatus = E_OK;
		
			if (consumerPointer!=NULL)
	         {
				 if( u8_TMU_Status==TMU_INIT)
				 { 
					
					if(TMU_BufferSize<(TMU_DUFFER_MAX_SIZE))
					
					{
						 if (u8_ConsumerId<TMU_DUFFER_MAX_SIZE)
						 {
						 
						
								   
							if(astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId == NULL_ID  )
								{
									if(u8_consumerMode< CONSUMER_MODE_PROTECTIN)
									{
									   astr_ConsumerBufferArr[u8_ConsumerId].P_Consumer=consumerPointer;
								  
									   astr_ConsumerBufferArr[u8_ConsumerId].u8_Perudicity=u8_consumerMode;
								   
									   astr_ConsumerBufferArr[u8_ConsumerId].u8_ConsumerTime=(u8_consumerTime/strTMU_Control.u8_TMU_reslution);
					
									   astr_ConsumerBufferArr[u8_ConsumerId].u8_ConsumerCount=CONSUMER_START_COUNT;
					   
									   astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId=u8_ConsumerId;
									   TMU_BufferSize ++ ;
									 }
									 else 
										u8_TUM_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_INVALIDE_PARAMETAR;
								}
							else 
								u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROE_EXIST_ID;
							   }
						 else 
							u8_TUM_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_INVALIDE_PARAMETAR;
							  }
					else
						u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_FULL_BUFFER;
						
		
						 }
				else 
					u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
					
			    }
		else
			u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_NULL_PTR ;
		
return u8_TUM_ErrorStatus;
}
/*
 * @param: input:  u8_ConsumerId    : Consumer Id 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Stops consumer     
 */
u8_ERROR_STATUS_t TMU_Stop_Timer(uint8_t u8_ConsumerId)
{
	u8_ERROR_STATUS_t u8_TUM_ErrorStatus = E_OK;
			
			 
	 if(u8_TMU_Status ==TMU_INIT){
				 
			if ( TMU_BufferSize > ZERO)
				  {
				  if (astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId!=NULL_ID  ){ 
					       
					 astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId=NULL_ID  ;
					  
					 TMU_BufferSize--;
					  } 
					else  
				u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_ELEMENT_NOT_EXIST;
				}
				
			else
				
				u8_TUM_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_EMPTY_BUFFER ;
			 }
	 else

		 u8_TUM_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
			
 return u8_TUM_ErrorStatus;
}

/*
 * @param: input:  None
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 *Description :Determines which consumer to be called    
 */

u8_ERROR_STATUS_t TMU_Dispatcher(void){
	 	
 u8_ERROR_STATUS_t u8_TUM_ErrorStatus = E_OK;
		 
 uint8_t u8_Tep_BufferIndex = ZERO;
		
	if ( u8_TMU_Status==TMU_INIT){
	 	
		if( TMU_ISR_Flag ==START_TMU_ISR){
		
			TMU_ISR_Flag=STOP_TMU_ISR;
		
				while (u8_Tep_BufferIndex < TMU_DUFFER_MAX_SIZE ){

						if (astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_consumerId!=NULL_ID  ){
					
							if((astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount )== (astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerTime)){
				
				
								astr_ConsumerBufferArr[u8_Tep_BufferIndex].P_Consumer();
	
									if(astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_Perudicity ==  PERUDIC ){
										astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount=CONSUMER_START_COUNT;
											}
									else
									{
		
										 astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_consumerId=NULL_ID  ;
		
									}
								}
			
 							else
							{
								astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount++;
				
							}
						}
			
 				u8_Tep_BufferIndex++;
 			
				}	
			
		}
			
	}
	else
		u8_TUM_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
		
return u8_TUM_ErrorStatus;
		
	}
/*
 * @param: input:None
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  De_initializes the TMU   
 */
u8_ERROR_STATUS_t TMU_DeInit ( void ) {
	
	u8_ERROR_STATUS_t u8_TUM_ErrorStatus = E_OK;

	  if ( u8_TMU_Status==TMU_INIT)
	  {
		   
		   u8_TMU_Status = TUM_UNINIT;
		 
		  Timer_Stop(strTMU_Control.u8_TimerID);
		 }
	  
	u8_TUM_ErrorStatus=  MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
	
	return u8_TUM_ErrorStatus;
}
/*
* @param: input:None
* @param: output: NONE
* @param :Input/output :None
* @Return : None
* Description :  TMU_ISR
*/
static void TMU_ISR_(void){
	
static volatile uint8_t u8_ISR_Count=TMU_ISR_START_COUNT;
			
if(u8_ISR_Count==strTMU_Control.u8_TMU_reslution){
				
	TMU_ISR_Flag=START_TMU_ISR;
	
	u8_ISR_Count=TMU_ISR_START_COUNT;

           }
		   
else 
	u8_ISR_Count++;
		
 Timer_SetValue(strTMU_Control.u8_TimerID,TCNT_INITIAL_COUNT);

}