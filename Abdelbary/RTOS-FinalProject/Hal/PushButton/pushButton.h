/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#include "pushButtonConfig.h"
#include "../../Utilities/common_macros.h"
typedef enum En_buttonId_t{
	BTN_0,
	BTN_1,
	BTN_2,
	BTN_3
}En_buttonId_t;

typedef enum En_buttonStatus_t{
	Pressed,
	Released
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
ERROR_STATUS pushButtonGetStatus(En_buttonId_t en_butotn_id,uint8_t * state);

ERROR_STATUS pushButtonPressed(uint8_t en_butotn_id,uint8_t* flag);

#endif /* PUSHBUTTON_H_ */