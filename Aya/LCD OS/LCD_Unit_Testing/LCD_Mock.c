/*
 * LCD_Mock.c
 *
 * Created: 3/16/2020 2:05:46 PM
 *  Author: A_ayman
 */


/*
*** Inclusions
*/

#include "LCD_Mock.h"


/*
*** Global Variables
*/

uint8_t gu8_DIO_Init_Return;
uint8_t gu8_DIO_Write_Return;
uint8_t gu8_DIO_Read_Return;
uint8_t gu8_DIO_Toggle_Return;

/* Function Implementation*/

/* this function doesn't do any thing just to compensate the absence of delay library of atmel*/
void _delay_ms(uint8_t u8_Delay_Time)
{
    u8_Delay_Time -= 1;

}
/* this function doesn't do any thing just to compensate the absence of delay library of atmel*/
void _delay_us(uint8_t u8_Delay_Time)
{
    u8_Delay_Time -= 1;

}

ERROR_STATUS DIO_Init (strDIOCfg_t *DIO_info)
{
    return gu8_DIO_Init_Return;
}

ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{
    return gu8_DIO_Write_Return;
}

ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{
    return gu8_DIO_Read_Return;
}
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{
    return gu8_DIO_Toggle_Return;
}
