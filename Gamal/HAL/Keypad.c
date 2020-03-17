/*
 ============================================================================
 Name        : Keypad.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */


#include "keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8_t KeyPad_getPressedKey(void)
{
	uint8_t col,row;
	uint8_t key=0;
	for(col=0;col<N_col;col++) /* loop for columns */
	{
		/*
		 * each time only one of the column pins will be output and
		 * the rest will be input pins include the row pins
		 */
		KEYPAD_PORT_DIR = (0b00010000<<col);

		/*
		 * clear the output pin column in this trace and enable the internal
		 * pull up resistors for the rows pins
		 */
		KEYPAD_PORT_OUT = (~(0b00010000<<col));
		for(row=0;row<N_row;row++) /* loop for rows */
		{
			if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row)) /* if the switch is press in this row */
			{
				#if (N_col == 3)
					key = ((row*N_col)+col+1);
			}
		}
	}
	return key;
}



#endif
