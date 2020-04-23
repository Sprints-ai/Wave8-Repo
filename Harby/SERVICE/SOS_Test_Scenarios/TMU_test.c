/*
 * SOSapp.c
 *
 * Created: 24-Feb-20 11:26:07 AM
 * Author : ahmed
 */

#include "stdio.h"
#include "SOS_TS/SOS.h"
#include "Error_table.h"

#define TASK_STATE_DONE		1
#define TASK_STATE_NOTDONE	2

st_SOS_init initTest = {
		SOS_TMR_CH0
};

void SOS_initTesting(st_SOS_init *ConfigPtr)
{
	sint8_t output = 0;

	output = SOS_Init(ConfigPtr);

	if(output == ERROR_NULL_PTR_INIT)
	{
		printf("INIT ERROR #1 - NULL POINTER DETECTED\n");
	}

	if(output == ERROR_MULTIPLE_MODULE_INIT)
	{
		printf("INIT ERROR #2 - MULTIPLE MODULE INITIALIZATION\n");
	}

	if(output == INVALID_INIT_PARAMETER)
	{
		printf("INIT ERROR #3 - INVALID PARAMETER\n");
	}

	if(output == 0)
	{
		printf("INIT FUNCTION NO ERRORS\n");
	}
}

// init:		null pointer, not initialized start, multi init, stop without start,
// invalid parameters, multiple stops, mutli starts, buffer full


void SOS_startTesting(SOS_TaskType *SOS_start)
{
	sint8_t output = 0;

	output = SOS_Add_Task(SOS_start);

	if(output == ERROR_NULL_PTR_START)
	{
		printf("START ERROR #1 - NULL POINTER DETECTED\n");
	}

	if(output == ERROR_MULTIPLE_MODULE_START)
	{
		printf("START ERROR #2 - MULTIPLE MODULE START\n");
	}

	if(output == ERROR_START_FULL_BUFFER)
	{
		printf("START ERROR #3 - FULL BUFFER\n");
	}

	if(output == ERROR_MODULE_NOT_INIT)
	{
		printf("START ERROR #4 - MODULE NOT INITIALIZED\n");
	}

	if(output == ERROR_INVALID_START_PARAMETERS)
	{
		printf("START ERROR #5 - INVALID START PARAMETERS\n");
	}

	if(output == 0)
	{
		printf("START FUNCTION NO ERRORS\n");
	}

	// invalid parameters, module not initialized
}

void SOS_dispatchTesting(void)
{
	sint8_t output = 0;

	output = SOS_Run();

	if(output == ERROR_MODULE_NOT_INIT)
	{
		printf("DISPATCH ERROR #1 - MODULE NOT INITIALIZED\n");
	}
}

void SOS_stopTesting(uint8_t ID)
{
	sint8_t output = 0;

	output = SOS_Delete_Task(ID);

	if(output == ERROR_MODULE_DIDNOT_START)
	{
		printf("STOP ERROR #1 - TASK NOT STARTED\n");
	}
}

void callBackTest(void)
{

}

int main(void)
{
	/*************************  SOS_INIT_TESTING  *********************/

	/*
	 * TEST 1 Description : inserting a null pointer and checking output
	 * expected: NULL_POINTER_ERROR
	 * please remove comment to check it

	SOS_initTesting(NULL);

	*/


	/*
	 * TEST 2 Description: making multiple init and reading error
	 * expected: multiple init error
	 * please remove comment to check it

	SOS_Init(&initTest);

	SOS_initTesting(&initTest);

	*/


	/*
	 * TEST 3 Description : inserting invalid paramters
	 * expected: error invalid parameters
	 * please remove comment to check it


	SOS_initTesting(&initTest);

	*/


	/*************************  SOS_START_TESTING  *********************/

	/*
	 * TEST 1 Description : inserting a null pointer and checking output
	 * expected: NULL_POINTER_ERROR
	 * please remove comment to check it

	SOS_TaskType test = {
			SOS_PERIODIC,
			1,
			0,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	SOS_Init(&initTest);

	SOS_startTesting(NULL);

	*/


	/*
	 * TEST 2 Description : making multiple start and reading error
	 * expected: multiple start error
	 * please remove comment to check it

	SOS_TaskType test = {
			SOS_PERIODIC,
			1,
			0,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	SOS_Init(&initTest);

	SOS_Start_Timer(&test);

	SOS_startTesting(&test);

	 */


	/*
	 * TEST 3 Description : adding tasks while buffer is full
	 * expected: error full buffer
	 * please remove comment to check it

	SOS_TaskType test = {
			SOS_PERIODIC,
			1,
			0,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	SOS_Init(&initTest);
	SOS_Start_Timer(&test);

	test.u8_id = 2;

	SOS_Start_Timer(&test);

	test.u8_id = 3;

	SOS_startTesting(&test);

	 */


	/*
	 * TEST 4 Description : starting without initialization
	 * expected: error not initialized
	 * please remove comment to check it

	SOS_TaskType test = {
			SOS_PERIODIC,
			1,
			0,
			100,
			TASK_STATE_NOTDONE,
			&callBackTest
	};

	SOS_startTesting(&test);

	*/


	/*
	 * TEST 5 Description : starting with invalid parameters (null pointer instead of callback function address)
	 * expected: error invalid parameters
	 * please remove comment to check it

		SOS_TaskType test = {
				SOS_ONESHOOT,
				1,
				9,
				100,
				TASK_STATE_NOTDONE,
				NULL
		};

		SOS_Init(&initTest);
		SOS_startTesting(&test);
	*/

	/*
	 * TEST 6 Description : starting with invalid parameters (Invalid priority)
	 * expected: error invalid parameters
	 * please remove comment to check it

		SOS_TaskType test = {
				SOS_ONESHOOT,
				1,
				10,
				100,
				TASK_STATE_NOTDONE,
				&callBackTest
		};

		SOS_Init(&initTest);
		SOS_startTesting(&test);
	 */

	/*
	 * TEST 7 Description : starting with invalid parameters (3 instead of 0 or 1 (task state not done & task state done))
	 * expected: error invalid parameters
	 * please remove comment to check it
	*/
		SOS_TaskType test = {
				2,
				1,
				9,
				100,
				TASK_STATE_NOTDONE,
				&callBackTest
		};

		SOS_Init(&initTest);
		SOS_startTesting(&test);


	/*************************  SOS_DISPATCH_TESTING  *********************/

	/*
	 * TEST 1 Description : Dispatch without initialization
	 * expected: error not initialized
	 * please remove comment to check it



	SOS_dispatchTesting();

	*/

	/*************************  SOS_STOP_TESTING  *********************/

	/*
	 * TEST 1 Description : Stop without starting
	 * expected: error not started
	 * please remove comment to check it


	SOS_TaskType test = {
			SOS_PERIODIC,
			1,
			0,
			100,
			2,
			&callBackTest
	};

	SOS_Init(&initTest);
	 */
	/* SOS_DeInit function wasn't handled yet */
}
