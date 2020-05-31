/*
 * ADC.h
 *
 *  Created on: Apr 25, 2020
 *      Author: K.Aladawy
 */

#ifndef MCAL_TI_PERIPHERALS_ADC_ADC_H_
#define MCAL_TI_PERIPHERALS_ADC_ADC_H_

/************************************************************************
 ******************************* INCLUDES *******************************
 ************************************************************************/
#include "ADC_Types.h"
#include "ADC_RegisterMap.h"
#include "ADC_Lcfg.h"
#include "ADC_Cfg.h"

#if (TEST_MODE)
#include <stdio.h>
#endif

/************************************************************************
 ***************************** GLOBAL MACRO *****************************
 ************************************************************************/




/************************************************************************
 *************************** APIS PROTOTYPES ****************************
 ************************************************************************/

/* Sync/Async: Synchronous
 * Parameters (in): (ConfigPtr) Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the ADC hardware units and driver.
 */
extern void Adc_Init( const Adc_ConfigType* ConfigPtr );



/* Sync/Async: Synchronous
 * Parameters (in): Group: Numeric ID of requested ADC channel group.
 *                  DataBufferPtr: pointer to result data buffer
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: Std_ReturnType: E_OK: result buffer pointer initialized correctly
 *                               E_NOT_OK: operation failed or development error occured
 * Description: Initializes ADC driver with the group specific result buffer start address where the conversion results will be stored.
 *              The application has to ensure that the application buffer, where DataBufferPtr points to, can hold all the conversion
 *              results of the specified group. The initialization with Adc_SetupResultBuffer is required after reset, before a group
 *              conversion can be started.
 */
extern Std_ReturnType Adc_SetupResultBuffer( Adc_SequencerType Group, Adc_ValueGroupType* DataBufferPtr );



/* Sync/Async: Asynchronous
 * Parameters (in): Group: Numeric ID of requested ADC Channel group.
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Description: Starts the conversion of all channels of the requested ADC Channel group.
 */
extern void Adc_StartGroupConversion( Adc_SequencerType Group );



/* Sync/Async: Synchronous
 * Parameters (in): Group: Numeric ID of requested ADC Channel group.
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Description: Stops the conversion of the requested ADC Channel group.
 */
extern void Adc_StopGroupConversion( Adc_SequencerType Group );



/* Sync/Async: Synchronous
 * Parameters (in): Group: Numeric ID of requested ADC channel group.
 * Parameters (inout): None
 * Parameters (out): DataBufferPtr: ADC results of all channels of the selected group are stored in
 *                   the data buffer addressed with the pointer.
 * Return value: Std_ReturnType: FALSE: results are available and written to the data buffer
 *                               TRUE: no results are available or development error occured
 * Description: Reads the group conversion result of the last completed conversion round of the requested group
 *              and stores the channel values starting at the DataBufferPtr address. The group channel values are stored
 *              in channel number on sequencer order.
 */
extern Std_ReturnType Adc_ReadGroup( Adc_SequencerType Group, Adc_ValueGroupType* DataBufferPtr );



/* Sync/Async: Synchronous
 * Parameters (in): Group: Numeric ID of requested ADC Channel group.
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: Adc_StatusType: Conversion status for the requested group.
 * Description: Returns the conversion status of the requested ADC Channel group.
 */
extern Adc_StatusType Adc_GetGroupStatus( Adc_SequencerType Group );
#endif /* MCAL_TI_PERIPHERALS_ADC_ADC_H_ */
