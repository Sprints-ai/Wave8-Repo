/*
 * ERROR_STORE.c
 *
 * Created: 2/25/2020 1:01:18 PM
 *  Author: Khaled
 */

 #include "ERROR-STORE.h"

 #define ZERO 0
 #define ONE 1
 /*global variables*/
 static uint8_t gu8_Error_Buffer_Counter;
 str_Error_t strarr_Error [ERROR_BUFFER_SIZE];


 extern void Error_Push (uint8_t Module, uint8_t Error)
 {
	 gu8_Error_Buffer_Counter++;
	 strarr_Error[gu8_Error_Buffer_Counter].u8_Module_Number = Module;
	 strarr_Error[gu8_Error_Buffer_Counter].u8_Error_Number = Error;

 }

 void Error_Print (void)
 {
    uint8_t au8_Print_Loop_Counter = ONE;
	 if (gu8_Error_Buffer_Counter==0)
	 {
		  printf("No Errors ");
	 }
	 else
	 {
		  for (au8_Print_Loop_Counter = ONE; au8_Print_Loop_Counter <= gu8_Error_Buffer_Counter; au8_Print_Loop_Counter++)
		  {
			  printf("Module name: ");
			  switch (strarr_Error[au8_Print_Loop_Counter].u8_Module_Number)
			  {
				  case SOS_MODULE:
				  printf("SOS MODULE \n");
				  break;
				  case BCM_MODULE:
				  printf("BCM MODULE \n");
				  break;
                  case TIMER_MODULE:
				  printf("TIMER MODULE \n");
				  break;


				  default:
				  printf("End of the errors \n");
				  break;
			  }

			  /******************************************************************************************/
			  printf(" Error name : ");
			  switch (strarr_Error[au8_Print_Loop_Counter].u8_Error_Number)
			  {
				  case ERROR_NULL_POINTER:
				  printf("NULL POINTER \n");
				  break;

				  case ERROR_INVALID_PARAMETER:
				  printf("INVALID PARAMETER \n");
				  break;

				  case ERROR_SOS_NOT_INITIALIZED:
				  printf("SOS NOT INITIALIZED \n");
				  break;
				  case ERROR_TIMER_NOT_INITIALIZED :
				  printf("TIMER NOT INITIALIZED \n");
				  break;
                  case ERROR_SOS_DELETING_BEFORE_CREATING:
                  printf("ERROR_SOS_DELETING_BEFORE_CREATING \n");
				  break;
				  case ERROR_SOS_ALREADY_INITIALIZED:
				  printf("SOS ALREADY INITIALIZED \n");
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
				  printf("**************************************************************************");
				  break;

			  }
			   printf(" \n");
		  }
	 }
 }
