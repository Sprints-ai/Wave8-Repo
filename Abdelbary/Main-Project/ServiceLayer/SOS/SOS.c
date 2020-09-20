/*
 * SOS.c
 *
 * Created: 2/24/2020 11:50:29 AM
 *  Author: mahmo
 */ 

#include "SOS.h"

#define TAKEN				1
#define NO_TASKS -1
typedef struct SOS_obj_str
{
	/*object to hold data to the call back functions to call periodically*/
	uint8_t Id;
	void (*callB_fun)(void);
	uint8_t fire_tick;
	uint8_t current_ticks;
	uint8_t priority;
	uint8_t type;  /*periodic or one shot*/
	
}gstr_SOS_obj;

STATIC uint8_t SOS_Init_flag = FALSE;
STATIC uint8_t SOS_Timer_ch;
STATIC gstr_SOS_obj gastr_SOS_ObjBuffer[SOS_OBJ_BUFFER_SIZE];
STATIC sint8_t u8_SOS_objBufferHead = ZERO-ONE;
STATIC uint8_t taken_Ids[SOS_OBJ_BUFFER_SIZE+ONE]; /*mark taken ids*/

ERROR_STATUS SOS_Init(gstr_SOS_cfg_t * SOS_cfg)
{
	sint16_t fun_error_status = OK;
	if(SOS_Init_flag || SOS_cfg == NULL || SOS_cfg->tick_reslution > SOS_MAX_TIMER_RESLUTION || SOS_cfg->timer_ch > SOS_TIMER_CH2 ) /*check for all errors*/
	{
		/************************************************************************ 
		 *	-module initialized before                          
		 *	-input validation.                                 
		 ************************************************************************/
		if (SOS_Init_flag)
		{
			fun_error_status = (SOS_MODULE_ERROR_NUM+MULTIPLE_INITALIZATION);
		}
		else if (SOS_cfg == NULL)
		{
			fun_error_status = (SOS_MODULE_ERROR_NUM+NULL_PTR_ERROR);
		}
		else if (SOS_cfg->tick_reslution > SOS_MAX_TIMER_RESLUTION 
				|| SOS_cfg->timer_ch > SOS_TIMER_CH2)
		{
			fun_error_status = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
		}
	}
	else
	{
		SOS_Init_flag = TRUE;
		SOS_Timer_ch = SOS_cfg->timer_ch;
		Timer_cfg_s timer_cfg;
		switch(SOS_cfg->timer_ch)
		{
			case SOS_TIMER_CH0:
				timer_cfg.Timer_CH_NO = TIMER_CH0;
				timer_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
				timer_cfg.Timer_Prescaler = TIMER_PRESCALER_256;
			break;
			case SOS_TIMER_CH1:
				timer_cfg.Timer_CH_NO = TIMER_CH1;
				timer_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
				timer_cfg.Timer_Prescaler = TIMER_PRESCALER_256;
			break;
			case SOS_TIMER_CH2:
				timer_cfg.Timer_CH_NO = TIMER_CH2;
				timer_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
				timer_cfg.Timer_Prescaler = TIMER_PRESCALER_256;
			break;
		}
		Timer_Init(&timer_cfg);
	}
	return fun_error_status;
}
ERROR_STATUS SOS_createTask(uint8_t Id,void (*callB_fun_ptr)(void),uint8_t lap_time,uint8_t type,uint8_t periority)
{
	sint16_t s16_fun_error_status = OK;
	/*lot of condition but it centralize error checking*/
	if(Id > SOS_OBJ_BUFFER_SIZE || callB_fun_ptr == NULL || lap_time > SOS_MAX_LAP_TIME
	|| type > ON_SHOT || SOS_Init_flag == FALSE || taken_Ids[Id] == TAKEN
	|| (lap_time%(SOS_linkCfg.tick_reslution)) != ZERO /*lap_time not multiple of reslution*/
	|| u8_SOS_objBufferHead ==(SOS_OBJ_BUFFER_SIZE-ONE) )
	{
		if ( SOS_Init_flag == FALSE)/*module unintalized*/
		{
			s16_fun_error_status = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
		}
		else if (callB_fun_ptr == NULL)
		{
			s16_fun_error_status = (SOS_MODULE_ERROR_NUM+NULL_PTR_ERROR);
		}
		else if(Id > SOS_OBJ_BUFFER_SIZE  ||taken_Ids[Id]  == TAKEN
		|| type > ON_SHOT  || lap_time > SOS_MAX_LAP_TIME
		|| (lap_time%(SOS_linkCfg.tick_reslution))
		|| u8_SOS_objBufferHead ==(SOS_OBJ_BUFFER_SIZE-ONE))/*invalid parameter*/
		{
			s16_fun_error_status = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
		}
		
	}
	else
	{
		STATIC uint8_t fun_frstTime_flag = FALSE;
		uint8_t u8_tempCounter = ZERO;
		/*check for first time entrance to start timer*/
		if(!fun_frstTime_flag)
		{
			/*start timer*/
			
			Timer_Start(SOS_Timer_ch,TIMER0_1MS_PRESCALER256);
			
			fun_frstTime_flag = TRUE;
		}
		
		/*
		*	1-get lap time eq
		*	2-setup new task struct
		*	3-load it in place correspond to its priority
		*
		*/
		/*set how many resolution time it takes to fire event*/
		lap_time = (lap_time/(SOS_linkCfg.tick_reslution));
		
		/*SOS_obj_str {id,callBack fun , ticks ,current_ticks,type[periodic,onshot]} */
		gstr_SOS_obj tobj  = {Id,callB_fun_ptr,lap_time,ZERO,periority,type};
		
		/*if there is no tasks put task in first pos*/
		if(u8_SOS_objBufferHead == NO_TASKS)
		{
			u8_SOS_objBufferHead++; /*increase buffer head to next empty position*/
			gastr_SOS_ObjBuffer[u8_SOS_objBufferHead] = tobj;
		}
		else
		{
			for (;u8_tempCounter <= u8_SOS_objBufferHead ; u8_tempCounter++)
			{
				if (gastr_SOS_ObjBuffer[u8_tempCounter].priority >= periority)
				{
					uint8_t u8_shiftCounter = (u8_SOS_objBufferHead + ONE);
					while(u8_shiftCounter > u8_tempCounter)
					{
						gastr_SOS_ObjBuffer[u8_shiftCounter] = gastr_SOS_ObjBuffer[(u8_shiftCounter-ONE)];
						u8_shiftCounter--;
					}
					gastr_SOS_ObjBuffer[u8_shiftCounter] = tobj;
					u8_SOS_objBufferHead++;
					break;
				}
			}
			/*check if the task is the lowest priority*/
			if(u8_tempCounter > u8_SOS_objBufferHead)
			{
				u8_SOS_objBufferHead++; /*increase buffer head to next empty position*/
				gastr_SOS_ObjBuffer[u8_SOS_objBufferHead] = tobj;
			}
		}
		
		taken_Ids[Id] = TAKEN ;/*mark this id as taken*/
	}
	return s16_fun_error_status;
}



ERROR_STATUS SOS_deletTask(uint8_t Id)
{
	sint16_t s16_fun_error_status = OK;
	
	if (SOS_Init_flag == FALSE)
	{
		s16_fun_error_status = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	}
	else if (Id>SOS_OBJ_BUFFER_SIZE  || taken_Ids[Id] != TAKEN)
	{
		s16_fun_error_status = (SOS_MODULE_ERROR_NUM+INVALAD_PARAMETER);
	}
	else
	{
		/*
		*  -loop for element in the buffer until reach head
		*				- copy header obj to it 
		*				- decrement header
		*/
		for(uint8_t u8_bufferCnt = 0 ; u8_bufferCnt <=u8_SOS_objBufferHead ; u8_bufferCnt++)
		{
			if(Id == gastr_SOS_ObjBuffer[u8_bufferCnt].Id)
			{
				gastr_SOS_ObjBuffer[u8_bufferCnt] = gastr_SOS_ObjBuffer[u8_SOS_objBufferHead];
				u8_SOS_objBufferHead--;
				taken_Ids[Id] = ZERO; /*mark id as not taken*/
			}
		}	
	}
	
	

	return s16_fun_error_status;
	
}



ERROR_STATUS	SOS_run(void)
{
	sint16_t s16_fun_error_status = OK;

	if (SOS_Init_flag == FALSE)
	{
		s16_fun_error_status = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	}
	else
	{
		STATIC uint8_t current_ticks = ZERO;
		STATIC uint8_t new_tick_flag = FALSE;
	
		/*
		*	-check for new time tick
		*	-if true loop throw the SOS OBJ Buffer
		*	-increment current ticks 
		*	-check if the current ticks == tick time if so call the CBF
		*	-keep going until finish with all obj in SOS buffer
		*/
	
		/*	check for new time tick
		*	for each timer tick increase current tick and make timer0_MS_flag false
		*	if current tick == lap_time
		*		-zero current tick
		*		-fire new_tick_flag
		*/
		if (timer0_MS_flag)
		{
			timer0_MS_flag = FALSE;
			current_ticks++;
			if (current_ticks == SOS_linkCfg.tick_reslution)
			{
				current_ticks = ZERO;
				new_tick_flag = TRUE;
			}
		}
	
		if(new_tick_flag)
		{
			new_tick_flag = FALSE;
			for(uint8_t bufferCnt = 0 ; bufferCnt <=u8_SOS_objBufferHead ; bufferCnt++)
			{
				(gastr_SOS_ObjBuffer[bufferCnt].current_ticks)++;
				/*check for CBF call time*/
				if((gastr_SOS_ObjBuffer[bufferCnt].current_ticks)==(gastr_SOS_ObjBuffer[bufferCnt].fire_tick))
					{
						gastr_SOS_ObjBuffer[bufferCnt].current_ticks = ZERO;
						gastr_SOS_ObjBuffer[bufferCnt].callB_fun();
					
						/*handle one_shot functions*/
						if (gastr_SOS_ObjBuffer[bufferCnt].type == ON_SHOT)
						{
							SOS_deletTask(gastr_SOS_ObjBuffer[bufferCnt].Id);
						}

					}
			}
		 }

	}
	
	return s16_fun_error_status;
}


ERROR_STATUS SOS_Deinit(void)
{
	
	/*
	*	1-deinit timer
	*	2-set SOS_init_flag to zero
	*/
	sint16_t s16_fun_error_status = OK;
	
	if(SOS_Init_flag == FALSE)
	{
		/*report error*/
		s16_fun_error_status = (SOS_MODULE_ERROR_NUM+MODULE_NOT_INITALIZED);
	}

	/*do deinit procedure anyway*/
	uint8_t u8_counter = 0;
	switch(SOS_Timer_ch)
	{
		case SOS_TIMER_CH0:
		Timer_DeInit(TIMER_CH0);
		break;
		case SOS_TIMER_CH1:
		Timer_DeInit(TIMER_CH1);
		break;
		case SOS_TIMER_CH2:
		Timer_DeInit(TIMER_CH2);
		break;
	}
	SOS_Init_flag = FALSE;
	u8_SOS_objBufferHead = ZERO-ONE;
		
	/*free taken ids*/
	for (;u8_counter <= SOS_OBJ_BUFFER_SIZE ; u8_counter++)
	{
		taken_Ids[u8_counter] = ZERO;
	}
	/*set default paramter*/
	SOS_linkCfg.tick_reslution = ONE;
	SOS_linkCfg.timer_ch = SOS_TIMER_CH0;
	
	return s16_fun_error_status;
}


