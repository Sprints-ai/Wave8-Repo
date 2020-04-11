#include "../includes/SysCtrl.h"
#include "../includes/SysCtrl_lCfg.h"
#include "../includes/MCU_hw.h"
#include "../../Services/includes/common_macros.h"
/**************************************************/
/*             Static Define                      */
/**************************************************/

#define PLLRIS                   6

//RCC BITS
#define RCC_OSCSRC_B4            4
#define RCC_OSCSRC_B5            5
#define RCC_XTAL_B6              6
#define RCC_XTAL_B7              7
#define RCC_XTAL_B8              8
#define RCC_XTAL_B9              9
#define RCC_XTAL_B10             10
#define RCC_BYPASS_B11           11
#define RCC_PWRDN_B13            13
#define RCC_USERSYSDIV_B22       22
#define RCC_SYSDIV_B23           23
#define RCC_SYSDIV_B24           24
#define RCC_SYSDIV_B25           25
#define RCC_SYSDIV_B26           26

//RCC 2 Fields Mask
#define RCC_SYSDIV_MASK
#define RCC_USERSYSDIV_MASK
#define RCC_BYPASS_MASK


//RCC 2 Fields Start Index
#define RCC_2_OSCSRC2_B4         4
#define RCC_2_OSCSRC2_B5         5
#define RCC_2_OSCSRC2_B6         6
#define RCC_2_BYPASS2_B11        11
#define RCC_2_SYSDIV2LSB_B22     22
#define RCC_2_SYSDIV2_B23        23
#define RCC_2_SYSDIV2_B24        24
#define RCC_2_SYSDIV2_B25        25
#define RCC_2_SYSDIV2_B26        26
#define RCC_2_SYSDIV2_B27        27
#define RCC_2_SYSDIV2_B28        28
#define RCC_2_DIV400_B30         30
#define RCC_2_USERCC2_B31        31

//RCC 2 Fields Mask
#define RCC_2_USERCC2_FIELD_MASK
#define RCC_2_DIV400_FIELD_MASK
#define RCC_2_SYSDIV2_FIELD_MASK
#define RCC_2_SYSDIV2LSB_FIELD_MASK
#define RCC_2_BYPASS2_FIELD_MASK
#define RCC_2_OSCSRC2_FIELD_MASK


void SysCtrl_Init(void)
{
	uint32_t sysDIV;
	uint8_t i;
	/* TODO: Set Desired System Clock  */
	
	#if SYSCTRL_PLL_MODE == ENABLE
	
	//1- Bypass the PLL and system clock divider
	SET_BIT(SYSCTL_RCC_R,RCC_BYPASS_B11);
	CLR_BIT(SYSCTL_RCC_R,RCC_USERSYSDIV_B22);
	
	//2- Select the XTAL, OSCSRC, Clear PWDN bit
	SET_BIT_MASK(SYSCTL_RCC_R,RCC_XTAL_MASK);//XTAL Selection
	SET_BIT_MASK(SYSCTL_RCC_R,RCC_OSCSRC_MASK);//OSCSRC Selection
	CLR_BIT(SYSCTL_RCC_R,RCC_PWRDN_B13);//Clear PWDN bit
	
	
	//3- Select the desired system divider
	SET_BIT(SYSCTL_RCC2_R,RCC_2_USERCC2_B31);
	
	//Calc the sysDivider
	sysDIV = (PLL_FREQ)/SYSCTRL_CLK_HZ;

	if(PLL_FREQ == PLL_FREQ_NODIV2)
	{
		SET_BIT(SYSCTL_RCC2_R,RCC_2_DIV400_B30);// NO Division and the sys division is 7-bit
		sysDIV = sysDIV<<RCC_2_SYSDIV2LSB_B22;
		
	}
	else if(PLL_FREQ == PLL_FREQ_DIV2)
	{
		CLR_BIT(SYSCTL_RCC2_R,RCC_2_DIV400_B30);// Division and the sys division is 6-bit
		sysDIV = sysDIV<<RCC_2_SYSDIV2_B23;
	}
	
	//4- Wait for the PLL to lock
	while((SYSCTL_RIS_R & (1<<PLLRIS)));
	
	//5- Enable the PLL
	CLR_BIT(SYSCTL_RCC2_R,RCC_2_BYPASS2_B11);
	
	#endif
	
	/*TODO: Enable Clock Gates */
	for(i=0;i<NUM_OF_PRIPHERALS;i++)
	{
		SET_BIT(*(periph_Clk[i].Reg),periph_Clk[i].RegName);
	}
}

