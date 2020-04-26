/*
 * APP.c
 *	Sprint1   -->>  Story 2
 *	Requirements :
 *	   Use an existing RTOS project to write a simple lock program with the following requirements:
 *
 *		AGILE_REQ1:
 *						< Two tasks with user defined periodicities >
 *		AGILE_REQ2:
 *						< A task dedicated to read input from keypad >
 *		AGILE_REQ3:
 *						< A task dedicated to output on LCD >
 *		AGILE_REQ4:
 *						< User shall be able to enter any number from (0 -> 6) on keypad and numbers entered
 *		              are displayed on LCD >
 *		AGILE_REQ5:
 *						< Keypad shall contain an erase button, When pressed the LCD is cleared and cursor returns home >
 * 	AGILE_REQ6:
 *					   < Keypad shall contain an enter button, When pressed the LCD is cleared and cursor returns home >
 *		AGILE_REQ7:
 *						< User shall enter a 6 digit code and press enter and if the code is correct LCD shall display “Correct password” for two seconds and switch to accept new inputs from user >
 *
 * Created on   : 4/15/2020 5:40:23 PM
 * Author       : AYA & EMAN
 */

/*
*** Inclusions
*/
#include "APP.h"

/*
*** Local Macros
*/

#define KEYPAD_GET_KEY_PERIODICITY		200
#define LCD_DISPLAY_CHAR_PERIODICITY   200	
#define PRIORITY_ONE			            1
#define PRIORITY_TWO		               2
#define MAX_NUMBER_OF_DIGIT	         6
#define TIME_TO_ACCEPT_NEW_INPUT       2000  //2 SEC

#define INITIAL_VALUE 0

/*
*** Global Static Variables
*/
volatile static uint8_t gu8_Kepad_Key ;
static uint8_t gu8_Password_Arr[6]= {1,2,3,4,5,6};
	
/*
*** Local Function Prototypes
*/
static void vTaskCode_KYEPAD_GetKey( void * );
static void vTaskCode_Init( void * );
static void vTaskCode_LCD_Display( void * );


/* 
 * vTasksCreation_LCD_Display
 * Prototype	: void vTasksCreation_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_LCD_Display( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_LCD_Display,       /* Function that implements the task. */
										"LCD Display Key",           /* Text name for the task. */
										configMINIMAL_STACK_SIZE,   /* Stack size in words, not bytes. */
										( void * ) 1,               /* Parameter passed into the task. */
										PRIORITY_ONE,               /* Priority at which the task is created. */
										&xHandle                    /* Used to pass out the created task's handle. */
							    );
}

/* 
 * vTaskCode_LCD_Display
 * Prototype	: static void vTaskCode_LCD_Display( void * pvParameters );
 * Description : Task Code for Display Input from Keypad on LCD every 200 msec
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void vTaskCode_LCD_Display( void * pvParameters )
{
	static uint8_t au8_Count_Digit = INITIAL_VALUE;
	uint8_t au8_Password_Arr[6] = {INITIAL_VALUE};
	uint8_t	au8_Correct_Digit_Count = INITIAL_VALUE;
	for( ;; )
	{
		/* In case we Enter C to Clear LCD*/
		if (gu8_Kepad_Key == 'c')
		{
			LCD_Send_Cmd(CLEAR_LCD);
			LCD_GoTo_Row_Col(ROW_0,COL_0);
			au8_Correct_Digit_Count = INITIAL_VALUE;
			au8_Count_Digit = INITIAL_VALUE;
		}
		/* In Case we Entered E to Enter the Password and need to check Whether it's a correct password or not */
		else if (gu8_Kepad_Key == 'E')
		{
			LCD_Send_Cmd(CLEAR_LCD);
			LCD_GoTo_Row_Col(ROW_0,COL_0 );
			
			/*It's mentioned that the password consists of 6 digit so we need to check first if it consists of 6 digit or not*/
			if (au8_Count_Digit == MAX_NUMBER_OF_DIGIT)
			{
				/* the second level of checking is to check whether the compare counter variable equal to the number of digit,
				   which mean the entered Password is correct or not*/
				if (au8_Correct_Digit_Count== MAX_NUMBER_OF_DIGIT)
				{
					LCD_Display_String("Correct Password");
					vTaskDelay(TIME_TO_ACCEPT_NEW_INPUT);
				}
				else
				{
					LCD_Display_String("Wrong Password");
					vTaskDelay(TIME_TO_ACCEPT_NEW_INPUT);

				}
	   	}
			else
			{
				LCD_Display_String("Wrong Password");
				vTaskDelay(TIME_TO_ACCEPT_NEW_INPUT);

			}
			
			/* Common actions we need to take Whether the password was correct or not */
			LCD_Send_Cmd(CLEAR_LCD);
			LCD_GoTo_Row_Col(ROW_0,COL_0);
			au8_Correct_Digit_Count = INITIAL_VALUE;
			au8_Count_Digit = INITIAL_VALUE;
		}
		
		/* It's Mentioned that the Password should consists of 6 digits including numbers from 0 to 6 */
		else if (gu8_Kepad_Key >= '0' && gu8_Kepad_Key <= '6' && au8_Count_Digit < MAX_NUMBER_OF_DIGIT)
	   {
			LCD_Display_Char(gu8_Kepad_Key );
				
			/* Store the key to compare it with the corresponding element in the global array which contain the correct password
				to determine whether the password is correct or not*/
			au8_Password_Arr[au8_Count_Digit]=gu8_Kepad_Key- '0';
				
			/* check Elements */
			if (au8_Password_Arr[au8_Count_Digit] == gu8_Password_Arr[au8_Count_Digit])
			{
				au8_Correct_Digit_Count++;      // increment the number of matched digits
			}
				
			au8_Count_Digit++;
		}
		
		vTaskDelay(LCD_DISPLAY_CHAR_PERIODICITY);
	}
		
}

/* 
 * vTaskCode_KYEPAD_GetKey
 * Prototype	: static void vTaskCode_KYEPAD_GetKey( void * pvParameters );
 * Description : Task Code for Read Input from Keypad every 200 msec
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */

static void vTaskCode_KYEPAD_GetKey( void * pvParameters )
{
	for( ;; )
	{
		gu8_Kepad_Key = KEYPAD_uint8_get_key_pressed();
		vTaskDelay(KEYPAD_GET_KEY_PERIODICITY);
	}
}


/* 
 * vTasksCreation_KYEPAD_GetKey
 * Prototype	: void vTasksCreation_KYEPAD_GetKey( void );
 * Description : Task Code To create Keypad Read Input Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreation_KYEPAD_GetKey( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_KYEPAD_GetKey,         /* Function that implements the task. */
										"KYEPAD GetKey",							/* Text name for the task. */
										configMINIMAL_STACK_SIZE,			/* Stack size in words, not bytes. */
										( void * ) 1,							/* Parameter passed into the task. */
										PRIORITY_TWO,							/* Priority at which the task is created. */
										&xHandle									/* Used to pass out the created task's handle. */
									);        
}

/* 
 * vTaskCode_Init
 * Prototype	: static void vTaskCode_Init( void * pvParameters );
 * Description : Task Code for Initialization Task
 * Input       : Pointer to the task’s parameters.
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
static void vTaskCode_Init( void * pvParameters )
{
	
	 LCD_Init();
	 KEYPAD_void_init();
	vTaskSuspend(NULL);
}


/* 
 * vTasksCreationInit
 * Prototype	: void vTasksCreationInit( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
void vTasksCreationInit( void )
{
	BaseType_t xReturned;
	TaskHandle_t xHandle = NULL;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(
										vTaskCode_Init,					/* Function that implements the task. */
										"Init Task",						/* Text name for the task. */
										configMINIMAL_STACK_SIZE,     /* Stack size in words, not bytes. */
										( void * ) 1,                 /* Parameter passed into the task. */
										PRIORITY_ONE,                 /* Priority at which the task is created. */
										&xHandle 
								  );
}

