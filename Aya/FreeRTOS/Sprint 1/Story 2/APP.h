/*
 * APP.h
 * Sprint1: Story 2
 * Created: 4/15/2020 5:40:37 PM
 *  Author: AYA and EMAN
 */ 



#ifndef APP_H_
#define APP_H_

/*
*** Inclusions
*/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/NEW_LCD.h"
#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"

/*
*** functions declaration
*/


/* 
 * vTasksCreation_LCD_Display
 * Prototype	: void vTasksCreation_LCD_Display( void );
 * Description : Task Code To create LCD Display Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_LCD_Display(void);

/* 
 * vTasksCreation_KYEPAD_GetKey
 * Prototype	: void vTasksCreation_KYEPAD_GetKey( void );
 * Description : Task Code To create Keypad Read Input Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_KYEPAD_GetKey( void );

/* 
 * vTasksCreationInit
 * Prototype	: void vTasksCreationInit( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreationInit( void );






#endif /* APP_H_ */