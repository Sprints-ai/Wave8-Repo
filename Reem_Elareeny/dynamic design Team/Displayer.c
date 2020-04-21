/*
 * Displayer.c
 *
 * Created: 3/30/2020 10:56:09 AM
 *  Author: Reem el-Areeny
 */ 

#include "Displayer.h"

uint8_t DISPLAYER_isInitialized = FALSE;

ERROR_STATUS Displayer_init()
{

	ERROR_STATUS ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;

	if(!DISPLAYER_isInitialized)
	{
		switch(Display_method)
		{
			case LCD:
				ERR = LCD_init();
				if(ERR == /*ERROR_LCD_MODULE +*/ E_OK)
				{
					ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;
					DISPLAYER_isInitialized = TRUE;
				}
				break;

			default:
				ERR = /*ERROR_DISPLAYER_MODULE +*/ ERROR_INVALID_PARAMETER;
				break;

		}
	}
	else
	{
		ERR = /*ERROR_DISPLAYER_MODULE +*/ ERROR_MODULE_ALREADY_INITIALIZED;
	}

	return ERR;
}


 ERROR_STATUS Displayer_write_digit(uint8_t u8_oneDigitVaue)
 {
 	ERROR_STATUS ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;
	
	if(DISPLAYER_isInitialized)
	{
		switch(Display_method)
		{
			case LCD:

// 				if(u8_oneDigitVaue/10 > 0){
// 					LCD_writeChar(u8_oneDigitVaue/10 + '0');
// 					LCD_writeChar(u8_oneDigitVaue%10 + '0');
// 
// 				}else{
// 					LCD_writeChar(u8_oneDigitVaue + '0');
// 				}

				if(u8_oneDigitVaue/10 > 0)  /*2 digit number*/
				{
					ERR = LCD_writeChar(u8_oneDigitVaue/10 + '0');
					if(ERR == /*ERROR_LCD_MODULE +*/ E_OK)
					{
						ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;
						ERR = LCD_writeChar(u8_oneDigitVaue%10 + '0');
						if(ERR == /*ERROR_LCD_MODULE +*/ E_OK)
							ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;
					}
				}
				else
				{
					ERR = LCD_writeChar(u8_oneDigitVaue + '0');
					if(ERR == /*ERROR_LCD_MODULE +*/ E_OK)
						ERR = /*ERROR_DISPLAYER_MODULE +*/ E_OK;
				}
 				break;
			default:
				ERR = /*ERROR_DISPLAYER_MODULE +*/ ERROR_INVALID_PARAMETER;
				break;
		}
	}
	else
	{
		ERR = /*ERROR_DISPLAYER_MODULE +*/ ERROR_MODULE_NOT_INITIALIZED;
	}
	return ERR;	
 }

 void displayer_clear(){
	LCD_Clear();
 }