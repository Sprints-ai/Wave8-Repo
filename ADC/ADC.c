#include "ADC_Types.h"
#include "ADC.h"
#include "ADC_Lcfg.h"
#include "ADC_Cfg.h"
#include "MCU_hw.h"

#define ClEAR_BIT(REGISTER,BIT) (REGISTER&=~(1<<BIT))
#define SET_BIT(REGISTER,BIT) (REGISTER|=(1<<BIT))

#define MAX_ADC_MODUEL_NUMBER		2
#define GET_MODUEL_BIT 				4	
#define GET_SS_NU					0x07
#define ENABLE_CHANNEL_INT (0x4)
#define CONTINUOUSLY_SAMPLE			0x0
#define THE_ENDx_BIT 					0x0002
#define MAX_ADC_SAMPLENCER_NUMBER		4 
#define ZERO												0
#define ADC_SAMPLE_POSISTION_BIT_MASK		4
#define ADC_SAMPLE_VALUE_BIT_MASK			0x000f
#define ADC_SAMPLE_SEQUENCER_REPETITIVE_REG		8
#define BUSY			0
#define BIT_0_BIT_MASK		0x1
#define BIT_8_BIT_MASK		8
#define ADC_CONVERSION_UNFINSH 	0
#define ADC_RESULT_STAK_NOT_EMPTY			0
#define LAST_VALUE_INDECAION_IN_ADC_STACK_RESULT 		0xFF


static uint16_t gau16_Max_AIT[MAX_ADC_MODUEL_NUMBER];
//static uint32_t u32_SampleSequencer_Status;

static uint32_t ADC_ModuelBaseAddress[MAX_ADC_MODUEL_NUMBER]= {ADC0_BASE_ADDRESS,ADC1_BASE_ADDRESS};


u8_ERROR_STATUS_t ADC_Init( void ){
	
	
	uint8_t u8_Sample_Init_Counter=ZERO ;
	uint8_t u8_moduel_counter=ZERO;
	uint8_t u8_Sample_Sequencer_Counter=ZERO ;
	
	
	ADC_Module_t ADC_Module =ZERO ;
	ADC_Sample_Sequencer_t ADC_Sample_Sequencer = ZERO;
	ADC_Channel_t ADC_Channel = ZERO;
	ADC_Sample_Sequencer_INT_Mode_t ADC_Sample_Sequencer_INT_Mode = ZERO;
	ADC_Sample_Position_t ADC_Sample_Position = ZERO ;
	
	for (;u8_Sample_Init_Counter < MAX_NUMBER_OF_ADC_CHANNEL ;u8_Sample_Init_Counter ++)
	{
		
		// Get moduel number 
		ADC_Module = (ADC_Cfg_Arr[u8_Sample_Init_Counter].ADC_Moduel_Sample_Sequencer >> GET_MODUEL_BIT);
		
		// Get Sample_Sequencer number 
		ADC_Sample_Sequencer = (ADC_Cfg_Arr[u8_Sample_Init_Counter].ADC_Moduel_Sample_Sequencer) &GET_SS_NU ;
		
		// Get ADC_Channel
		ADC_Channel = ADC_Cfg_Arr[u8_Sample_Init_Counter].ADC_Channel;
		
		// Get ADC_Sample_Sequencer_INT_Mode
		ADC_Sample_Sequencer_INT_Mode  = ADC_Cfg_Arr[u8_Sample_Init_Counter].ADC_Sample_Sequencer_INT_Mode;
		// GetADC_Sample_Position
		ADC_Sample_Position = ADC_Cfg_Arr[u8_Sample_Init_Counter].ADC_Sample_Position;
		// Get Max_ADC_Sample_Position
		

		if (((gau16_Max_AIT[ADC_Module]>>(ADC_SAMPLE_POSISTION_BIT_MASK * ADC_Sample_Sequencer))&ADC_SAMPLE_VALUE_BIT_MASK )<ADC_Sample_Position)
		{
			
			gau16_Max_AIT[ADC_Module]=((gau16_Max_AIT[ADC_Module]&~(ADC_SAMPLE_VALUE_BIT_MASK << ADC_Sample_Sequencer))|(ADC_Sample_Position<<ADC_Sample_Sequencer));
		}
		
		
		//ADCACTSS Disable crossponding ssx
		
		ClEAR_BIT(ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCACTSS, ADC_Sample_Sequencer);
		
		//ADCEMUX cfg the triger event ->continus sample 
	//	ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCEMUX |= (CONTINUOUSLY_SAMPLE << (4*ADC_Sample_Sequencer));
		
		//ADCSSMUXn cfg the I/p source for each SS 
	
		*(&(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCSSMUX0)+(ADC_SAMPLE_SEQUENCER_REPETITIVE_REG*ADC_Sample_Sequencer))=(ADC_Channel<<(4*ADC_Sample_Position)); 
		
		//ADCIM Enable/disable the Interrupt 
		if(ADC_Sample_Sequencer_INT_Mode == ADC_Sample_Sequencer_INT_MODE)
		{
			SET_BIT(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCIM,ADC_Sample_Sequencer);   
			
			*(&(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCSSCTL0)+(ADC_SAMPLE_SEQUENCER_REPETITIVE_REG*ADC_Sample_Sequencer)) |= (ENABLE_CHANNEL_INT <<(ADC_SAMPLE_POSISTION_BIT_MASK *ADC_Sample_Sequencer));
		}
		else 
		{
			ClEAR_BIT(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCIM,ADC_Sample_Sequencer);
		}
			
		//ADCACTSS enable crossponding ssx
		SET_BIT(ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCACTSS, ADC_Sample_Sequencer);
		
		//ADCPSSI initiate the sample 

		//SET_BIT(ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCPSSI, ADC_Sample_Sequencer);

	
	}
	
		
		//SET ENDx bit in ADCSSCTL0 //last position in ADC FIFO
	for(;u8_moduel_counter < MAX_ADC_MODUEL_NUMBER;u8_moduel_counter++)
	{
		for(u8_Sample_Sequencer_Counter=0;u8_Sample_Sequencer_Counter < MAX_ADC_SAMPLENCER_NUMBER;u8_Sample_Sequencer_Counter++)
		{
		
			uint8_t u8_AIT_ShiftVAlue =ADC_SAMPLE_POSISTION_BIT_MASK * u8_Sample_Sequencer_Counter;
			*(&(ADC_REG(ADC_ModuelBaseAddress[u8_moduel_counter]).ADCSSCTL0)+(ADC_SAMPLE_SEQUENCER_REPETITIVE_REG*u8_Sample_Sequencer_Counter)) |= (THE_ENDx_BIT<<(4*((gau16_Max_AIT[u8_moduel_counter]>>u8_AIT_ShiftVAlue)&0x000F)));
		}
		
	}
	

return E_OK;}

//u8_ERROR_STATUS_t ADC_ReadChannel();

u8_ERROR_STATUS_t ADC_ReadSS(ADC_Moduel_Sample_Sequencer_t ADC_Moduel_Sample_Sequencer ,uint16_t(* u16_ReadValue)[9]){
	
	ADC_Module_t ADC_Module = ZERO;
	ADC_Sample_Sequencer_t ADC_Sample_Sequencer = ZERO;
	uint8_t u8_FIFO_MaxCount = ZERO;
	static uint8_t u8_FIFO_Counter=ZERO;
			//ADCPSSI initiate the sample 

	
	
	u8_FIFO_MaxCount = (gau16_Max_AIT[ADC_Module]>>(4*ADC_Sample_Sequencer))&0x000f;
	// Get moduel number 
	ADC_Module = (ADC_Moduel_Sample_Sequencer >> GET_MODUEL_BIT);
	
	// Get Sample_Sequencer number 
	ADC_Sample_Sequencer = (ADC_Moduel_Sample_Sequencer) &GET_SS_NU ;
	SET_BIT(ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCPSSI, ADC_Sample_Sequencer); 

	while (((ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCRIS >> ADC_Sample_Sequencer)&BIT_0_BIT_MASK)== ADC_CONVERSION_UNFINSH);
	
	//Clear interrupt flag
	
	ADC_REG( ADC_ModuelBaseAddress[ADC_Module]).ADCISC |= BIT_0_BIT_MASK <<ADC_Sample_Sequencer;
	//read the value 
	for (;u8_FIFO_Counter <u8_FIFO_MaxCount;u8_FIFO_Counter ++){
		
		if((((*(&(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCSSFSTAT0)+(ADC_SAMPLE_SEQUENCER_REPETITIVE_REG*ADC_Sample_Sequencer)))>>BIT_8_BIT_MASK)& BIT_0_BIT_MASK)==ADC_RESULT_STAK_NOT_EMPTY)//not empty 
		{
		*((*u16_ReadValue)+u8_FIFO_Counter)=*(&(ADC_REG(ADC_ModuelBaseAddress[ADC_Module]).ADCSSFIFO0)+(ADC_SAMPLE_SEQUENCER_REPETITIVE_REG*ADC_Sample_Sequencer));	
		}
		else
		{
			break;
		}
	}
	//NULL To indcate the end of the reading 
	*((*u16_ReadValue)+u8_FIFO_Counter)=LAST_VALUE_INDECAION_IN_ADC_STACK_RESULT; 
	if(u8_FIFO_Counter >= u8_FIFO_MaxCount )
	{
		u8_FIFO_Counter =ZERO;
	}

return E_OK;//Error_status
}





