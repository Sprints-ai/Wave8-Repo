/*
 * lcd.c
 *
 * Created: 3/15/2020 1:32:20 PM
 *  Author: Mohamed Ramadan
 */ 
 /*********************************************
 *				Includes  					 *
 ********************************************/
 #include "lcd.h"

/*********************************************
*				Defines  					 *
********************************************/ 


/*********************************************
 *	   Function Implementation  	       	  *
 ********************************************/


EnmLCDError_t LCD_SendNibble(uint8_t data){
	/**Err_status store of the error of the function**/
	uint8_t Err_status  = E_OK;
	
	LCD_PORT = data;
	
	/**return the error status of the function**/
	return	Err_status;
}
/**
 * Func			: LCD_Configure_Pins
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_Configure_Pins(void){
	/**Err_status store of the error of the function**/
		uint8_t Err_status  = E_OK;
	
	
	/**Initialize the RS Pin in PORTA as output**/
	DIO_init(&LCD_RS_Cfg_S);
	/**Initialize the RW Pin in PORTA as output**/
	DIO_init(&LCD_RW_Cfg_S);
	/**Initialize the EN Pin in PORTA as output**/
	DIO_init(&LCD_EN_Cfg_S);
	/**Initialize the D4 Pin in PORTA as output**/
	DIO_init(&LCD_D4_Cfg_S);
	/**Initialize the D5 Pin in PORTA as output**/
	DIO_init(&LCD_D5_Cfg_S);
	/**Initialize the D6 Pin in PORTA as output**/
	DIO_init(&LCD_D6_Cfg_S);
	/**Initialize the D7 Pin in PORTA as output**/
	DIO_init(&LCD_D7_Cfg_S);
	
	/**return the error status of the function**/
	return	Err_status;
}
/**
 * Func			: LCD_SendCommand
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_SendCommand(uint8_t data){
	/**Err_status store of the error of the function**/
	uint8_t Err_status  = E_OK;
	
	DIO_Write(LCD_RS_PORT,LCD_RS_PIN,LOW);
	
	LCD_SendNibble(data);
	LCD_EN_Start();
	
	LCD_SendNibble(data<<4);
	LCD_EN_Start();
	_delay_ms(1);
	/**return the error status of the function**/
	return	Err_status;
}

/**
 * Func			: LCD_Init
 * Input		: NO
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (LCD PINS)
 */
EnmLCDError_t LCD_Init(void){
	/**Err_status store of the error of the function**/
		uint8_t Err_status  = E_OK;
		
		/**Configure pins in LCD in OUTPUT mode**/
		LCD_Configure_Pins();
		_delay_ms(20);
		
		
		//LCD_SendCommand(0x33);
		return	Err_status;
}