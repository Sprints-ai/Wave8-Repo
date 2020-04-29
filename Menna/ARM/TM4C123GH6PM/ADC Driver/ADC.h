
/**************************************************************************************/
/*																ADC.h						  														    */
/**************************************************************************************/

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"

/**
 * Fun----------: ERROR_STATUS ADC_Init(void);
 * Return-------: ERROR_STATUS
 * Description--: ADC Module initialization
*/

extern ERROR_STATUS ADC_init(void);

/**
 * Fun----------: ERROR_STATUS ADC_Init(void);
 * Output-------: result the value converted 
 * Return-------: ERROR_STATUS
 * Description--: initializes the the ADC Module 
*/
extern ERROR_STATUS start_conversion(uint8_t* result) ;


#endif /* ADC_H_ */
