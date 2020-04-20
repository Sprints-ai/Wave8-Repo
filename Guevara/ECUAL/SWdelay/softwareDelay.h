/*
 * softwareDelay.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef SOFTWAREDELAY_H_
#define SOFTWAREDELAY_H_
#include "../../Infrastructure/std_types.h"
/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the milli-seconds
 */
void SwDelay_ms(uint32_t n);

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the micro-seconds
 */
void SwDelay_us(uint32_t n);

#endif /* SOFTWAREDELAY_H_ */
