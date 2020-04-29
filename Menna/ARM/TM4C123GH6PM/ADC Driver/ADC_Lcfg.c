
#include "ADC_Lcfg.h"



ADC_CfgType ADC_Cfg1 = 
{ 
	
	ADC_0,
	ADC_SEQ_Number3,
	ADC_TRIGGER_MODE_PROCESSOR,
	NO_PWM,/*PWM module*/
	ENABLE_INT,/*enable interrupt */
	/*end seq bit*/
	{1,0,0,0,0,0,0,0},
	/*temp o input*/
	{0,0,0,0,0,0,0,0},
	/*single-ended sample or diffrential*/
	{0,0,0,0,0,0,0,0},
	{AIN0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7},
	/* interrupt after each sample */
	{1,0,0,0,0,0,0,0}

};


