/*
 * NVIC.h
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */
 
 #ifndef __NVIC_H__
#define __NVIC_H__

 
/************************************************************************/
/*				               INCLUDES			                        */
/************************************************************************/

#include "NVIC_lCfg.h"


/************************************************************************/
/*				               defines			                        */
/************************************************************************/


#define INT_EN_LENGTH                  32
#define INT_PRI_LENGHT                 4


#define PRI_INTA                       0
#define PRI_INTB                       1
#define PRI_INTC                       2

#define PRI_START_INDEX_INTA           5
#define PRI_START_INDEX_INTB           13
#define PRI_START_INDEX_INTC           21

/************************************************************************/
/*				     function prototypes	                            */
/************************************************************************/


extern void NVIC_Init(void);

#endif