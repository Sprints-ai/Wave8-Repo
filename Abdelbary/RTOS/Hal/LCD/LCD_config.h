#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "util/delay.h"
#include "../../Mcal/DIO/gpio.h"
#include "../../Utilities/regesters.h"
#include "../../Utilities/common_macros.h"
#include "../../Utilities/std_types.h"/*
 * LCD pins
 */
#define RS						PA1
#define RW 						PA2
#define E  						PA3
#define LCD_CTRL_PORT_DIR 		PORTA_DIR
#define LCD_CTRL_PORT 			PORTA_DATA
#define LCD_DATA_PORT_DIR 		PORTA_DIR
#define LCD_DATA_PORT 			PORTA_DATA

/*
 * LCD Commands
 */
#define CLEAR_COMMAND					0x01
#define TWO_LINE_LCD_EIGHT_BIT_MODE 	0x38
#define FOUR_BITS_DATA_MODE_ACTIVATED 	0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 		0x28
#define CURSOR_OFF 						0x0C
#define CURSOR_ON 						0x0E
#define SET_CURSOR_LOCATION 			0x80



/*
 * Macros for operating mode
 */
#define DATA_BITS_MODE 4
#if(DATA_BITS_MODE == 4)
#define UPPER_PORT_BITS
#endif

#endif /* LCD_CONFIG_H_ */