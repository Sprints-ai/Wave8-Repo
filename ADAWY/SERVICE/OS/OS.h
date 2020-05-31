/*
 * OS.h
 *
 * Created: 2/24/2020 3:04:56 PM
 *  Author: Khaled
 */ 


#ifndef OS_H_
#define OS_H_

/* Inclusions */
#include "../../MCAL/Timer/timers.h"
#include "../std_types.h"
#include "OS_Cfg.h"
#include "OS_PbCfg.h"
#include "../Errors.h"
#include "../ERROR/ERROR-STORE.h"


/* Constants */

/*
*** this macro determine whether the task would be repeated or happen only once
*/

#define ONE_SHOT 0 
#define PERIODIC 1

/*macro to select timer id*/
#define  Timer_0      0
#define  Timer_1      1
#define  Timer_2      2





/* function declarations*/


/******************************************************************************
* Function        : ERROR_STATUS OS_Init (const str_OS_InitConfig_t * pstr_OS_ConfigPtr );
* Type            : public
* Input parameters: OSCfg Structure (u8_Timer_Id, u8_OS_Res)
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : initialize the OS configuration, which initialize the Timer.
*****************************************************************************/
extern ERROR_STATUS OS_Init (const str_OS_InitConfig_t * pstr_OS_ConfigPtr );

/******************************************************************************
* Function        : ERROR_STATUS OS_Dispatch(void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : check timing to serve the consumer function.
*****************************************************************************/
extern ERROR_STATUS OS_RUN(void);

/******************************************************************************
* Function        : ERROR_STATUS OS_Stop(uint8_t Task_Id, void(* Ptr_Func)(void));
* Type            : public
* Input parameters: Task_Id, void(* Ptr_Func)(void)
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : stop OS for a specific task
*****************************************************************************/
extern ERROR_STATUS Task_Delet(uint8_t Task_Id, void(* Ptr_Func)(void));

/******************************************************************************
* Function        : ERROR_STATUS OS_Start (uint16_t Time_Delay,uint8_t Task_Id, uint8_t Repeat, void(* Ptr_Func)(void));
* Type            : public
* Input parameters: Time_Delay(0 : 65536), Task_Priorty(0 : bufer size -1), Repeat (one shot or periodic), void(* Ptr_Func)(void))
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : start OS for a specific task
*****************************************************************************/
extern ERROR_STATUS Task_Creat (uint16_t Time_Delay,uint8_t Task_Priorty, uint8_t Repeat, void(* Ptr_Func)(void));


/******************************************************************************
* Function        : ERROR_STATUS OS_DeInit (void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : start OS
*****************************************************************************/
extern ERROR_STATUS OS_DeInit (void);

#endif /* OS_H_ */
