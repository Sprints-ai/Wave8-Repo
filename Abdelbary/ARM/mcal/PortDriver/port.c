#define MAX_NUM_OF_CH_IN_PORT       8
#define MAX_NUM_OF_PORTS            6

#include "utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include "../../config/port_cfg.h"
#include "../mcu_hw.h"
#include "port_types.h"
#include "port.h"

extern Port_CfgType PortCfgArr[];
static volatile PORT_RegType* BaseAddrArr[MAX_NUM_OF_PORTS] = { PORTA_BaseAddr,
PORTB_BaseAddr,
                                                                PORTC_BaseAddr,
                                                                PORTD_BaseAddr,
                                                                PORTE_BaseAddr,
                                                                PORTF_BaseAddr };

void PORT_init(void)
{
    uint8 CfgArrIndex;
    Port_IdType PortId;
    Port_ChIdType ChannelId;
    uint8 ChannelPosInPort;
    volatile PORT_RegType* BaseAddr;

    for (CfgArrIndex = 0; CfgArrIndex < PORT_NUM_OF_ACTIVATED_CH; ++CfgArrIndex)
    {
        /*get channelID from CfgIndex*/
        ChannelId = PortCfgArr[CfgArrIndex].Channel;

        /*get PORTId using ChannelId*/
        ChannelPosInPort = ChannelId / MAX_NUM_OF_CH_IN_PORT;

        /*get Channel Position in PortGroup using ChannelId */
        PortId = (Port_IdType) (ChannelId % MAX_NUM_OF_CH_IN_PORT);

        /*get baseAddress using PortId*/
        BaseAddr = BaseAddrArr[PortId];

        /*NOTE use channel position in Group to write in corresponding bit in Desired Register */

        /*TODO: set channel direction */

        (*BaseAddr).GPIODIR = (PortCfgArr[CfgArrIndex].Dir) << ChannelPosInPort;

        /*TODO: set channel mode */
        (*BaseAddr).GPIOPCTL = (PortCfgArr[CfgArrIndex].Mode)
                << (ChannelPosInPort * 4);/***because of the register divided to 8 parts***/

        /*TODO: set Interrupt configuration */
        if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntDisable)
        {

            CLR_BIT(BaseAddr->GPIOIM, ChannelPosInPort);
        }
        else
        {
            SET_BIT(BaseAddr->GPIOIM, ChannelPosInPort);
            SET_BIT(BaseAddr->GPIOMIS, ChannelPosInPort);
            /***sense for edges****/
            CLR_BIT(BaseAddr->GPIOIS, ChannelPosInPort);

            if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntFallingEdge)
            {
                /***not the both edges***/
                CLR_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);
                BaseAddr->GPIOIEV |= 0 << ChannelPosInPort;

            }
            else if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntRisingEdge)
            {
                /***not the both edges***/
                CLR_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);
                BaseAddr->GPIOIEV |= 1 << ChannelPosInPort;
            }
            else
            {
                /***the both edges***/
                SET_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);

            }

        }

        if (PortCfgArr[CfgArrIndex].Dir == port_Dir_Input)
        {
            /*TODO: set Internal Attachment configuration */
            if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_OpenDrain)
            {
                BaseAddr->GPIOODR |= 1 << ChannelPosInPort;
            }
            else if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_PullUpRes)
            {
                BaseAddr->GPIOPUR |= 1 << ChannelPosInPort;
            }

            else if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_PullDownRes)
            {
                BaseAddr->GPIOPDR = 1 << ChannelPosInPort;
            }
            else
            {
                BaseAddr->GPIOODR |= 0 << ChannelPosInPort;
                BaseAddr->GPIOPUR |= 0 << ChannelPosInPort;
                BaseAddr->GPIOPDR |= 0 << ChannelPosInPort;

            }
        }
        /*TODO: set current strength configuration */

        if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_2mA)
        {
            BaseAddr->GPIODR2R |= 1 << ChannelPosInPort;
            BaseAddr->GPIODR4R |= 0 << ChannelPosInPort;
            BaseAddr->GPIODR8R |= 0 << ChannelPosInPort;
        }
        else if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_4mA)
        {
            BaseAddr->GPIODR4R |= 1 << ChannelPosInPort;
            BaseAddr->GPIODR2R |= 0 << ChannelPosInPort;
            BaseAddr->GPIODR8R |= 0 << ChannelPosInPort;
        }
        else if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_8mA)
        {
            BaseAddr->GPIODR8R |= 1 << ChannelPosInPort;
            BaseAddr->GPIODR2R |= 0 << ChannelPosInPort;
            BaseAddr->GPIODR4R |= 0 << ChannelPosInPort;

        }
        else
        {
            BaseAddr->GPIODR2R |= 0 << ChannelPosInPort;
            BaseAddr->GPIODR4R |= 0 << ChannelPosInPort;
            BaseAddr->GPIODR8R |= 0 << ChannelPosInPort;
        }

        /*Check if analog functionality is required*/
        if (PortCfgArr[CfgArrIndex].Mode != Port_Mode_AIN)
        {

            BaseAddr->GPIOADCCTL = 0 << ChannelPosInPort;
            BaseAddr->GPIODEN = 1 << ChannelPosInPort;

            /*TODO: enable digital and disable ADC  */

        }
        else
        {
            BaseAddr->GPIOADCCTL = 1 << ChannelPosInPort;
            BaseAddr->GPIODEN = 0 << ChannelPosInPort;

        }
    }
}
