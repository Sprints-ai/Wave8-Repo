/*
 * SOS.h
 *
 * Created: 3/11/2020 7:21:24 AM
 *  Author: A_ayman
 */ 


#ifndef SOS_H_
#define SOS_H_

/* Inclusions */
#include "../../MCAL/TIMERS/timers.h"
#include "../Utilis/std_types.h"
#include "SOS_CFG.h"
#include "SOS_PbCFG.h"
#include "../ERROR_HANDLING/ERROR-STORE.h"
#include "../ERROR_HANDLING/Errors.h"
#include "../CPU Meassurements/CPU_power_management.h"



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
* Function        : ERROR_STATUS Sos_Init (const gstr_SOS_InitConfig_t * pstr_SOS_ConfigPtr );
* Type            : public
* Input parameters: gstr_SOS_InitConfig_t (u8_Timer_Id, u8_SOS_Res)
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : initialize the Sos configuration, which initialize the Timer.
*****************************************************************************/
extern ERROR_STATUS Sos_Init (const gstr_SOS_InitConfig_t * pstr_SOS_ConfigPtr );

/******************************************************************************
* Function        : ERROR_STATUS Sos_Run(void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : check timing to serve the Tasks.
*****************************************************************************/
extern ERROR_STATUS Sos_Run(void);

/******************************************************************************
* Function        : ERROR_STATUS Sos_Delete_Task(uint8_t Task_Id);
* Type            : public
* Input parameters: Task_Id
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : Delete a specific task
*****************************************************************************/
extern ERROR_STATUS Sos_Delete_Task(uint8_t Task_Id);

/******************************************************************************
* Function        : Sos_Create_Task (gstr_Task_Info_t*);
* Type            : public
* Input parameters: Time_Delay(0 : 65536), Task_Id(0 : 255), Repeat (one shot or periodic), void(* Ptr_Func)(void))
* Return type     : ERROR_STATUS
* Reentrancy	   : Reentrant
* Description     : Create task
*****************************************************************************/
extern ERROR_STATUS Sos_Create_Task (gstr_Task_Info_t*);


/******************************************************************************
* Function        : SOS_DeInit (void);
* Type            : public
* Input parameters: none
* Return type     : ERROR_STATUS
* Reentrancy	   : Non Reentrant
* Description     : stop sos
*****************************************************************************/
extern ERROR_STATUS Sos_DeInit (void);





#endif /* SOS_H_ */