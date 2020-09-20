#ifndef SOFTWAREDELAY_H_
#define SOFTWAREDELAY_H_
#include "std_types.h"

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param a_delay_in_ms: the milli-seconds
 */

#define NUMBER_OF_ITERATIONS 433

void softwareDelayMs(uint32_t u32_delay_in_ms);

#endif /* SOFTWAREDELAY_H_ */



