/*
 * NVIC.h
 *
 * Created: 4/3/2020 2:27:43 PM
 *  Author: A_ayman
 */ 


#ifndef NVIC_H_
#define NVIC_H_

/*
*** Inclusions
*/
#include "NVIC_Types.h"
#include "Common_Macros.h"
#include "NVIC_LCFG.h"
#include "ARM_STD_t.h"
#include "MCU_HW_Registers.h"

/*
*** Function Declaration
*/

/*
*** this function is responsible to initialize NVIC, By setting APINT combination
*** Enable Interrupt and set priority
*** Input : none
*** Output : none
*/
extern void NVIC_Init(void);




#endif /* NVIC_H_ */
