/*
 * APP.h
 * Sprint2: Story 1
 * Created: 4/21/2020 1:48:36 AM
 *  Author: AYA and EMAN
 */ 



#ifndef APP_H_
#define APP_H_

/*
*** Inclusions
*/

#include "../HAL/LCD/NEW_LCD.h"
#include "../HAL/PUSH BUTTON/pushButton.h"
#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../RTOS/event_groups.h"

/*
*** functions declaration
*/


/* 
 * Create_TaskA_LCD_Display
 * Prototype	: void Create_TaskA_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskA_LCD_Display( void );

/* 
 * Create_TaskB_Get_Button_State
 * Prototype	: void Create_TaskB_Get_Button_State( void );
 * Description : Task Code To create Button monitoring state Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskB_Get_Button_State( void );

/* 
 * Create_TaskC_Send_Data
 * Prototype	: void Create_TaskC_Send_Data( void );
 * Description : Task Code To create a Task to Send Data To LCD.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskC_Send_Data( void );

/* 
 * Create_Init_Task
 * Prototype	: void Create_Init_Task( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_Init_Task( void );






#endif /* APP_H_ */