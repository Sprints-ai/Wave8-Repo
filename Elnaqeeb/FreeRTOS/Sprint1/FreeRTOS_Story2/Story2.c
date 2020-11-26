/*
 * FreeRTOS_Story2.c
 *
 * Created: 4/13/2020 1:24:58 PM
 * Author : Ahmed
 */ 

/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "LCD.h"
#include "KPD.h"
#include "FreeRTOS.h"
#include "task.h"

/************************************************************************/
/*                        System control macros                         */
/************************************************************************/

/*Password and system control*/
#define CURSOR_RST		(0)
#define ENTERED_NUM_RST	(0)
#define LCD_INIT_STATUS	(0)
#define LCD_DONE_STATUS	(1)
#define PASSWORD_LENGTH	(6)

/*Tasks delay*/
#define DEL_TWO_SEC		(2000)
#define DEL_200_MS		(200)

/*Tasks priorities*/
#define INIT_TASK_PRI	(3)
#define LCD_TASK_PRI	(2)
#define KPD_TASK_PRI	(1)


/************************************************************************/
/*                          Tasks important variables                   */
/************************************************************************/

/*System password*/
uint8_t gu8_password[] = "123456";

/*Password cursor*/
uint8_t gu8_cursor = 0;

/*Password cursor*/
uint8_t gu8_entered = 0;

/*Flag indicates LCD status*/
uint8_t gu8_LCD_flag = 0;

/*Shared variable used to pass data between KPD and LCD*/
uint8_t gu8_LCD_KPD_data = 0;

/*KPD error status variable*/
EnmKPDError_t KPD_err_var = 0; 

/*System initialization task*/
void SystemInit_Task(void *pv_init)
{
	for(;;)
	{
		/*System initialization*/
		KPD_init();
		LCD_init();
		
		/*Delete this task*/
		vTaskDelete(NULL);
	}	
	return;
}

/*KeyPad task used to get the pressed key*/
void KPD_Task(void *pv_KPD_Data)
{
	for(;;)
	{
		/*Get the pressed key of the keypad*/
		KPD_err_var = KPD_PressedKey(&gu8_LCD_KPD_data);
		
		/*Validate if there's a new key pressed*/
		if(KPD_err_var == KPD_NEW_PRESS)
		{	
			/*Validate the new key is part from the system password or not*/
			if(gu8_LCD_KPD_data == gu8_password[gu8_cursor])
			{
				/*Increase the the password cursor*/
				gu8_cursor++;
			}
			else
			{
				/*Do nothing*/
			}
		}
		else
		{
			/*Do nothing*/
		}
		
		/*Task yielding to the scheduler*/
		taskYIELD();
	}	
	return;
}

/*LCD Task used to display the pressed key*/
void LCD_Task(void *pv_LCD_Data)
{
	for(;;)
	{
		/*Check the task status*/
		if(gu8_LCD_flag == LCD_INIT_STATUS)
		{
			/*Clear LCD and display the welcome message*/
			LCD_clear();
			LCD_displayString((uint8_t*)"Enter password:");
			LCD_gotoRowColumn(ROW_1,COL_0);
			
			/*Reset the system counters*/
			gu8_entered  = ENTERED_NUM_RST;
			gu8_cursor   = CURSOR_RST;
			
			/*Convert LCD status into DONE*/
			gu8_LCD_flag = LCD_DONE_STATUS;
		}
		else
		{
			/*Do nothing*/
		}
		
		/*Validate if there's a new key pressed*/
		if(KPD_err_var == KPD_NEW_PRESS)
		{	
			/*Increase the number of entered keys*/
			gu8_entered++;
			
			/*Validate the entered digits if it's equal to the password or not*/
			if((gu8_cursor == PASSWORD_LENGTH) && (gu8_entered == (PASSWORD_LENGTH+1)) && (gu8_LCD_KPD_data == '#'))
			{
				/*Clear the LCD, Display Valid Password!, Reset the counters and LCD status*/
				LCD_clear();
				LCD_displayStringRowColumn((uint8_t*)"Valid Password!",ROW_0 , COL_0);
				gu8_entered  = ENTERED_NUM_RST;
				gu8_cursor   = CURSOR_RST;
				gu8_LCD_flag = LCD_INIT_STATUS;
				
				/*Block the task for 2 seconds*/
				vTaskDelay(DEL_TWO_SEC);
			}
			else if(((gu8_cursor != PASSWORD_LENGTH) || (gu8_entered > (PASSWORD_LENGTH+1))) && (gu8_LCD_KPD_data == '#'))
			{
				/*Clear the LCD, Display Invalidate Password!, Reset the counters and LCD status*/
				LCD_clear();
				LCD_displayStringRowColumn((uint8_t*)"Invalid Password!",ROW_0 , COL_0);
				LCD_gotoRowColumn(ROW_1 , COL_0);
				gu8_entered  = ENTERED_NUM_RST;
				gu8_cursor   = CURSOR_RST;
				gu8_LCD_flag = LCD_INIT_STATUS;
				
				/*Block the task for 2 seconds*/
				vTaskDelay(DEL_TWO_SEC);
			}
			else if(gu8_LCD_KPD_data == '*')
			{
				/*Clear the LCD, Reset the counters and LCD status*/
				LCD_clear();
				gu8_entered  = ENTERED_NUM_RST;
				gu8_cursor   = CURSOR_RST;
				gu8_LCD_flag = LCD_INIT_STATUS;				
			}
			else
			{
				/*Display the pressed key*/
				LCD_displayChar(gu8_LCD_KPD_data);	
			}
		} 
		else
		{
			/*Do nothing*/
		}
		
		/*Block the task for 200ms*/
		vTaskDelay(DEL_200_MS);	
	}
	return;
}

int main(void)
{
	/*Tasks creation to be scheduled by RTOS kernel*/
	xTaskCreate(SystemInit_Task,"InitTask",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRI,NULL);
	xTaskCreate(LCD_Task,"LCDTask",configMINIMAL_STACK_SIZE,NULL,LCD_TASK_PRI,NULL);
	xTaskCreate(KPD_Task,"KPDTask",configMINIMAL_STACK_SIZE,NULL,KPD_TASK_PRI,NULL);
	
	/*Start scheduling*/
	vTaskStartScheduler();
	
	while(1) 
    {
		/*Do nothing*/			
    }
	return 0;
}

