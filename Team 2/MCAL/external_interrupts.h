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
#include "../Common/std_types.h"
#include "DIO.h"


#define FLAG_HIGH 1
#define FLAG_LOW 0
/**************************************ENUMs**********************************/
typedef enum EN_Edge_t{
	LOW_LEVEL=0,
	ANY_CHANGE=1,
	FALLING_EDGE = 2,
	RISIGING_EDGE = 3
}EN_Edge_t;



/*********************************global variables*********************************/
extern volatile void (*g_callBackPtr_INT2)(void);
extern uint8_t gu8_UltraSonic_Erro_Detection;
/************************************functions*******************************/
ERROR_STATUS INT0_Init(EN_Edge_t);
ERROR_STATUS INT1_Init(EN_Edge_t);
ERROR_STATUS INT2_Init(EN_Edge_t);
ERROR_STATUS INT0_DeInit(void);
ERROR_STATUS INT1_DeInit(void);
ERROR_STATUS INT2_DeInit(void);
ERROR_STATUS INT2_SetEdge(EN_Edge_t en_edge_selection);
#endif /* EXTERNAL_INTERRUPTS_H_ */
