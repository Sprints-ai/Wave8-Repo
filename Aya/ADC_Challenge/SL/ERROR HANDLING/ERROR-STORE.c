/*
 * ERROR_STORE.c
 *
 * Created: 2/25/2020 1:01:18 PM
 *  Author: Khaled
 */ 

 #include "ERROR-STORE.h"
 #include "Errors.h"

 #define ZERO 0

 /*global variables*/
 static uint8_t gu8_Error_Buffer_Counter;
 str_Error_t strarr_Error [ERROR_BUFFER_SIZE];




 extern void Error_Push (uint8_t Module, uint8_t Error)
 {
	 strarr_Error[gu8_Error_Buffer_Counter].u8_Module_Number = Module;
	 strarr_Error[gu8_Error_Buffer_Counter].u8_Error_Number = Error;
	 gu8_Error_Buffer_Counter++;
 }

 void Error_Print (void)
 {
    uint8_t au8_Print_Loop_Counter = ZERO;
	 
	 for (au8_Print_Loop_Counter = ZERO; au8_Print_Loop_Counter <= gu8_Error_Buffer_Counter; au8_Print_Loop_Counter++)
	 {
	    printf("Module name: ");
		 switch (strarr_Error[au8_Print_Loop_Counter].u8_Module_Number)
	    {
		    case ADC_MODULE:
			 printf("ADC MODULE /n");
			 break;

			 default:
			 printf("End of the errors /n");
			 break;
	    }
		 /******************************************************************************************/
		 printf("Error name: ");
		 switch (strarr_Error[au8_Print_Loop_Counter].u8_Module_Number)
		 {
			 case ERROR_NULL_POINTER:
			 printf("NULL POINTER /n");
			 break;
			 
			 case ERROR_NOT_INITIALIZED:
			 printf("MODULE NOT INITIALIZED /n");
			 break;

			 case ERROR_ALREADY_INITIALIZED:
			 printf("MODULE ALREADY INITIALIZED /n");
			 break;


			 case ERROR_INVALID_CHANNEL_PARAMETER :
			 printf(" INVALID CHANNEL PARAMETER /n");
			 break;
			 
			 case ERROR_INVALID_MODULE_NUMBER :
			 printf(" INVALID MODULE NUMBER /n");
			 break;
			 
			 case ERROR_READ_WITHOUT_INITIALIZATION :
			 printf(" TRY TO READ WITHOUT INITIALIZE THE MODULE/n");
			 break;

			 case ERROR_INVALID_INPUT_SOURCE :
			 printf(" INVALID INPUT SOURCE/n");
			 break;
			 
			 case ERROR_INVALID_MUX_VALUE	:
			 printf(" INVALID MUX VALUE /n");
			 break;
			 
			 case  ERROR_INVALID_SAMPLE_SEQUENCER:
			 printf(" INVALID SAMPLE SEQUENCER VALUE /n");
			 break;
			 
			 case NO_ERROR :
			 printf(" NO ERROR /n");
			 break;
			 
			 default:
			 printf("**************************************************************************");
			 break;
		 }
	 }
 }