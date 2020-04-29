#include "../../utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include "../../config/port_cfg.h"
#include "../mcu_hw.h"
#include "port_types.h"
#include "port.h"

#define MAX_NUM_OF_PORT_CHANNELS       8

extern Port_CfgType PortCfgArr[];

void PORT_init(void)
{
    uint8 i;
    Port_IdType PortId;
    Port_ChIdType ChId;

    volatile PORT_RegType* PORT_Addr;

    for (i = 0; i < PORT_NUM_OF_ACTIVATED_CH; ++i)
    {
        PortId = i / MAX_NUM_OF_PORT_CHANNELS ;
        ChId = i % MAX_NUM_OF_PORT_CHANNELS ;

        switch (PortId)
        {
        case Port_Id_A:
            PORT_Addr = &PORTA_REG;
            break;
        case Port_Id_B:
            PORT_Addr = &PORTB_REG;
            break;
        case Port_Id_C:
            PORT_Addr = &PORTC_REG;
            break;
        case Port_Id_D:
            PORT_Addr = &PORTD_REG;
            break;
        case Port_Id_E:
            PORT_Addr = &PORTE_REG;
            break;
        case Port_Id_F:
            PORT_Addr = &PORTF_REG;
            break;
        }

        // set channel direction
        if (PortCfgArr[i].Dir == port_Dir_Input )
        {
            CLR_BIT(PORT_Addr -> GPIODIR, ChId);
        }
        else
        {
            SET_BIT(PORT_Addr -> GPIODIR, ChId);
        }

        // set channel mode
        if (PortCfgArr[i].Mode == Port_Mode_DIO)
        {
            CLR_BIT(PORT_Addr -> GPIOAFSEL, ChId);
        }
        // set interrupt
        if(PortCfgArr[i].Interrupt == Port_IntDisable)
        {
            CLR_BIT( PORT_Addr-> GPIOIM , ChId);
        }
        else
        {
            SET_BIT(PORT_Addr-> GPIOIM , ChId);
        }

        // change the attachment for  configuration
        switch(PortCfgArr[i].AttachedRes)
        {
        case Port_InternalAttach_NA:
            // clear the rest of the pin.
             break;
        case Port_InternalAttach_PullUpRes:
            SET_BIT(PORT_Addr-> GPIOPUR, ChId);
            break;
        case Port_InternalAttach_PullDownRes:
            SET_BIT(PORT_Addr-> GPIOPDR, ChId);
            break;
        case Port_InternalAttach_OpenDrain:
            SET_BIT(PORT_Addr-> GPIOODR, ChId);
            break;
        default:
            break;
        }


        // change the current strength
        switch(PortCfgArr[i].CurrentDrive)
        {
        case Port_CurrDrive_2mA:
            // do nothing
            break;
        case Port_CurrDrive_4mA:
            SET_BIT(PORT_Addr-> GPIODR4R, ChId);
            break;
        case Port_CurrDrive_8mA:
            SET_BIT(PORT_Addr-> GPIODR8R, ChId);
            break;
        default:
            break;
        }

        /*Check if analog functionality is required*/
        if(PortCfgArr[i].Mode != Port_Mode_AIN )
        {
            SET_BIT(PORT_Addr-> GPIODEN, ChId);
            // ADC disabled by default.
        }
        else
        {
            // enable ADC
            SET_BIT(PORT_Addr-> GPIOADCCTL, ChId);
        }
    }
}