/*
 * pushButton.c
 *
 * Created: 18/01/2020 09:04:38 ص
 *  Author: TOSHIBA
 */ 
#include "pushButton.h"

#define BOUNCING_TIMEiNm				40
#define INIT						 	0
#define UNINT							-1
#define START_DELAY						0
#define MAX_PPRESEED_INDECATOR_NUMBER	25

/*		 pushButtonGetStatus state		  */ 

#define IDLE_SATE			0
#define BTN_COUNT_STATE		1
#define BTN_DECISON_STATE	2
#define FINSH_STATE			3

typedef struct {
	uint8_t u8_BTN_Port;
	uint8_t u8_BTN_Pin;
	sint8_t s8_BTN_Status;
	uint8_t u8_BTN_DelayCount;
	}str_BTN_Cfg_t;
	
	
static 	str_BTN_Cfg_t astr_BTN_Cfg[BTN_MAX_NUM]; 
static uint8_t u8_BTN_CfgInitFlag;


u8_ERROR_STATUS_t pushButtonInit(uint8_t en_butotn_id){
	u8_ERROR_STATUS_t u8_BTN_Error = E_OK;
	if(en_butotn_id>BTN_MAX_NUM || en_butotn_id<BTN_0){
	//	error invalid arrgement
	}
	else
	 {
		if(u8_BTN_CfgInitFlag==0)
		{
			uint8_t u8_BTN_CfgInitCount=0;
			astr_BTN_Cfg[BTN_0].u8_BTN_Port = BTN_0_GPIO;
			astr_BTN_Cfg[BTN_0].u8_BTN_Pin  = BTN_0_BIT;
			
			astr_BTN_Cfg[BTN_1].u8_BTN_Port = BTN_1_GPIO;
			astr_BTN_Cfg[BTN_1].u8_BTN_Pin  = BTN_1_BIT;
			
			for(;u8_BTN_CfgInitCount<BTN_MAX_NUM;u8_BTN_CfgInitCount++)
			{
				astr_BTN_Cfg[u8_BTN_CfgInitCount].s8_BTN_Status = UNINT ;
				astr_BTN_Cfg[u8_BTN_CfgInitCount].u8_BTN_DelayCount= 0;
			}
			u8_BTN_CfgInitFlag = 1;
		}
		if(astr_BTN_Cfg[en_butotn_id].s8_BTN_Status >= INIT)
		{
			//error multiple init
		}
		else
		{
			gstr_DIO_Cfg_t str_BTN_0_Cfg={astr_BTN_Cfg[en_butotn_id].u8_BTN_Port,astr_BTN_Cfg[en_butotn_id].u8_BTN_Pin,INPUT};
			DIO_init(&str_BTN_0_Cfg);
			astr_BTN_Cfg[en_butotn_id].s8_BTN_Status = INIT;
		}
			
	}
		return u8_BTN_Error;
}

u8_ERROR_STATUS_t pushButtonGetStatus(uint8_t en_butotn_id,uint8_t * staut_flag){
	u8_ERROR_STATUS_t u8_BTN_ErrorStatus = E_OK;
	
	uint8_t u8_BTN_Read=0;
	static uint8_t u8_BTN_GetStatusState=IDLE_SATE;
	if(staut_flag==NULL){
		//error NULLPOINTER
	}
	else
	{
		if(astr_BTN_Cfg[en_butotn_id].s8_BTN_Status <= UNINT)
		{
			//error uninit
		}
		else {
			
			* staut_flag = Released;
			
			switch(u8_BTN_GetStatusState)
			{
				
				case IDLE_SATE:
								

					DIO_Read(astr_BTN_Cfg[en_butotn_id].u8_BTN_Port,astr_BTN_Cfg[en_butotn_id].u8_BTN_Pin,&u8_BTN_Read);
				
					// check if Button is pressed 
					if(u8_BTN_Read == astr_BTN_Cfg[en_butotn_id].u8_BTN_Pin)
					{
						astr_BTN_Cfg[en_butotn_id].s8_BTN_Status = Pressed;
						u8_BTN_GetStatusState = BTN_COUNT_STATE;
					}
					else 
					{
						u8_BTN_ErrorStatus = BTN_READ_DONE;
					}
				
				/* Provide debouncing delay */
				
				case BTN_COUNT_STATE:;
				
				
				/*		Matching  debouncing delay		*/
				
				if(astr_BTN_Cfg[en_butotn_id].u8_BTN_DelayCount==BOUNCING_TIMEiNm)
				{
					astr_BTN_Cfg[en_butotn_id].u8_BTN_DelayCount = START_DELAY; 
					u8_BTN_GetStatusState = BTN_DECISON_STATE;
				}
				
				/*			Counting debouncing delay			 */
				else
				{														

					DIO_Read(astr_BTN_Cfg[en_butotn_id].u8_BTN_Port,astr_BTN_Cfg[en_butotn_id].u8_BTN_Pin,&u8_BTN_Read);
					
					if(u8_BTN_Read == astr_BTN_Cfg[en_butotn_id].u8_BTN_Pin)
					{
						astr_BTN_Cfg[en_butotn_id].s8_BTN_Status ++; 	
					}
					
					astr_BTN_Cfg[en_butotn_id].u8_BTN_DelayCount++;
				}
				
				break;
				
				/* Decide if the button is pressed or not and reset the state to the idle state    */
				
				case BTN_DECISON_STATE:
				
				if(astr_BTN_Cfg[en_butotn_id].s8_BTN_Status >= MAX_PPRESEED_INDECATOR_NUMBER) 
				{
					*staut_flag = Pressed;
				}
				astr_BTN_Cfg[en_butotn_id].s8_BTN_Status = Released;
				astr_BTN_Cfg[en_butotn_id].u8_BTN_DelayCount=START_DELAY;
				u8_BTN_ErrorStatus = BTN_READ_DONE;
				u8_BTN_GetStatusState = IDLE_SATE ;
				
				break;

				default:
				break;
			}
		}
		
	}
	
	
		
	return u8_BTN_ErrorStatus ;
}
