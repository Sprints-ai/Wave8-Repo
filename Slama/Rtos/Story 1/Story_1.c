#include "FreeRTOS.h"
#include "task.h"
#include "/LCD_APP/MCAL/DIO.h"


/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/
#define PERIORITY_1 (1)
#define PERIORITY_2 (2)
#define PERIORITY_3 (3)

#define STACK_100_WORD (100)

#define NO_PARAMETERS (1)

#define DELAY_TICKS (1000)
/************************************************************************/
/*							TASK Varibales                              */
/************************************************************************/
/*Create Dio Struct*/
st_DIO_Cfg_t Dio_init;

/************************************************************************/
/*								APIS                                    */
/************************************************************************/

/*LCDInit
*Description : Task To init LCD once then Suspended
..It has the highest priority
*/
void Sys_Init(void * pvParameters)
{
	while(1)
	{
	Dio_init.dir = OUTPUT;
	Dio_init.GPIO = GPIOA;
	Dio_init.pins = PIN0;
	
	DIO_init(&Dio_init);
	vTaskSuspend(NULL);
	}
}

/*Story 1 Task:
*Description : Toggle led with 1 second Periodicity
*/
void Led_Task(void * pvParameters)
{
	while(1)
	{
		DIO_Toggle(GPIOA , PIN0);
		
		vTaskDelay(DELAY_TICKS);
	}
}


int main(void)
{
	
	/*Create Tasks Handles*/
	TaskHandle_t Sys_Initialize = ZERO;
	TaskHandle_t LED = ZERO;
	
    /*Task Creation*/
	xTaskCreate(Led_Task,"LED" , STACK_100_WORD , (void *) NO_PARAMETERS ,PERIORITY_1, &LED);
	xTaskCreate(Sys_Init,"SysIn" , STACK_100_WORD , (void * ) NO_PARAMETERS , PERIORITY_3 , &Sys_Initialize);
	
	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{
	
	}
}
