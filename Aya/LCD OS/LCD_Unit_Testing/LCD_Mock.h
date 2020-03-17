/*
 * LCD_Mock.h
 *
 * Created: 3/16/2020 2:05:46 PM
 *  Author: A_ayman
 */

/*
*** Inclusions
*/
#ifndef LCD_MOCK_H_INCLUDED
#define LCD_MOCK_H_INCLUDED
#include "SL/Utilis/std_types.h"
#include "SL/Utilis/module_retval.h"
#include "MCAL/DIO/DIO.h"


extern uint8_t gu8_DIO_Init_Return;
extern uint8_t gu8_DIO_Write_Return;
extern uint8_t gu8_DIO_Read_Return;
extern uint8_t gu8_DIO_Toggle_Return;

/* this function is used to compensate the absence of delay library of atmel */
extern void _delay_ms(uint8_t u8_Delay_Time);
/* this function is used to compensate the absence of delay library of atmel */
extern void _delay_us(uint8_t u8_Delay_Time);
extern ERROR_STATUS DIO_Init (strDIOCfg_t *DIO_info);
extern ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value);
extern ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data);
extern ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins);
#endif // LCD_MOCK_H_INCLUDED
