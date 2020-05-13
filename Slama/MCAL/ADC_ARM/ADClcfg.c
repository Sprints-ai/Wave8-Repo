
/*Include Regs File*/
#include "PerRegs.h"
#include "ADClcfg.h"




/*Create array of structs for multi ADC*/
str_ADCCFG_t ADC_Conf[ADC_USED] ={{ .ADC_Module = ADC1 ,
									.ADC_Mode = 0 ,
									.Scan_Mode = ADC_CR1_SCAN_OFF ,
									.Chnl_Used = {ADC_CHNL_1} ,
									.Resolution = ADC_CR1_RESOLUTION_12 ,
									.Continous_Mode = ADC_CR2_CONT_MODE,
									.Software_Trig = 1,
									.Irq_State = ADC_CR1_IRQ_OFF ,
									.CHnl_Len = ADC_SQR1_1_CONV ,
									.Disc_Mode = ADC_CR1_DISC_1_CHNL,
									.ADC_Module_Used_CK = ADC1_CK ,
									.Bit_Alignment = ADC_RIGHT_ALIGNMENT,
									.Trigger_Polarity = ADC_CR2_NO_TRIGGER,
									.Conv_Trigger = ADC_CR2_TRIGGER_TIMER1_CC1
								   }};
