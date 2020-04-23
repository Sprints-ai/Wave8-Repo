#include "LCD.h"

/*
 * Description : A Function to Initialize the LCD Driver.
 */
ERROR_STATUS LCD_init(void)
{
    ERROR_STATUS retval=E_OK;
	LCD_CTRL_PORT_DIR |= (1 << E) | (1 << RS) | (1 << RW);
	switch(DATA_BITS_MODE){
case 8:
    LCD_DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
	 retval=E_OK;
    break;
case 4:
    #ifdef UPPER_PORT_BITS
	LCD_DATA_PORT_DIR |= 0xF0;
#else
	LCD_DATA_PORT_DIR |= 0x0F;
#endif
	retval&=LCD_sendCommand(FOUR_BITS_DATA_MODE_ACTIVATED);
	retval&=LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
retval=E_OK;
    break;
default:
    retval=E_NOK;
break;
	}
/*#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT_DIR |= 0xF0;
#else
	LCD_DATA_PORT_DIR |= 0x0F;
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE_ACTIVATED);
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
#endif*/
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
	return retval;
}

/*
 * Description : A Function to send a Command.
 */
ERROR_STATUS LCD_sendCommand(uint8 command)
{
    ERROR_STATUS retval=E_OK;
	CLEAR_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	//_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
	switch(DATA_BITS_MODE){
case 8:
    LCD_DATA_PORT = command;
    retval=E_OK;
    break;
case 4:
    #ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif
retval=E_OK;
    break;
default:
    retval=E_NOK;
    break;
	}
/*#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command;
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif*/
	//_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif

	//_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	switch(command){
	case CLEAR_COMMAND:
	retval&=E_OK;
	break;
	case TWO_LINE_LCD_EIGHT_BIT_MODE:
	retval&=E_OK;
	break;
 	case FOUR_BITS_DATA_MODE_ACTIVATED:
	retval&=E_OK;
	break;
 	case TWO_LINE_LCD_FOUR_BIT_MODE:
	retval&=E_OK;
	break;
	case CURSOR_OFF:
	retval&=E_OK;
	break;
 	case  CURSOR_ON:
	retval&=E_OK;
	break;
    case  SET_CURSOR_LOCATION:
	retval&=E_OK;
	break;
    default:
        retval&=E_NOK;
        break;
	}
	//_delay_us(10);
	return retval;
}

/*
 * Description : A Function to write data (display character).
 */
ERROR_STATUS LCD_displayCharacter(uint8 data)
{
    ERROR_STATUS retval=E_OK;
	SET_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	//_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
	switch(DATA_BITS_MODE){
    case 8:
        LCD_DATA_PORT = data;
        retval=E_OK;
        break;
    case 4:
        #ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif
retval=E_OK;
        break;
    default:
        retval=E_NOK;
        break;
	}
/*#if(DATA_BITS_MODE == 8)
	LCD_DATA_PORT = data;
#elif(DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif*/
	//_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
	SET_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
#ifdef UPPER_PORT_BITS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif
	//_delay_us(10);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	//_delay_us(10);
	return retval;
}

/*
 * Description : A Function to display a string.
 */
ERROR_STATUS LCD_displayString(const sint8* str)
{
    ERROR_STATUS retval=E_OK;
    if(str!=NULL){
	uint8 index=0;
	while((str[index]) != '\0')
	{
		LCD_displayCharacter(str[index]);
		index++;
	}
	retval=NULL_PTR_ERROR;
    }
    return retval;
}

/*
 * Description : A Function to move the cursor to an exact spot.
 */
ERROR_STATUS LCD_goToRowColumn(uint8 row, uint8 col)
{
    ERROR_STATUS retval=E_OK;
	uint8 address;
	switch(row)
	{
	case 0 :
		address = col;
		break;
	case 1 :
		address = col + 0x40;
		break;
	case 2 :
		address = col + 0x10;
		break;
	case 3 :
		address = col + 0x50;
		break;
    default:
        retval=E_NOK;
        break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
	return retval;
}

/*
 * Description : A Function to move the cursor to an exact spot and display a string at the spot.
 */
ERROR_STATUS LCD_displayStringRowColumn(uint8 row, uint8 col, const sint8* str)
{
    ERROR_STATUS retval=NULL_PTR_ERROR;
    if(str!=NULL){
	LCD_goToRowColumn(row, col);
	LCD_displayString(str);
	retval=E_OK;
	}
	retval&=LCD_goToRowColumn(row,col);
	return retval;
}

/*
 * Description : A Function to display an integer number.
 */
ERROR_STATUS LCD_displayInteger(uint8 num)
{
    ERROR_STATUS retval=E_OK;
	uint8 buff[12];
	uint8* ptr = &buff[11]; 				// char *ptr = (buff + 11); [] is another way of describing the dereferencing operator
	char N_flag = 0;
	if(num < 0)
	{
		N_flag = 1;
		num = -num;
	}
	*ptr = '\0';
	do{
	    *--ptr = (num % 10) + 48;
	    num /= 10;
	}while(num != 0);
	if(N_flag)
		*--ptr = '-';
	retval&=LCD_displayString(ptr);
	return retval;
}

/*
 * Description : A Function to Clear the LCD Screen.
 */
ERROR_STATUS LCD_clearScreen(void)
{
    ERROR_STATUS retval=E_OK;
	retval&=LCD_sendCommand(CLEAR_COMMAND); //clear display
	return retval;
}
