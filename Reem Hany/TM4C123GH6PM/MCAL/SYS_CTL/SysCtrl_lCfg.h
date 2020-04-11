#ifndef __SYSCTRL_LCFG_H__
#define __SYSCTRL_LCFG_H__
#include "../../Services/includes/std_types.h"
#include "SysCtrl_types.h"



/***********************************************/
/*            Defines                          */
/***********************************************/

#define XTAL_NOPLL_4MHZ                       0x06            
#define XTAL_NOPLL_4_096MHZ                   0X07
#define XTAL_PLL_4_9152MHZ                    0x08
#define XTAL_USB_5MHZ                         0x09
#define XTAL_5_12MHZ                          0x0A
#define XTAL_USB_6MHZ                         0x0B
#define XTAL_6_144MHZ                         0x0C
#define XTAL_7_37284MHZ                       0x0D
#define XTAL_USB_8MHZ                         0x0E
#define XTAL_8_192MHZ                         0x0F
#define XTAL_12_288MHZ                        0x12
#define XTAL_13_56MHZ                         0x13
#define XTAL_14_31818MHZ                      0x14
#define XTAL_USB_16MHZ                        0x15
#define XTAL_16_384MHZ                        0x16
#define XTAL_USB_18MHZ                        0x19
#define XTAL_USB_20MHZ                        0x18
#define XTAL_USB_24MHZ                        0x19
#define XTAL_USB_25MHZ                        0x1A
																              
#define OSCSRC_MOSC                           0x0
#define OSCSRC_PIOSC                          0x01
#define OSCSRC_PIOSC_4                        0x02
#define OSCSRC_LFIOSC                         0x03     
																              
																              
#define RCC_XTAL_MASK                         XTAL_USB_16MHZ<<6
#define RCC_OSCSRC_MASK                       OSCSRC_MOSC<<4

#define SYSCTRL_CLK_HZ                        40000000

#define PLL_FREQ_NODIV2                       400000000
#define PLL_FREQ_DIV2                         200000000
#define PLL_FREQ                              PLL_FREQ_NODIV2

/*
#define SYSCTRL_SYSDIV_3                      3
#define SYSCTRL_SYSDIV_4                      4
#define SYSCTRL_SYSDIV_5                      5
#define SYSCTRL_SYSDIV_6                      6
#define SYSCTRL_SYSDIV_7                      7
#define SYSCTRL_SYSDIV_8                      8
#define SYSCTRL_SYSDIV_9                      9
#define SYSCTRL_SYSDIV_10                     10
#define SYSCTRL_SYSDIV_11                     11
#define SYSCTRL_SYSDIV_12                     12
#define SYSCTRL_SYSDIV_13                     13
#define SYSCTRL_SYSDIV_14                     14
#define SYSCTRL_SYSDIV_15                     15
#define SYSCTRL_SYSDIV_16                     16*/




#define SYSCTRL_PLL_MODE                      ENABLE 
#define NUM_OF_PRIPHERALS                     3

extern strSysCtlCfg_s_t periph_Clk[NUM_OF_PRIPHERALS]; 

#endif
