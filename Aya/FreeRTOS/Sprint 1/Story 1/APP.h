/*
 * APP.h
 * Sprint1: Story 1
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


/*
*** Functions Declaration
*/

/* 
 * vTasksCreation_Toggle_LED
 * Prototype	: void vTasksCreation_LED_Toggle( void );
 * Description : Task Code for create Toggle Led Task.
 * Input       : None
 * Output      : None
 * In/Out      : None
 * Return      : None
 */
extern void vTasksCreation_Toggle_LED( void );

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