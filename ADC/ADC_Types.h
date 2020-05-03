#ifndef __ADC_Types_h__
#define __ADC_Types_h__

#include "..//std_types.h"
typedef uint8_t ADC_Module_t;
	#define ADC_MODULE0			0
	#define ADC_MODULE1			1

typedef uint8_t ADC_Moduel_Sample_Sequencer_t ;
	#define MODUEL0_SAMPLE_SEQUENCER0		0x00
	#define MODUEL0_SAMPLE_SEQUENCER1   	0x01   
	#define MODUEL0_SAMPLE_SEQUENCER2   	0x02   
	#define MODUEL0_SAMPLE_SEQUENCER3   	0x03   
	#define MODUEL1_SAMPLE_SEQUENCER0   	0x10   
	#define MODUEL1_SAMPLE_SEQUENCER1   	0x11   
	#define MODUEL1_SAMPLE_SEQUENCER2   	0x12   
	#define MODUEL1_SAMPLE_SEQUENCER3   	0x13   

typedef uint8_t ADC_Channel_t;
	#define AIN0 	(0x0)    //					(0x23)		// PE3 (35)	
	#define AIN1 	(0x1)    //					(0x22)		// PE2 (34)	
	#define AIN2 	(0x2)    //					(0x21)		// PE1 (33)	
	#define AIN3 	(0x3)    //					(0x20)		// PE0 (32)	
	#define AIN4  	(0x4)    //					(0x1B)		// PD3 (27)
	#define AIN5  	(0x5)    //					(0x1A)		// PD2 (26)
	#define AIN6  	(0x6)    //					(0x19)		// PD1 (25)
	#define AIN7  	(0x7)    //					(0x18)		// PD0 (24)
	#define AIN8  	(0x8)    //					(0x25)		// PE5 (37)
	#define AIN9  	(0x9)    //					(0x24)		// PE4 (36)
	#define AIN10 	(0xA)    //					(0x0C)		// PB4 (12)
	#define AIN11   (0xB)    //					(0x0D)		// PB5 (13)


typedef uint8_t ADC_Sample_Sequencer_INT_Mode_t ;
	 #define ADC_Sample_Sequencer_POLLING_MODE	0
	 #define ADC_Sample_Sequencer_INT_MODE		1

	
typedef  uint8_t ADC_Sample_Position_t;

	  #define ADC_Sample_Position0		0x0
	  #define ADC_Sample_Position1		0x1
	  #define ADC_Sample_Position2		0x2
	  #define ADC_Sample_Position3		0x3
	  #define ADC_Sample_Position4		0x4
	  #define ADC_Sample_Position5		0x5
	  #define ADC_Sample_Position6		0x6
	  #define ADC_Sample_Position7		0x7
	 



typedef struct{
	//ADC_Module_t			ADC_Module;
	ADC_Moduel_Sample_Sequencer_t 			ADC_Moduel_Sample_Sequencer;
	ADC_Channel_t							ADC_Channel			;
	ADC_Sample_Sequencer_INT_Mode_t			ADC_Sample_Sequencer_INT_Mode		;
	ADC_Sample_Position_t 					ADC_Sample_Position	;
} ADC_Cfg_t;

 


typedef uint8_t ADC_Sample_Sequencer_t;
	#define SAMPLE_SEQUENCER0 0x00
	#define SAMPLE_SEQUENCER1 0x01
	#define SAMPLE_SEQUENCER2 0x02
	#define SAMPLE_SEQUENCER3 0x03

	



























#endif


