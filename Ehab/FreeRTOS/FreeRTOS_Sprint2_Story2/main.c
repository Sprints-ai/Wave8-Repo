/*
 * FreeRTOS_Story2.c
 *
 * Created: 15/04/2020 05:22:24 م
 * Author : TOSHIBA
 */ 
#include "Services/FreeRTOS/FreeRTOS.h"

#include "Services/FreeRTOS/task.h"

#include "Services/FreeRTOS/semphr.h"

#include "Services/FreeRTOS/event_groups.h"

#include "ECUAL/LED/led.h"

#include "ECUAL/LCD/LCD.h"


#include "ECUAL/PushButton/pushButton.h"

#define LED_Flag	0x01
#define BTN0_Flag	0x02
#define BTN1_Flag	0x04


TaskHandle_t		LED_Handler = NULL;
TaskHandle_t		LCD_Handler = NULL;
SemaphoreHandle_t   LED_Mutex = NULL;
EventGroupHandle_t  EventGroup = NULL;

void Init_Task( void * pvParameters ){
   
    Led_Init(LED_0);
  
    pushButtonInit(BTN_0);
	
	pushButtonInit(BTN_1);
	
	Led_Off(LED_0);
	
	LCD_init();
// 	while(1)
// 	{
	  //  LCD_WriteStringToXY(0,5,(uint8_t *)"hi  hok");
		//LCD_displayString((uint8_t *)"hi  hok");//}
	
	vTaskSuspend(NULL);
}
void Led_Task( void * pvParameters ){
	
	EventBits_t  Led_bitFlag=0;
	TickType_t   xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		
		Led_bitFlag = xEventGroupGetBits( EventGroup );
		
		if( (Led_bitFlag & LED_Flag) == LED_Flag)
		{
			Led_On(LED_0);
			
			/* Event base */
			//xEventGroupClearBits( EventGroup , LED_ON_Flag);
			
		}
		
		else 
			{
				Led_Off(LED_0);
				
			}
			
			//Led_On(LED_0);
	   // vTaskDelayUntil( &xLastWakeTime, 100 );

			vTaskSuspend(NULL);
	}
}
void BTN0_Task( void * pvParameters ){
	
	TickType_t   xLastWakeTime;
	
	uint8_t		 u8_BTN0_State = Released , u8_BTN0_Sample_Nu = 0;
	
	xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		pushButtonGetStatus(BTN_0, &u8_BTN0_State );
		
		if( (u8_BTN0_State == Pressed) &&( u8_BTN0_Sample_Nu < 3))
		{
		
			u8_BTN0_Sample_Nu ++ ;
			
			u8_BTN0_State = Released ;
		}
		
		else if ( ( u8_BTN0_State == Released ) )
		{
			
			
			if (u8_BTN0_Sample_Nu == 4)
			
			{
				xEventGroupClearBits(EventGroup,(LED_Flag|BTN0_Flag)); 
				vTaskResume(LCD_Handler);
				vTaskResume(LED_Handler);				
				xSemaphoreGive(LED_Mutex);
			}
			
			u8_BTN0_Sample_Nu = 0 ;
		}
		if( u8_BTN0_Sample_Nu == 3)
		{
			if(xSemaphoreTake(LED_Mutex,( TickType_t ) 0) == pdTRUE)

			{
				xEventGroupSetBits(EventGroup,(LED_Flag|BTN0_Flag));
				vTaskResume(LCD_Handler);	
				vTaskResume(LED_Handler);			
				u8_BTN0_Sample_Nu ++;
			}
		}
		
		vTaskDelayUntil( &xLastWakeTime, 50 );		
	}
}
void BTN1_Task( void * pvParameters ){	
	
	TickType_t   xLastWakeTime;
	
	uint8_t		 u8_BTN1_State = Released , u8_BTN1_Sample_Nu = 0;
	
	xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		pushButtonGetStatus(BTN_1, &u8_BTN1_State );
		
		if( (u8_BTN1_State == Pressed) &&( u8_BTN1_Sample_Nu < 3))
		{
			
			u8_BTN1_Sample_Nu ++ ;
			
			u8_BTN1_State = Released ;
		}
		
		else if ( ( u8_BTN1_State == Released ) )
		{
			
			
			if (u8_BTN1_Sample_Nu == 4)
			
			{
				xEventGroupClearBits(EventGroup,(LED_Flag|BTN1_Flag));
				vTaskResume(LCD_Handler);
				vTaskResume(LED_Handler);
				xSemaphoreGive(LED_Mutex);
			}
			
			u8_BTN1_Sample_Nu = 0 ;
		}
		if( u8_BTN1_Sample_Nu == 3) 
		{
			if(xSemaphoreTake(LED_Mutex,( TickType_t ) 0) == pdTRUE)
			{
				xEventGroupSetBits(EventGroup,(LED_Flag|BTN1_Flag));
				vTaskResume(LCD_Handler);
				vTaskResume(LED_Handler);

				u8_BTN1_Sample_Nu ++;
			}
		}
		
		vTaskDelayUntil( &xLastWakeTime, 50 );
	}
}
void LCD_Task( void * pvParameters )
{
	EventBits_t  Led_Btn_BitSFlag =0;
	TickType_t   xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();
	
	uint8_t * au8_Massege[5]={(uint8_t *)"FF",(uint8_t *)"N ",(uint8_t *)"Un",(uint8_t *)"0 ",(uint8_t *)"1 "};
	
	LCD_displayStringRowColumn(0,0,(uint8_t *)"Led : OFF");// col 12
	LCD_displayStringRowColumn(1,0,(uint8_t *)"BTNs :Unpressed");// col 12
	
	while (1)
	{
		
		Led_Btn_BitSFlag = xEventGroupGetBits( EventGroup );
		

		LCD_displayStringRowColumn(0,7,au8_Massege[Led_Btn_BitSFlag & LED_Flag]); 
		
		LCD_displayStringRowColumn(1,6,au8_Massege[2+((Led_Btn_BitSFlag & (BTN0_Flag|BTN1_Flag)) >> 1)]); 	
			
			PORTD_DATA = 2+((Led_Btn_BitSFlag & (BTN0_Flag|BTN1_Flag)) >> 1);
			
			PORTD_DIR = ((Led_Btn_BitSFlag & (BTN0_Flag|BTN1_Flag)) >> 1) ;
			
			   
	   // vTaskDelayUntil( &xLastWakeTime, 50 );
	   			vTaskSuspend(NULL);

	}

}

int main(void)
{
	 EventGroup = xEventGroupCreate();
	 LED_Mutex = xSemaphoreCreateMutex();
	 
	 xTaskCreate(Init_Task,NULL,configMINIMAL_STACK_SIZE,NULL,3,NULL );
     xTaskCreate(Led_Task,NULL,configMINIMAL_STACK_SIZE,NULL,1,&LED_Handler );
 	 xTaskCreate(BTN0_Task,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL );
     xTaskCreate(BTN1_Task,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL );
	 xTaskCreate(LCD_Task,NULL,configMINIMAL_STACK_SIZE,NULL,0,&LCD_Handler );
	    
	 xEventGroupCreate();

	 vTaskStartScheduler();
	return 0;  
}

