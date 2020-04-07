/*
* LCD.c
*
* Created: 3/15/2020 11:49:48 AM
*  Author: MENNA
*/
#include "LCD.h"
#include "LCD_cfg.h"


#include "../MCAL/DIO.h"
#include "../MCAL/registers.h"
#include <stdio.h>
#include <stdlib.h>


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
uint8_t sendStr_done = FALSE ;


ERROR_STATUS LCD_init(void){

	ERROR_STATUS error_state = E_OK ;
	DIO_Cfg_s portA_cfg ;
	static uint8_t au8_counter = ZERO_VALUE;

	static uint8_t init_task_state = init_state_1 ;

	au8_counter++ ;

	switch(init_task_state){

		case init_state_1 :

		portA_cfg.GPIO = LCD_PORT ;
		portA_cfg.pins = LCD_RS| LCD_R_W | LCD_DATA | LCD_EN ;
		portA_cfg.dir = OUTPUT ;

		DIO_init(&portA_cfg);

		init_task_state = init_state_send_1;
		au8_counter = ZERO_VALUE ;
		break;

		case init_state_send_1 :

		/* send return home command */
		LCD_sendCommand(DATA_MODE_4_BIT);
		if (au8_counter == THREE)
		{
			init_task_state =init_state_send_2;
			au8_counter = ZERO_VALUE ;
		}
		break;
		case init_state_send_2 :

		/* send 4 bit mode commands */
		LCD_sendCommand(DATA_MODE_2_LINE_4_BIT);
		if (au8_counter == THREE )
		{
			init_task_state =init_state_send_3;
			au8_counter = ZERO_VALUE ;
		}
		break;
		
		case init_state_send_3 :

		/* cursor state*/
		LCD_sendCommand(CURSOR_ON) ;
		if (au8_counter == THREE)
		{
			init_task_state =init_state_send_4;
			au8_counter = ZERO_VALUE ;
		}
		break;
		
		case init_state_send_4 :

		/* cursor state*/
		LCD_sendCommand(CLEAR_SCREEN);
		if (au8_counter == THREE)
		{
			init_task_state =init_state_done;
			au8_counter = ZERO_VALUE ;
		}

		break;

		case init_state_done :
		init_done = TRUE ;

		break;
		default:
		break;
	}

	return error_state ;

}

ERROR_STATUS LCD_sendCommand(uint8_t command) {

	/*send most first then least */
	uint8_t au8_MSB_command , au8_LSB_command ;
	ERROR_STATUS error_state = E_OK ;
	static uint8_t sendCommand_state = SEND_COMMAND_STATE_1 ;
	static uint8_t au8_counter = ZERO_VALUE ;

	au8_counter++;
	au8_MSB_command = GET_NIBBLE_HIGH(command) ;
	au8_LSB_command = GET_NIBBLE_LOW(command) ;

	switch(sendCommand_state){

		case SEND_COMMAND_STATE_1 :

		/* select whether it is WRITE or READ */
		DIO_Write(LCD_PORT,LCD_R_W,LOW);

		/* select whether it is DATA or COMMAND */
		DIO_Write(LCD_PORT ,LCD_RS , LOW);

		/* send MSB_command */

		error_state |= DIO_Write(LCD_PORT ,LCD_DATA , au8_MSB_command << FOUR) ;
		error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);

		sendCommand_state = SEND_COMMAND_STATE_2 ;

		break;

		case SEND_COMMAND_STATE_2 :

		error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);

		/* send LSB_command */

		error_state |= DIO_Write(LCD_PORT ,LCD_DATA , au8_LSB_command << FOUR) ;
		error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);

		sendCommand_state = SEND_COMMAND_STATE_3 ;

		break;

		case SEND_COMMAND_STATE_3 :

		error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
		sendCommand_state = SEND_COMMAND_STATE_1 ;
		break;

	}


	return error_state ;
}



ERROR_STATUS LCD_displayChar(uint8_t data) {

	/*send most first then least */
	uint8_t au8_MSB_data , au8_LSB_data ;

	ERROR_STATUS error_state = E_OK ;
	static uint8_t sendChar_state = SEND_CHAR_STATE_1 ;

	au8_MSB_data = GET_NIBBLE_HIGH(data) ;
	au8_LSB_data = GET_NIBBLE_LOW(data) ;

	switch(sendChar_state){

		case SEND_CHAR_STATE_1 :

		/* select whether it is DATA or COMMAND */
		DIO_Write(LCD_PORT ,LCD_RS , HIGH);
		/* select whether it is WRITE or READ */
		DIO_Write(LCD_PORT,LCD_R_W,LOW);

		/* send MSB_data */

		error_state |= DIO_Write(LCD_PORT ,LCD_DATA , au8_MSB_data << FOUR ) ;
		error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);


		sendChar_state = SEND_CHAR_STATE_2 ;

		break;

		case SEND_CHAR_STATE_2 :

		error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);

		/* send LSB_data */

		error_state |= DIO_Write(LCD_PORT ,LCD_DATA , au8_LSB_data << FOUR ) ;
		error_state |= DIO_Write(LCD_PORT , LCD_EN , HIGH);

		sendChar_state = SEND_CHAR_STATE_3 ;

		break;

		case SEND_CHAR_STATE_3 :

		error_state |= DIO_Write(LCD_PORT , LCD_EN , LOW);
		sendChar_state = SEND_CHAR_STATE_1 ;
		break ;
	}

	return error_state ;
}



ERROR_STATUS LCD_displayString(sint8_t * str_data ) {
	ERROR_STATUS au8_error_state = E_OK ;

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
			au8_counter++;
		}
		else
		{
			au8_str_counter++ ;
			au8_counter = ZERO_VALUE ;
		}
		}else{
		sendStr_done = TRUE ;
		au8_str_counter=ZERO_VALUE ;
		
		LCD_sendCommand(CLEAR_SCREEN);
		LCD_sendCommand(CLEAR_SCREEN);
		LCD_sendCommand(CLEAR_SCREEN);

	}

	if (au8_str_counter == LCD_MAX_WIDTH)
	{

		LCD_gotoRowColumn(LCD_SECOND_ROW,ZERO);

	}

	return au8_error_state ;
}

ERROR_STATUS LCD_clear() {

	ERROR_STATUS error_state = E_OK ;

	LCD_sendCommand(CLEAR_SCREEN);
	return error_state ;
}

ERROR_STATUS LCD_gotoRowColumn( uint8_t row , uint8_t col) {
	ERROR_STATUS error_state = E_OK ;

	uint8_t au8_address = ZERO_VALUE ;

	switch(row)
	{
		case 0:
		au8_address = col;
		break;
		case 1:
		au8_address = 0x40 + col;
		break;
		default:
		error_state = INVALID__PARAMETER + LCD_MODEULE_ERROR ;
		break;

	}
	LCD_sendCommand ( au8_address | SET_CURSOR_LOCATION);
	return error_state ;
}

ERROR_STATUS LCD_displayInteger(uint16_t IntegerNumber)
{
	ERROR_STATUS as8_Ret ;
	char buff[16];
	itoa(IntegerNumber,buff,10);  /* 10 for decimal */
	LCD_displayString(buff);

	as8_Ret = LCD_displayString(buff);


	return as8_Ret;
}
