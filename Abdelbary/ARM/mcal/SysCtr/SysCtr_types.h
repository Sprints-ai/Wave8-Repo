#ifndef TM4C123_FIRMWARE_MCAL_SYSCTR_SYSCTR_TYPES_H_
#define TM4C123_FIRMWARE_MCAL_SYSCTR_SYSCTR_TYPES_H_

#include "../../utils/Std_Types.h"

typedef struct
{
    uint8 u8_crystalFreq;
    uint8 u8_clockSource;
    uint8 u8_sysClkFreq;

}str_sysCtrCfg_t;

#endif /* TM4C123_FIRMWARE_MCAL_SYSCTR_SYSCTR_TYPES_H_ */
