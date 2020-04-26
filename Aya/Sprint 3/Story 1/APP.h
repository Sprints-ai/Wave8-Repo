/*
 * APP.h
 * Sprint3: Story 1
 * Created: 4/22/2020 1:48:36 AM
 *  Author: AYA and EMAN
 */ 

#ifndef APP_H_
#define APP_H_

/*
*** Inclusions
*/

#include "../HAL/LCD/NEW_LCD.h"
#include "../MCAL/UART/UART.h"
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
 * vTasksCreation_KYEPAD_GetKey
 * Prototype	: void vTasksCreation_KYEPAD_GetKey( void );
 * Description : Task Code To create Keypad Read Input Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskB_KYEPAD_GetKey( void );

/* 
 * Create_TaskC_Get_UART_Data
 * Prototype	: void Create_TaskC_Get_UART_Data( void );
 * Description : Task Code To create a Task to rec data from UART.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskC_Get_UART_Data( void );

/* 
 * Create_TaskD_Get_Button1_State
 * Prototype	: void Create_TaskD_Get_Button1_State( void );
 * Description : Task Code To create Push Button 1 Get status Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void Create_TaskD_Get_Button1_State( void );


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