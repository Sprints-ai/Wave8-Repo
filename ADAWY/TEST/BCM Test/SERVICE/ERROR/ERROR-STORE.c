/*
 * ERROR_STORE.c
 *
 * Created: 2/25/2020 1:01:18 PM
 *  Author: Khaled
 */ 

#include "ERROR-STORE.h"

#define ZERO 0

/*global variables*/
static uint8_t gu8_Error_Buffer_Counter = ZERO;
str_Error_t strarr_Error [ERROR_BUFFER_SIZE];



extern void Error_Push (uint8_t Module, uint8_t Error)
{
	gu8_Error_Buffer_Counter++;
	strarr_Error[gu8_Error_Buffer_Counter].u8_Module_Number = Module;
	strarr_Error[gu8_Error_Buffer_Counter].u8_Error_Number = Error;

}

void Error_Print (void)
{
	uint8_t au8_Print_Loop_Counter = ZERO;
	if (ZERO == gu8_Error_Buffer_Counter)
	{
		printf("NO ERRORS");
	}
	else if (ZERO != gu8_Error_Buffer_Counter)
	{
		for (au8_Print_Loop_Counter = 1; au8_Print_Loop_Counter <= gu8_Error_Buffer_Counter; au8_Print_Loop_Counter++)
		{
			printf("Module name: ");
			switch (strarr_Error[au8_Print_Loop_Counter].u8_Module_Number)
			{
			case TMU_MODULE:
				printf("TMU MODULE \n");
				break;

			default:
				printf("End of the errors \n");
				break;
			}
			/******************************************************************************************/
			printf("Error name: ");
			switch (strarr_Error[au8_Print_Loop_Counter].u8_Error_Number)
			{
			case ERROR_NULL_POINTER:
				printf("NULL POINTER \n");
				break;

			case ERROR_INVALID_PARAMETER:
				printf("INVALID PARAMETER \n");
				break;

			case ERROR_NOT_INITIALIZED:
				printf("NOT INITIALIZED \n");
				break;

			case ERROR_ALREADY_INITIALIZED:
				printf("ALREADY INITIALIZED \n");
				break;

			case ERROR_STOP_WITHOUT_START:
				printf("STOP WITHOUT START \n");
				break;

			case ERROR_MULTIPLE_START:
				printf("MULTIPLE START \n");
				break;

			case ERROR_FULL_BUFFER:
				printf("FULL BUFFER \n");
				break;

			case ERROR_NOT_FULL_BUFFER:
				printf("NOT FULL BUFFER \n");
				break;

			case ERROR_EMPTY_BUFFER:
				printf("EMPTY BUFFER \n");
				break;

			case ERROR_NOT_EMPTY_BUFFER:
				printf("NOT EMPTY BUFFER \n");
				break;

			default:
				printf("**************************************************************************\n");
				break;
			}
		}
		gu8_Error_Buffer_Counter = ZERO;
	}
}
