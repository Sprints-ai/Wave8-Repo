#include "std_types.h"
#include "NVIC.h"

/******************************************************************/
/*					General macros	            				  */
/******************************************************************/

#define REGISTER_BITS   (32)
#define HIGH_BIT        (1)
#define NVIC_PRI_REG    (4)
#define SHIFT_BY_5      (5)
#define INT_NUM_SELECT  (8)

/******************************************************************/
/*					NVIC functions' definitions					  */
/******************************************************************/

void NVIC_EnableInt(uint8_t au8_intID)
{
    /*Get the interrupt enable register*/
    uint8_t au8_register = au8_intID / REGISTER_BITS;

    /*Get the interrupt enable bit*/
    uint8_t au8_bit = au8_intID % REGISTER_BITS; 

    /*Enable the interrupt in NVIC*/
    NVIC_REG -> EN_ARR[au8_register] = HIGH_BIT << au8_bit;

    return;
}

void NVIC_DisableInt(uint8_t au8_intID)
{
    /*Get the interrupt disable register*/
    uint8_t au8_register = au8_intID / REGISTER_BITS;

    /*Get the interrupt disable bit*/
    uint8_t au8_bit = au8_intID % REGISTER_BITS; 

    /*Disable the interrupt in NVIC*/
    NVIC_REG -> DIS_ARR[au8_register] = HIGH_BIT << au8_bit;

    return;
}

void NVIC_PendInt(uint8_t au8_intID)
{
    /*Get the interrupt pending register*/
    uint8_t au8_register = au8_intID / REGISTER_BITS;

    /*Get the interrupt pending bit*/
    uint8_t au8_bit = au8_intID % REGISTER_BITS; 

    /*Pend the interrupt in NVIC*/
    NVIC_REG -> PEND_ARR[au8_register] = HIGH_BIT << au8_bit;

    return;
}

void NVIC_UnPendInt(uint8_t au8_intID)
{
    /*Get the interrupt un-pending register*/
    uint8_t au8_register = au8_intID / REGISTER_BITS;

    /*Get the interrupt un-pending bit*/
    uint8_t au8_bit = au8_intID % REGISTER_BITS; 

    /*Un-pend the interrupt in NVIC*/
    NVIC_REG -> UPEND_ARR[au8_register] = HIGH_BIT << au8_bit;

    return;
}

void NVIC_SetIntPriority(uint8_t au8_intID , uint8_t au8_intPriority)
{
    /*Get the interrupt priority register*/
    uint8_t au8_register = au8_intID / NVIC_PRI_REG;

    /*Get the interrupt number*/
    uint8_t au8_intNumber = au8_intID % NVIC_PRI_REG;

    /*Set the interrupt priority*/
    NVIC_REG -> PRI_ARR[au8_register] =  au8_intPriority << (SHIFT_BY_5 + (au8_intNumber * INT_NUM_SELECT));

    return;
}
