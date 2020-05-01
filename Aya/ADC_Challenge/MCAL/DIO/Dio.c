/*
 * Dio.c
 *
 * Created: 4/8/2020 6:31:39 PM
 *  Author: Khaled
 */ 
#include "Dio.h"


#define NUM_OF_CHANNELS                                     8
#define NUM_OF_PORTS                                        6

#define TEMP_VALUE_INITIAL_VALUE                            0

#define DIO_PORTA_DATA_REG   ((reg_type32_t)0x400043FC)
#define DIO_PORTB_DATA_REG   ((reg_type32_t)0x400053FC)
#define DIO_PORTC_DATA_REG   ((reg_type32_t)0x400063FC)
#define DIO_PORTD_DATA_REG   ((reg_type32_t)0x400073FC)
#define DIO_PORTE_DATA_REG   ((reg_type32_t)0x400243FC)
#define DIO_PORTF_DATA_REG   ((reg_type32_t)0x400253FC)

 static volatile uint32_t* U32ARR_DataAddrArr[NUM_OF_PORTS] = { DIO_PORTA_DATA_REG,
                                                                DIO_PORTB_DATA_REG,
                                                                DIO_PORTC_DATA_REG,
                                                                DIO_PORTD_DATA_REG,
                                                                DIO_PORTE_DATA_REG,
                                                                DIO_PORTF_DATA_REG };


void DIO_Write (Dio_ChannelType DIO_Channel, STD_levelType Level)
{
    uint32_t  au32_TempValue    = TEMP_VALUE_INITIAL_VALUE;
    uint8_t   au8_PortNum       = NUM_OF_PORTS;
    uint8_t   au8_ChannelOffset = NUM_OF_CHANNELS;

    au8_PortNum = DIO_Channel / NUM_OF_CHANNELS;  /*determine the channel PORT*/
    
    au8_ChannelOffset = DIO_Channel % NUM_OF_CHANNELS; /*determine the channel pin*/

    au32_TempValue = ( 1 << au8_ChannelOffset ); /*calculate PIN mask*/

    if (STD_LOW == Level)
    {
        *U32ARR_DataAddrArr[au8_PortNum] &= ~au32_TempValue; /*Clear desired bit*/ 
    } 
    else if (STD_HIGH == Level)
    {
        *U32ARR_DataAddrArr[au8_PortNum] |= au32_TempValue; /*set desired bit*/ 
    }
    else
    {
        //return error
    }
}


void DIO_Read (Dio_ChannelType DIO_Channel, STD_levelType *Level)
{
    uint32_t  au32_TempValue    = TEMP_VALUE_INITIAL_VALUE;
    uint8_t   au8_PortNum       = NUM_OF_PORTS;
    uint8_t   au8_ChannelOffset = NUM_OF_CHANNELS;
    
    au8_PortNum = DIO_Channel / NUM_OF_CHANNELS;  /*determine the channel PORT*/
    
    au8_ChannelOffset = DIO_Channel % NUM_OF_CHANNELS; /*determine the channel pin*/
    
    au32_TempValue = ( 1 << au8_ChannelOffset ); /*calculate PIN mask*/

    au32_TempValue &= *U32ARR_DataAddrArr[au8_PortNum]; /*git pin value*/

    *Level =  (au32_TempValue >> au8_ChannelOffset); /*return pin level*/
}


void DIO_Toggle (Dio_ChannelType DIO_Channel)
{
    uint32_t  au32_TempValue    = TEMP_VALUE_INITIAL_VALUE;
    uint8_t   au8_PortNum       = NUM_OF_PORTS;
    uint8_t   au8_ChannelOffset = NUM_OF_CHANNELS;
    
    au8_PortNum = DIO_Channel / NUM_OF_CHANNELS;  /*determine the channel PORT*/
    
    au8_ChannelOffset = DIO_Channel % NUM_OF_CHANNELS; /*determine the channel pin*/
    
    au32_TempValue = ( 1 << au8_ChannelOffset ); /*calculate PIN mask*/

    *U32ARR_DataAddrArr[au8_PortNum] ^= au32_TempValue; /*toggle desired bit*/
}


void DIO_Write_Port (Dio_PortType DIO_Channel, uint8_t Value)
{
    *U32ARR_DataAddrArr[DIO_Channel] = Value; /*store the value in the data register*/
}

void DIO_Read_Port (Dio_PortType DIO_Channel, uint8_t* Value)
{
    *Value = *U32ARR_DataAddrArr[DIO_Channel]; /*return data register value7*/
}
