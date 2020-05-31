/* Story2.c
 *
 * Created: 4/12/2020 1:41:08 PM
 *  Author: Khaled
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "Story2.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define STORY_SM_PASSWORD_ENTRY_STATE			0
#define STORY_SM_PASSWORD_CORRECT_STATE			1
#define STORY_SM_PASSWORD_INCORRECT_STATE		2
#define STORY_SM_NEW_INPUTS						3

#define PASSWORD_RANGE_MIN			0
#define PASSWORD_RANGE_MAX			6
#define PASSWORD_LENGTH				6

#define ERASE_BUTTON				7
#define ENTER_BUTTON				9

#define CORRECT_PASSWORD			123456

/********************************************************************************
 * 							  Global Static Variables							*
 ********************************************************************************/

static uint8_t gu8_Key;
static uint32_t gu32_StoredPassword = CORRECT_PASSWORD;
static uint32_t gu32_EnteredPassword = ZERO;


/********************************************************************************
 * 							  Story2 Tasks Declaration							*
 ********************************************************************************/

void Story2_KeyTask (void *pvParameters);
void Story2_InitTask (void *pvParameters);
void Story2_LcdWriteTask (void *pvParameters);


/********************************************************************************
 * 							   Story2 Implementation							*
 ********************************************************************************/

void Story2 (void)
{
	/* Create variable to store task handle */
	TaskHandle_t Story2_InitTaskHandle;

	/* Creation of Key task */
	xTaskCreate (Story2_KeyTask, "Key Checking", 100, NULL, 2,NULL);
	/* Creation of Initialization task */
	xTaskCreate (Story2_InitTask, "Init", 300, (void *)&Story2_InitTaskHandle, 3,&Story2_InitTaskHandle);
	/* Creation of Lcd task */
	xTaskCreate (Story2_LcdWriteTask, "D", 100, NULL, 1,NULL);

	/* Start Scheduler */
	vTaskStartScheduler();
}


/********************************************************************************
 * 							  Story2 Tasks Definition							*
 ********************************************************************************/

void Story2_InitTask (void *pvParameters)
{
	TickType_t xLastWakeTime;
	/* Create variable to store task handle */
	TaskHandle_t Story2_InitTaskHandle;

	/* Cast argument to variable type and store in the variable */
	Story2_InitTaskHandle = *((TaskHandle_t *)pvParameters);
	/* Initialize the xLastWakeTime variable with the current time */
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		/* Initialize our modules (LCD only in this story) */
		LCD_init();

		/* Suspend the task as it's an initialization task */
		vTaskSuspend( Story2_InitTaskHandle );/*suspend the task after finishing the initialization */
	}

}

void Story2_LcdWriteTask (void *pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 150;
	/* A counter to calculate number of entered numbers */
	static uint8_t au8_Counter = ZERO;

	/* State Machine for the task */
	uint8_t au8_Task_SM = STORY_SM_PASSWORD_ENTRY_STATE;

	/* Initialize the xLastWakeTime variable with the current time */
	xLastWakeTime = xTaskGetTickCount();

	while (1)
	{
		/* Wait for the next cycle */
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		switch(au8_Task_SM)
		{
		/* Case1: Need a correct password to proceed */
		case STORY_SM_PASSWORD_ENTRY_STATE:
			if(gu8_Key != NOT_PRESSED)
			{
				/* This if condition is entered in case the user didn't enter the full password */
				if(gu8_Key >= PASSWORD_RANGE_MIN && gu8_Key <= PASSWORD_RANGE_MAX && au8_Counter != PASSWORD_LENGTH)
				{
					/* Increment the counter of entered numbers */
					au8_Counter++;

					/* Display an asterisk instead of the entered number (because it is a password) */
					LCD_displayCharacter('*');

					/* Calculation of the entered password */
					gu32_EnteredPassword = gu32_EnteredPassword * 10 + gu8_Key;
				}
				/* This if condition is entered in case the user entered a correct password */
				else if(gu8_Key == ENTER_BUTTON && gu32_EnteredPassword == gu32_StoredPassword && au8_Counter == PASSWORD_LENGTH)
				{
					/* Clear the LCD screen */
					LCD_clear();

					/* Then go to the correct password state */
					au8_Task_SM = STORY_SM_PASSWORD_CORRECT_STATE;
				}
				/* This if condition is entered in case the user entered an incorrect password */
				else if(gu8_Key == ENTER_BUTTON && gu32_EnteredPassword != gu32_StoredPassword && au8_Counter == PASSWORD_LENGTH)
				{
					/* Clear the LCD screen */
					LCD_clear();

					/* Then go to the incorrect password state */
					au8_Task_SM = STORY_SM_PASSWORD_INCORRECT_STATE;
				}
			}
			break;
			/* Case2: The password is correct */
		case STORY_SM_PASSWORD_CORRECT_STATE:
			/* Display the "Correct" string on the LCD for 2 seconds */
			LCD_displayStringRowColumn(0, 0, "Correct!");
			vTaskDelay(2000);

			/* Then Clear the LCD screen and move to the new inputs state */
			LCD_clear();
			au8_Task_SM = STORY_SM_NEW_INPUTS;
			break;
			/* Case3: The password is incorrect */
		case STORY_SM_PASSWORD_INCORRECT_STATE:
			/* Display the "Incorrect" string on the LCD for 2 seconds */
			LCD_displayStringRowColumn(0, 0, "Incorrect, retry");
			vTaskDelay(2000);

			/* Then Clear the LCD screen and move to the entry state to let the user retry */
			LCD_clear();
			au8_Task_SM = STORY_SM_PASSWORD_ENTRY_STATE;

			/* Reset the variables which are to be reused in the re-trial process */
			gu32_EnteredPassword = 0;
			au8_Counter = 0;
			break;
			/* Case4: Last case in which the user can see the numbers he/she presses on the lcd */
		case STORY_SM_NEW_INPUTS:
			/* If the user reaches this case then he/she has entered the correct password and
			   now into the system, therefore, he/she can see the entered numbers */
			if(gu8_Key == ERASE_BUTTON)
				LCD_clear();
			else if(gu8_Key == ENTER_BUTTON)
				LCD_clear();
			else if(gu8_Key != NOT_PRESSED)
				LCD_displayInteger(gu8_Key);
			break;
		}
	}
}

void Story2_KeyTask (void *pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 150;

	/* Initialise the xLastWakeTime variable with the current time */
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		/* Wait for the next cycle */
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		/* Get the pressed key on the keypad */
		KeyPad_getPressedKey(&gu8_Key);
	}
}
