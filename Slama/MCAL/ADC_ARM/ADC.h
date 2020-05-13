/*
 * ADC.h
 *
 *  Created on: Apr 25, 2020
 *      Author: ahmed
 */

#ifndef ADC_H_
#define ADC_H_

#include "./SERVICES/std_types.h"

/*ADC Modules Macros For Read API*/
#define ADC_MODULE_1 (1)
#define ADC_MODULE_2 (2)
#define ADC_MODULE_3 (3)

ERROR_STATUS ADC_Link_Init(void);

ERROR_STATUS ADC_Read(uint16_t *Ptr_ADC_Val , uint8_t ADC_Module);
#endif /* ADC_H_ */
