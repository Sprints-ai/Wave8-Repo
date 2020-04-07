/*
 * NVIC_Types.h
 *
 * Created: 4/7/2020 10:05 AM
 *  Author: Ema
 */
#include"STD_Types.h"

typedef uint8_t IntNumType
typedef uint8_t SubGroup_PriorityType
typedef uint8_t Group_PriorityType

typedef struct
{
	IntNumType              IntNum;
	Group_PriorityType      Group_Priority;
	SubGroup_PriorityType	SubGroup_Priority
}NVIC_CfgType;
