/*
*	File name: DIO.h
*	Author : Tamoo7, Ahmed, Metwally
*	version: 1.3
*
*/

#ifndef	DIO_H
#define DIO_H

#include "../Infrastructure/std_types.h"
#include "../Infrastructure/registers.h"

/************************************************************************/
/*						PINS/BITS defines                               */
/************************************************************************/

#define PIN0	0x01
#define PIN1	0x02
#define PIN2	0x04
#define PIN3	0x08
#define PIN4	0x10
#define PIN5	0x20
#define PIN6	0x40
#define PIN7	0x80



#define UPPER_NIBBLE	0xF0
#define LOWER_NIBBLE	0x0F
#define FULL_PORT		0xFF

#define GPIOA			0
#define GPIOB			1
#define GPIOC			2
#define GPIOD			3

#define OUTPUT			0xFF
#define INPUT			0x00

/************************************************************************/
/*						Typedefs defines                               	*/
/************************************************************************/
typedef struct DIO_Cfg_s
{
	uint8_t GPIO;
	uint8_t pins;
	uint8_t dir;
}DIO_Cfg_s;

/**
 * Description: set the whole port , a nibble ,a group of random pins or a single pin's direction 
 * @param DIO_Info: Pointer to the pre_configured struct
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info);


/**
 * Description: set the value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 * @param value: set the value and takes the following values
 * 				- 0x00 -> LOW
 * 				- 0xFF -> HIGH
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value);

/**
 * Description: reads the mask value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 * @param data: output parameter : returns the mask value
 * 	
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data);

/**
 * Description: toggles the value of a whole port , a nibble , a group of random pins or a single pin
 * @param GPIO: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				a single value of the following values or a group of them ORed together:
 * 				- 0x01-> PIN0
 * 				- 0x02-> PIN1
 * 				- 0x04-> PIN2
 * 				- 0x08-> PIN3
 * 				- 0x10-> PIN4
 * 				- 0x20-> PIN5
 * 				- 0x40-> PIN6
 * 				- 0x80-> PIN7
 *
 * @return function status :
 *				- 0 -> E_NOK
 *				- 1 -> E_OK
 */
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins);



#endif