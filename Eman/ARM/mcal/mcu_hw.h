/*
 * mcu_hw.h
 *
 * Created: 4/7/2020 8:43 AM
 *  Author: Ema
 */

#include"STD_Types.h"

#define NVIC_EN_REG              (*((volatile NVIC_EN_REGs*)0xE000E100))
#define NVIC_PR_REG              (*((volatile NVIC_PR_REGs*)0xE000E400))

#define RCGC_PERIPHIRALS_REGS    (*((volatile RCGC_Periphiral*)0x400FE600))


/***NVIC_REG***/

/**Use this with NVIC_EN_REG to get direct access to any INT to enable it**/
typedef struct
{
    uint32_t B0:1;
    uint32_t B1:1;
    uint32_t B2:1;
    uint32_t B3:1;
    uint32_t B4:1;
    uint32_t B5:1;
    uint32_t B6:1;
    uint32_t B7:1;
    uint32_t B8:1;
    uint32_t B9:1;
    uint32_t B10:1;
    uint32_t B11:1;
    uint32_t B12:1;
    uint32_t B13:1;
    uint32_t B14:1;
    uint32_t B15:1;
    uint32_t B16:1;
    uint32_t B17:1;
    uint32_t B18:1;
    uint32_t B19:1;
    uint32_t B20:1;
    uint32_t B21:1;
    uint32_t B22:1;
    uint32_t B23:1;
    uint32_t B24:1;
    uint32_t B25:1;
    uint32_t B26:1;
    uint32_t B27:1;
    uint32_t B28:1;
    uint32_t B29:1;
    uint32_t B30:1;
    uint32_t B31:1;
}NVIC_INTx_EN_b;


typedef struct
{
    NVIC_INTx_EN_b EN0 ;
    NVIC_INTx_EN_b EN1 ;
    NVIC_INTx_EN_b EN2 ;
    NVIC_INTx_EN_b EN3 ;
    NVIC_INTx_EN_b EN4 ;
}NVIC_EN_REGs;

/**Use this with NVIC_PR_REG to get direct access to set INT priority**/
typedef struct
{
    uint32_t reserved0:5;
    uint32_t INT0x:3;
    uint32_t reserved1:5;
    uint32_t INT1x:3;
    uint32_t reserved2:5;
    uint32_t INT2x:3;
    uint32_t reserved3:5;
    uint32_t INT3x:3;
}NVIC_INTx_PR_b;

typedef struct
{
    NVIC_INTx_PR_b PRI0;
    NVIC_INTx_PR_b PRI1;
    NVIC_INTx_PR_b PRI2;
    NVIC_INTx_PR_b PRI3;
    NVIC_INTx_PR_b EPRI4;
}NVIC_PR_REGs;


/***RCGC_REG***/

/**Use this with RCGC_Peripheral to get direct access to any channel of any peripheral to enable it**/
typedef struct
{
    uint32_t R0:1;
    uint32_t R1:1;
    uint32_t R2:1;
    uint32_t R3:1;
    uint32_t R4:1;
    uint32_t R5:1;
    uint32_t reseved:26;
}RCGC_Rx;

typedef struct
{
    RCGC_Rx RCGCWD;
    RCGC_Rx RCGCTIMER;
    RCGC_Rx RCGCGPIO;
    RCGC_Rx RCGCDMA;
    RCGC_Rx RCGCHIB;
    RCGC_Rx RCGCUART;
    RCGC_Rx RCGCSSI;
    RCGC_Rx RCGCI2C;
    RCGC_Rx RCGCUSB;
    RCGC_Rx RCGCCAN;
    RCGC_Rx RCGCADC;
    RCGC_Rx RCGCACMP;
    RCGC_Rx RCGCPWM;
    RCGC_Rx RCGCQEI;
    RCGC_Rx RCGCEEPROM;
    RCGC_Rx RCGCWTIMER;
}RCGC_Periphiral;



