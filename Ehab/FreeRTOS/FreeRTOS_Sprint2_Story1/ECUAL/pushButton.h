/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include "pushButtonConfig.h"



#define BTN_0		0
#define BTN_1		1
#define BTN_2		2
#define BTN_3		3


#define Pressed		1
#define Released	0

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
extern ERROR_STATUS pushButtonInit(uint8_t u8_butotn_id);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
extern ERROR_STATUS pushButtonUpdate(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
extern ERROR_STATUS pushButtonGetStatus(uint8_t u8_butotn_id , uint8_t* pu8_ButtonStatus);

#endif /* PUSHBUTTON_H_ */