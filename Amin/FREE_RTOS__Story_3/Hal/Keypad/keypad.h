
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "gpio.h"
#include "regesters.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4
#define NO_KEY_PRESSED 20
#define KEYPAD_DONE 26

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8_t KeyPad_getPressedKey(uint8_t* Pressed_Key);

#endif /* KEYPAD_H_ */

