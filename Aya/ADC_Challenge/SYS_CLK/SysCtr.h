/*
 * SysCtr.h
 *
 * Created: 4/9/2020 2:53:14 AM
 *  Author: A_ayman
 */ 


#ifndef SYSCTR_H_
#define SYSCTR_H_

/*
*** Inclusions
*/
#include "../SL/ARM_STD_t.h"
#include "../SL/Common_Macros.h"
#include "SysCtr_Lcfg.h"
#include "../MCAL/PORT/MCU_HW_Registers.h"


/*
*** Function Declaration
*/

/*
*** this function is responsible to initialize System Clock
*** Input  : none
*** Output : none
*/
extern void SysCtr_init(void);

#endif /* SYSCTR_H_ */

