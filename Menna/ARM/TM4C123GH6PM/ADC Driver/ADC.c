/*
 * NVIC.c
 *
 * Created: 4/3/2020 10:52:14 AM
 *  Author: MENNA
 */

/**************************************************************************************/
/*																	ADC.c																				      */
/**************************************************************************************/

#include "ADC.h"
#include "ADC_Lcfg.h"
#include "MCU_HW.h"
#include "std_types.h"

#define SAMPLES_NUMBER_SEQ0 8 
#define SAMPLES_NUMBER_SEQ1 4
#define SAMPLES_NUMBER_SEQ2 4
#define SAMPLES_NUMBER_SEQ3 1

/*
 * Fun----------: ERROR_STATUS ADC_Init(void);
 * Return-------: ERROR_STATUS
 * Description--: ADC Module initialization
*/

ERROR_STATUS ADC_init(void)
{
	uint8_t ADC_Seq_offset ;
	uint8_t ADC_Seq_SamplesNo ;
	ADC_ChannelType ADC_Chn = ADC_Cfg1.ADC_Channel ;
	uint8_t au8_counter1 ;
	ADC_SEQ_NumberType ADC_SEQ_NO = ADC_Cfg1.ADC_SEQ_Number ;
	
	if (ADC_SEQ_NO == SEQ_0)
	{
		ADC_Seq_offset = ZERO ;
		ADC_Seq_SamplesNo = SAMPLES_NUMBER_SEQ0 ;
	}
	else if (ADC_SEQ_NO == SEQ_1)
	{
		ADC_Seq_offset = ONE ;
		ADC_Seq_SamplesNo = SAMPLES_NUMBER_SEQ1 ;
	}
	else if (ADC_SEQ_NO == SEQ_2)
	{
		ADC_Seq_offset = TWO ;
		ADC_Seq_SamplesNo = SAMPLES_NUMBER_SEQ2 ;
	}
	else if (ADC_SEQ_NO == SEQ_3)
	{
		ADC_Seq_offset = THREE ;
		ADC_Seq_SamplesNo = SAMPLES_NUMBER_SEQ3 ;
	}
	
	/* initialize ADC0 */
	
	/* disable SS3 during configuration */
	CLEAR_BIT(ADCACTSS(ADC_Chn),ADC_Seq_offset) ;
	
	/* software trigger conversion */
	ADCEMUX(ADC_Chn)|= (ADC_Cfg1.ADC_Trigger_Mode)<<FOUR*ADC_Seq_offset ;
	
	if (ADC_Cfg1.ADC_Trigger_Mode == ADC_TRIGGER_MODE_PWM0)
		ADCTSSEL(ADC_Chn) |=  (ADC_Cfg1.ADC_PWM_module)<<4 ;
	if (ADC_Cfg1.ADC_Trigger_Mode == ADC_TRIGGER_MODE_PWM1)
		ADCTSSEL(ADC_Chn) |=  (ADC_Cfg1.ADC_PWM_module)<<12 ;
	if (ADC_Cfg1.ADC_Trigger_Mode == ADC_TRIGGER_MODE_PWM2)
		ADCTSSEL(ADC_Chn) |=  (ADC_Cfg1.ADC_PWM_module)<<20 ;
	if (ADC_Cfg1.ADC_Trigger_Mode == ADC_TRIGGER_MODE_PWM3)
		ADCTSSEL(ADC_Chn) |=  (ADC_Cfg1.ADC_PWM_module)<<28 ;

	
	/* chooose input channel for each sampler */
	for(au8_counter1 = ZERO ; au8_counter1<ADC_Seq_SamplesNo; au8_counter1++)
	{
		ADCSSMUX(ADC_Chn, ADC_SEQ_NO) |= (ADC_Cfg1.Sample_Input_arr[au8_counter1])<<4*au8_counter1; 
	}
	
	/*enable interrupt */
	ADCIM(ADC_Chn)|= ADC_Cfg1.ADC_SEQ_INT_Enable<<ADC_Seq_offset ;
	
	/* CTL for sequincers */
	
	for(au8_counter1 = ZERO ; au8_counter1<ADC_Seq_SamplesNo; au8_counter1++)
	{
		ADCSSCTL(ADC_Chn, ADC_SEQ_NO) |= (ADC_Cfg1.single_endded_difrrential_arr[au8_counter1])<<4*au8_counter1; 
		ADCSSCTL(ADC_Chn, ADC_SEQ_NO) |= (ADC_Cfg1.End_of_Seq_bit_arr[au8_counter1])<<((4*au8_counter1)+1); 
		ADCSSCTL(ADC_Chn, ADC_SEQ_NO) |= (ADC_Cfg1.Enable_sample_INT_arr[au8_counter1])<<((4*au8_counter1)+2); 
		ADCSSCTL(ADC_Chn, ADC_SEQ_NO) |= (ADC_Cfg1.Temp_sensor_enable_arr[au8_counter1])<<((4*au8_counter1)+3 ); 
	
	}
		
	/* enable ADC0 sequencer 3 */
	SET_BIT(ADCACTSS(ADC_Chn),ADC_Seq_offset) ;
 
}

/*
 * Fun----------: ERROR_STATUS ADC_Init(void);
 * Output-------: result the value converted 
 * Return-------: ERROR_STATUS
 * Description--: initializes the the ADC Module 
*/

ERROR_STATUS start_conversion(uint8_t * result)
{
	uint8_t ADC_Seq_offset ;
	ADC_ChannelType ADC_Chn = ADC_Cfg1.ADC_Channel ;
	ADC_SEQ_NumberType ADC_SEQ_NO = ADC_Cfg1.ADC_SEQ_Number ;
	
	if (ADC_SEQ_NO == SEQ_0)
	{
		ADC_Seq_offset = ZERO ;
	}
	else if (ADC_SEQ_NO == SEQ_1)
	{
		ADC_Seq_offset = ONE ;
	}
	else if (ADC_SEQ_NO == SEQ_2)
	{
		ADC_Seq_offset = TWO ;
	}
	else if (ADC_SEQ_NO == SEQ_3)
	{
		ADC_Seq_offset = THREE ;
	}
	
	/* start a conversion sequence  */
	SET_BIT(ADCPSSI(ADC_Chn),ADC_Seq_offset)   ; 
			
	while ((ADCRIS(ADC_Chn) & ( ONE << ADC_Seq_offset)) == ZERO ); /* wait for conversion complete */
	
		*result = ADCSSFIFO(ADC_Chn , ADC_SEQ_NO); /* read conversion result */
	
	 /* clear completion flag */
	SET_BIT(ADCISC(ADC_Chn),ADC_Seq_offset);

}	

