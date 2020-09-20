/*
 * Msg_App.c
 *
 * Created: 17-Mar-20 1:51:55 AM
 *  Author: ahmed
 */ 

/************************************************************************/
/*							INCLUDES                                    */
/************************************************************************/
#include "/LCD_APP/MCAL/registers.h"
#include "/LCD_APP/SERVICE/LCD.h"
#include "/LCD_APP/SERVICE/SOS.h"
#include "/LCD_APP/MCAL/interrupt.h"

/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/
#define ISR_HIGH		(1)
#define LCD_FIRST_MSG	(1)
#define LCD_SECOND_MSG	(2)
#define LCD_THIRD_MSG	(3)
#define LCD_FOURTH_MSG	(4)
#define DEBOUNCE_PROTECTION_TICKS	(2)
#define LCD_FIFTH_MSG	(5)
#define LCD_INIT_TICKS	(10)
#define LCD_BUSY_GUARD	(105)
#define MAX_SCORE		(4)
#define YES				(0)
#define NO				(1)

/************************************************************************/
/*					GLOBAL VARIBALES                                    */
/************************************************************************/
static uint8_t gu8_debounceGuard = ZERO;
static	uint8_t LCD_STATE = ZERO;
static uint8_t gu8_msg0Guard = ZERO;
static uint8_t ISR_state = ZERO;
//here 10 for the first msg which is welcoming one
static uint8_t gar_ScoreBuff[5] = {10,1,1,1,1};
static uint8_t gu8_scoreDisp = ZERO;
static uint8_t gu8_scoreCnt = ZERO;

/** APPLICATION
*	Description
** a small application of two toggles one of them is done once"one shot"
other is done periodicly
*/
void msg1()
{
	if(gu8_debounceGuard < LCD_INIT_TICKS)
	{
		
		LCD_init(DATA_BITS_4);
		gu8_debounceGuard++;
	}
	else{
		LCD_displayStringRowColumn(0,0,"HEY THERE PRESS");
		LCD_displayStringRowColumn(1,0,"ANY KEY when RDY");
		gu8_debounceGuard=0;
		gu8_msg0Guard = ZERO;
		LCD_STATE = LCD_FIRST_MSG;
		SOS_Stop_Timer(2);
	}

	
};
void msg2()
{
	if(LCD_STATE == LCD_FIRST_MSG && ISR_state == ISR_HIGH)
	{
		if(gu8_debounceGuard == ZERO)
		{
			LCD_clearScreen();
		}
		
		if(gu8_debounceGuard > 10){

			LCD_displayStringRowColumn(0,0,"IS THE OIL ");
			LCD_displayStringRowColumn(1,0,"PRICE INCREASING?");
			
			if(gu8_debounceGuard == LCD_BUSY_GUARD){
				LCD_STATE = LCD_SECOND_MSG;
				ISR_state = ZERO;

				gu8_debounceGuard = ZERO;
				
				gu8_msg0Guard = ZERO;
			}
		}	
		gu8_debounceGuard++;
	}	
}

void msg3()
{
	if(LCD_STATE == LCD_SECOND_MSG && ISR_state == ISR_HIGH)
	{
		if(gu8_debounceGuard > DEBOUNCE_PROTECTION_TICKS){
			LCD_displayStringRowColumn(ZERO , ZERO ,"IS TOMATO A ");
			LCD_displayStringRowColumn(1 , ZERO ,"FRUIT?          ");
			
			if(gu8_debounceGuard == LCD_BUSY_GUARD){
				
				LCD_STATE = LCD_THIRD_MSG;
				ISR_state = ZERO;
				gu8_debounceGuard = ZERO;
				
				gu8_msg0Guard = ZERO;
			}
		}
		
		gu8_debounceGuard++;
	}
}

void msg4()
{

	if(LCD_STATE == LCD_THIRD_MSG && ISR_state == ISR_HIGH)
	{
		if(gu8_debounceGuard > DEBOUNCE_PROTECTION_TICKS){
			LCD_displayStringRowColumn(ZERO , ZERO ,"DOES BOZA MEAN ");
			LCD_displayStringRowColumn(1 , ZERO,"THE GENIUS?        ");
			
			if(gu8_debounceGuard == LCD_BUSY_GUARD){
				
				LCD_STATE = LCD_FOURTH_MSG;
				ISR_state = ZERO;
				gu8_debounceGuard = ZERO;
				
				gu8_msg0Guard = ZERO;
			}
		}
		gu8_debounceGuard++;
	}
}

void msg5()
{
	

	if(LCD_STATE == 4 && ISR_state == ISR_HIGH)
	{
		if(gu8_debounceGuard > DEBOUNCE_PROTECTION_TICKS){
			LCD_displayStringRowColumn(ZERO ,ZERO ,"DOES AUGUST MEAN ");
			LCD_displayStringRowColumn(1, ZERO,"BEAUTY ?        ");
			
			if(gu8_debounceGuard == LCD_BUSY_GUARD){
				
				LCD_STATE = LCD_FIFTH_MSG;
				ISR_state = ZERO;
				gu8_debounceGuard = ZERO;
				
				PORTC_DIR = gu8_scoreDisp;
				gu8_msg0Guard = ZERO;
			}
		}
		gu8_debounceGuard++;
	}
}

void msg6()
{
	if(LCD_STATE == LCD_FIFTH_MSG && ISR_state == ISR_HIGH)
	{
		if(gu8_debounceGuard > DEBOUNCE_PROTECTION_TICKS){
			
			if(gu8_scoreDisp == MAX_SCORE)
			LCD_displayStringRowColumn(ZERO ,ZERO ,"CONGRATZ BUDDY  ");
			LCD_displayStringRowColumn(1, ZERO,"YOU WON      ");
		}
			
			else
			{
				LCD_displayStringRowColumn(ZERO ,ZERO ,"SORRY BUDDY    ");
				LCD_displayStringRowColumn(1, ZERO,"YOU LOSE      ");
			}
			if(gu8_debounceGuard == LCD_BUSY_GUARD){
				
				LCD_STATE = 6;
				ISR_state = ZERO;
				gu8_debounceGuard = ZERO;
				
				PORTC_DIR = gu8_scoreDisp;
				gu8_msg0Guard = ZERO;
			}
		gu8_debounceGuard++;
	}
}

ERROR_STATUS Init_Create_tasks()
{
	/*create ERROR_FLAG*/
	ERROR_STATUS ERR_STATE = E_NOK;
	
	
	/*inits and creation of Tasks*/
	st_SOS_init_t timer_chnl = {SOS_TMR_CH0};
	ERR_STATE = SOS_Init(&timer_chnl);
	
	st_SOS_TaskType_t task;
	
	task.u32_counts = 1;
	task.u8_id = 2;
	task.u8_TaskPriority =1;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg1;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	task.u32_counts = 1;
	task.u8_id = 3;
	task.u8_TaskPriority = 2;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg2;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	task.u32_counts = 1;
	task.u8_id = 4;
	task.u8_TaskPriority = 3;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg3;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	task.u32_counts = 1;
	task.u8_id = 5;
	task.u8_TaskPriority =4;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg4;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	task.u32_counts = 1;
	task.u8_id = 6;
	task.u8_TaskPriority =5;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg5;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	task.u32_counts = 1;
	task.u8_id = 7;
	task.u8_TaskPriority =6;
	task.u8_periodic_state = SOS_PERIODIC;
	task.task_ptr = msg6;
	
	ERR_STATE = SOS_Start_Timer(&task);
	
	
	/*enabling external interrupt*/
	PORTD_DIR = 0x00;
	GICR |= (0x80 | 0x20);
	
	return ERR_STATE;
}

ISR(INT1_irq)
{
	ISR_state = ISR_HIGH;
	
	if(gu8_msg0Guard == ZERO)
	{	
		if(gar_ScoreBuff[gu8_scoreCnt] == ZERO)
		{
				gu8_scoreDisp++;		
		}
		gu8_scoreCnt++;
	}
	gu8_msg0Guard++;	
}

ISR(INT2_irq)
{
	ISR_state = ISR_HIGH;
	
	if(gu8_msg0Guard == ZERO)
	{
		if(gar_ScoreBuff[gu8_scoreCnt] == NO)
		{
			gu8_scoreDisp++;		
		}
		gu8_scoreCnt++;
	}
	gu8_msg0Guard++;
}