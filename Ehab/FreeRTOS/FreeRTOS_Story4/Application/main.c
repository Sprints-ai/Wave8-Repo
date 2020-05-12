

#include "../Services/FreeRTOS/FreeRTOS.h"
#include "../Services/FreeRTOS/task.h"

#define INIT_TASK_PRIORITY				(0)

#define BUTTON_TASK_PRIORITY			(1)
#define BUTTON_TASK_DELAY				(1)		/*Button Task delay in Milli seconds*/


#define	TRAFFIC_LIGHT_TASK_PRIORITY		(2)

#define GREEN_LIGHT						LED_2
#define YELLOW_LIGHT					LED_1
#define RED_LIGHT						LED_0

#define RED_LIGHT_DELAY					(10000)	/*delay time in Milli seconds*/
#define RED_LIGHT_DELAY_75PERCENT	((RED_LIGHT_DELAY/4)*3)
#define RED_LIGHT_TOGGLE				(200)		/*Toggling delay in Milli seconds*/

#define YELLOW_LIGHT_DELAY				(4000)	/*delay time in Milli seconds*/
#define YELLOW_LIGHT_DELAY_75PERCENT	((YELLOW_LIGHT_DELAY/4)*3)
#define YELLOW_LIGHT_TOGGLE				(200)		/*Toggling delay in Milli seconds*/

#define GREEN_LIGHT_DELAY				(1)		/*delay time in Milli seconds*/

#define INITIAL_COUNT					(-1)

 
/*Handler to the button Task to be used to suspend it for a while until the button is ready to be pressed again*/
TaskHandle_t gx_ButtonHandler;

/*Global Flag to be shared between the tasks*/
uint8_t gu8_TrafficLightTaskReady; 

/************************************************************************/
/*                     Initialization Task                              */
/************************************************************************/
void InitTask(void* pvParameters)
{
	while(1)
	{
		/*Initialize Traffic Light's LEDs*/
		Led_Init(GREEN_LIGHT);
		Led_Init(RED_LIGHT);
		Led_Init(YELLOW_LIGHT);
		
		/*Initialize push button 0*/
		pushButtonInit(BTN_0);
		
		/*Initialize the "ready flag" by FALSE which is to be set when the button is pressed*/
		gu8_TrafficLightTaskReady = FALSE;
		
		/*Suspend the task as it is of no further use*/
		vTaskSuspend(NULL);
		
	}
}

/************************************************************************/
/*                     PushButton Task                                  */
/************************************************************************/
void PushButtonTask(void* pvParameters)
{
	/*Variable to store the push button status in*/
	uint8_t u8_PushButtonStatus = Released;
	
	while(1)
	{
		/*Get the push button status*/
		pushButtonGetStatus(BTN_0,&u8_PushButtonStatus);
		
		/*Check the push button status if it is pressed set the "ready flag" for the traffic light task*/
		if (u8_PushButtonStatus == Pressed )
		{
			gu8_TrafficLightTaskReady = TRUE;
			
			/*Suspend the task untill the button is ready to be pressed again*/
			vTaskSuspend(gx_ButtonHandler);
		}
		
		/*delay for 1 Milli second*/
		vTaskDelay(BUTTON_TASK_DELAY);
	}
}

/************************************************************************/
/*                     Led Toggle Task                                  */
/************************************************************************/
void TrafficLightTask(void* pvParameters)
{

	sint32_t s32_Counter = INITIAL_COUNT;
	
	while(1)
	{
		/*check the "ready flag" which is set when the button is pressed*/
		if (gu8_TrafficLightTaskReady)
		{
			/*Switch the green light OFF*/
			Led_Off(GREEN_LIGHT);
			
			/*increment the counter each time this task is repeated (1 ms periodicity except when toggling the LED)*/
			s32_Counter++;
			
			/*this condition is true if the counter is less than the operation time of the yellow light*/
			if(s32_Counter<=YELLOW_LIGHT_DELAY)
			{
				/*this condition is true if the counter is more than or equal 75% of the yellow light operation time*/
				if (s32_Counter >= YELLOW_LIGHT_DELAY_75PERCENT)
				{
					/*Toggle the led and increment the counter by the value of the led toggling periodicity*/
					Led_Toggle(YELLOW_LIGHT);
					s32_Counter+=YELLOW_LIGHT_TOGGLE;
					
					/*Delay for the time of the led toggling periodicity*/
					vTaskDelay(YELLOW_LIGHT_TOGGLE);
				}
				/*Switch the yellow light ON when the time is less than 75% of the yellow light operation time*/
				else
				{
					Led_On(YELLOW_LIGHT);
				}
			}
			/*this condition is true if the counter is more than the operation time of the yellow light and less than
			the operation time of the red light + the operation time of the yellow light*/
			else if (s32_Counter>YELLOW_LIGHT_DELAY && s32_Counter<=(RED_LIGHT_DELAY+YELLOW_LIGHT_DELAY))
			{
				/*Switch the yellow light OFF*/
				Led_Off(YELLOW_LIGHT);
				
				/*this condition is true if the counter is more than or equal 75% of the red light operation time*/
				if(s32_Counter >= (YELLOW_LIGHT_DELAY+RED_LIGHT_DELAY_75PERCENT))
				{
					/*Toggle the led and increment the counter by the value of the led toggling periodicity*/
					Led_Toggle(RED_LIGHT);
					s32_Counter+=RED_LIGHT_TOGGLE;
					
					/*Delay for the time of the led toggling periodicity*/
					vTaskDelay(RED_LIGHT_TOGGLE);
					
				}
				/*Switch the red light ON when the time is less than 75% of the red light operation time*/
				else
				{
					Led_On(RED_LIGHT);
				}
			}
			/*This condition is true if the counter is more than the operation times of the red light + yellow light*/
			else if (s32_Counter>(RED_LIGHT_DELAY+YELLOW_LIGHT_DELAY))
			{
				/*Clear the "Read flag" for the traffic light task*/
				gu8_TrafficLightTaskReady = FALSE;
				
				/*Resume the push button task as the button is now ready for another press*/
				vTaskResume(gx_ButtonHandler);
				
				/*Reset the counter to it's initial value*/
				s32_Counter = INITIAL_COUNT;
			}
		}
		/*if the "ready flag" is not set (push button is not pressed)*/
		else
		{
			/*Switch the green light ON*/
			Led_On(GREEN_LIGHT);
			
			/*Switch the yellow light OFF*/
			Led_Off(YELLOW_LIGHT);
			
			/*Switch the red light OFF*/
			Led_Off(RED_LIGHT);
		}
		
		
		vTaskDelay(GREEN_LIGHT_DELAY);
	}
	
}

/**************************************************************************************/
int main(void)
{
	/*Create the init task*/
	xTaskCreate(InitTask,NULL,configMINIMAL_STACK_SIZE,NULL,INIT_TASK_PRIORITY,NULL);
	
	/*Create the push button's task*/
	xTaskCreate(PushButtonTask,NULL,configMINIMAL_STACK_SIZE,NULL,BUTTON_TASK_PRIORITY,&gx_ButtonHandler);
	
	/*Create the Traffic light's Task*/
	xTaskCreate(TrafficLightTask,NULL,configMINIMAL_STACK_SIZE,NULL,TRAFFIC_LIGHT_TASK_PRIORITY,NULL);
	
	/*Start the scheduler*/
	vTaskStartScheduler();
	
	/*Code should not reach this point unless there is an error*/
	return 0;
}
