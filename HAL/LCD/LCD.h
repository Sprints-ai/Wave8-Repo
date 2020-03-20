/*
 * LCD.h
 *
 * Created: 14/03/2020 06:51:20 م
 *  Author: TOSHIBA
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../Infrastructure/std_types.h"
#include "LCD_Cfg.h"

#define  LCD_INIT_DONE				0xFF
#define	 LCD_WRITE_STRING_DONE		0xFF
#define	 WRITE_COMMAND_DONE			0xFF
#define LCD_CHAR_WRITE_DONE 0xff
//DEFINE FOR ERROR

u8_ERROR_STATUS_t LCD_init (void);

u8_ERROR_STATUS_t LCD_WriteCommand (const uint8_t u8_Command);

u8_ERROR_STATUS_t LCD_WriteChar (const uint8_t u8_data);

u8_ERROR_STATUS_t LCD_WriteString (const uint8_t* pu8_data);

//u8_ERROR_STATUS_t LCD_displayStringRowColumn (const uint8_t* u8_data ,const uint8_t u8_RowNum,const uint8_t u8_ColNum);

u8_ERROR_STATUS_t LCD_clear (void);

//u8_ERROR_STATUS_t LCD_gotoRowColumn (const uint8_t u8_RowNum,const uint8_t u8_ColNum);




#endif /* LCD_H_ */