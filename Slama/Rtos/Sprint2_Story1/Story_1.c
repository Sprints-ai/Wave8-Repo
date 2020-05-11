#include "FreeRTOS.h"
#include "task.h"
#include "/LCD_APP/MCAL/DIO.h"
#include "/LCD_APP/MCAL/registers.h"
#include "/LCD_APP/SERVICE/LCD.h"
#include "my_keypad.h"
#include "event_groups.h"

/************************************************************************/
/*							DEFINES                                     */
/************************************************************************/

/*Priorities*/
#define PERIORITY_1 (1)
#define PERIORITY_2 (2)
#define PERIORITY_3 (3)
#define PERIORITY_4 (4)
#define PERIORITY_5 (5)

/*Flags Macros*/
#define BTN_HIGH (1)
#define BTN_LOW (0)

/*LED Control*/
#define BTN2_CONTROL (2)
#define BTN1_CONTROL (1)
#define NO_CONTROL (0)

/*Task Parameters Defines*/
#define STACK_100_WORD (100)
#define NO_PARAMETERS (1)

/*LCD Defines*/
#define NULL_CHAR ('0')
#define MAX_CHAR_NUM (7)


/*Common Struct for variables*/
typedef struct
{
	uint8_t BTN1_Flag;
	uint8_t BTN2_Flag;
	uint8_t LED_CNTROL;
}str_Flags_t;

/************************************************************************/
/*							GLOBALS                                      */
/************************************************************************/
/*Create Dio Struct*/
st_DIO_Cfg_t st_Dio_init;

str_Flags_t str_Flags;

/*Event group Variables*/
EventGroupHandle_t xCreatedEventGroup;

/*Event Groupt Macro*/
#define EVENT_BIT_2 (0x02)

/*Handles*/
TaskHandle_t Sys_Init = ZERO;
TaskHandle_t BTN1_Handle = ZERO;
TaskHandle_t BTN2_Handle = ZERO;
TaskHandle_t LED_Handle = ZERO;

/************************************************************************/
/*								APIS                                    */
/************************************************************************/
/*SystemInit
*Description : Task To init LCD and Dio once then Suspended
..It has the highest priority
*/
void System_Init(void * pvParameters)
{
	while(1)
	{
	st_Dio_init.GPIO = GPIOB;
	st_Dio_init.pins = PIN0;
	st_Dio_init.dir = INPUT;
	
	DIO_init(&st_Dio_init);
	st_Dio_init.GPIO = GPIOB;
	st_Dio_init.pins = PIN1;
	st_Dio_init.dir = INPUT;
	
	DIO_init(&st_Dio_init);
	
	st_Dio_init.GPIO = GPIOB;
	st_Dio_init.pins = PIN2;
	st_Dio_init.dir = OUTPUT;
	
	DIO_init(&st_Dio_init);
	
	LCD_init(DATA_BITS_4);
	
	 xCreatedEventGroup = xEventGroupCreate();

	vTaskSuspend(NULL);
	}
}

void BTN1(void)
{
	/*Create Event bits*/
	EventBits_t uxBits;
	
	/*Create Btn Flag*/
	uint8_t Data = LOW;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 50;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	/*Check if event was created or not*/
	if(xCreatedEventGroup == NULL);
	
	else
	{
		/*Set Even Bit*/
		uxBits = xEventGroupSetBits(xCreatedEventGroup , EVENT_BIT_2);
		
			
	}
	while(1)
	{
		DIO_Read(GPIOB,PIN0,&Data);
		
		if(Data == PIN0)
		{
			
			uxBits = xEventGroupWaitBits(xCreatedEventGroup,EVENT_BIT_2 ,pdFALSE,pdFALSE,0);
			
			/*Check if event 2 is available or not*/
			if(uxBits == EVENT_BIT_2)
			{
				/*Raise btn flag and give control to button 1*/
				str_Flags.BTN1_Flag = BTN_HIGH;
				str_Flags.LED_CNTROL = BTN1_CONTROL;
			}
			else
			{
				/*Wait Only*/
			}
		}
		else
		{
			/*If no input then clear event flag*/
			xEventGroupClearBits(xCreatedEventGroup , EVENT_BIT_2);
			
			/*Clear btn flag*/
			str_Flags.BTN1_Flag = BTN_LOW;
			
		}
		vTaskDelayUntil(&xLastWakeTime , xFrequency);
	}
}

void BTN2(void)
{
	/*Create Event bits*/
	EventBits_t uxBits;
	
	/*Create Btn Flag*/
	uint8_t Data = LOW;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 50;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
	DIO_Read(GPIOB,PIN1,&Data);
	
	/*Check for Data*/
	if(Data == PIN1)
	{
		uxBits = xEventGroupWaitBits(xCreatedEventGroup,0x02 ,pdFALSE,pdFALSE,0);
	
		/*Check if event flag is cleared or btn1 uses it*/
		if(uxBits == 0x00)
		{
			/*Raise btn2 flag and give control to it*/
			str_Flags.BTN2_Flag = BTN_HIGH;
			str_Flags.LED_CNTROL = BTN2_CONTROL;
		}
		else
		{
			/*Wait till flag cleared*/
		}
	}
	else
	{
		/*if not data then set event flag to let btn1 uses it*/
		uxBits = xEventGroupSetBits(xCreatedEventGroup , EVENT_BIT_2);
		
		/*Clear btn2 flag*/
		str_Flags.BTN2_Flag = BTN_LOW;
	}
	vTaskDelayUntil(&xLastWakeTime , xFrequency);	
	}
}

void LED(void)
{
	/*Create Event bits*/
	EventBits_t uxBits;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		/*If any btn pressed then turn led on*/
		if((str_Flags.BTN1_Flag == BTN_HIGH ) || (str_Flags.BTN2_Flag == BTN_HIGH))
		{
			DIO_Write(GPIOB , PIN2 , HIGH);
		}
		/*Clear led and switch led flag to no control*/
		else
		{
			str_Flags.LED_CNTROL = NO_CONTROL;
			DIO_Write(GPIOB , PIN2 , LOW);
		}
		vTaskDelayUntil(&xLastWakeTime , xFrequency);
	}
}

void LCD(void)
{	
	/*Create Event bits*/
	EventBits_t uxBit;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		
		if(str_Flags.LED_CNTROL == BTN1_CONTROL)
		{
			
			LCD_displayStringRowColumn(0,0,"BTN1 OPERATE");
		}
		else if(str_Flags.LED_CNTROL == BTN2_CONTROL)
		{
			LCD_displayStringRowColumn(0,0,"BTN2 OPERATE");
		}
		else
		{
			LCD_displayStringRowColumn(0,0,"LED IS OFF  ");
		}
		
		vTaskDelayUntil(&xLastWakeTime , xFrequency);
	}
}

int main(void)
{

	
	/*Task Creation*/
	xTaskCreate(LCD,"LCD" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_1,&LED_Handle );
	xTaskCreate(LED,"LED" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_2,&LED_Handle );
	xTaskCreate(BTN2,"BTN2" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_3, &BTN2_Handle);
 	xTaskCreate(BTN1,"BTN1" , STACK_100_WORD , (void * ) NO_PARAMETERS ,PERIORITY_4, &BTN1_Handle);
 	xTaskCreate(System_Init,"SysIn" , STACK_100_WORD , (void * ) NO_PARAMETERS , PERIORITY_5 , &Sys_Init);
 	
 	/* Start Scheduler */
 	vTaskStartScheduler();

	while(1)
	{
		
	}
}
