#include "../includes/ADC_LCfg.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"

stADC_Cfg_t ADC_Cfg =
{
	ADC_Num0,
	ADC_Sequencer3,
	ADC_TRIGGER_PROCESSOR,
	1,//One Channel
	{AIN1_E2},
	INTERRUPT_DISABLE,
	{INTERRUPT_EN},
	ADC_InputChannel,
	SingleEnded
};