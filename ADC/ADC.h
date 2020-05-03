
#ifndef __ADC_H__
#define __ADC_H__

#include "..\std_types.h"
#include "ADC_Types.h"


/*
 * @param: input:  NONE  
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the ADC   
 */

u8_ERROR_STATUS_t ADC_Init( void );

/*
* @param: input:  ADC_Moduel_Sample_Sequencer  :a)witch indicate the ADC moduel number(takes one of(0,1) )
*																								b)witch indicate the Sample sequencer number (takes one of(0,1,2,3))
* @param: output: u16_ReadValue :whitch it is a pointer to array of 9 element (send the address of an array of 16 
*																ex:( uint16_t arr[9]; 
*																			ADC_ReadSS(...,&arr))
* @param :Input/output :None 
* @Return : Error status 
* Description :  Initializes the ADC   
*/

u8_ERROR_STATUS_t ADC_ReadSS(ADC_Moduel_Sample_Sequencer_t ADC_Moduel_Sample_Sequencer ,uint16_t (* u16_ReadValue)[9]);



#endif
