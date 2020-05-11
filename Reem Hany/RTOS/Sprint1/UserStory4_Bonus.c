#include "Services/FreeRTOS/FreeRTOS.h"
#include "Services/FreeRTOS/task.h"
#include "HAL/LED/LED.h"
#include "HAL/PushButton/pushButton.h"



/********************** BONUS *****************/
/*____________________________________________*/
/*_______________Bonus Types _________________*/
/*____________________________________________*/
typedef enum LedStates{
	yON,
	yFLASHING,
	rON,
	rFLASHING,
	gON,
}LedStates;

/*____________________________________________*/
/*______________Static Globals _______________*/
/*____________________________________________*/

static TaskHandle_t xHandle ;//Traffic task handle
static TaskHandle_t xHandle1;//Btn task handle
static TaskHandle_t xHandle2;//System init task handle
static LedStates LedCurrentState;//TrafficStates

/*____________________________________________*/
/*______________Task definition_______________*/
/*____________________________________________*/

/*
 * Task: SystemInit_Task
 * Task description: This Task used for initializing the used modules and globals
 */
void SystemInit_Task(void)
{
	//initializing globals
	LedCurrentState = gON;
	while(1)
	{
		//initializing modules
		Led_Init(LED_0);
		Led_Init(LED_1);
		Led_Init(LED_2);
		pushButtonInit(BTN_0);
		//Suspend this task to avoid repeating it again
		vTaskSuspend( xHandle2 );
	}
	
	
	
}


/*
 * Task: BTN_Task
 * Task description: This Task used for detecting whether the button is pressed
 *                   to indicate that user needs to pass the road by pressing a push button and
 *                   releasing it one time
 */
void BTN_Task(void)
{
	TickType_t xLastWakeTime;
	const TickType_t delayTicks = 200;//delay 200 ms
	static uint8__t u8IDLE =TRUE;
	while(1)
	{
		//Check if the btn is pressed
		if(pushButtonGetStatus(BTN_0) == Pressed)
		{
			u8IDLE= FALSE;//Mark that the btn is pressed and the task is not idle
		}
		else
		{
			//In case the task is not idle and the btn is pressed and released
			if (!u8IDLE)
			{
				//In case the light is green
				if( LedCurrentState == gON )
				{
						LedCurrentState =yON;//start traffic light system
				}
				u8IDLE =TRUE;//Mark that the task is idle again
			}
		}
		vTaskDelayUntil(&xLastWakeTime,delayTicks );
	}
}

/*
 * Task: Traffic_Task
 * Task description: This Task used for starting the traffic light system
 */
void Traffic_Task(void)
{
	TickType_t xLastWakeTime;
	 TickType_t delayTicks=50;
	static uint16__t u16flashingCounter=0;
	while (1)
	{
		switch(LedCurrentState)
		{
			//in case the state of light is yellow and time did not pass the expected 75% of the time(4secs)
			case yON:
			Led_On(LED_0);//yellow on
			Led_Off(LED_1);//red off
			Led_Off(LED_2);//green off
			LedCurrentState = yFLASHING;// changing the state
			delayTicks = 3000;// time for the delay 3 secs
			break;
			
			//in case the state of light is yellow and time passed the expected 75% of the time ( 10secs)
			case yFLASHING:
			Led_Toggle(LED_0);//yellow toggle
			Led_Off(LED_1);   //red off
			Led_Off(LED_2);  //green off
			//In case the remaining time of the yellow led state(flashing time)  hasn't finished yet
			if(u16flashingCounter<=800){
				u16flashingCounter+= 200;//increment the counter
				delayTicks=200;//time delay 200 ms
			}
			//In case the remaining time of the yellow led state(flashing time)  has finished 
			else
			{
				u16flashingCounter= 0;
				LedCurrentState = rON;//changing state
				delayTicks=200;//time delay 200 ms
				
			}
			break;
			
			//in case the state of light is red and time did not pass the expected 75% of the time(	10secs)
			case rON:
			Led_On(LED_1);//red on
			Led_Off(LED_0);//yellow off
			Led_Off(LED_2);//green off
			LedCurrentState = rFLASHING;// changing the state
			delayTicks=7500;// time for the delay 7.5 secs
			break;
			
			
			case rFLASHING:
			Led_Toggle(LED_1); //yellow toggle
			Led_Off(LED_0);	   //red off
			Led_Off(LED_2);	   //green off
			
			//In case the remaining time of the red led state(flashing time)  hasn't finished yet
			if(u16flashingCounter<=2200){
				u16flashingCounter+= 200;//increment the counter
				delayTicks=200;//time delay 200ms
			}
			//In case the remaining time of the yellow led state(flashing time)  has finished 
			else
			{
				u16flashingCounter= 0;
				LedCurrentState = gON;// changing the state
				delayTicks= 100;// time delay 100 ms rest of the 25% of the whole period
				
			}
			break;
			
			//in case the state of light is green 
			case gON:
			Led_On(LED_2);//green on
			Led_Off(LED_0);//yellow off
			Led_Off(LED_1);//red
			delayTicks=50; // time for the delay 50 ms
			break;
			
		}
		
		vTaskDelayUntil(&xLastWakeTime,delayTicks);

	}
	
}

int main(void)
{
	
    BaseType_t ret_,ret_1,ret_2,ret_3,ret_4;
	xHandle  = NULL;
	xHandle1 = NULL;
	xHandle2 = NULL;
	/*Creating tasks*/
    ret_2=  xTaskCreate(Traffic_Task   , "Traffic" , 1000 , NULL , 1 , &xHandle);
	ret_3= xTaskCreate (BTN_Task       , "BTN"     , 100 , NULL , 2 , &xHandle1);
	ret_4= xTaskCreate (SystemInit_Task, "sysInit" , 100  , NULL , 3 , &xHandle2);
	/* Start Scheduler */
	vTaskStartScheduler();

	
	return 0;
}
