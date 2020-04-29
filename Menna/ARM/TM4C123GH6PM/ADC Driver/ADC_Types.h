
#ifndef ADC_TYPES_H_
#define ADC_TYPES_H_

typedef uint32_t ADC_ChannelType ;

#define ADC_CHANNEL0 ADC_0
#define ADC_CHANNEL1 ADC_1


typedef uint8_t ADC_SEQ_NumberType ;

#define ADC_SEQ_Number0 SEQ_0
#define ADC_SEQ_Number1 SEQ_1
#define ADC_SEQ_Number2 SEQ_2
#define ADC_SEQ_Number3 SEQ_3

typedef uint8_t ADC_SEQ_INT_EnableType ;
#define DISABLE_INT 0
#define ENABLE_INT  1

typedef uint8_t Sample_InputType ;
#define  AIN0 0 
#define  AIN1 1
#define  AIN2 2
#define  AIN3 3
#define  AIN4 4
#define  AIN5 5
#define  AIN6 6
#define  AIN7 7
#define  AIN8 8
#define  AIN9 9 
#define  AIN10 10
#define  AIN11 11

#define	 DIFF_PAIR0 0
#define	 DIFF_PAIR1 1
#define	 DIFF_PAIR2 2
#define	 DIFF_PAIR3 3
#define	 DIFF_PAIR4 4
#define	 DIFF_PAIR5 5

typedef uint8_t ADC_Trigger_ModeType ;
#define ADC_TRIGGER_MODE_PROCESSOR 					0x0
#define	ADC_TRIGGER_MODE_ANALOG_COMPARATOR0 0x1
#define	ADC_TRIGGER_MODE_ANALOG_COMPARATOR1 0x2
#define	ADC_TRIGGER_MODE_EXTERNAL 					0x4
#define	ADC_TRIGGER_MODE_TIMER 							0x5
#define	ADC_TRIGGER_MODE_PWM0 							0x6
#define	ADC_TRIGGER_MODE_PWM1								0x7
#define	ADC_TRIGGER_MODE_PWM2 							0x8
#define	ADC_TRIGGER_MODE_PWM3 							0x9
#define	ADC_TRIGGER_MODE_ALWAYS 						0xF


typedef uint8_t ADC_PWM_moduleType ;

#define PWM_MODULE_0  0
#define PWM_MODULE_1  1
#define NO_PWM 0 
typedef struct
{
	/*ADC number*/
	ADC_ChannelType ADC_Channel ;
	
	/*seq number*/
	ADC_SEQ_NumberType ADC_SEQ_Number ;
	

	/*Trigger mood*/
	ADC_Trigger_ModeType ADC_Trigger_Mode ;

	/*the PWM module */
	ADC_PWM_moduleType ADC_PWM_module ;
	
	/*Enable interrupt*/
	ADC_SEQ_INT_EnableType ADC_SEQ_INT_Enable ;
	
	/*end seq bit*/
	/* array for last bit in_sequance ctl-1*/
	uint8_t End_of_Seq_bit_arr[8] ;
	
	/*temp o input*/
	/*array for each sample temp oR input ctl-2*/
	uint8_t Temp_sensor_enable_arr[8] ;
	
	/*single-ended sample or diffrential*/
	/*array of input pin number or pair number  ctl-3 */
		uint8_t single_endded_difrrential_arr[8] ;
		
			
	/*PIN NUMBER OR pair number for samples array*/
	Sample_InputType Sample_Input_arr[8] ;

	/*interupt*/
	/*array for each sample to interrupt or no ctl-4*/
		uint8_t Enable_sample_INT_arr[8] ;

	
}ADC_CfgType;

#endif /*ADC_TYPES_H_*/
