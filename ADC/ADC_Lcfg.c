
#include "ADC_Types.h"
#include "ADC_Lcfg.h"


ADC_Cfg_t ADC_Cfg_Arr[MAX_NUMBER_OF_ADC_CHANNEL] ={
	
	// /* ADC_Moduel_Sample_Sequencer_t */   ,  /* ADC_Channel_t*/		/*ADC_Sample_Sequencer_INT_Mode_t*/ /*ADC_Sample_Position_t*/
	{  MODUEL0_SAMPLE_SEQUENCER3	,		AIN1		,		ADC_Sample_Sequencer_POLLING_MODE	,  ADC_Sample_Position0			},
	{  MODUEL1_SAMPLE_SEQUENCER3	,		AIN0		,		ADC_Sample_Sequencer_POLLING_MODE	,  ADC_Sample_Position0			},
	{  MODUEL0_SAMPLE_SEQUENCER0	,		AIN4		,		ADC_Sample_Sequencer_POLLING_MODE	,  ADC_Sample_Position1			}
	
	
};

