/*
 * Dio.h
 *
 * Created: 4/8/2020 6:29:24 PM
 *  Author: Khaled
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "Common_Macros.h"
#include "std_types.h"


typedef uint8_t STD_levelType;
#define STD_LOW              0
#define STD_HIGE             1


typedef uint8_t Dio_ChannelType;
#define	PORTDRIVER_CHANNEL_A0                              0
#define	PORTDRIVER_CHANNEL_A1                              1
#define	PORTDRIVER_CHANNEL_A2                              2
#define	PORTDRIVER_CHANNEL_A3                              3
#define	PORTDRIVER_CHANNEL_A4                              4
#define	PORTDRIVER_CHANNEL_A5                              5
#define	PORTDRIVER_CHANNEL_A6                              6
#define	PORTDRIVER_CHANNEL_A7                              7

#define	PORTDRIVER_CHANNEL_B0                              8
#define	PORTDRIVER_CHANNEL_B1                              9
#define	PORTDRIVER_CHANNEL_B2                              10
#define	PORTDRIVER_CHANNEL_B3                              11
#define	PORTDRIVER_CHANNEL_B4                              12
#define	PORTDRIVER_CHANNEL_B5                              13
#define	PORTDRIVER_CHANNEL_B6                              14
#define	PORTDRIVER_CHANNEL_B7                              15

#define	PORTDRIVER_CHANNEL_C0                              16
#define	PORTDRIVER_CHANNEL_C1                              17
#define	PORTDRIVER_CHANNEL_C2                              18
#define	PORTDRIVER_CHANNEL_C3                              19
#define	PORTDRIVER_CHANNEL_C4                              20
#define	PORTDRIVER_CHANNEL_C5                              21
#define	PORTDRIVER_CHANNEL_C6                              22
#define	PORTDRIVER_CHANNEL_C7                              23

#define	PORTDRIVER_CHANNEL_D0                              24
#define	PORTDRIVER_CHANNEL_D1                              25
#define	PORTDRIVER_CHANNEL_D2                              26
#define	PORTDRIVER_CHANNEL_D3                              27
#define	PORTDRIVER_CHANNEL_D4                              28
#define	PORTDRIVER_CHANNEL_D5                              29
#define	PORTDRIVER_CHANNEL_D6                              30
#define	PORTDRIVER_CHANNEL_D7                              31

#define	PORTDRIVER_CHANNEL_E0                              32
#define	PORTDRIVER_CHANNEL_E1                              33
#define	PORTDRIVER_CHANNEL_E2                              34
#define	PORTDRIVER_CHANNEL_E3                              35
#define	PORTDRIVER_CHANNEL_E4                              36
#define	PORTDRIVER_CHANNEL_E5                              37
#define	PORTDRIVER_CHANNEL_E6_RESERVED                     38
#define	PORTDRIVER_CHANNEL_E7_RESERVED                     39

#define	PORTDRIVER_CHANNEL_F0                              40
#define	PORTDRIVER_CHANNEL_F1                              41
#define	PORTDRIVER_CHANNEL_F2                              42
#define	PORTDRIVER_CHANNEL_F3                              43
#define	PORTDRIVER_CHANNEL_F4                              44
#define	PORTDRIVER_CHANNEL_F5_RESERVED                     45
#define	PORTDRIVER_CHANNEL_F6_RESERVED                     46
#define	PORTDRIVER_CHANNEL_F7_RESERVED	                   47

typedef uint8_t Dio_PortType;
#define Dio_Port_A			0
#define Dio_Port_B			1
#define Dio_Port_C			2
#define Dio_Port_D			3
#define Dio_Port_E          4
#define Dio_Port_F          5




#define OUTPUT			0xFF
#define INPUT			0x00



/*
*Input: GPIO -> to get PORT name
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
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
void DIO_Write (Dio_ChannelType DIO_Channel, STD_levelType Level);

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be read from.
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
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
void DIO_Read (Dio_ChannelType DIO_Channel, STD_levelType *Level);

/*
*Input: GPIO -> to get PORT name
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
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
void DIO_Toggle (Dio_ChannelType DIO_Channel);



/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		value 	-> The desired value
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
void DIO_Write_Port (Dio_PortType DIO_Channel, uint8_t Value);


void DIO_Read_Port (Dio_PortType DIO_Channel, uint8_t* Value);



#endif /* DIO_H_ */
