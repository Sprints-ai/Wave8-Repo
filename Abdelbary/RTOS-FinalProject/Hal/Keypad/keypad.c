
#include "keypad.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8_t KeyPad_getPressedKey(uint8_t* Pressed_Key)
{
	uint8_t retVal=0;
	uint8_t keyFound = 0;
	uint8_t result=0;
	static uint8_t prevResult = NO_KEY_PRESSED;
	uint8_t col,row,gotKey=1;
	*Pressed_Key = NO_KEY_PRESSED;
	gpioPortDirection(GPIOC,0xF0);
	for(col=0;col<N_col;col++) /* loop for columns */
	{

		gpioPortWrite(GPIOC,(~(0b00010000<<col)));

		for(row=0;row<N_row;row++) /* loop for rows */
		{gpioPinRead(GPIOC,(row+1),&gotKey);
		if(gotKey==0) /* if the switch is press in this row */
		{
			result = (row*N_col)+col+1;
			//*Pressed_Key = result;
			keyFound = 1;
		}
	
		}
	}


	if(keyFound == 1)
	{
		if(result == prevResult)
		{
			*Pressed_Key = result;
			retVal = KEYPAD_DONE;
	 if(result>6){
		*Pressed_Key=*Pressed_Key-3;
	}
		}
		else if((result != prevResult))
		{
			prevResult = result;
			retVal = NO_KEY_PRESSED;
		}

		keyFound = 0;
	}
	else
	{
		prevResult = NO_KEY_PRESSED;
		retVal = NO_KEY_PRESSED;
	}

	return retVal;

}