/*
 * ADC_Lcfg.c
 *
 * Created: 4/27/2020 6:09:52 AM
 *  Author: A_ayman
 */ 

/*
*** Inclusions
*/
#include "ADC_Lcfg.h"

strADC_Cfg_t gstr_ADC_Activated_Channels_Arr [NUM_ACTIVATED_ADC_CHANNELS ] = 
{
	//ADC_INDEX  //ADC_MODULE  //ADC_Channel  //Sample Sequencer     //ADC MUX                     //INPUT Source        //Trigger_Source          
	{ADC_INDEX0 , ADC_MODULE_0,  ADC_CH_1,   ADC_SAMPLE_SEQUENCER_3, ADC_MUX0_SAMPLE_INPUT_SELECT,ADC_INPUT_CHANNELS,ADC_EMUX_EM3_PROCESSOR	}};
