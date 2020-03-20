/*
 * SOS.c
 *
 * Created: 24/02/2020 02:56:11 م
 *  Author: TOSHIBA
 */ 
/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "SOS.h"
//#include "SOS_PbCfg.h"


//#include "stdio.h"

/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/			
							
#define SOS_UNINIT       (0)				
#define SOS_INIT         (1)				
#define SOS_BUFFER_EMPTY (0)
#define CONSUMER_START_COUNT (0)
#define SOS_ISR_START_COUNT (0)
#define ZERO                  0	
#define MAX_TIMER_CH_NU       (3)	
#define NULL_ID              256
#define START_SOS_ISR         1
#define STOP_SOS_ISR         0	
#define TCNT_INITIAL_COUNT 6
#define TCNT_NUMBER_OF_COUNT 250
#define CONSUMER_MODE_PROTECTIN 2  
#define ONE                     1
//#define IDLE_TASK_ID      (SOS_DUFFER_MAX_SIZE-ONE)

typedef struct {void (*P_Consumer)(void);
	uint8_t u8_Perudicity ;
	uint8_t u8_ConsumerTime;
	uint8_t u8_ConsumerCount ;
	uint16_t u8_consumerId;
} str_CONSUMER;

	
static str_CONSUMER astr_ConsumerBufferArr[SOS_DUFFER_MAX_SIZE]={0};
static strSOS_Cfg_t strSOS_Control;			
static uint8_t SOS_BufferSize= SOS_BUFFER_EMPTY;
static uint8_t u8_SOS_Status=SOS_UNINIT;
//static uint8_t volatile SOS_ISR_Flag=START_SOS_ISR; 
static volatile uint8_t u8_ISR_Count;

static void SOS_ISR_(void);

 
/*
 * @param: input:  strSOS_Cfg_t  *
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the SOS   
 */
u8_ERROR_STATUS_t SOS_Init (const strSOS_Cfg_t * ConfigPtr )
 {
	
	u8_ERROR_STATUS_t u8_SOS_ErrorStatus=E_OK;
	
	uint8_t u8_BufferIndex = ZERO;
	
	      if (ConfigPtr != NULL)
			 {
				if( u8_SOS_Status==SOS_UNINIT){
			
			
					 strSOS_Control.u8_TimerID = ConfigPtr->u8_TimerID;
					 
					 strSOS_Control.u8_SOS_reslution = ConfigPtr->u8_SOS_reslution;
					 
						 if(strSOS_Control.u8_TimerID < MAX_TIMER_CH_NU )
						 {
			
                         gstrTimerConfig_t SOS_TimerCfg={strSOS_Control.u8_TimerID, TIMER_MODE,TIMER_PRESCALER_64,TIMER_MODE_INT,SOS_ISR_};
	    
		                 Timer_Init(&SOS_TimerCfg);
						 //init the task buffer with initial value 
		 
						while ( u8_BufferIndex< SOS_DUFFER_MAX_SIZE )
						{
					 
						astr_ConsumerBufferArr[u8_BufferIndex].u8_consumerId=NULL_ID ;
						u8_BufferIndex ++;
						 }
	 
						Timer_Start(SOS_TimerCfg.u8_TimerCh,TCNT_NUMBER_OF_COUNT);
           
		                 u8_SOS_Status = SOS_INIT;
						 
						}
		
					else
						u8_SOS_ErrorStatus= ERROR_INVALIDE_PARAMETAR+ MODULE_ERROR_NUMBER  ;
						}
			else 
				u8_SOS_ErrorStatus= ERROR_MULTIPLE_INIT+ MODULE_ERROR_NUMBER  ;
		}
		else 
			u8_SOS_ErrorStatus= ERROR_NULL_PTR+ MODULE_ERROR_NUMBER ;
	 
	return  u8_SOS_ErrorStatus;
	
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

u8_ERROR_STATUS_t SOS_Create_Task( const strSOS_CreatTask_t *  strSOS_CreatTask ){
		u8_ERROR_STATUS_t u8_SOS_ErrorStatus = E_OK;
		
			if (strSOS_CreatTask->consumerPointer!=NULL)
	         {
				 if( u8_SOS_Status==SOS_INIT)
				 { 
					
					if(SOS_BufferSize<(SOS_DUFFER_MAX_SIZE))
					
					{
						 if (strSOS_CreatTask->u8_ConsumerId<SOS_DUFFER_MAX_SIZE)
						 {
						 
						
								   
							if(astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].u8_consumerId == NULL_ID  )
								{
									if(strSOS_CreatTask->u8_consumerMode< CONSUMER_MODE_PROTECTIN)
									{
									   astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].P_Consumer=strSOS_CreatTask->consumerPointer;
								  
									   astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].u8_Perudicity=strSOS_CreatTask->u8_consumerMode;
								   
									   astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].u8_ConsumerTime=(strSOS_CreatTask->u8_consumerTime/strSOS_Control.u8_SOS_reslution);
					
									   astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].u8_ConsumerCount=CONSUMER_START_COUNT;
					   
									   astr_ConsumerBufferArr[strSOS_CreatTask->u8_ConsumerId].u8_consumerId=strSOS_CreatTask->u8_ConsumerId;
									   SOS_BufferSize ++ ;
									 }
									 else 
										u8_SOS_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_INVALIDE_PARAMETAR;
								}
							else 
								u8_SOS_ErrorStatus= MODULE_ERROR_NUMBER+ERROE_EXIST_ID;
							   }
						 else 
							u8_SOS_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_INVALIDE_PARAMETAR;
							  }
					else
						u8_SOS_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_FULL_BUFFER;
						
		
						 }
				else 
					u8_SOS_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
					
			    }
		else
			u8_SOS_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_NULL_PTR ;
		
return u8_SOS_ErrorStatus;
}
/*
 * @param: input:  u8_ConsumerId    : Consumer Id 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Stops consumer     
 */ 
u8_ERROR_STATUS_t SOS_Delete_Task(uint8_t u8_ConsumerId)
{
	u8_ERROR_STATUS_t u8_SOS_ErrorStatus = E_OK;
			
			 
	 if(u8_SOS_Status ==SOS_INIT){
				 
			if ( SOS_BufferSize > ZERO)
				  {
				  if (astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId!=NULL_ID  ){ 
					       
					 astr_ConsumerBufferArr[u8_ConsumerId].u8_consumerId=NULL_ID  ;
					  
					 SOS_BufferSize--;
					  } 
					else  
				u8_SOS_ErrorStatus= MODULE_ERROR_NUMBER+ERROR_ELEMENT_NOT_EXIST;
				}
				
			else
				
				u8_SOS_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_EMPTY_BUFFER ;
			 }
	 else

		 u8_SOS_ErrorStatus=MODULE_ERROR_NUMBER+ERROR_UNILTILZED_MODULE;
			
 return u8_SOS_ErrorStatus;
}

/*
 * @param: input:  None
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 *Description :Determines which consumer to be called    
 */

void SOS_Run(void){
	
	uint8_t u8_ISR_CopyFlag=ZERO;
	uint8_t u8_Tep_BufferIndex=ZERO;
	Sleep_Mode(IDLE);
	

	while(1)
	{
	
		DIS_EN_G_INT();
	    u8_ISR_CopyFlag=u8_ISR_Count;
		u8_ISR_Count=ZERO;
		EN_G_INT();     
		
		u8_Tep_BufferIndex = ZERO;
		
		if ( u8_SOS_Status==SOS_INIT){
			
				
				while (u8_Tep_BufferIndex < SOS_DUFFER_MAX_SIZE ){
					if (astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_consumerId!=NULL_ID  ){
						
						astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount += u8_ISR_CopyFlag;
						
						if((astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount )>= (astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerTime)){
							
							
							astr_ConsumerBufferArr[u8_Tep_BufferIndex].P_Consumer();
							
							if(astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_Perudicity ==  PERUDIC ){
								astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount=CONSUMER_START_COUNT;
							}
							else
							{
								
								//astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_consumerId=NULL_ID  ;
								
							}
						}
						
						else
						{	//IN SOS do nothing
							//astr_ConsumerBufferArr[u8_Tep_BufferIndex].u8_ConsumerCount++;
							
						}
					}
					
					u8_Tep_BufferIndex++;
					
				}	
			EN_Sleep();
				
		}	
	}		
}


/*
* @param: input:None
* @param: output: NONE
* @param :Input/output :None
* @Return : None
* Description : SOS_ISR
*/
static void SOS_ISR_(void)
{
	u8_ISR_Count++;
		
 Timer_SetValue(strSOS_Control.u8_TimerID,TCNT_INITIAL_COUNT);

}
