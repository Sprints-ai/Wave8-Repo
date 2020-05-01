/*
 * ADC.c
 *
 * Created: 4/27/2020 5:47:48 AM
 *  Author: A_ayman
 */ 

/*
*** Inclusions
*/
#include "ADC.h"


/*
*** Local Macros
*/
#define INITIALIZED				1
#define NOT_INITIALIZED			0
#define ADC0_VREF					3.3
#define ADC1_VREF					3.3
#define ADC0_DIGITAL_VALUE    4095.0
#define ADC1_DIGITAL_VALUE    4095.0
									   
/*
*** Static Global Variables
*/

/* We Save Results in Two Different Arrays, one for Each Module, in Case the two modules Have different initialization, ex: having different Vref */
static uint32_t gu32_ADC0_Result[NUM_ACTIVATED_ADC_CHANNELS ];   // Store results of each ADC module 0 Activated Channel
static uint32_t gu32_ADC1_Result[NUM_ACTIVATED_ADC_CHANNELS ];   // Store results of each ADC module 1 Activated Channel
static uint8_t gu8_ADC_Module_Status = NOT_INITIALIZED;


/* this struct is used to store the status of every used channel*/
typedef struct 
{
	uint8_t  Channel_Status;  // only two variables initialized or not initialized
	}str_ADC_Channel_Status;
	
uint8_t ADC_Channel_Status_Arr[NUM_ACTIVATED_ADC_CHANNELS ];




/*  
*** void ADC_Init (void)
*** 
*** This Function is Responsible for Initialize ADC, by Following Some steps
*** - First step is to Enable CLK "Done in SysCtr configuration file"
*** - Second Step is to Enable the clock to the appropriate GPIO modules "Done in Port configuration file"
*** - Third Step is to Set the GPIO AFSEL bits for the ADC input pins 
*** -	Fourth Step is to Configure the AINx signals to be analog inputs
***      *** Sample Sequencer Configuration ***
*** - Fifth Step is to Ensure that the sample sequencer is disabled
*** - Sixth Step is to Configure the trigger event for the sample sequencer in the ADCEMUX register.
*** - Seventh Step is to configure the corresponding input source in the ADCSSMUXn register
*** - Eighth Step is to configure the sample control bits in the corresponding nibble in the ADCSSCTLn register
*** - Ninth Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS register.
*** Input : none
*** Output : ERROR_STATUS
**
*/
ERROR_STATUS ADC_Init (void)
{
	uint8_t au8_Loop_counter = ZERO;
	uint8_t au8_Ret_Status = E_OK;
	uint8_t au8_ADC_Module;
   uint8_t au8_ADC_Input;
	uint8_t au8_ADC_Sample_Sequencer;
	uint32_t au32_ADC_EMUX;
	uint32_t au32_ADC_SSMUX;
	uint32_t au32_ADC_Channel;
	
	
	//Check if the Module Initialized Before Or NOt
	if (gu8_ADC_Module_Status == NOT_INITIALIZED)
	{
		//Starting From This Step We Take Element By Element From The Array Of Structure and Apply The Steps Mensioned Before  
		for (au8_Loop_counter = ZERO; au8_Loop_counter < NUM_ACTIVATED_ADC_CHANNELS; au8_Loop_counter++)
		{
			au8_ADC_Module = gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Module; 
			au8_ADC_Input =  gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Input;
			au8_ADC_Sample_Sequencer = gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Sample_Sequencer;
			au32_ADC_Channel = gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Channel;
			au32_ADC_EMUX = gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Trigger_Source;
			au32_ADC_SSMUX = gstr_ADC_Activated_Channels_Arr[au8_Loop_counter].ADC_Sample_Input_Select;
		
		
			/* Determine Which ADC Module we are going to use */
   		switch (au8_ADC_Module ) 
			{
				case ADC_MODULE_0:
				{
					/* Determine Which Sample Sequencer we are going to use */
					switch (au8_ADC_Sample_Sequencer)
					{
						case 0:
						{
							/* Ensure that the sample sequencer is disabled */
							ADC0_ACTSS_R &= ~ ADC_ACTSS_ASEN0;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register */
							ADC0_EMUX_R &= ~ ADC_EMUX_EM0_M;
							ADC0_EMUX_R |= au32_ADC_EMUX;
						
							/* Determine whether we are going to read through input channel or reading internal temperature sensor */
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								/* To Make Sure That We Read From a Valid Channel Number */
								if (au32_ADC_Channel >= ADC_CH_0 && au32_ADC_Channel <= ADC_CH_11 )
								{
									switch (au32_ADC_EMUX)
									{
										case (ADC_MUX0_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R &= ~ADC_SSMUX0_MUX0_M;
									
											ADC0_SSMUX0_R |= au32_ADC_Channel << ADC_SSMUX0_MUX0_S;  // It specifies which of the analog inputs is
																														//	sampled for the analog-to-digital conversion. The value set here indicates
																														//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

											ADC0_SSCTL0_R |= ADC_SSCTL0_END0;   //1st Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE0;    //1st Sample Interrupt Enable  
											break;
										}
										case (ADC_MUX1_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX1_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX1_S; 
											ADC0_SSCTL0_R |= ADC_SSCTL0_END1;   //2nd Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE1;    //2nd Sample Interrupt Enable
											break;
										}
										case (ADC_MUX2_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX2_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX2_S;
											ADC0_SSCTL0_R |= ADC_SSCTL0_END2;   //3rd Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE2;    //3rd Sample Interrupt Enable
											break;
										}
										case (ADC_MUX3_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX3_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX3_S;
											ADC0_SSCTL0_R |= ADC_SSCTL0_END3;   //4th Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE3;    //4th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX4_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX4_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX4_S;
											ADC0_SSCTL0_R |= ADC_SSCTL0_END4;   //5th Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE4;    //5th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX5_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX5_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX5_S;
											ADC0_SSCTL0_R |= ADC_SSCTL0_END5;   //6th Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE5;    //6th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX6_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX6_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX6_S;
									
											ADC0_SSCTL0_R |= ADC_SSCTL0_END6;   //7th Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE6;    //7th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX7_SAMPLE_INPUT_SELECT):
										{
											ADC0_SSMUX0_R  &= ~ADC_SSMUX0_MUX7_M;
											ADC0_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX7_S;
									
											ADC0_SSCTL0_R |= ADC_SSCTL0_END7;   //8th Sample Is the End Of Sequence
											ADC0_SSCTL0_R |= ADC_SSCTL0_IE7;    //8th Sample Interrupt Enable
											break;
										}
										default:
										{
											au8_Ret_Status = E_NOK;
											//error invalid number of MUX
											Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
											break;
										}
									}
								}
								else
								{
									au8_Ret_Status = E_NOK;
									//error invalid channel number 
									Error_Push(ADC_MODULE, ERROR_INVALID_CHANNEL_PARAMETER);
								
								}
							}
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
	                   			ADC0_SSCTL0_R |= ADC_SSCTL0_TS0;    //1st Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END0;   //1st Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE0;    //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS1;    //2nd Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END1;   //2nd Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS2;    //3rd Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END2;   //3rd Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS3;    //4th Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END3;   //4th Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE3;    //4th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX4_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS4;    //5th Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END4;   //5th Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE4;    //5th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX5_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS5;    //6th Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END5;   //6th Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE5;    //6th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX6_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS6;    //7th Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END6;   //7th Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE6;    //7th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX7_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL0_R |= ADC_SSCTL0_TS7;    //8th Sample Interrupt Enable
										ADC0_SSCTL0_R |= ADC_SSCTL0_END7;   //8th Sample Is the End Of Sequence
										ADC0_SSCTL0_R |= ADC_SSCTL0_IE7;    //8th Sample Interrupt Enable
										break;
									}
									default:
									{
										au8_Ret_Status = E_NOK;
										//error invalid number of MUX
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								//Error Invalid Input Source 
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							
							}
						
							/* Enable Sample Sequencer */
							ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
							break;
						}
						case ADC_SAMPLE_SEQUENCER_1 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC0_ACTSS_R &= ~ ADC_ACTSS_ASEN1;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC0_EMUX_R &= ~ ADC_EMUX_EM1_M;
							ADC0_EMUX_R |= au32_ADC_EMUX;
						
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX1_R &= ~ADC_SSMUX1_MUX0_M;
									
										ADC0_SSMUX1_R |= au32_ADC_Channel << ADC_SSMUX1_MUX0_S;  // It specifies which of the analog inputs is
																													//	sampled for the analog-to-digital conversion. The value set here indicates
																													//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

										ADC0_SSCTL1_R |= ADC_SSCTL1_END0;   //1st Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE0 ;   //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX1_R &= ~ADC_SSMUX1_MUX1_M;
										ADC0_SSMUX1_R |= au32_ADC_Channel <<  ADC_SSMUX1_MUX1_S;
										ADC0_SSCTL1_R |= ADC_SSCTL1_END1;   //2nd Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX1_R  &= ~ADC_SSMUX1_MUX2_M;
										ADC0_SSMUX1_R  |= au32_ADC_Channel <<  ADC_SSMUX1_MUX2_S;
										ADC0_SSCTL1_R |= ADC_SSCTL1_END2;   //3rd Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX1_R  &= ~ADC_SSMUX1_MUX3_M;
										ADC0_SSMUX1_R  |= au32_ADC_Channel <<  ADC_SSMUX1_MUX3_S;
										ADC0_SSCTL1_R |= ADC_SSCTL1_END3;   //4th Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE3;    //4th Sample Interrupt Enable
										break;	
									}
									default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL1_R |= ADC_SSCTL1_TS0;    //1st Sample Interrupt Enable
										ADC0_SSCTL1_R |= ADC_SSCTL1_END0;   //1st Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE0;    //1st Sample Interrupt Enable
										break;						  
									}									  
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{									  
										ADC0_SSCTL1_R |= ADC_SSCTL1_TS1;    //2nd Sample Interrupt Enable
										ADC0_SSCTL1_R |= ADC_SSCTL1_END1;   //2nd Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE1;    //2nd Sample Interrupt Enable
										break;						  
									}									  
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{									  
										ADC0_SSCTL1_R |= ADC_SSCTL1_TS2;    //3rd Sample Interrupt Enable
										ADC0_SSCTL1_R |= ADC_SSCTL1_END2;   //3rd Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE2;    //3rd Sample Interrupt Enable
										break;						  
									}									  
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{									  
										ADC0_SSCTL1_R |= ADC_SSCTL1_TS3;    //4th Sample Interrupt Enable
										ADC0_SSCTL1_R |= ADC_SSCTL1_END3;   //4th Sample Is the End Of Sequence
										ADC0_SSCTL1_R |= ADC_SSCTL1_IE3;    //4th Sample Interrupt Enable
										break;						  
									}

									default:
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							}
						
							/* Enable Sample Sequencer */
							ADC0_ACTSS_R |= ADC_ACTSS_ASEN1;
							break;
						}
					
						case ADC_SAMPLE_SEQUENCER_2 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC0_ACTSS_R &= ~ ADC_ACTSS_ASEN2;
											
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC0_EMUX_R &= ~ ADC_EMUX_EM2_M;
							ADC0_EMUX_R |= au32_ADC_EMUX;
											
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX2_R &= ~ADC_SSMUX2_MUX0_M;
										ADC0_SSMUX2_R |= au32_ADC_Channel << ADC_SSMUX2_MUX0_S;  // It specifies which of the analog inputs is
																													//	sampled for the analog-to-digital conversion. The value set here indicates
																													//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

										ADC0_SSCTL2_R |= ADC_SSCTL2_END0;   //1st Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE0 ;   //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX2_R &= ~ADC_SSMUX2_MUX1_M;
										ADC0_SSMUX2_R |= au32_ADC_Channel <<  ADC_SSMUX2_MUX1_S;
										ADC0_SSCTL2_R |= ADC_SSCTL2_END1;   //2nd Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX2_R  &= ~ADC_SSMUX2_MUX2_M;
										ADC0_SSMUX2_R  |= au32_ADC_Channel <<  ADC_SSMUX2_MUX2_S;
										ADC0_SSCTL2_R |= ADC_SSCTL2_END2;   //3rd Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSMUX2_R &= ~ADC_SSMUX2_MUX3_M;
										ADC0_SSMUX2_R |= au32_ADC_Channel <<  ADC_SSMUX2_MUX3_S;
										ADC0_SSCTL2_R |= ADC_SSCTL2_END3;   //4th Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE3;    //4th Sample Interrupt Enable
										break;
									}
									default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							/* In Case We Need To Read  Internal Temperature Sensor*/
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL2_R |= ADC_SSCTL2_TS0;    //1st Sample Interrupt Enable
										ADC0_SSCTL2_R |= ADC_SSCTL2_END0;   //1st Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE0;    //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL2_R |= ADC_SSCTL2_TS1;    //2nd Sample Interrupt Enable
										ADC0_SSCTL2_R |= ADC_SSCTL2_END1;   //2nd Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL2_R |= ADC_SSCTL2_TS2;    //3rd Sample Interrupt Enable
										ADC0_SSCTL2_R |= ADC_SSCTL2_END2;   //3rd Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC0_SSCTL2_R |= ADC_SSCTL2_TS3;    //4th Sample Interrupt Enable
										ADC0_SSCTL2_R |= ADC_SSCTL2_END3;   //4th Sample Is the End Of Sequence
										ADC0_SSCTL2_R |= ADC_SSCTL2_IE3;    //4th Sample Interrupt Enable
										break;
									}

									default:
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							}

							/* Enable Sample Sequencer */
							ADC0_ACTSS_R |= ADC_ACTSS_ASEN2;
							break;
						}
						case ADC_SAMPLE_SEQUENCER_3 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN3;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC0_EMUX_R &= ~ ADC_EMUX_EM3_M ;   
							ADC0_EMUX_R |= au32_ADC_EMUX;
						
							/* Check weather we need a Channel Input or Internal Temperature Sensor*/
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{					
								switch (au32_ADC_SSMUX)
								{
									case ADC_MUX0_SAMPLE_INPUT_SELECT :
									{
										ADC0_SSMUX3_R &= ~ADC_SSMUX3_MUX0_M ;
										ADC0_SSMUX3_R |= au32_ADC_Channel << ADC_SSMUX3_MUX0_S;
										ADC0_SSCTL3_R |= ADC_SSCTL3_END0;      //1st Sample Is the End Of Sequence          
										ADC0_SSCTL3_R |= ADC_SSCTL3_IE0;       //1st Sample Interrupt Enable
										break;															
									}
									default :
									{
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										au8_Ret_Status = E_NOK;
										break;
									}
								}			
							}
							
							/* In Case We Need To Read  Internal Temperature Sensor*/
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_SSMUX)
								{
									case ADC_MUX0_SAMPLE_INPUT_SELECT :
									{											   
										ADC0_SSCTL3_R |= ADC_SSCTL3_TS0;   //1st Sample Interrupt Enable
										ADC0_SSCTL3_R |= ADC_SSCTL3_END0;  //1st Sample Is the End Of Sequence
										ADC0_SSCTL3_R |= ADC_SSCTL3_IE0;   //1st Sample Interrupt Enable
										break;
									}
									default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
								
									}
								}
							}
							else
							{
								//Error Invalid argument, invalid input source
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
								au8_Ret_Status = E_NOK;
							}

							/* Enable Sample Sequencer */
							ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;
							break;
						}
						default:
						{
							au8_Ret_Status = E_NOK;
							Error_Push(ADC_MODULE, ERROR_INVALID_SAMPLE_SEQUENCER);
							break;
						}
					}	
					break;	
				}
			
				/********************************************************* ADC1 Module ************************************************/
			
				case ADC_MODULE_1:
				{
					/* Determine Which Sample Sequencer we are going to use */
					switch (au8_ADC_Sample_Sequencer)
					{
						case ADC_SAMPLE_SEQUENCER_0 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC1_ACTSS_R &= ~ ADC_ACTSS_ASEN0;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register */
							ADC1_EMUX_R &= ~ ADC_EMUX_EM0_M;
							ADC1_EMUX_R |= au32_ADC_EMUX;
						
							/* Determine whether we are going to read through input channel or reading internal temperature sensor */
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								/* To Make Sure That We Read From a Valid Channel Number */
								if (au32_ADC_Channel >= ADC_CH_0 && au32_ADC_Channel <= ADC_CH_11 )
								{
									switch (au32_ADC_EMUX)
									{
										case (ADC_MUX0_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R &= ~ADC_SSMUX0_MUX0_M;
										
											ADC1_SSMUX0_R |= au32_ADC_Channel << ADC_SSMUX0_MUX0_S;  // It specifies which of the analog inputs is
											//	sampled for the analog-to-digital conversion. The value set here indicates
											//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

											ADC1_SSCTL0_R |= ADC_SSCTL0_END0;   //1st Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE0;    //1st Sample Interrupt Enable
											break;
										}
										case (ADC_MUX1_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX1_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX1_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END1;   //2nd Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE1;    //2nd Sample Interrupt Enable
											break;
										}
										case (ADC_MUX2_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX2_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX2_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END2;   //3rd Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE2;    //3rd Sample Interrupt Enable
											break;
										}
										case (ADC_MUX3_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX3_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX3_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END3;   //4th Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE3;    //4th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX4_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX4_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX4_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END4;   //5th Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE4;    //5th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX5_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX5_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX5_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END5;   //6th Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE5;    //6th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX6_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX6_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX6_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END6;   //7th Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE6;    //7th Sample Interrupt Enable
											break;
										}
										case (ADC_MUX7_SAMPLE_INPUT_SELECT):
										{
											ADC1_SSMUX0_R  &= ~ADC_SSMUX0_MUX7_M;
											ADC1_SSMUX0_R  |= au32_ADC_Channel <<  ADC_SSMUX0_MUX7_S;
											ADC1_SSCTL0_R |= ADC_SSCTL0_END7;   //8th Sample Is the End Of Sequence
											ADC1_SSCTL0_R |= ADC_SSCTL0_IE7;    //8th Sample Interrupt Enable
											break;
										}
										default:
										{
											au8_Ret_Status = E_NOK;
											//error invalid number of MUX
										//	Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
											break;
										}
									}
								}
								else
								{
									au8_Ret_Status = E_NOK;
									//error invalid channel number
									Error_Push(ADC_MODULE, ERROR_INVALID_CHANNEL_PARAMETER);
								
								}
							}
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS0;    //1st Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END0;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE0;    //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS1;    //2nd Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END1;   //2nd Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS2;    //3rd Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END2;   //3rd Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS3;    //4th Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END3;   //4th Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE3;    //4th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX4_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS4;    //5th Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END4;   //5th Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE4;    //5th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX5_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS5;    //6th Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END5;   //6th Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE5;    //6th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX6_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS6;    //7th Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END6;   //7th Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE6;    //7th Sample Interrupt Enable
										break;
									}
									case (ADC_MUX7_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL0_R |= ADC_SSCTL0_TS7;    //1st Sample Interrupt Enable
										ADC1_SSCTL0_R |= ADC_SSCTL0_END7;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL0_R |= ADC_SSCTL0_IE7;    //1st Sample Interrupt Enable
										break;
									}
									default:
									{
										au8_Ret_Status = E_NOK;
										//error invalid number of MUX
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								//Error Invalid Input Source
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							
							}
						
							/* Enable Sample Sequencer */
							ADC1_ACTSS_R |= ADC_ACTSS_ASEN0;
							break;
						}
						case ADC_SAMPLE_SEQUENCER_1 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC1_ACTSS_R &= ~ ADC_ACTSS_ASEN1;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC1_EMUX_R &= ~ ADC_EMUX_EM1_M;
							ADC1_EMUX_R |= au32_ADC_EMUX;
						
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX1_R &= ~ADC_SSMUX1_MUX0_M;
										ADC1_SSMUX1_R |= au32_ADC_Channel << ADC_SSMUX1_MUX0_S;  // It specifies which of the analog inputs is
																													//	sampled for the analog-to-digital conversion. The value set here indicates
																													//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

										ADC1_SSCTL1_R |= ADC_SSCTL1_END0;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE0 ;   //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX1_R &= ~ADC_SSMUX1_MUX1_M;
										ADC1_SSMUX1_R |= au32_ADC_Channel <<  ADC_SSMUX1_MUX1_S;
										ADC1_SSCTL1_R |= ADC_SSCTL1_END1;   //2nd Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX1_R  &= ~ADC_SSMUX1_MUX2_M;
										ADC1_SSMUX1_R  |= au32_ADC_Channel <<  ADC_SSMUX1_MUX2_S;
										ADC1_SSCTL1_R |= ADC_SSCTL1_END2;   //3rd Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX1_R  &= ~ADC_SSMUX1_MUX3_M;
										ADC1_SSMUX1_R  |= au32_ADC_Channel <<  ADC_SSMUX1_MUX3_S;
										ADC1_SSCTL1_R |= ADC_SSCTL1_END3;   //4th Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE3;    //4th Sample Interrupt Enable
										break;
									}
									default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL1_R |= ADC_SSCTL1_TS0;    //1st Sample Interrupt Enable
										ADC1_SSCTL1_R |= ADC_SSCTL1_END0;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE0;    //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL1_R |= ADC_SSCTL1_TS1;    //2nd Sample Interrupt Enable
										ADC1_SSCTL1_R |= ADC_SSCTL1_END1;   //2nd Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL1_R |= ADC_SSCTL1_TS2;    //3rd Sample Interrupt Enable
										ADC1_SSCTL1_R |= ADC_SSCTL1_END2;   //3rd Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL1_R |= ADC_SSCTL1_TS3;    //4th Sample Interrupt Enable
										ADC1_SSCTL1_R |= ADC_SSCTL1_END3;   //4th Sample Is the End Of Sequence
										ADC1_SSCTL1_R |= ADC_SSCTL1_IE3;    //4th Sample Interrupt Enable
										break;
									}

									default:
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							}
						
							/* Enable Sample Sequencer */
							ADC1_ACTSS_R |= ADC_ACTSS_ASEN1;
							break;
						}
					
						case ADC_SAMPLE_SEQUENCER_2 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC1_ACTSS_R &= ~ ADC_ACTSS_ASEN2;
						
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC1_EMUX_R &= ~ ADC_EMUX_EM2_M;
							ADC1_EMUX_R |= au32_ADC_EMUX;
						
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX2_R &= ~ADC_SSMUX2_MUX0_M;
									
										ADC1_SSMUX2_R |= au32_ADC_Channel << ADC_SSMUX2_MUX0_S;  // It specifies which of the analog inputs is
																													//	sampled for the analog-to-digital conversion. The value set here indicates
																													//	the corresponding pin, for example, a value of 0x1 indicates the input is AIN1.

										ADC1_SSCTL2_R |= ADC_SSCTL2_END0;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE0 ;   //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX2_R &= ~ADC_SSMUX2_MUX1_M;
										ADC1_SSMUX2_R |= au32_ADC_Channel <<  ADC_SSMUX2_MUX1_S;
										ADC1_SSCTL2_R |= ADC_SSCTL2_END1;   //2nd Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX2_R  &= ~ADC_SSMUX2_MUX2_M;
										ADC1_SSMUX2_R  |= au32_ADC_Channel <<  ADC_SSMUX2_MUX2_S;
										ADC1_SSCTL2_R |= ADC_SSCTL2_END2;   //3rd Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSMUX2_R &= ~ADC_SSMUX2_MUX3_M;
										ADC1_SSMUX2_R |= au32_ADC_Channel <<  ADC_SSMUX2_MUX3_S;
										ADC1_SSCTL2_R |= ADC_SSCTL2_END3;   //4th Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE3;    //4th Sample Interrupt Enable
										break;
									}
									default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							 }
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_EMUX)
								{
									case (ADC_MUX0_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL2_R |= ADC_SSCTL2_TS0;    //1st Sample Interrupt Enable
										ADC1_SSCTL2_R |= ADC_SSCTL2_END0;   //1st Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE0;    //1st Sample Interrupt Enable
										break;
									}
									case (ADC_MUX1_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL2_R |= ADC_SSCTL2_TS1;    //2nd Sample Interrupt Enable
										ADC1_SSCTL2_R |= ADC_SSCTL2_END1;   //2nd Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE1;    //2nd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX2_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL2_R |= ADC_SSCTL2_TS2;    //3rd Sample Interrupt Enable
										ADC1_SSCTL2_R |= ADC_SSCTL2_END2;   //3rd Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE2;    //3rd Sample Interrupt Enable
										break;
									}
									case (ADC_MUX3_SAMPLE_INPUT_SELECT):
									{
										ADC1_SSCTL2_R |= ADC_SSCTL2_TS3;    //4th Sample Interrupt Enable
										ADC1_SSCTL2_R |= ADC_SSCTL2_END3;   //4th Sample Is the End Of Sequence
										ADC1_SSCTL2_R |= ADC_SSCTL2_IE3;    //4th Sample Interrupt Enable
										break;
									}

									default:
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								au8_Ret_Status = E_NOK;
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
							}

							/* Enable Sample Sequencer */
							ADC1_ACTSS_R |= ADC_ACTSS_ASEN2;
							break;
						}
						case ADC_SAMPLE_SEQUENCER_3 :
						{
							/* Ensure that the sample sequencer is disabled */
							ADC1_ACTSS_R &= ~ADC_ACTSS_ASEN3;
							
							/* Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
							ADC1_EMUX_R &= ~ ADC_EMUX_EM3_M ;
							ADC1_EMUX_R |= au32_ADC_EMUX;
							
							/* Check weather we need a Channel Input or Internal Temperature Sensor*/
							if (au8_ADC_Input == ADC_INPUT_CHANNELS)
							{
								switch (au32_ADC_SSMUX)
								{
									case ADC_MUX0_SAMPLE_INPUT_SELECT :
									{
										ADC1_SSMUX3_R &= ~ADC_SSMUX3_MUX0_M ;
										ADC1_SSMUX3_R |= au32_ADC_Channel << ADC_SSMUX3_MUX0_S;
										ADC1_SSCTL3_R |= ADC_SSCTL3_END0;      //1st Sample Is the End Of Sequence
										ADC1_SSCTL3_R |= ADC_SSCTL3_IE0;       //1st Sample Interrupt Enable
										break;
									}
									default :
									{
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										au8_Ret_Status = E_NOK;
										break;
									}
								}
							}
							else if (au8_ADC_Input == ADC_INTERNAL_TEMPERATURE_SENSOR)
							{
								switch (au32_ADC_SSMUX)
								{
									case ADC_MUX0_SAMPLE_INPUT_SELECT :
									{
										ADC1_SSCTL3_R |= ADC_SSCTL3_TS0;   //1st Sample Interrupt Enable
										ADC1_SSCTL3_R |= ADC_SSCTL3_END0;  //1st Sample Is the End Of Sequence
										ADC1_SSCTL3_R |= ADC_SSCTL3_IE0;   //1st Sample Interrupt Enable
										break;
									}
									
								   default :
									{
										au8_Ret_Status = E_NOK;
										Error_Push(ADC_MODULE, ERROR_INVALID_MUX_VALUE);
										break;
									}
								}
							}
							else
							{
								//Error Invalid argument, invalid input source
								Error_Push(ADC_MODULE, ERROR_INVALID_INPUT_SOURCE);
								au8_Ret_Status = E_NOK;
							}

								/* Enable Sample Sequencer */
								ADC1_ACTSS_R |= ADC_ACTSS_ASEN3;
								break;
							}
							default:
							{
								au8_Ret_Status = E_NOK;
								Error_Push(ADC_MODULE, ERROR_INVALID_SAMPLE_SEQUENCER);
								break;
							}
						}
						break;
					}
			
				default:
				{
					Error_Push(ADC_MODULE, ERROR_INVALID_MODULE_NUMBER);
					au8_Ret_Status = E_NOK;
					break;
				}
		
		
			}
			
			gu8_ADC_Module_Status |= au8_Ret_Status ;         // Accumulate all channels status so we can determine overall whether the module is initialized or not
																			  // for example if the channel 0 is initialized well, and channel 1 doesn't so over all adc is not initialized well						
			if (au8_Ret_Status == E_NOK)
			{
				ADC_Channel_Status_Arr[au8_Loop_counter] = NOT_INITIALIZED;
				au8_Ret_Status = E_OK;
			}
			else
			{
				ADC_Channel_Status_Arr[au8_Loop_counter] = INITIALIZED;
			}
		
		}
		if (gu8_ADC_Module_Status == E_OK)
		{
			gu8_ADC_Module_Status = INITIALIZED;
			au8_Ret_Status = E_OK;
		}
		else
		{
			gu8_ADC_Module_Status = NOT_INITIALIZED;
			au8_Ret_Status = E_NOK;
		
		}
	}
	else
	{
		Error_Push(ADC_MODULE, ERROR_ALREADY_INITIALIZED);
	}
	
	return au8_Ret_Status;

}


/*
*** this function is responsible to Start ADC Conversion
*** Input  : uint8_t  ADC_Index -> determine which elemnt from the  gstr_ADC_Activated_Channels_Arr we want to statart Conversion for it
***          uint32_t* u32_ADC_Digital_Reading -> to Get the Value using it
*** Output : ERROR_STATUS
*/
ERROR_STATUS ADC_Start_Conversion(uint8_t u8_ADC_Index, uint32_t* u32_ADC_Digital_Reading)
{
	
	uint8_t au8_ADC_Module;
	uint8_t au8_ADC_Sample_Sequencer;
   uint8_t au8_ADC_Ch_Status ;
	uint8_t au8_Ret_Status = E_OK;
	
	if (gu8_ADC_Module_Status == INITIALIZED)   //Make Sure that Module is already Initialized before Starting Conversion
	{
		if ((ADC0_ACTSS_R & ~ ADC_ACTSS_BUSY) != ADC_ACTSS_BUSY ) //Check If ADC is not busy 
		{
		
			au8_ADC_Module = gstr_ADC_Activated_Channels_Arr[u8_ADC_Index].ADC_Module; //Determine which Module
			au8_ADC_Sample_Sequencer = gstr_ADC_Activated_Channels_Arr[u8_ADC_Index].ADC_Sample_Sequencer;  //Determine Sample Sequencer
			au8_ADC_Ch_Status = ADC_Channel_Status_Arr[u8_ADC_Index]; // Determine The Channel Status

			if (au8_ADC_Ch_Status == INITIALIZED)
			{
				switch (au8_ADC_Module)
				{
					case ADC_MODULE_0:
					{
						switch (au8_ADC_Sample_Sequencer)
						{
							case ADC_SAMPLE_SEQUENCER_0:
							{
								ADC0_PSSI_R |= ADC_PSSI_SS0;
								while ((ADC0_RIS_R & ADC_RIS_INR0)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC0_Result[u8_ADC_Index] = ADC0_SSFIFO0_R ;            // Get Conversion Result
								ADC0_ISC_R = ADC_ISC_IN0; //Clear Completion Flag
								break;
				
							}
							case ADC_SAMPLE_SEQUENCER_1:
							{
								ADC0_PSSI_R |= ADC_PSSI_SS1;
								while ((ADC0_RIS_R & ADC_RIS_INR1)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC0_Result[u8_ADC_Index]= ADC0_SSFIFO1_R ;            // Get Conversion Result
								ADC0_ISC_R = ADC_ISC_IN1; //Clear Completion Flag
								break;
				
							}
							case ADC_SAMPLE_SEQUENCER_2:
							{
								ADC0_PSSI_R |= ADC_PSSI_SS2;
								while ((ADC0_RIS_R & ADC_RIS_INR2) == ZERO);   // Wait For Conversion Complete
								gu32_ADC0_Result[u8_ADC_Index]= ADC0_SSFIFO2_R ;            // Get Conversion Result
								ADC0_ISC_R = ADC_ISC_IN2; //Clear Completion Flag
								break;
				
							}
							case ADC_SAMPLE_SEQUENCER_3:
							{
								ADC0_PSSI_R |= ADC_PSSI_SS3;
								while ((ADC0_RIS_R & ADC_RIS_INR3)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC0_Result[u8_ADC_Index] = ADC0_SSFIFO3_R ;            // Get Conversion Result
								ADC0_ISC_R = ADC_ISC_IN3; //Clear Completion Flag
								break;
			
							}
							default:
							au8_Ret_Status = E_NOK;
							break;
						}
						*u32_ADC_Digital_Reading = gu32_ADC0_Result[u8_ADC_Index];
						break;
					}
					case ADC_MODULE_1:
					{
						switch (au8_ADC_Sample_Sequencer)
						{
							case ADC_SAMPLE_SEQUENCER_0:
							{
								ADC1_PSSI_R |= ADC_PSSI_SS0;
								while ((ADC1_RIS_R & ADC_RIS_INR0)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC1_Result[u8_ADC_Index] = ADC1_SSFIFO0_R ;            // Get Conversion Result
								ADC1_ISC_R = ADC_ISC_IN0; //Clear Completion Flag
								break;
							
							}
							case ADC_SAMPLE_SEQUENCER_1:
							{
								ADC1_PSSI_R |= ADC_PSSI_SS1;
								while ((ADC1_RIS_R & ADC_RIS_INR1)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC1_Result[u8_ADC_Index]= ADC1_SSFIFO1_R ;            // Get Conversion Result
								ADC1_ISC_R = ADC_ISC_IN1; //Clear Completion Flag
								break;
							
							}
							case ADC_SAMPLE_SEQUENCER_2:
							{
								ADC1_PSSI_R |= ADC_PSSI_SS2;
								while ((ADC1_RIS_R & ADC_RIS_INR2) == ZERO);   // Wait For Conversion Complete
								gu32_ADC1_Result[u8_ADC_Index]= ADC1_SSFIFO2_R ;            // Get Conversion Result
								ADC1_ISC_R = ADC_ISC_IN2; //Clear Completion Flag
								break;
							
							}
							case ADC_SAMPLE_SEQUENCER_3:
							{
								ADC1_PSSI_R |= ADC_PSSI_SS3;
								while ((ADC1_RIS_R & ADC_RIS_INR3)  == ZERO);   // Wait For Conversion Complete
								gu32_ADC1_Result[u8_ADC_Index] = ADC1_SSFIFO3_R ;            // Get Conversion Result
								ADC1_ISC_R = ADC_ISC_IN3; //Clear Completion Flag
								break;
							
							}
							default:
							au8_Ret_Status = E_NOK;
							break;
						}
							
							*u32_ADC_Digital_Reading =gu32_ADC1_Result[u8_ADC_Index];
							break;
						
			    }
		
				default:
				au8_Ret_Status = E_NOK;
				break;
				}
		
			}
			else
			{
				au8_Ret_Status = E_NOK;
				Error_Push(ADC_MODULE,ERROR_CHANNEL_NOT_INITIALIZED	);
			}
	}
	}
	else
	{
		au8_Ret_Status = E_NOK;
		Error_Push(ADC_MODULE, ERROR_NOT_INITIALIZED);
	}
	return au8_Ret_Status;
}


/*
*** this function is responsible to convert ADC Digital Value To Analog Voltage Value
*** Input  : uint8_t  ADC_Index -> determine which elemnt from the  gstr_ADC_Activated_Channels_Arr we want to get it's value
***          float* Voltage_Value -> to Get the Value using it
*** Output : ERROR_STATUS
*/
ERROR_STATUS ADC_Get_Voltage_Reading(uint8_t u8_ADC_Index,float* Voltage_Value)
{
	uint8_t au8_ADC_Module;
	uint8_t au8_Ret_Status = E_OK;
	
	// Determine which Module we want to read it's channels
	au8_ADC_Module = gstr_ADC_Activated_Channels_Arr[u8_ADC_Index].ADC_Module; 
	
	// Check if the Module Initialized First
	if (Voltage_Value != NULL)
	{
	
	   //Make Sure That Module Is Initialized
		if (gu8_ADC_Module_Status == INITIALIZED)
		{
			if (au8_ADC_Module == ADC_MODULE_0)
			{
			
				*Voltage_Value = (( gu32_ADC0_Result[u8_ADC_Index] * ADC0_VREF) /ADC0_DIGITAL_VALUE);
			}
			else if (au8_ADC_Module == ADC_MODULE_1)
			{
				*Voltage_Value = (( gu32_ADC1_Result[u8_ADC_Index] * ADC1_VREF) /ADC1_DIGITAL_VALUE);
			}
			else
			{
				au8_Ret_Status = E_NOK;
			}
		}
		else
		{
			au8_Ret_Status = E_NOK;
			Error_Push(ADC_MODULE, ERROR_READ_WITHOUT_INITIALIZATION);
		}
		
	}
	else
	{
		au8_Ret_Status = E_NOK;
		Error_Push(ADC_MODULE, ERROR_NULL_POINTER);
	}
	
	return au8_Ret_Status;
}
