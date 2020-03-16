/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

typedef enum En_buttonId_t{
	BTN_0,
	BTN_1
}En_buttonId_t;

typedef enum En_buttonStatus_t{
	Released,
	Prepressed,
	Pressed,
	Prereleased

}En_buttonStatus_t;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
ERROR_STATUS pushButtonInit(En_buttonId_t en_butotn_id);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
ERROR_STATUS pushButtonUpdate(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
ERROR_STATUS pushButtonGetStatus(En_buttonId_t en_butotn_id , En_buttonStatus_t* state);

#endif /* PUSHBUTTON_H_ */
