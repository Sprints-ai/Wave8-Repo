/*
 * key.h
 *
 * Created: 3/16/2020 2:40:11 PM
 *  Author: hazem
 */ 


#ifndef KEY_H_
#define KEY_H_

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
uint8_t KeyPad_getPressedKey(void);





#endif /* KEY_H_ */