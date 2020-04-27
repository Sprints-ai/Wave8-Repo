#include "../includes/ADC.h"
#include "../includes/ADC_LCfg.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"
#include <math.h>

void ADC_Init(void)
{
	uint8_t i=0,au8Sequencer_no;
	uint32_t ADC,ADCMUX,ADCControl;
	
	//Get Sequencer Number
	au8Sequencer_no = log2(ADC_Cfg.ADC_Sequencer);
	
	//Get the offset of the adcmux
	ADCMUX = ADCSSMUX0 + (ADC_OFFSET_STEP*au8Sequencer_no);
	
	//Get the offset of the adcCTL
	ADCControl = ADCSSCTL0 + (ADC_OFFSET_STEP*au8Sequencer_no);
	
	//Get the Base address of the adc
	ADC= ADC0+ADC_BASE_STEP*ADC_Cfg.ADC_NUM;
	
	
	//Disable the Sequencer
	CLR_BIT_MASK(ADCREG(ADC,ADCACTSS),ADC_Cfg.ADC_Sequencer);
	
	//Choose Software Trigger
	SET_BIT_MASK(ADCREG(ADC,ADCEMUX),(ADC_Cfg.ADC_Trigger << (REG_STEP*au8Sequencer_no)));
	
	//Set the sequencer interrupt mask
	(ADCREG(ADC,ADCIM)) |= ADC_Cfg.ADC_IRQ<<au8Sequencer_no;
	
	//Select the Input Channel
	for(i = 0 ; i < ADC_Cfg.NumoFChannels ; i++)
	{
		/*Select the MUX*/
		(ADCREG(ADC,ADCMUX)) |= ADC_Cfg.ADC_Channels[i];
		
		/*Adjust the Control register*/
		
		//Single or diffrential
		(ADCREG(ADC,ADCControl)) |= (ADC_Cfg.DigitalOutputMode << ((i*REG_STEP)+D_BIT)); //sift the must in case the sequencer is not =0
		
		//Check whether it's the final sample or not
		if(i == ADC_Cfg.NumoFChannels-1)
		{
			//SET THE END BIT
			SET_BIT((ADCREG(ADC,ADCControl)),(END_BIT+(i*REG_STEP)));
		}
		else
		{
			//CLR THE END BIT
			CLR_BIT((ADCREG(ADC,ADCControl)),(END_BIT+(i*REG_STEP)));
		}
		
		//Set the interrupt mask of the channel 
		(ADCREG(ADC,ADCControl)) |= (ADC_Cfg.ChannelsIRQ[i] << ((i*REG_STEP)+IE_BIT));
			
	}
	if(ADC_Cfg.ADC_InputMode == ADC_InternalTempSensor || ADC_Cfg.ADC_InputMode==ADC_BOTH)
	{
		//SET THE Temp Sensor bit
		SET_BIT((ADCREG(ADC,ADCControl)),(TS_BIT+(i*REG_STEP)));
	}
	else
	{
		//CLR THE Temp Sensor bit
		CLR_BIT((ADCREG(ADC,ADCControl)),(TS_BIT+(i*REG_STEP)));
	}
	
	//Enable the Sequencer
	SET_BIT_MASK(ADCREG(ADC,ADCACTSS),ADC_Cfg.ADC_Sequencer);
}



void ADC_READ(uint16_t * ReadingBuffer)
{
	uint8_t i=0,au8Sequencer_no;
	uint32_t ADCFFIFO,ADC;
	
	//Get Sequencer Number
	au8Sequencer_no = log2(ADC_Cfg.ADC_Sequencer);
	
	//Get the offset of the adcFIFO
	ADCFFIFO = ADCSSFIFO0 + (ADC_OFFSET_STEP*au8Sequencer_no);
	
	//Get the Base address of the adc
	ADC= ADC0+ADC_BASE_STEP*ADC_Cfg.ADC_NUM;
	
	for(i=0 ; i<ADC_Cfg.NumoFChannels;i++)
	{
		ADCREG(ADC,ADCPSSI) |= ADC_Cfg.ADC_Sequencer;
		while(!(ADCREG(ADC,ADCRIS) & ADC_Cfg.ADC_Sequencer));
		ReadingBuffer[i] = ADCREG(ADC,ADCFFIFO);
		(ADCREG(ADC,ADCISC)) = ADC_Cfg.ADC_Sequencer;
	}
}