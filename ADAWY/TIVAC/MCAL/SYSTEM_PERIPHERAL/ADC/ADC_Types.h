/*
 * ADC_Types.h
 *
 *  Created on: Apr 25, 2020
 *      Author: K.Aladawy
 */

#ifndef MCAL_TI_PERIPHERALS_ADC_ADC_TYPES_H_
#define MCAL_TI_PERIPHERALS_ADC_ADC_TYPES_H_

#include "stdint.h"


typedef uint8_t Std_ReturnType;
#define NULL    ((void *)0)


typedef uint8_t Adc_SequencerType; /*Numeric ID of an ADC channel group.*/
#define ADC_SEQUENCER_0_MODULE0                                           (0u)
#define ADC_SEQUENCER_1_MODULE0                                           (1u)
#define ADC_SEQUENCER_2_MODULE0                                           (2u)
#define ADC_SEQUENCER_3_MODULE0                                           (3u)
#define ADC_SEQUENCER_0_MODULE1                                           (10u)
#define ADC_SEQUENCER_1_MODULE1                                           (11u)
#define ADC_SEQUENCER_2_MODULE1                                           (12u)
#define ADC_SEQUENCER_3_MODULE1                                           (13u)


typedef uint8_t Adc_EventTriggerSourceType;
#define ADC_TRIGGER_SOURCE_PPROCESSOR                                     (0X0u)
#define ADC_TRIGGER_SOURCE_ANALOG_COMPARATOR_0                            (0X1u)
#define ADC_TRIGGER_SOURCE_ANALOG_COMPARATOR_1                            (0X2u)
#define ADC_TRIGGER_SOURCE_EXTERNAL                                       (0X4u)
#define ADC_TRIGGER_SOURCE_TIMER                                          (0X5u)
#define ADC_TRIGGER_SOURCE_PWM_GENERATOR_0                                (0X6u)
#define ADC_TRIGGER_SOURCE_PWM_GENERATOR_1                                (0X7u)
#define ADC_TRIGGER_SOURCE_PWM_GENERATOR_2                                (0X8u)
#define ADC_TRIGGER_SOURCE_PWM_GENERATOR_3                                (0X9u)
#define ADC_TRIGGER_SOURCE_CONTINUOUS                                     (0XFu)


/*Numeric ID of an ADC channel.*/
typedef uint8_t Adc_ChannelType;
#define ADC_CHANNEL_AIN0                                                  (0x0u)
#define ADC_CHANNEL_AIN1                                                  (0x1u)
#define ADC_CHANNEL_AIN2                                                  (0x2u)
#define ADC_CHANNEL_AIN3                                                  (0x3u)
#define ADC_CHANNEL_AIN4                                                  (0x4u)
#define ADC_CHANNEL_AIN5                                                  (0x5u)
#define ADC_CHANNEL_AIN6                                                  (0x6u)
#define ADC_CHANNEL_AIN7                                                  (0x7u)
#define ADC_CHANNEL_AIN8                                                  (0x8u)
#define ADC_CHANNEL_AIN9                                                  (0x9u)
#define ADC_CHANNEL_AIN10                                                 (0xAu)
#define ADC_CHANNEL_AIN11                                                 (0xBu)
#define ADC_CHANNEL_TEMP_SENSOR                                           (0xFu)


typedef uint8_t Adc_NumOfSampleInSequencer;
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_0                                  (0x0u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_1                                  (0x1u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_2                                  (0x2u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_3                                  (0x3u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_4                                  (0x4u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_5                                  (0x5u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_6                                  (0x6u)
#define ADC_NUM_OF_SAMPLE_IN_SEQUENCER_7                                  (0x7u)


typedef uint8_t Adc_OperationModeType;
#define ADC_OPERATION_MODE_POLLING                                        (0x1u)
#define ADC_OPERATION_MODE_INTERRUPT                                      (0x2u)


typedef uint8_t Adc_EndOfSampleType;
#define ADC_END_OF_SAMPLE_ACTIVE                                          (0x1u)
#define ADC_END_OF_SAMPLE_DEACTIVATE                                      (0x0u)


typedef uint8_t Adc_SequencerPriorityType;
#define ADC_SEQUENCER_PRIORITY_0                                          (0x0u)
#define ADC_SEQUENCER_PRIORITY_1                                          (0x1u)
#define ADC_SEQUENCER_PRIORITY_2                                          (0x2u)
#define ADC_SEQUENCER_PRIORITY_3                                          (0x3u)


typedef uint8_t Adc_SamplePhaseType;
#define ADC_SAMPLE_PHASE_0_0                                              (0x0u)
#define ADC_SAMPLE_PHASE_22_5                                             (0x1u)
#define ADC_SAMPLE_PHASE_45_0                                             (0x2u)
#define ADC_SAMPLE_PHASE_90_0                                             (0x3u)
#define ADC_SAMPLE_PHASE_112_5                                            (0x4u)
#define ADC_SAMPLE_PHASE_135_0                                            (0x5u)
#define ADC_SAMPLE_PHASE_157_5                                            (0x6u)
#define ADC_SAMPLE_PHASE_180_0                                            (0x7u)
#define ADC_SAMPLE_PHASE_202_5                                            (0x8u)
#define ADC_SAMPLE_PHASE_225_0                                            (0x9u)
#define ADC_SAMPLE_PHASE_247_5                                            (0xAu)
#define ADC_SAMPLE_PHASE_270_0                                            (0xBu)
#define ADC_SAMPLE_PHASE_292_5                                            (0xDu)
#define ADC_SAMPLE_PHASE_315_0                                            (0xEu)
#define ADC_SAMPLE_PHASE_337_5                                            (0xFu)


typedef uint8_t Adc_SampleModeType;
#define ADC_SAMPLE_MODE_SINGLE_END                                        (0xFu)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR0                               (0x0u)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR1                               (0x1u)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR2                               (0x2u)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR3                               (0x3u)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR4                               (0x4u)
#define ADC_SAMPLE_MODE_DIFFERENTIAL_PAIR5                               (0x05)


typedef uint8_t Adc_SampleAveragingCircuitType;
#define ADC_SAMPLE_AVERAGING_CIRCUIT_No_HARDWARE_OVERSAMPLING             (0X0u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_2x_HARDWARE_OVERSAMPLING             (0X1u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_4x_HARDWARE_OVERSAMPLING             (0X2u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_8x_HARDWARE_OVERSAMPLING             (0X3u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_16x_HARDWARE_OVERSAMPLING            (0X4u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_32x_HARDWARE_OVERSAMPLING            (0X5u)
#define ADC_SAMPLE_AVERAGING_CIRCUIT_64x_HARDWARE_OVERSAMPLING            (0X6u)


/* Data structure containing the set of configuration parameters required for initializing the ADC Driver and ADC HW Unit(s).*/
typedef struct
{
    Adc_SequencerType                 ADC_Sequencer;
    Adc_EventTriggerSourceType        ADC_TriggerSource;
    Adc_NumOfSampleInSequencer        ADC_SampleNum;
    Adc_ChannelType                   ADC_Channel;
    Adc_OperationModeType             ADC_OperationMode;
    Adc_EndOfSampleType               ADC_EndOfSample;
    Adc_SequencerPriorityType         ADC_SequencerPriority;
    Adc_SamplePhaseType               ADC_SamplePhase;
    Adc_SampleModeType                ADC_SampleMode;
    Adc_SampleAveragingCircuitType    ADC_SampleAveragingCircuit;
}Adc_ConfigType;


/* Type for reading the converted values of a channel group
 * (raw, without further scaling, alignment according precompile switch ADC_RESULT_ALIGNMENT).
 */
typedef uint32_t Adc_ValueGroupType;


/*Type of channel resolution in number of bits.*/
typedef uint8_t Adc_ResolutionType;
#define ADC_RESOLUTION_12_BIT                    12


/*Current status of the conversion of the requested ADC Channel group.*/
typedef uint8_t Adc_StatusType;
#define ADC_IDLE                                  1 /* The conversion of the specified group has not been started.
                                                     * No result is available
                                                     */

#define ADC_BUSY                                  2 /* The conversion of the specified group has been started and is still going on.
                                                     * So far no result is available.
                                                     */

#define ADC_COMPLETED                             3 /* A conversion round of the specified group has been finished.
                                                     * A result is available for all channels of the group.
                                                     */


#endif /* MCAL_TI_PERIPHERALS_ADC_ADC_TYPES_H_ */
