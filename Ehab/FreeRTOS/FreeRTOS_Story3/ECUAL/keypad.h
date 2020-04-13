/*
 * keypad.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Youssef
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../Infrastructure/std_types.h"
#include "../MCAL/DIO.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 3

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC_DATA
#define KEYPAD_PORT_IN  PORTC_PIN
#define KEYPAD_PORT_DIR PORTC_DIR

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
void KeyPad_getPressedKey(uint8_t* key);

#endif /* KEYPAD_H_ */
