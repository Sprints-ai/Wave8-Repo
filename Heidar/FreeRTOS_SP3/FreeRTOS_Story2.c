 /*
 * FreeRTOS_Story2.c
 *
 *      Author: Abdallah Heidar
 */

#include "std_types.h"
#include "USART.h"
#include "DIO.h"
#include "LCD.h"
#include "KPD.h"
#include "FreeRTOS.h"
#include "task.h"

#define LEDS_PORT         	(GPIOB)
#define RECV_LED_PIN      	(DIO_PIN7)
#define SENT_LED_PIN      	(DIO_PIN6)
#define PB_PORT           	(GPIOB)
#define PB_PIN            	(DIO_PIN5)

#define RESET             	(0)
#define UART_MSG_LENGTH   	(16)
#define UART_MSG_TERM_CHR 	('F')
#define INIT_TASK_PRI     	(4)
#define UART_TASK_PRI     	(3)
#define LCD_TASK_PRI      	(2)
#define KPD_TASK_PRI      	(1)

#define DELAY_30MS          (30)
#define DELAY_200MS		  	(200)
#define DELAY_500MS         (500)
#define DELAY_2SEC          (2000)

EnmUSARTError_t UART_Status = 0;
uint8_t gu8_UART_SendArr[UART_MSG_LENGTH] = {0};
uint8_t gu8_UART_Recv = 0;
uint8_t gu8_UART_EnteredData = 0;
EnmKPDError_t KPD_Status = 0;
uint8_t gu8_KPD_Char = 0;
uint8_t gu8_KPD_EnteredData = 0;

void SystemInit_Task(void *pv_init)
{
	while(1)
	{
		DIO_init(LEDS_PORT, (RECV_LED_PIN | SENT_LED_PIN) , OUTPUT);
		DIO_init(PB_PORT, PB_PIN, INPUT);
		DIO_Write(PB_PORT, PB_PIN, HIGH);
		USART_init();
		LCD_init();
		KPD_init();
		
		vTaskDelete(NULL);
	}	
	return;
}

void LCD_Task(void *pv_LCD_Data)
{
	while(1)
	{
		if(KPD_Status == KPD_NEW_PRESS)
		{
			LCD_gotoRowColumn(ROW_0, (COL_0 + gu8_KPD_EnteredData));
			LCD_displayChar(gu8_KPD_Char);
			gu8_UART_SendArr[gu8_KPD_EnteredData] = gu8_KPD_Char;
			gu8_KPD_EnteredData++;
		}
		else
		{
			/* TODO */
		}
		
		if(UART_Status == USART_DATA_RECEIVED)
		{
			if(gu8_UART_Recv != UART_MSG_TERM_CHR && gu8_UART_Recv != RESET)
			{
				LCD_gotoRowColumn(ROW_1, (COL_0 + gu8_UART_EnteredData));
				LCD_displayChar(gu8_UART_Recv);
				gu8_UART_EnteredData++;				
			}
			else if(gu8_UART_Recv == UART_MSG_TERM_CHR)
			{
				gu8_UART_Recv = RESET;
				vTaskDelay(DELAY_2SEC);
				LCD_clear();
			}
		} 
		else
		{
			/* TODO */
		}
		vTaskDelay(DELAY_200MS);
	}
	return;
}

void KPD_Task(void *pv_KPD_Data)
{
	while(1)
	{
		KPD_Status = KPD_PressedKey(&gu8_KPD_Char);
		vTaskDelay(DELAY_30MS);
	}	
	return;
}

void UART_Task(void *pv_UART_Data)
{
	uint8_t au8_PB_Status = 0;
	uint8_t au8_loop_var = 0;
	while(1)
	{	
		DIO_Read(PB_PORT, PB_PIN, &au8_PB_Status);
		if(au8_PB_Status == LOW)
		{
			for(au8_loop_var = 0; au8_loop_var < gu8_KPD_EnteredData; au8_loop_var++)
			{
				USART_sendByte(gu8_UART_SendArr[au8_loop_var]);
				vTaskDelay(DELAY_200MS);
			}
			USART_sendByte(UART_MSG_TERM_CHR);
			vTaskDelay(DELAY_200MS);
			DIO_Write(LEDS_PORT, SENT_LED_PIN, HIGH);
			vTaskDelay(DELAY_200MS);
			DIO_Write(LEDS_PORT, SENT_LED_PIN, LOW);
			LCD_clear();
			
			gu8_KPD_EnteredData = RESET;
		}
		else
		{
			/* TODO */
		}
		
		UART_Status = USART_recvByte(&gu8_UART_Recv);
		
		if(gu8_UART_Recv == UART_MSG_TERM_CHR)
		{
			gu8_UART_EnteredData = RESET;
			DIO_Write(LEDS_PORT , RECV_LED_PIN , HIGH);
			vTaskDelay(DELAY_500MS);
			DIO_Write(LEDS_PORT , RECV_LED_PIN , LOW);			
		}
		else
		{
			/* TODO */
		}
		
		vTaskDelay(DELAY_200MS);
	}
	return;
}

int main(void)
{
	xTaskCreate(SystemInit_Task, "Init Task", configMINIMAL_STACK_SIZE, NULL, INIT_TASK_PRI, NULL);
	xTaskCreate(UART_Task, "UART Task", configMINIMAL_STACK_SIZE, NULL, UART_TASK_PRI, NULL);	
	xTaskCreate(LCD_Task, "LCD Task", configMINIMAL_STACK_SIZE, NULL, LCD_TASK_PRI, NULL);
	xTaskCreate(KPD_Task, "KPD Task", configMINIMAL_STACK_SIZE, NULL, KPD_TASK_PRI, NULL);

	vTaskStartScheduler();
	
	while(1) 
    {
    }
	return 0;
}
