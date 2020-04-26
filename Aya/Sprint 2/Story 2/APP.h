/*
 * APP.h
 * Sprint2: Story 2
 * Created: 4/21/2020 1:48:36 AM
 *  Author: AYA and EMAN
 */ 



#ifndef APP_H_
#define APP_H_

/*
*** Inclusions
*/

#include "../HAL/LCD/NEW_LCD.h"
#include "../HAL/LED/led.h"
#include "../HAL/PUSH BUTTON/pushButton.h"
#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../RTOS/event_groups.h" 
/*
*** functions declaration
*/

/* 
 * Create_TaskA_Get_Button1_State
 * Prototype	: void Create_TaskA_Get_Button1_State( void );
 * Description : Task Code To create Push Button 1 Get status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskA_Get_Button1_State( void );

/* 
 * Create_TaskC_Switch_LED
 * Prototype	: void Create_TaskC_Switch_LED( void );
 * Description : Task Code To create a Task to switch LED ON, OFF.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskC_Switch_LED( void );

/* 
 * Create_TaskB_Get_Button2_State
 * Prototype	: void Create_TaskB_Get_Button2_State( void );
 * Description : Task Code To create Push Button 2 Get Status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskB_Get_Button2_State( void );

/* 
 * Create_TaskD_LCD_Display
 * Prototype	: void Create_TaskD_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskD_LCD_Display( void );

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