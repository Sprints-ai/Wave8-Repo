/*
 * FreeRTOS_SP3_Story1.c
 *
 * Created: 4/13/2020 1:24:58 PM
 * Author : Ahmed
 */ 

/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "std_types.h"
#include "DIO.h"
#include "USART.h"
#include "LCD.h"
#include "KPD.h"
#include "FreeRTOS.h"
#include "task.h"

/************************************************************************/
/*                           General macros                             */
/************************************************************************/

/*Push button configuration*/
#define PB_PORT         (GPIOB)
#define PB_PIN          (DIO_PIN7)

/************************************************************************/
/*                            Tasks configuration                       */
/************************************************************************/

/*Tasks priority*/
#define INIT_TASK_PRI   (5)
#define TASKA_PRI       (2)
#define TASKB_PRI       (1)
#define TASKC_PRI       (3)
#define TASKD_PRI       (4)

/*Tasks delay*/
#define TASK_DEL_50MS  (50)
#define TASK_DEL_200MS (200)

/************************************************************************/
/*                           Important variables                        */
/************************************************************************/

/*Variable used in communication between KPD and LCD*/
uint8_t gu8_KPD_LCD_Var = 0;

/*Variable used in to carry current status of KPD*/
EnmKPDError_t KPD_Status = 0;

/*Variable used to count digits entered by KPD*/
uint8_t gu8_KPD_Entred_DataNum = 0;

/*Variable used in communication between UART and LCD*/
uint8_t gu8_UART_LCD_Var = 0;

/*Variable used to carry the current status of UART*/
EnmUSARTError_t UART_Status = 0;

/*Variable used to count characters entered by UART*/
uint8_t gu8_UART_Entred_DataNum = 0;

/************************************************************************/
/*                          System tasks                                */
/************************************************************************/

/*System initialization task*/
void SystemInit_Task(void *pv_init)
{
	for(;;)
	{
		/*LCD Initialization*/
		LCD_init();
		
		/*Keypad Initialization*/
		KPD_init();
		
		/*PB Initialization as INPUT and Activate pull-up resistor*/
		DIO_init(PB_PORT , PB_PIN , INPUT);
		
		/*Pull-up resistor activation*/
		DIO_Write(PB_PORT , PB_PIN , HIGH);
		
		/*USART Initialization*/
		USART_init();
		
		vTaskDelete(NULL);
	}	
	return;
}

/*Task A used for monitoring LCD*/
void taskA_LCD(void *pv_LCD_Data)
{
	for(;;)
	{
		/*Checks if there's a new press over the KPD or not*/
		if(KPD_Status == KPD_NEW_PRESS)
		{
			/*If there's a new press display the digit over LCD ROW_1*/
			LCD_gotoRowColumn(ROW_0 , (COL_0 + gu8_KPD_Entred_DataNum));
			LCD_displayChar(gu8_KPD_LCD_Var);
			
			/*Increase the Columns by 1 to enter the new digit*/
			gu8_KPD_Entred_DataNum++;
		} 
		else
		{
			/*Do nothing*/
		}
		
		/*Checks if there's a new data received over UART or not*/
		if(UART_Status == USART_DATA_RECEIVED)
		{
			/*If there's a new data received over UART display it on LCD*/
			LCD_gotoRowColumn(ROW_1 , (COL_0 + gu8_UART_Entred_DataNum));
			LCD_displayChar(gu8_UART_LCD_Var);
			
			/*Increase the Columns by 1 to enter the new character*/
			gu8_UART_Entred_DataNum++;			
		}
		else
		{
			/*DO nothing*/
		}
		
		/*Block the task for 200ms*/
		vTaskDelay(TASK_DEL_200MS);
	}
	return;
}

/*KeyPad task used to get the pressed key*/
void taskB_KPD(void *pv_KPD_Data)
{
	for(;;)
	{
		/*Monitor keypad status and gets digits pressed over KPD*/
		KPD_Status = KPD_PressedKey(&gu8_KPD_LCD_Var);
		
		/*Block the task for 50ms*/
		vTaskDelay(TASK_DEL_50MS);
	}	
	return;
}

/*Task C responsible for receiving any USART data*/
void taskC_USART(void* pv_USART_Data)
{
	for(;;)
	{
		/*Monitor UART status and gets any received data*/
		UART_Status = USART_recvByteInt(&gu8_UART_LCD_Var);
		
		/*Block the task for 200ms*/
		vTaskDelay(TASK_DEL_200MS);		
	}
	return;
}

/*Task D responsible for monitoring PB status*/
void taskD_PushButton(void* pv_PB_Data)
{
	/*Variable used in getting push button status*/
	uint8_t au8_PB_Status = 0;
	
	for(;;)
	{
		/*Reads the status of the push button*/
		DIO_Read(PB_PORT , PB_PIN , &au8_PB_Status);
		
		/*Checks that the push button is pressed or not*/
		if(au8_PB_Status == LOW)
		{
			/*If PB is pressed reset the data counting variables and clear the LCD*/
			gu8_KPD_Entred_DataNum = 0;
			gu8_UART_Entred_DataNum = 0;
			
			/*Clear the LCD*/
			LCD_clear();
		} 
		else
		{
			/*Do nothing*/
		}
		
		/*Block the task for 50ms*/
		vTaskDelay(TASK_DEL_50MS);
	}
	return;
}

int main(void)
{
	/*Tasks creation to be scheduled by RTOS kernel*/
	xTaskCreate(SystemInit_Task,"InitTask",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRI,NULL);
	xTaskCreate(taskA_LCD,"LCDTask",configMINIMAL_STACK_SIZE,NULL,TASKA_PRI,NULL);
	xTaskCreate(taskB_KPD,"KPDTask",configMINIMAL_STACK_SIZE,NULL,TASKB_PRI,NULL);
	xTaskCreate(taskC_USART,"UTASK",configMINIMAL_STACK_SIZE,NULL,TASKC_PRI,NULL);
	xTaskCreate(taskD_PushButton,"PBTASK",configMINIMAL_STACK_SIZE,NULL,TASKD_PRI,NULL);
	
	/*Start scheduling*/
	vTaskStartScheduler();
	
	while(1) 
    {
		/*Do nothing*/			
    }
	return 0;
}

