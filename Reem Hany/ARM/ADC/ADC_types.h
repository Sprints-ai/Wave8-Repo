#ifndef __ADC_TYPES_H__
#define __ADC_TYPES_H__
#include "../../Services/includes/std_types.h"


#define REG_STEP          4
#define ADC_BASE_STEP     0x1000
#define ADC_OFFSET_STEP   0X20
/**********ADC Num***************/
typedef enum{
	ADC_Num0 = 0x0,
	ADC_Num1 = 0x1
}ADCNum_t;
/**********Sequencer*************/
typedef enum{
	ADC_Sequencer0 = 0x1,
	ADC_Sequencer1 = 0x2,
	ADC_Sequencer2 = 0x4,
	ADC_Sequencer3 = 0x8
}ADCSequencer_n_t;

/**********trigger*************/
typedef uint8_t ADCTrigger_Type;
#define ADC_TRIGGER_PROCESSOR     0x0
#define ADC_TRIGGER_ANALOG_COMP0  0x1
#define ADC_TRIGGER_ANALOG_COMP1  0x2
#define ADC_TRIGGER_EXT_GPIO      0x4
#define ADC_TRIGGER_TIMER         0x5
#define ADC_TRIGGER_PWM_0         0x6
#define ADC_TRIGGER_PWM_1         0x7
#define ADC_TRIGGER_PWM_2         0x8
#define ADC_TRIGGER_PWM_3         0x9
#define ADC_TRIGGER_CONT_SAMPLING 0xF

/**********ADC_MODE*************/

typedef enum{
	ADC_InputChannel,
	ADC_InternalTempSensor,
	ADC_BOTH
}ADC_InputMode_t;
/**********ADC Input ChannelsMode**********/
typedef enum 
{
	SingleEnded=0,
	Differential=1
}ChannelsDigitalOutputMode_t;

/**********ADC_InputChannels*************/
typedef uint8_t ADCInputChannel_Type;
#define AIN0_E3            0
#define AIN1_E2            1
#define AIN2_E1            2
#define AIN3_E0            3
#define AIN4_D3            4
#define AIN5_D2            5
#define AIN6_D1            6
#define AIN7_D0            7
#define AIN8_E5            8
#define AIN9_E4            9
#define AIN10_B4           10
#define AIN11_B5           11

#define DIFF_AIN0_1        0
#define DIFF_AIN2_3        1
#define DIFF_AIN4_5        2
#define DIFF_AIN6_7        3
#define DIFF_AIN8_9        4
#define DIFF_AIN10_11      5

/**************CTL Bits order************/
#define D_BIT         0
#define END_BIT       1
#define IE_BIT        2
#define TS_BIT        3
/************Interrupts*****************/
typedef uint8_t InterruptMode;
#define INTERRUPT_EN         1
#define INTERRUPT_DISABLE    0

/***********ADC Cfg*********************/
typedef struct stADC_Cfg_t{
	ADCNum_t ADC_NUM;
	
	ADCSequencer_n_t ADC_Sequencer;//SQRT(Seq)
	
	ADCTrigger_Type   ADC_Trigger;//will be shifted 4* seq_no
	
	uint8_t NumoFChannels;
	ADCInputChannel_Type ADC_Channels[8];//loop 0>>,shift<<i*
	
	InterruptMode ADC_IRQ;        //ADCIM reg
	InterruptMode ChannelsIRQ[8];//enable or disble for the corresponding channel
																			//reg=(ChannelsIRQ[i]<<(i*REG_STEP)+IE_BIT))
	
	ADC_InputMode_t ADC_InputMode;//Check on it in case it is internal temp or not 
	
	ChannelsDigitalOutputMode_t DigitalOutputMode;//SingleEnded / Differrential (reg=(DigitalOutputMode<<(i*REG_STEP)+D_BIT))
	
}stADC_Cfg_t;

#endif
