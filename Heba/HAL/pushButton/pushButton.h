/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_
#include "pushButtonConfig.h"
#include "../../Infrastructure/softwareDelay.h"




/*	 En_buttonId	*/

#define	BTN_0		0
#define BTN_1		1
	

/*	 Button Status	*/
#define Released    0

#define	Pressed		1
	



/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1) to Input
 * @param btn_id: The btn to be initialized and it takes BTN_0 or BTN_1
 * 				  
 *
 */
u8_ERROR_STATUS_t pushButtonInit(uint8_t en_butotn_id);

/**
 * Description: read BTN_x (where x 0, 1) state
 * 				
 *
 */
u8_ERROR_STATUS_t pushButtonGetStatus(uint8_t en_butotn_id,uint8_t * staut_flag);

#endif /* PUSHBUTTON_H_ */