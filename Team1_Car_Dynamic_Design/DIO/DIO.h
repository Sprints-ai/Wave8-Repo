/*
*	File name: DIO.h
*	Author : Ahmed Ashraf
*	version: 1.0
*
*/

#ifndef	__DIO_H__
#define __DIO_H__

/************************************************************************/
/*						PINS/BITS defines                               */
/************************************************************************/

#define PIN0	       (0x01)
#define PIN1	       (0x02)
#define PIN2		   (0x04)
#define PIN3		   (0x08)
#define PIN4		   (0x10)
#define PIN5		   (0x20)
#define PIN6		   (0x40)
#define PIN7		   (0x80)

#define UPPER_NIBBLE   (0xF0)
#define LOWER_NIBBLE   (0x0F)
#define FULL_PORT	   (0xFF)

#define GPIOA		   (0)
#define GPIOB		   (1)
#define GPIOC		   (2)
#define GPIOD		   (3)

#define OUTPUT		   (0xFF)
#define INPUT		   (0x00)

#define HIGH		   (1)
#define LOW			   (0)


/************************************************************************/
/*						General macros                                  */
/************************************************************************/

#define E_OK		   (1)
#define E_NOK		   (-1)

/************************************************************************/
/*						User typedef defines                          	*/
/************************************************************************/

typedef sint8_t ERROR_STATUS;

/************************************************************************/
/*                           DIO functions prototypes                   */
/************************************************************************/
/*
*Input: port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*	    status -> Sets the specified pin to output or input.
*Output: N/A
*In/Out: N/A
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (uint8_t port, uint8_t pins, uint8_t status);


/*
*Input: port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: N/A
*In/Out: N/A
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t port, uint8_t pins, uint8_t value);

/*
*Input: port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*Output: 
*		data -> the acquired pin data whether it was high or low
*In/Out: N/A
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8_t port,uint8_t pin, uint8_t *data);

/*
*Input: port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: N/A
*In/Out: N/A
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t port, uint8_t pins);

#endif /*__DIO_H__*/