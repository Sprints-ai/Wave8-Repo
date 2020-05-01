/*
 * ADC.h
 *
 * Created: 4/27/2020 5:39:55 AM
 *  Author: A_ayman
 */ 


#ifndef ADC_H_
#define ADC_H_

/*
*** Inclusions
*/
#include "ADC_Lcfg.h"
#include "../../SL/ARM_STD_t.h"
#include "../../SL/ERROR HANDLING/ERROR-STORE.h"
#include "../../MCAL/PORT/MCU_HW_Registers.h"



/*
*** void ADC_Init (void)
***
*** This Function is Responsible for Initialize ADC, by Following Some steps
*** - First step is to Enable CLK "Done in SysCtr configuration file"
*** - Second Step is to Enable the clock to the appropriate GPIO modules "Done in Port configuration file"
*** - Third Step is to Set the GPIO AFSEL bits for the ADC input pins
*** -	Fourth Step is to Configure the AINx signals to be analog inputs
***      *** Sample Sequencer Configuration ***
*** - Fifth Step is to Ensure that the sample sequencer is disabled
*** - Sixth Step is to Configure the trigger event for the sample sequencer in the ADCEMUX register.
*** - Seventh Step is to configure the corresponding input source in the ADCSSMUXn register
*** - Eighth Step is to configure the sample control bits in the corresponding nibble in the ADCSSCTLn register
*** - Ninth Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS register.
*** Input : none
*** Output : ERROR_STATUS
**
*/
extern ERROR_STATUS ADC_Init ();

/*
*** this function is responsible to Start ADC Conversion
*** Input  : uint8_t  ADC_Index -> determine which elemnt from the  gstr_ADC_Activated_Channels_Arr we want to statart Conversion for it 
***          uint32_t* u32_ADC_Digital_Reading -> to Get the Value using it 
*** Output : ERROR_STATUS
*/
extern ERROR_STATUS  ADC_Start_Conversion(uint8_t u8_ADC_Index, uint32_t* u32_ADC_Digital_Reading);


/*
*** this function is responsible to convert ADC Digital Value To Analog Voltage Value 
*** Input  : uint8_t  ADC_Index -> determine which elemnt from the  gstr_ADC_Activated_Channels_Arr we want to get it's value
***          float* Voltage_Value -> to Get the Value using it
*** Output : ERROR_STATUS
*/
extern ERROR_STATUS ADC_Get_Voltage_Reading(uint8_t u8_ADC_Index,float* Voltage_Value);

#endif /* ADC_H_ */


