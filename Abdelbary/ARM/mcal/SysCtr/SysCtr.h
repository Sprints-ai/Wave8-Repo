#ifndef E15_ARM_REPO_MCAL_SYS_CTR_SYSCTR_H_
#define E15_ARM_REPO_MCAL_SYS_CTR_SYSCTR_H_
/******************************INCLUDES************************************/
#include "../../utils/Std_Types.h"
#include "../../config/SysCtr_cfg.h"

/******************************DEFINES************************************/

 /* defines to  be passed to SysCtr_prepheralClkEnable() API*/
#define SYSCTL_PERIPH_ADC0      0x3800  // ADC 0
#define SYSCTL_PERIPH_ADC1      0x3801  // ADC 1
#define SYSCTL_PERIPH_CAN0      0x3400  // CAN 0
#define SYSCTL_PERIPH_CAN1      0x3401  // CAN 1
#define SYSCTL_PERIPH_COMP0     0x3c00  // Analog Comparator Module 0
#define SYSCTL_PERIPH_EMAC0     0x9c00  // Ethernet MAC0
#define SYSCTL_PERIPH_EPHY0     0x3000  // Ethernet PHY0
#define SYSCTL_PERIPH_EPI0      0x1000  // EPI0
#define SYSCTL_PERIPH_GPIOA     0x0800  // GPIO A
#define SYSCTL_PERIPH_GPIOB     0x0801  // GPIO B
#define SYSCTL_PERIPH_GPIOC     0x0802  // GPIO C
#define SYSCTL_PERIPH_GPIOD     0x0803  // GPIO D
#define SYSCTL_PERIPH_GPIOE     0x0804  // GPIO E
#define SYSCTL_PERIPH_GPIOF     0x0805  // GPIO F
#define SYSCTL_PERIPH_HIBERNATE 0x1400  // Hibernation module
#define SYSCTL_PERIPH_CCM0      0x7400  // CCM 0
#define SYSCTL_PERIPH_EEPROM0   0x5800  // EEPROM 0
#define SYSCTL_PERIPH_FAN0      0x5400  // FAN 0
#define SYSCTL_PERIPH_FAN1      0x5401  // FAN 1
#define SYSCTL_PERIPH_I2C0      0x2000  // I2C 0
#define SYSCTL_PERIPH_I2C1      0x2001  // I2C 1
#define SYSCTL_PERIPH_I2C2      0x2002  // I2C 2
#define SYSCTL_PERIPH_I2C3      0x2003  // I2C 3
#define SYSCTL_PERIPH_ONEWIRE0  0x9800  // One Wire 0
#define SYSCTL_PERIPH_PWM0      0x4000  // PWM 0
#define SYSCTL_PERIPH_PWM1      0x4001  // PWM 1
#define SYSCTL_PERIPH_QEI0      0x4400  // QEI 0
#define SYSCTL_PERIPH_QEI1      0x4401  // QEI 1
#define SYSCTL_PERIPH_SSI0      0x1c00  // SSI 0
#define SYSCTL_PERIPH_SSI1      0x1c01  // SSI 1
#define SYSCTL_PERIPH_SSI2      0x1c02  // SSI 2
#define SYSCTL_PERIPH_SSI3      0x1c03  // SSI 3
#define SYSCTL_PERIPH_TIMER0    0x0400  // Timer 0
#define SYSCTL_PERIPH_TIMER1    0x0401  // Timer 1
#define SYSCTL_PERIPH_TIMER2    0x0402  // Timer 2
#define SYSCTL_PERIPH_TIMER3    0x0403  // Timer 3
#define SYSCTL_PERIPH_TIMER4    0x0404  // Timer 4
#define SYSCTL_PERIPH_TIMER5    0x0405  // Timer 5
#define SYSCTL_PERIPH_UART0     0x1800  // UART 0
#define SYSCTL_PERIPH_UART1     0x1801  // UART 1
#define SYSCTL_PERIPH_UART2     0x1802  // UART 2
#define SYSCTL_PERIPH_UART3     0x1803  // UART 3
#define SYSCTL_PERIPH_UART4     0x1804  // UART 4
#define SYSCTL_PERIPH_UART5     0x1805  // UART 5
#define SYSCTL_PERIPH_UART6     0x1806  // UART 6
#define SYSCTL_PERIPH_UART7     0x1807  // UART 7
#define SYSCTL_PERIPH_UDMA      0x0c00  // uDMA
#define SYSCTL_PERIPH_USB0      0x2800  // USB 0
#define SYSCTL_PERIPH_WDOG0     0x0000  // Watchdog 0
#define SYSCTL_PERIPH_WDOG1     0x0001  // Watchdog 1
#define SYSCTL_PERIPH_WTIMER0   0x5c00  // Wide Timer 0
#define SYSCTL_PERIPH_WTIMER1   0x5c01  // Wide Timer 1
#define SYSCTL_PERIPH_WTIMER2   0x5c02  // Wide Timer 2
#define SYSCTL_PERIPH_WTIMER3   0x5c03  // Wide Timer 3
#define SYSCTL_PERIPH_WTIMER4   0x5c04  // Wide Timer 4
#define SYSCTL_PERIPH_WTIMER5   0x5c05  // Wide Timer 5

/*************************EXTENAL FUNCTION PROTOTYPES*****************************/

/**
 * Function : SysCtr_init
 *
 * Description: Function initialize the clock depending on the user configuration
 * if user select MAIN OSC or internal 16MHz the PLL would be output 400MHz and then divide it to get user selected clock.
 * */
extern void SysCtr_init(void);

/**
 * Function: SysCtr_prepheralClkEnable.
 *
 * Inputs:u16_prepheral -> higher byte decide the peripheral register offset
 * and lower byte contain the bit number at that register
 * Example: SYSCTL_PERIPH_ADC1  defined by 0x3801 -> 0x38 is RCGCADC REG offset
 * and ADC1 is enabled by set by bit 0x01 at that register
 *
 * Description: function enables the clock to the selected peripheral.
 * */
extern void SysCtr_prepheralClkEnable(uint16 u16_peripheral);

/**
 * Function: SysCtr_getSysClockFreq
 * @return: the actual value of the clock frequency by KHz
 * Description: function get the actual value of clk frequency by mapping SYSDIV2 field by look up table.
 */
extern uint32 SysCtr_getSysClockFreq(void);



#endif /* E15_ARM_REPO_MCAL_SYS_CTR_SYSCTR_H_ */
