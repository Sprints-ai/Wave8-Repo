/*
 * Processor.h
 *
 * Created: 4/3/2020 11:40:57 AM
 *  Author: Khaled
 */ 


#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "stdint.h"

#define SWITCH_TO_PRIVILAGE     __asm__ ( "SVC #0x00" )

#define SWITCH_TO_UNPRIVILAGE   /*Read CONTROL reg*/            \
                                __asm__ ("MRS R0, CONTROL");    \
                                                                \
                                /*set bit 0*/                   \
                                __asm__ ("ORR R0, #0x01");      \
                                                                \
                                /*write in CONTROL reg*/        \
                                __asm__ ("MSR CONTROL, R0");    \







#endif /* PROCESSOR_H_ */
