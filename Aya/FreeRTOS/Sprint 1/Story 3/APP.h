/*
 * APP.h
 * Sprint1: Story 3
 * Created: 4/15/2020 5:40:37 PM
 *  Author: AYA and EMAN
 */ 



#ifndef APP_H_
#define APP_H_

/*
*** Inclusions
*/
#include "../HAL/LED/led.h"
#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../HAL/PUSH BUTTON/pushButton.h"

/* 
 * vTasksCreation_LED_Toggle
 * Prototype	: void vTasksCreation_LED_Toggle( void );
 * Description : Task Code To create Led Toggle Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_LED_Toggle( void );

/* 
 * vTasksCreation_PushButton
 * Prototype	: void vTasksCreation_PushButton( void );
 * Description : Task Code To create Push Button Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_PushButton( void );


/* 
 * vTasksCreation_Init_Task
 * Prototype	: void vTasksCreation_Init_Task( void );
 * Description : Task Code for create Initialization Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_Init_Task( void );

#endif /* APP_H_ */