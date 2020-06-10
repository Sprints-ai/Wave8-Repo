 /*
 * FreeRTOS_Story1.c
 *
 *      Author: Abdallah Heidar
 */

#include "std_types.h"
#include "DIO.h"
#include "USART.h"
#include "LCD.h"
#include "KPD.h"
#include "FreeRTOS.h"
#include "task.h"

#define PB_PORT         	(GPIOB)
#define PB_PIN          	(DIO_PIN7)

#define INIT_TASK_PRI   	(5)
#define TASKA_PRI       	(2)
#define TASKB_PRI       	(1)
#define TASKC_PRI       	(3)
#define TASKD_PRI       	(4)

#define TASK_DELAY_50MS  	(50)
#define TASK_DELAY_200MS 	(200)

uint8_t gu8_KPDLCDVar = 0;
EnmKPDError_t KPD_Status = 0;
uint8_t gu8_KPD_Entred_DataNum = 0;
uint8_t gu8_UART_LCD_Var = 0;
EnmUSARTError_t UART_Status = 0;
uint8_t gu8_UART_Entred_DataNum = 0;

void SystemInit_Task(void *pv_init)
{
	while(1)
	{
		LCD_init();
		KPD_init();
		DIO_init(PB_PORT, PB_PIN, INPUT);
		DIO_Write(PB_PORT, PB_PIN, HIGH);
		USART_init();
		vTaskDelete(NULL);
	}	
	return;
}

void Task_A_LCD(void *pv_LCD_Data)
{
	while(1)
	{
		if(KPD_Status == KPD_NEW_PRESS)
		{
			LCD_gotoRowColumn(ROW_0, (COL_0 + gu8_KPD_Entred_DataNum));
			LCD_displayChar(gu8_KPDLCDVar);
			gu8_KPD_Entred_DataNum++;
		} 
		else
		{
			/* TODO */
		}
		
		if(UART_Status == USART_DATA_RECEIVED)
		{
			LCD_gotoRowColumn(ROW_1, (COL_0 + gu8_UART_Entred_DataNum));
			LCD_displayChar(gu8_UART_LCD_Var);
			gu8_UART_Entred_DataNum++;			
		}
		else
		{
			/* TODO */
		}
		vTaskDelay(TASK_DELAY_200MS);
	}
	return;
}

void Task_B_KPD(void *pv_KPD_Data)
{
	while(1)
	{
		KPD_Status = KPD_PressedKey(&gu8_KPDLCDVar);
		vTaskDelay(TASK_DELAY_50MS);
	}	
	return;
}

void Task_C_USART(void* pv_USART_Data)
{
	while(1)
	{
		UART_Status = USART_recvByteInt(&gu8_UART_LCD_Var);
		vTaskDelay(TASK_DELAY_200MS);		
	}
	return;
}

void Task_D_PushButton(void* pv_PB_Data)
{
	uint8_t au8_PB_Status = 0;
	while(1)
	{
		DIO_Read(PB_PORT, PB_PIN, &au8_PB_Status);
		if(au8_PB_Status == LOW)
		{
			gu8_KPD_Entred_DataNum = 0;
			gu8_UART_Entred_DataNum = 0;
			LCD_clear();
		} 
		else
		{
			/* TODO */
		}
		vTaskDelay(TASK_DELAY_50MS);
	}
	return;
}

int main(void)
{
	xTaskCreate(SystemInit_Task, "Init Task", configMINIMAL_STACK_SIZE, NULL, INIT_TASK_PRI, NULL);
	xTaskCreate(Task_A_LCD, "LCD Task", configMINIMAL_STACK_SIZE, NULL, TASKA_PRI, NULL);
	xTaskCreate(Task_B_KPD, "KPD Task", configMINIMAL_STACK_SIZE, NULL, TASKB_PRI, NULL);
	xTaskCreate(Task_C_USART, "UART TASK", configMINIMAL_STACK_SIZE, NULL,TASKC_PRI, NULL);
	xTaskCreate(Task_D_PushButton, "Push Button TASK", configMINIMAL_STACK_SIZE, NULL, TASKD_PRI, NULL);
	
	vTaskStartScheduler();
	
	while(1) 
    {
    }
	return 0;
}

