/*
 ============================================================================
 Name        : external_interrupt.h
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "interrupt.h"
#include "../HAL/ICU.h"
#include "../Common/std_types.h"
#include "DIO.h"
/**************************************ENUMs**********************************/
typedef enum EN_Edge_t{
	LOW_LEVEL=0,
	ANY_CHANGE=1,
	FALLING_EDGE = 2,
	RISIGING_EDGE = 3
}EN_Edge_t;



/*********************************global flags*********************************/



/************************************functions*******************************/
ERROR_STATUS INT0_Init(EN_Edge_t);
ERROR_STATUS INT1_Init(EN_Edge_t);
ERROR_STATUS INT2_Init(EN_Edge_t);
ERROR_STATUS INT0_DeInit(void);
ERROR_STATUS INT1_DeInit(void);
ERROR_STATUS INT2_DeInit(void);
ERROR_STATUS INT2_SetEdge(EN_Edge_t en_edge_selection);
#endif /* EXTERNAL_INTERRUPTS_H_ */
