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
#include "USART.h"
#include "DIO.h"
#include "LCD.h"
#include "KPD.h"
#include "FreeRTOS.h"
#include "task.h"

/************************************************************************/
/*                            General macros                            */
/************************************************************************/

/*LEDs PORT*/
#define LEDS_PORT         (GPIOB)

/*Received LED configuration*/
#define RECV_LED_PIN      (DIO_PIN7)

/*Sent LED configuration*/
#define SENT_LED_PIN      (DIO_PIN6)

/*Push button configuration*/
#define PB_PORT           (GPIOB)
#define PB_PIN            (DIO_PIN5)

/*Macro used to reset operation variables state to zero*/
#define RESET             (0)

/*Maximum UART msg length according to width of LCD*/
#define UART_MSG_LENGTH   (16)

/*UART Terminating character*/
#define UART_MSG_TERM_CHR ('F')

/*Tasks priority*/
#define INIT_TASK_PRI     (4)
#define UART_TASK_PRI     (3)
#define LCD_TASK_PRI      (2)
#define KPD_TASK_PRI      (1)

/*Task delays*/
#define DEL_30MS          (30)
#define DEL_200MS		  (200)
#define DEL_500MS         (500)
#define DEL_2SEC          (2000)

/************************************************************************/
/*                            Important variables                       */
/************************************************************************/

/*Variable used in indicating UART status*/
EnmUSARTError_t UART_Status = 0;

/*Array used to hold data entered from keypad*/
uint8_t gu8_UART_SendArr[UART_MSG_LENGTH] = {0};

/*Variable used to hold received data from UART*/	
uint8_t gu8_UART_Recv = 0;

/*Variable used to count data bytes entered from UART*/
uint8_t gu8_UART_EnteredData = 0;

/*Variable used in indicating KPD status*/
EnmKPDError_t KPD_Status = 0;

/*Variable used in holding KPD pressed key character*/
uint8_t gu8_KPD_Char = 0;

/*Variable used in counting entered characters from KPD*/
uint8_t gu8_KPD_EnteredData = 0;

/************************************************************************/
/*                            System tasks                              */
/************************************************************************/

/*System initialization task*/
void SystemInit_Task(void *pv_init)
{
	for(;;)
	{
		/*LEDs initialization as output pins*/
		DIO_init(LEDS_PORT , (RECV_LED_PIN | SENT_LED_PIN) , OUTPUT);
		
		/*PB initialization as input pin*/
		DIO_init(PB_PORT , PB_PIN , INPUT);
		
		/*Activate pull up resistor for PB*/
		DIO_Write(PB_PORT , PB_PIN , HIGH);
		
		/*USART initialization*/
		USART_init();
		
		/*LCD Initialization*/
		LCD_init();
		
		/*KPD initialization*/
		KPD_init();
		
		/*Delete this task after initialization*/
		vTaskDelete(NULL);
	}	
	return;
}

/*LCD Task used to display the entered message from KPD or Received through UART from the other MCU*/
void LCD_Task(void *pv_LCD_Data)
{
	for(;;)
	{
		/*Validate if there's a new character pressed over LCD or not*/
		if(KPD_Status == KPD_NEW_PRESS)
		{
			/*If there's a new character display it over LCD first ROW*/
			LCD_gotoRowColumn(ROW_0 , (COL_0 + gu8_KPD_EnteredData));
			
			/*Display the new character*/
			LCD_displayChar(gu8_KPD_Char);
			
			/*Store the new character in UART data array to be sent later*/
			gu8_UART_SendArr[gu8_KPD_EnteredData] = gu8_KPD_Char;
			
			/*Increase data characters entered by KPD*/
			gu8_KPD_EnteredData++;
		}
		else
		{
			/*DO nothing*/
		}
		
		/*Validate if there's a new data byte received by UART or not*/
		if(UART_Status == USART_DATA_RECEIVED)
		{
			/*Validate if the received data isn't the terminating character and not in reset condition*/
			if(gu8_UART_Recv != UART_MSG_TERM_CHR && gu8_UART_Recv != RESET)
			{
				/*Display the received data over LCD in the second ROW*/
				LCD_gotoRowColumn(ROW_1 , (COL_0 + gu8_UART_EnteredData));
				
				/*Display the received data byte*/
				LCD_displayChar(gu8_UART_Recv);
				
				/*Increase the counter of received bytes by UART*/
				gu8_UART_EnteredData++;				
			}
			else if( gu8_UART_Recv == UART_MSG_TERM_CHR)
			{
				/*If the UART received the terminating character then keep the receiving variable in reset mode*/
				gu8_UART_Recv = RESET;
				
				/*Block the task for 2 seconds then clear the LCD*/
				vTaskDelay(DEL_2SEC);
				
				/*Clear the LCD*/
				LCD_clear();
			}
		} 
		else
		{
			/*Do nothing*/
		}
		
		/*Task periodicity is 200ms*/
		vTaskDelay(DEL_200MS);
	}
	return;
}

/*KeyPad task used to get the pressed key*/
void KPD_Task(void *pv_KPD_Data)
{
	for(;;)
	{
		/*Check the pressed key over KPD and get the KPD status*/
		KPD_Status = KPD_PressedKey(&gu8_KPD_Char);
		
		/*Task periodicity is 30ms*/
		vTaskDelay(DEL_30MS);
	}	
	return;
}

/*Task used to send or receive data over UART*/
void UART_Task(void *pv_UART_Data)
{
	/*Variable used in indicating push button status*/
	uint8_t au8_PB_Status = 0;
	
	/*Variable used in looping operation*/
	uint8_t au8_loop_var = 0;
	for(;;)
	{	
		/*Read push button status*/
		DIO_Read(PB_PORT , PB_PIN , &au8_PB_Status);
		
		/*Validate push button status if it's pressed or not*/
		if(au8_PB_Status == LOW)
		{
			/*Send entered msg from KPD over UART*/
			for(au8_loop_var = 0 ; au8_loop_var < gu8_KPD_EnteredData ; au8_loop_var++)
			{
				/*Send bytes of entered msg by KPD*/
				USART_sendByte(gu8_UART_SendArr[au8_loop_var]);
				
				/*Sending periodicity is 200ms*/
				vTaskDelay(DEL_200MS);
			}
			
			/*Sending the terminating character*/
			USART_sendByte(UART_MSG_TERM_CHR);
			
			/*Wait for 200ms so that LCD task can catch it*/
			vTaskDelay(DEL_200MS);
			
			/*Turn ON SENT LED indicating that bytes has been sent successfully*/
			DIO_Write(LEDS_PORT , SENT_LED_PIN , HIGH);
			
			/*Wait for 200ms*/
			vTaskDelay(DEL_200MS);
			
			/*Turn off SENT LED*/
			DIO_Write(LEDS_PORT , SENT_LED_PIN , LOW);
			
			/*Clear the LCD*/
			LCD_clear();
			
			/*Entered KPD counter will be reset*/
			gu8_KPD_EnteredData = RESET;
		}
		else
		{
			/*Do nothing*/
		}
		
		/*Get the received byte through UART and report UART current status*/
		UART_Status = USART_recvByte(&gu8_UART_Recv);
		
		/*Validate if the received byte is the terminating character or not*/
		if(gu8_UART_Recv == UART_MSG_TERM_CHR)
		{
			/*Reset the UART received bytes counter*/
			gu8_UART_EnteredData = RESET;
			
			/*Turn On RECV LED*/
			DIO_Write(LEDS_PORT , RECV_LED_PIN , HIGH);
			
			/*Wait for 500ms*/
			vTaskDelay(DEL_500MS);
			
			/*Turn OFF RECV LED*/
			DIO_Write(LEDS_PORT , RECV_LED_PIN , LOW);			
		}
		else
		{
			/*DO nothing*/
		}
		
		/*Task periodicity is 200ms*/
		vTaskDelay(DEL_200MS);
	}
	return;
}

int main(void)
{
	/*Tasks creation to be scheduled by RTOS kernel*/
	xTaskCreate(SystemInit_Task,"InitTask",configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRI,NULL);
	xTaskCreate(UART_Task,"UARTT",configMINIMAL_STACK_SIZE,NULL,UART_TASK_PRI,NULL);	
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

