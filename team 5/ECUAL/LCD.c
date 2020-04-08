/*
 * LCD.c
 *
 * Created: 3/15/2020 11:49:48 AM
 *  Author: MENA
 */ 
#include "DIO.h"
#include  "softwareDelay.h"
#include  "LCD.h"
#include "registers.h"
#include "avr/interrupt.h"


#define init_state_1 0
#define init_state_send_1 1
#define init_state_send_2 2
#define init_state_send_3 3
#define init_state_send_4 4
#define init_state_done	  5


#define SEND_COMMAND_STATE_1 0
#define SEND_COMMAND_STATE_2 1
#define SEND_COMMAND_STATE_3 2

#define SEND_CHAR_STATE_1 0
#define SEND_CHAR_STATE_2 1
#define SEND_CHAR_STATE_3 2


uint8_t init_done = FALSE;

ERROR_STATUS LCD_init(void){
	
	ERROR_STATUS error_state = E_OK ;
	DIO_Cfg_s portA_cfg ;
	static uint8_t counter = ZERO_VALUE;

static uint8_t init_task_state = init_state_1 ;
	
	
	counter++ ;

	switch(init_task_state){
		
		case init_state_1 :
		
		portA_cfg.GPIO = LCD_PORT ;
		portA_cfg.pins = LCD_RS| LCD_R_W | LCD_DATA | LCD_EN ;
		portA_cfg.dir = OUTPUT ;
		
		DIO_init(&portA_cfg);
		
		init_task_state = init_state_send_1;
		counter = 0 ;
		break;
		
		case init_state_send_1 :
		
		/* send return home command */
		LCD_sendCommand(DATA_MODE_4_BIT);
		if (counter==3)
		{
			init_task_state =init_state_send_2;
			counter = ZERO_VALUE ;
		}
		case init_state_send_2 :
		
		/* send 4 bit mode commands */
		LCD_sendCommand(DATA_MODE_2_LINE_4_BIT);
		if (counter==3)
		{
			init_task_state =init_state_send_3;
			counter = ZERO_VALUE ;
		}
		case init_state_send_3 :
		
		/* cursor state*/
		LCD_sendCommand(CURSOR_ON) ;
		if (counter==3)
		{
			init_task_state =init_state_send_4;
			counter = ZERO_VALUE ;
		}
		case init_state_send_4 :

		/* cursor state*/
		LCD_sendCommand(CLEAR_SCREEN);
		if (counter==3)
		{
			init_task_state =init_state_done;
			counter = ZERO_VALUE ;
		}

		
		break;

		case init_state_done :
		//init_task_state =init_state_done;
		init_done = TRUE ;
	
		break;
		default:
		break;
	}
	
/*
	portA_cfg.GPIO = LCD_PORT ;
	portA_cfg.pins = LCD_RS| LCD_R_W | LCD_DATA | LCD_EN ;
	portA_cfg.dir = OUTPUT ;
	
	DIO_init(&portA_cfg);
	softwareDelayMs(15);
	
	/ * return home mode commands * /
	LCD_sendCommand(DATA_MODE_4_BIT);
	
	/ * send 4 bit mode commands * /
	LCD_sendCommand(DATA_MODE_2_LINE_4_BIT);
	
	/ * cursor state* /
	LCD_sendCommand(CURSOR_ON) ;
	LCD_sendCommand(CLEAR_SCREEN);
	
	softwareDelayMs(25);
*/
	return error_state ;

}

ERROR_STATUS LCD_sendCommand(uint8_t command) {
	
	/*send most first then least */
	uint8_t MSB_command , LSB_command ;
	ERROR_STATUS error_state = E_OK ;
	static uint8_t sendCommand_state = SEND_COMMAND_STATE_1 ;
	static uint8_t counter = ZERO_VALUE ;
		
	counter++;
	MSB_command = GET_NIBBLE_HIGH(command) ;
	LSB_command = GET_NIBBLE_LOW(command) ;
	

	
// 	
// 	/* select whether it is WRITE or READ */
// 	DIO_Write(LCD_PORT,LCD_R_W,LOW);
// 	
// 	/* select whether it is DATA or COMMAND */
// 	DIO_Write(LCD_PORT ,LCD_RS , LOW);
// 		
// 	/* send MSB_command */
// 	
// 	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , MSB_command<<4) ;
// 	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
// 	
// 	softwareDelayMs(1);
// 	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
// 	
// 	/* send LSB_command */
// 	
// 	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , LSB_command<<4) ;
// 	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
// 	softwareDelayMs(1);
// 	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);



 		switch(sendCommand_state){
 			
 			case SEND_COMMAND_STATE_1 :
		
 			/* select whether it is WRITE or READ */
 			DIO_Write(LCD_PORT,LCD_R_W,LOW);
 			
 			/* select whether it is DATA or COMMAND */
 			DIO_Write(LCD_PORT ,LCD_RS , LOW);
 			
 			/* send MSB_command */
			 
 			
 			error_state |= DIO_Write(LCD_PORT ,LCD_DATA , MSB_command<<4) ;
 			error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
 			
 			sendCommand_state = SEND_COMMAND_STATE_2 ;
 			
 			break;
 			
 			case SEND_COMMAND_STATE_2 :
			 	  
 			
 			error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
 			
 			
 			/* send LSB_command */
 			
 			error_state |= DIO_Write(LCD_PORT ,LCD_DATA , LSB_command<<4) ;
 			error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
 			
			 
 			sendCommand_state = SEND_COMMAND_STATE_3 ;
 			
 			break;
 			
 			case SEND_COMMAND_STATE_3 :
 			
 			error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
 			sendCommand_state = SEND_COMMAND_STATE_1 ;
 			break;
 			
 		}
 


	//error_state |= DIO_Write(LCD_PORT ,LCD_DATA , ZERO_VALUE) ;
	
	return error_state ;
}



ERROR_STATUS LCD_displayChar(uint8_t data) {
	
	/*send most first then least */
	uint8_t MSB_data , LSB_data ;
	
	ERROR_STATUS error_state = E_OK ;
	static uint8_t sendChar_state = SEND_CHAR_STATE_1 ;
		
	MSB_data = GET_NIBBLE_HIGH(data) ;
	LSB_data = GET_NIBBLE_LOW(data) ;
	
	switch(sendChar_state){
		
		case SEND_CHAR_STATE_1 :
		
	/* select whether it is DATA or COMMAND */
	DIO_Write(LCD_PORT ,LCD_RS , HIGH);
	/* select whether it is WRITE or READ */
	DIO_Write(LCD_PORT,LCD_R_W,LOW);
	
	/* send MSB_data */
		
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , MSB_data<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	
	//softwareDelayMs(1);
	
	sendChar_state = SEND_CHAR_STATE_2 ;
	
	break;
	
	case SEND_CHAR_STATE_2 :
	
	
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
	
	
	/* send LSB_data */
		
	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , LSB_data<<4) ;
	error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);
	//softwareDelayMs(1);
	
	sendChar_state = SEND_CHAR_STATE_3 ;
	
	break;
	
	case SEND_CHAR_STATE_3 :
	
	error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
	sendChar_state = SEND_CHAR_STATE_1 ;
		break ;
	}
	
 //	error_state |= DIO_Write(LCD_PORT ,LCD_DATA , ZERO_VALUE) ;

	return error_state ;
}


ERROR_STATUS LCD_displayString(uint8_t * str_data ) {
	ERROR_STATUS error_state = E_OK ;

	static uint8_t au8_str_counter = ZERO_VALUE ;
	static uint8_t au8_counter = ZERO_VALUE ;

	if (str_data==NULL )
	{
		return NULL_PTR_ERROR +	LCD_MODEULE_ERROR ;
	}
	

	
 	if(str_data[au8_str_counter]!='\0'){
 		
 		
 		if (au8_counter<3)
 		{
 			
 			LCD_displayChar(str_data[au8_str_counter]);
 			//softwareDelayMs(1);
 			au8_counter++;
 		}
 		else
 		{
 			au8_str_counter++ ;
 			au8_counter = ZERO_VALUE ;
 		}
	 }


// while(str_data[au8_counter]!='\0'){
//  		LCD_displayChar(str_data[au8_counter]);
//  		softwareDelayMs(1);
//  		LCD_displayChar(str_data[au8_counter]);
//  		softwareDelayMs(1);
//  		LCD_displayChar(str_data[au8_counter]);
// 		 au8_counter ++ ;
// 
// }
		if (au8_str_counter == LCD_MAX_WIDTH)
		{
			
			LCD_gotoRowColumn(LCD_SECOND_ROW,ZERO);
			

		}
	//}
// 	else
// 	{
// 		au8_str_counter = ZERO_VALUE ;
// 	}
	return error_state ;
}


ERROR_STATUS LCD_clear() {
	
	ERROR_STATUS error_state = E_OK ;

	LCD_sendCommand(CLEAR_SCREEN);
	return error_state ;
}


ERROR_STATUS LCD_gotoRowColumn( uint8_t row , uint8_t col) {
	ERROR_STATUS error_state = E_OK ;

	uint8_t address = 0 ;
	
	switch(row)
	{
		case 0:
		address = col;
		break;
		case 1:
		address = 0x40 + col;
		break;
		default:
		error_state = INVALID__PARAMETER + LCD_MODEULE_ERROR ;
		break;
		
	}
	LCD_sendCommand ( address | SET_CURSOR_LOCATION);
	return error_state ;
}
