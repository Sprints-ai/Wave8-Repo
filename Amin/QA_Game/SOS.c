#include "SOS.h"

static volatile uint32 g_systick =0;
static volatile uint32 g_indexISR =0;
static volatile uint32 g_creat_counter =0;
extern OS_ConfigType *OS_Config_Ptr;

EnmOSError_t SOS_Init (const OS_ConfigType * ConfigPtr){
	SREG|=0x80;
	EnmOSError_t status =SUCCEED;
	g_systick=ConfigPtr->System_Tick;
	Timer_cfg_s conf={TIMER_CH0,TIMER_MODE,TIMER_INTERRUPT_MODE,TIMER_PRESCALER_64};
		Timer_Init(&conf);
	switch(ConfigPtr->Timer_ID){
	case TIMER0:
		TIMER0_OVF_setCallBack(SOS_cal);
		Timer_Start(TIMER0);
		break;
	case TIMER1:
		TIMER1_OVF_setCallBack(SOS_cal);
		Timer_Start(TIMER1);
		break;
	case TIMER2:
		TIMER2_OVF_setCallBack(SOS_cal);
		Timer_Start(TIMER2);
		break;
	default:
		status =FAILED;
		break;
	}
	return status;
}

EnmOSError_t SOS_Create_Task(uint32 periodicity,uint16 priority,ptrToFunction FuncName){
	EnmOSError_t status =SUCCEED;
	Task_ConfigType temp_1;
	Task_ConfigType temp_2;
	uint8 flag = 0;
	uint8 flag_swap =0;
	uint32 index = 0;
	if(g_creat_counter <= Tasks_NUM){
		if(g_creat_counter == 0){
			Task_Config_arr[g_creat_counter].g_function = FuncName;
			Task_Config_arr[g_creat_counter].periodicity = periodicity;
			Task_Config_arr[g_creat_counter].priority = priority;
			Task_Config_arr[g_creat_counter].state = READY;
		}
		else if(priority >= Task_Config_arr[g_creat_counter-1].priority){
			Task_Config_arr[g_creat_counter].g_function = FuncName;
			Task_Config_arr[g_creat_counter].periodicity = periodicity;
			Task_Config_arr[g_creat_counter].priority = priority;
			Task_Config_arr[g_creat_counter].state = READY;
		}
		else{
			for(index=0;index<g_creat_counter;index++){
				if(flag_swap == 0){
					if(priority < Task_Config_arr[index].priority){
						temp_1 = Task_Config_arr[index];
						Task_Config_arr[index].g_function = FuncName;
						Task_Config_arr[index].periodicity = periodicity;
						Task_Config_arr[index].priority = priority;
						Task_Config_arr[index].state = READY;
						flag =1;
						flag_swap = 1;
					}
				}
				if(flag == 1){
					temp_2 = Task_Config_arr[index+1];
					Task_Config_arr[index+1] = temp_1;
					flag=2;
				}
				else if(flag == 2){
					temp_1 = Task_Config_arr[index+1];
					Task_Config_arr[index+1] = temp_2;
					flag=1;
				}
			}
		}
	}
	else {
		status = FAILED;
	}
	g_creat_counter++;

	return status;
}

EnmOSError_t SOS_Delete_Task(ptrToFunction FuncName){
	EnmOSError_t status =SUCCEED;
	uint32 index =0;
	uint8 flag_del =0;
	if(g_creat_counter >0){
		for(index = 0;index<g_creat_counter;index++){
			if(Task_Config_arr[index].g_function == FuncName){
				if(index == g_creat_counter-1){
					Task_Config_arr[index].state = DELETED;
					Task_Config_arr[index].g_function = NULL;
					break;
				}
				flag_del =1;
			}
			if(flag_del == 1){
				Task_Config_arr[index] = Task_Config_arr[index+1];
			}
			else{
				status = FAILED;
			}
		}
		g_creat_counter--;
	}
	else{
		status = FAILED;
	}
	return status;
}

void SOS_Run(void){
	uint32 l_counter=0;
		for(l_counter =0 ;l_counter < g_creat_counter; l_counter++){
			if((((Task_Config_arr[l_counter].task_counter) == (Task_Config_arr[l_counter].periodicity)) ) \
					&& (((Task_Config_arr[l_counter].periodicity)*2) >= (Task_Config_arr[l_counter].task_counter))){
				Task_Config_arr[l_counter].task_counter=0;
				if(Task_Config_arr[l_counter].state == READY){
					Task_Config_arr[l_counter].g_function();
				}
				else if(Task_Config_arr[l_counter].state == WAITING){
					Task_Config_arr[l_counter].state = READY;
				}
			}
		}
}
void SOS_cal(void){
	for(g_indexISR=0;g_indexISR < g_creat_counter;g_indexISR++){
		Task_Config_arr[g_indexISR].task_counter ++;
	}
}