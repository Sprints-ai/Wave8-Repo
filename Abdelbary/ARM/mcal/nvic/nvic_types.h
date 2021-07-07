

#ifndef TM4C123_FIRMWARE_MCAL_NVIC_NVIC_TYPES_H_
#define TM4C123_FIRMWARE_MCAL_NVIC_NVIC_TYPES_H_

typedef struct
{
    uint32         :5;
    uint32 INTA    :3;
    uint32         :5;
    uint32 INTB    :3;
    uint32         :5;
    uint32 INTC    :3;
    uint32         :5;
    uint32 INTD    :3;
}str_NVIC_PRI_REG;

typedef struct
{


    /*Store InterruptNum*/
    uint8 Interrupt_NO;

    /*Store Priority Group*/
    uint8 Interrupt_PriorityGroup;

    /*Store Sub-priority Group*/
    uint8 Interrupt_SubPriorityGroup;


}NVIC_CfgType;



#endif /* TM4C123_FIRMWARE_MCAL_NVIC_NVIC_TYPES_H_ */
