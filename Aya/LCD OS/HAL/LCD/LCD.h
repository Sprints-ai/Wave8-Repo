/*
 * LCD.h
 *
 * Created: 3/13/2020 2:05:46 PM
 *  Author: A_ayman
 */ 


#ifndef LCD_H_
#define LCD_H_


/*
*** Inclusions
*/
#include <util/delay.h>
#include "../../MCAL/DIO/registers.h"
#include "../../SL/Utilis/std_types.h"
#include "../../SL/Utilis/module_retval.h"
#include "../../SL/ERROR_HANDLING/ERROR-STORE.h"
#include "../../SL/ERROR_HANDLING/Errors.h"
#include "LCD_cfg.h"
#include "../../MCAL/DIO/DIO.h"

/*
*** Local Macros
*/
#define F_CPU 16000000


/*
*** LCD Commands
*/
#define CURSOR_OFF           0x0c     /*Turn cursor off*/
#define CLEAR_LCD            0x01    /*start with clear display*/
#define FOUR_BIT_MODE        0x32
#define eight_bit_InputMode  0x38

/*
*** Function Prototypes
*/
/*
*** This Function Is Used to initialize LCD which initialize DIO
*** input : none
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_Init ();

/*
*** This Function Is Used to clear LCD 
*** input : none
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_clear ();

/*
*** This Function Is used to send commands
*** input : uint8_t 
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_sendCommand (uint8_t);

/*
*** This Function Is used to display single character 
*** input : uint8_t
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_displayChar (uint8_t );

/*
*** This Function Is used to display a whole string
*** input : pointer to character 
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_displayString (uint8_t*) ;

/*
*** This Function Is used to force cursor to move to a specific position
*** input : uint8_t (Row position),  uint8_t (col position),
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_displayStringRowColumn  (uint8_t,uint8_t) ;

/*
*** This Function Is used to display single character
*** input : uint8_t
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_displayChar_None_OS(uint8_t );

/*
*** This Function Is used to send commands
*** input : uint8_t
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_sendCommand_None_OS(uint8_t);

/*
*** This Function Is used to display a whole string
*** input : pointer to character
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_displayString_None_OS (uint8_t*) ;

/*
*** This Function Is Used to initialize LCD which initialize DIO 8_bit mode 
*** input : none
*** OUtput: Error Status
*/
extern ERROR_STATUS LCD_init_8Bit_Mode();




#endif /* LCD_H_ */