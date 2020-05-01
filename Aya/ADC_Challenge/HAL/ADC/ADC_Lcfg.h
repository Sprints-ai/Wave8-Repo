/*
 * ADC_Lcfg.h
 *
 * Created: 4/27/2020 6:10:11 AM
 *  Author: A_ayman
 */ 


#ifndef ADC_LCFG_H_
#define ADC_LCFG_H_

/*
*** Inclusions
*/
#include "ADC.h"
#include "../../SL/ARM_STD_t.h"

#define NUM_ACTIVATED_ADC_CHANNELS      1

typedef uint8_t ADC_Index_t;
#define ADC_INDEX0							 0
#define ADC_INDEX1							 1
#define ADC_INDEX2							 2
#define ADC_INDEX3							 3
#define ADC_INDEX4							 4 
#define ADC_INDEX5							 5
#define ADC_INDEX6							 6
#define ADC_INDEX7							 7
#define ADC_INDEX8							 8
#define ADC_INDEX9							 9
#define ADC_INDEX10							 10
#define ADC_INDEX11							 11

typedef uint8_t ADC_Module_t;
#define ADC_MODULE_0							 0
#define ADC_MODULE_1							 1

typedef uint8_t ADC_Channel_t;
#define ADC_CH_0								 0
#define ADC_CH_1								 1
#define ADC_CH_2								 2
#define ADC_CH_3								 3
#define ADC_CH_4								 4
#define ADC_CH_5								 5
#define ADC_CH_6								 6
#define ADC_CH_7								 7
#define ADC_CH_8								 8
#define ADC_CH_9								 9
#define ADC_CH_10								 10
#define ADC_CH_11								 11


typedef uint8_t ADC_Sample_Sequencer_t;
#define ADC_SAMPLE_SEQUENCER_0			 0
#define ADC_SAMPLE_SEQUENCER_1			 1
#define ADC_SAMPLE_SEQUENCER_2			 2
#define ADC_SAMPLE_SEQUENCER_3			 3


typedef uint8_t ADC_Trigger_Source_t;
#define ADC_EMUX_EM3_M						 0x0000F000  // SS3 Trigger Select
#define ADC_EMUX_EM3_PROCESSOR			 0x00000000  // Processor (default)
#define ADC_EMUX_EM3_COMP0					 0x00001000  // Analog Comparator 0
#define ADC_EMUX_EM3_COMP1					 0x00002000  // Analog Comparator 1
#define ADC_EMUX_EM3_EXTERNAL				 0x00004000  // External (GPIO PB4)
#define ADC_EMUX_EM3_TIMER					 0x00005000  // Timer
#define ADC_EMUX_EM3_PWM0					 0x00006000  // PWM0
#define ADC_EMUX_EM3_PWM1					 0x00007000  // PWM1
#define ADC_EMUX_EM3_PWM2					 0x00008000  // PWM2
#define ADC_EMUX_EM3_PWM3					 0x00009000  // PWM3
#define ADC_EMUX_EM3_ALWAYS				 0x0000F000  // Always (continuously sample)
#define ADC_EMUX_EM2_M						 0x00000F00  // SS2 Trigger Select
#define ADC_EMUX_EM2_PROCESSOR			 0x00000000  // Processor (default)
#define ADC_EMUX_EM2_COMP0					 0x00000100  // Analog Comparator 0
#define ADC_EMUX_EM2_COMP1					 0x00000200  // Analog Comparator 1
#define ADC_EMUX_EM2_EXTERNAL				 0x00000400  // External (GPIO PB4)
#define ADC_EMUX_EM2_TIMER					 0x00000500  // Timer
#define ADC_EMUX_EM2_PWM0					 0x00000600  // PWM0
#define ADC_EMUX_EM2_PWM1					 0x00000700  // PWM1
#define ADC_EMUX_EM2_PWM2					 0x00000800  // PWM2
#define ADC_EMUX_EM2_PWM3					 0x00000900  // PWM3
#define ADC_EMUX_EM2_ALWAYS				 0x00000F00  // Always (continuously sample)
#define ADC_EMUX_EM1_M						 0x000000F0  // SS1 Trigger Select
#define ADC_EMUX_EM1_PROCESSOR			 0x00000000  // Processor (default)
#define ADC_EMUX_EM1_COMP0					 0x00000010  // Analog Comparator 0
#define ADC_EMUX_EM1_COMP1					 0x00000020  // Analog Comparator 1
#define ADC_EMUX_EM1_EXTERNAL				 0x00000040  // External (GPIO PB4)
#define ADC_EMUX_EM1_TIMER					 0x00000050  // Timer
#define ADC_EMUX_EM1_PWM0					 0x00000060  // PWM0
#define ADC_EMUX_EM1_PWM1					 0x00000070  // PWM1
#define ADC_EMUX_EM1_PWM2					 0x00000080  // PWM2
#define ADC_EMUX_EM1_PWM3					 0x00000090  // PWM3
#define ADC_EMUX_EM1_ALWAYS				 0x000000F0  // Always (continuously sample)
#define ADC_EMUX_EM0_M						 0x0000000F  // SS0 Trigger Select
#define ADC_EMUX_EM0_PROCESSOR			 0x00000000  // Processor (default)
#define ADC_EMUX_EM0_COMP0					 0x00000001  // Analog Comparator 0
#define ADC_EMUX_EM0_COMP1					 0x00000002  // Analog Comparator 1
#define ADC_EMUX_EM0_EXTERNAL				 0x00000004  // External (GPIO PB4)
#define ADC_EMUX_EM0_TIMER					 0x00000005  // Timer
#define ADC_EMUX_EM0_PWM0					 0x00000006  // PWM0
#define ADC_EMUX_EM0_PWM1					 0x00000007  // PWM1
#define ADC_EMUX_EM0_PWM2					 0x00000008  // PWM2
#define ADC_EMUX_EM0_PWM3					 0x00000009  // PWM3
#define ADC_EMUX_EM0_ALWAYS				 0x0000000F  // Always (continuously sample)


typedef uint8_t ADC_Sample_Input_Select_t;
#define ADC_MUX0_SAMPLE_INPUT_SELECT     0
#define ADC_MUX1_SAMPLE_INPUT_SELECT	  1
#define ADC_MUX2_SAMPLE_INPUT_SELECT  	  2
#define ADC_MUX3_SAMPLE_INPUT_SELECT  	  3
#define ADC_MUX4_SAMPLE_INPUT_SELECT  	  4
#define ADC_MUX5_SAMPLE_INPUT_SELECT  	  5
#define ADC_MUX6_SAMPLE_INPUT_SELECT  	  6
#define ADC_MUX7_SAMPLE_INPUT_SELECT     7


typedef uint8_t ADC_Input_t;
#define ADC_INPUT_CHANNELS               0
#define ADC_INTERNAL_TEMPERATURE_SENSOR  1



typedef struct 
{  ADC_Index_t ADC_Index;
	ADC_Module_t ADC_Module;
	ADC_Channel_t ADC_Channel;
	ADC_Sample_Sequencer_t ADC_Sample_Sequencer;
	ADC_Sample_Input_Select_t ADC_Sample_Input_Select;
	ADC_Input_t ADC_Input;
	ADC_Trigger_Source_t ADC_Trigger_Source;
	}strADC_Cfg_t;
	
extern strADC_Cfg_t gstr_ADC_Activated_Channels_Arr[];


#endif /* ADC_LCFG_H_ */
	
	