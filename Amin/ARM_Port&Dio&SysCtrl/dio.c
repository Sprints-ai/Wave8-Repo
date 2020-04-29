#include "../../utils/Bit_Math.h"
#include "../../utils/STD_Types.h"
#include "../../mcal/mcu_hw.h"
#include "dio.h"

STD_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    STD_levelType ret;
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    // read channel
    switch(PortId)
     {
     case Dio_Port_A :
         ret = GET_BIT(PORTA_REG.GPIODATA, ChannelPos);
         break;

     case Dio_Port_B:
         ret = GET_BIT(PORTB_REG.GPIODATA, ChannelPos);
         break;

     case Dio_Port_C:
         ret = GET_BIT(PORTC_REG.GPIODATA, ChannelPos);
         break;

     case Dio_Port_D:
         ret = GET_BIT(PORTD_REG.GPIODATA, ChannelPos);
         break;

     case Dio_Port_E:
         ret = GET_BIT(PORTE_REG.GPIODATA, ChannelPos);
         break;

     case Dio_Port_F:
         ret = GET_BIT(PORTF_REG.GPIODATA, ChannelPos);
         break;

     default:
         break;

     }

    return ret;
}
void Dio_WriteChannel(Dio_ChannelType ChannelId, STD_levelType Level)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    switch(PortId)
    {
    case Dio_Port_A:
        if (Level == STD_high)
        {
            SET_BIT(PORTA_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTA_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_B:
        if (Level == STD_high)
        {
            SET_BIT(PORTB_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTB_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_C:
        if (Level == STD_high)
        {
            SET_BIT(PORTC_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTC_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_D:
        if (Level == STD_high)
        {
            SET_BIT(PORTD_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTD_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_E:
        if (Level == STD_high)
        {
            SET_BIT(PORTE_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTE_REG.GPIODATA, ChannelPos);
        }
        break;

    case Dio_Port_F:
        if (Level == STD_high)
        {
            SET_BIT(PORTF_REG.GPIODATA, ChannelPos);
        }
        else
        {
            CLR_BIT(PORTF_REG.GPIODATA, ChannelPos);
        }
        break;

    default:
        break;

    }

}

uint8 Dio_ReadPort(Dio_PortType PortId )
{
    uint8 ret;

    switch(PortId)
     {
     case Dio_Port_A:
         ret = (uint8)(PORTA_REG.GPIODATA);
         break;

     case Dio_Port_B:
         ret = (uint8)(PORTB_REG.GPIODATA);
         break;

     case Dio_Port_C:
         ret = (uint8)(PORTC_REG.GPIODATA);
         break;

     case Dio_Port_D:
         ret = (uint8)(PORTD_REG.GPIODATA);
         break;

     case Dio_Port_E:
         ret = (uint8)(PORTE_REG.GPIODATA);
         break;

     case Dio_Port_F:
         ret = (uint8)(PORTF_REG.GPIODATA);
         break;

     default:
         break;
     }

    return ret;
}

void Dio_WritePort( Dio_PortType PortId, uint8 value)
{
    switch(PortId)
     {
     case Dio_Port_A:
         PORTA_REG.GPIODATA = value;
         break;

     case Dio_Port_B:
         PORTB_REG.GPIODATA = value;
         break;

     case Dio_Port_C:
         PORTC_REG.GPIODATA = value;
         break;

     case Dio_Port_D:
         PORTD_REG.GPIODATA = value;
         break;

     case Dio_Port_E:
         PORTE_REG.GPIODATA = value;
         break;

     case Dio_Port_F:
         PORTF_REG.GPIODATA = value;
         break;

     default:
         break;
     }
}

void Dio_FlipChannel( Dio_ChannelType ChannelId)
{
    Dio_PortType PortId = ChannelId / 8;
    Dio_ChannelType ChannelPos = ChannelId % 8;

    switch(PortId)
        {
        case Dio_Port_A:

            TOGGLE_BIT(PORTA_REG.GPIODATA, ChannelPos);
        break;

        case Dio_Port_B:

            TOGGLE_BIT(PORTB_REG.GPIODATA, ChannelPos);
        break;

        case Dio_Port_C:

            TOGGLE_BIT(PORTC_REG.GPIODATA, ChannelPos);
        break;

        case Dio_Port_D:

            TOGGLE_BIT(PORTD_REG.GPIODATA, ChannelPos);
        break;

        case Dio_Port_E:

            TOGGLE_BIT(PORTE_REG.GPIODATA, ChannelPos);
        break;

        case Dio_Port_F:

            TOGGLE_BIT(PORTF_REG.GPIODATA, ChannelPos);
        break;

        default:
            break;
        }
}

void Dio_FlipPort(Dio_PortType PortId)
{

    switch(PortId)
        {
        case Dio_Port_A:
            PORTA_REG.GPIODATA ^= 0xff;
        break;

        case Dio_Port_B:
            PORTB_REG.GPIODATA ^= 0xff;
        break;

        case Dio_Port_C:
            PORTC_REG.GPIODATA ^= 0xff;
        break;

        case Dio_Port_D:
            PORTD_REG.GPIODATA ^= 0xff;
        break;

        case Dio_Port_E:
            PORTE_REG.GPIODATA ^= 0xff;
        break;

        case Dio_Port_F:
            PORTF_REG.GPIODATA ^= 0xff;
        break;

        default:
            break;

        }
}

