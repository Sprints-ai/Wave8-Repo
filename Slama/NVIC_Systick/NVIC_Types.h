/*Author : Ahmed Salama
*/

#ifndef NVIC_TYPES_H
#define NVIC_TYPES_H

/*Include*/
#include "../std_types.h"

/*interrupt Configs*/
typedef uint8_t SubGroup_PriorityType;
typedef uint8_t Group_PriorityType;
typedef uint8_t IntNumType;

typedef struct NVIC_Types
{
    /* Struct contains interrupts info */
    IntNumType IntNum;
    Group_PriorityType Group_Priority;
    SubGroup_PriorityType SubGroup_priority;
}NVIC_CfgType;


#endif
