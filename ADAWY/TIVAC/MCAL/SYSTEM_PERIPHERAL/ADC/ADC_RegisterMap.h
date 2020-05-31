/*
 * ADC_RegisterMap.h
 *
 *  Created on: Apr 25, 2020
 *      Author: K.Aladawy
 */

#ifndef MCAL_TI_PERIPHERALS_ADC_ADC_REGISTERMAP_H_
#define MCAL_TI_PERIPHERALS_ADC_ADC_REGISTERMAP_H_
#include "stdint.h"

typedef struct
{
    uint32_t ADCSSMUX             ;
    uint32_t ADCSSCTL             ;
    uint32_t ADCSSFIFO            ;
    uint32_t ADCSSFSTAT           ;
    uint32_t ADCSSOP              ;
    uint32_t ADCSSDC              ;
    uint32_t Reserved_3           ;
    uint32_t Reserved_4           ;
}SEQUENCER_Register_Type;


typedef struct
{
    uint32_t ADCACTSS              ;
    uint32_t ADCRIS                ;
    uint32_t ADCIM                 ;
    uint32_t ADCISC                ;
    uint32_t ADCOSTAT              ;
    uint32_t ADCEMUX               ;
    uint32_t ADCUSTAT              ;
    uint32_t ADCTSSEL              ;
    uint32_t ADCSSPRI              ;
    uint32_t ADCSPC                ;
    uint32_t ADCPSSI               ;
    uint32_t Reserved_1            ;
    uint32_t ADCSAC                ;
    uint32_t ADCDCISC              ;
    uint32_t ADCCTL                ;
    uint32_t Reserved_2            ;
    SEQUENCER_Register_Type SEQUENCER_ARR[4];
    uint8_t  REserved_9[0xC38]     ;
    uint32_t ADCDCRIC              ;
    uint8_t  REserved_10[0xFC]     ;
    uint32_t ADCDCCTL0             ;
    uint32_t ADCDCCTL1             ;
    uint32_t ADCDCCTL2             ;
    uint32_t ADCDCCTL3             ;
    uint32_t ADCDCCTL4             ;
    uint32_t ADCDCCTL5             ;
    uint32_t ADCDCCTL6             ;
    uint32_t ADCDCCTL7             ;
    uint8_t  REserved_11[0x20]     ;
    uint32_t ADCDCCMP0             ;
    uint32_t ADCDCCMP1             ;
    uint32_t ADCDCCMP2             ;
    uint32_t ADCDCCMP3             ;
    uint32_t ADCDCCMP4             ;
    uint32_t ADCDCCMP5             ;
    uint32_t ADCDCCMP6             ;
    uint32_t ADCDCCMP7             ;
    uint8_t  REserved_12[0x160]    ;
    uint32_t ADCPP                 ;
    uint32_t ADCPC                 ;
    uint32_t ADCCC                 ;
}ADC_Register_Type;



#define ADC0      ((ADC_Register_Type*)0x40038000)
#define ADC1      ((ADC_Register_Type*)0x40039000)


#endif /* MCAL_TI_PERIPHERALS_ADC_ADC_REGISTERMAP_H_ */
