/*
 * SysCtr.c
 *
 * Created: 4/9/2020 2:54:58 AM
 *  Author: A_ayman
 */ 


/*
*** Inclusions
*/	
#include "SysCtr.h"
	
/*
*** Local Macros 
*/

/*Register's offset values */								  
#define SYSCTL_RCGCWD_OFFSET		0x600
#define SYSCTL_RCGCTIMER_OFFSET	0x604
#define SYSCTL_RCGCGPIO_OFFSET	0x608
#define SYSCTL_RCGCDMA_OFFSET		0x60c
#define SYSCTL_RCGCHIB_OFFSET		0x614
#define SYSCTL_RCGCUART_OFFSET	0x618
#define SYSCTL_RCGCSSI_OFFSET		0x61c
#define SYSCTL_RCGCI2C_OFFSET		0x620
#define SYSCTL_RCGCUSB_OFFSET		0x628
#define SYSCTL_RCGCCAN_OFFSET		0x634
#define SYSCTL_RCGCADC_OFFSET		0x638
#define SYSCTL_RCGCACMP_OFFSET	0x63c
#define SYSCTL_RCGCPWM_OFFSET		0x640
#define SYSCTL_RCGCQEI_OFFSET		0x644
#define SYSCTL_RCGCEEPROM_OFFSET	0x658
#define SYSCTL_RCGCWTIMER_OFFSET	0x65c


/* Array Elements type */
#define REG_OFFSET					0
#define PERIPHERAL_GATE				1

/*
*** primitive Data Types
*/

// Two Dimension Array, column 0 determine the corresponding Offset for each register, based on the value of column 1 which determine the peripheral gate
static unsigned long  Sys_CLK_MaskArr[38][2]={   //column0               //column1                //column0               //column1
                                                //REG_OFFSET            //PERIPHERAL_GATE        //REG_OFFSET            //PERIPHERAL_GATE        
															{SYSCTL_RCGCWD_OFFSET	 , SYSCTL_RCGCWD_R0	  }, {SYSCTL_RCGCWD_OFFSET	  , SYSCTL_RCGCWD_R1	  },
																
															{SYSCTL_RCGCTIMER_OFFSET , SYSCTL_RCGCTIMER_R0 }, {SYSCTL_RCGCTIMER_OFFSET, SYSCTL_RCGCTIMER_R1},
															{SYSCTL_RCGCTIMER_OFFSET , SYSCTL_RCGCTIMER_R2 }, {SYSCTL_RCGCTIMER_OFFSET, SYSCTL_RCGCTIMER_R3},
															{SYSCTL_RCGCTIMER_OFFSET , SYSCTL_RCGCTIMER_R4 }, {SYSCTL_RCGCGPIO_OFFSET , SYSCTL_RCGCGPIO_R0 },
															{SYSCTL_RCGCGPIO_OFFSET	 , SYSCTL_RCGCGPIO_R1  }, {SYSCTL_RCGCGPIO_OFFSET , SYSCTL_RCGCGPIO_R2 },
															{SYSCTL_RCGCGPIO_OFFSET	 , SYSCTL_RCGCGPIO_R3  }, {SYSCTL_RCGCGPIO_OFFSET , SYSCTL_RCGCGPIO_R4 },
															{SYSCTL_RCGCGPIO_OFFSET	 , SYSCTL_RCGCGPIO_R5  }, {SYSCTL_RCGCDMA_OFFSET  , SYSCTL_RCGCDMA_R0  },
															{SYSCTL_RCGCHIB_OFFSET	 , SYSCTL_RCGCHIB_R0   }, {SYSCTL_RCGCUART_OFFSET , SYSCTL_RCGCUART_R0 },
															{SYSCTL_RCGCUART_OFFSET	 , SYSCTL_RCGCUART_R1  }, {SYSCTL_RCGCUART_OFFSET , SYSCTL_RCGCUART_R2 },
															{SYSCTL_RCGCSSI_OFFSET	 , SYSCTL_RCGCSSI_R0   }, {SYSCTL_RCGCSSI_OFFSET  , SYSCTL_RCGCSSI_R1  },
															{SYSCTL_RCGCI2C_OFFSET	 , SYSCTL_RCGCI2C_R0   }, {SYSCTL_RCGCI2C_OFFSET  , SYSCTL_RCGCI2C_R1  },
															{SYSCTL_RCGCUSB_OFFSET	 , SYSCTL_RCGCUSB_R0   }, {SYSCTL_RCGCCAN_OFFSET  , SYSCTL_RCGCCAN_R0  },
															{SYSCTL_RCGCCAN_OFFSET	 , SYSCTL_RCGCCAN_R0   }, {SYSCTL_RCGCADC_OFFSET  , SYSCTL_RCGCADC_R0  },
															{SYSCTL_RCGCADC_OFFSET	 ,	SYSCTL_RCGCADC_R1	  }, {SYSCTL_RCGCACMP_OFFSET , SYSCTL_RCGCACMP_R0 },
															{SYSCTL_RCGCPWM_OFFSET	 , SYSCTL_RCGCPWM_R0   }, {SYSCTL_RCGCPWM_OFFSET  , SYSCTL_RCGCPWM_R0  },
															{SYSCTL_RCGCQEI_OFFSET	 , SYSCTL_RCGCQEI_R0   }, {SYSCTL_RCGCQEI_OFFSET  , SYSCTL_RCGCQEI_R0  },
															{SYSCTL_RCGCEEPROM_OFFSET,	SYSCTL_RCGCEEPROM_R0}};


/*
*** Function Implementation
*/

/*
*** this function is responsible to initialize System Clock.
*/
void SysCtr_init(void)
{
	uint8_t u8_Loop_Counter = 0;
	uint8_t u8_Peripheral_Index = 0;
	uint32_t u32_SISDIV_Value = 0;
	unsigned long const u32_Base_Address = 0x400FE000;
	
	/* Set Desired System Clock */
	/*choose whether we use Internal or External Clock Source*/
	if (CLOCK_SOURCE == INTERNAL_CLK_SOURCE)
	{
		/*PLL Configurations*/
		
		/********* RCC1 Configuration ************/
		/* 1- Set the BYPASS bit */
		SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS; 
		SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;
		
		/* 2- Clear the USESYS  */
		SYSCTL_RCC_R &= ~SYSCTL_RCC_USESYSDIV;
		
		/* 3- Select OSCSRC     */
		SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_M ;
		SYSCTL_RCC_R |= SYSCTL_RCC_OSCSRC_INT|SYSCTL_RCC_MOSCDIS;
		
		/* 4- Clear the PWRDN   */
		SYSCTL_RCC_R &= ~SYSCTL_RCC_PWRDN;
	
	
	   /********* RCC2 Configuration ************/
		
		/* 1- Set USERCC2 To be able to use RCC2*/
		SYSCTL_RCC2_R |=SYSCTL_RCC2_USERCC2;
		
		/* 2- Set the BYPASS bit */
		SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2 ;
		SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2 ;
		
		/* 3- Clear the USESYS	*/
		SYSCTL_RCC2_R &= ~SYSCTL_RCC2_DIV400 ;
		
		/* 4- Select OSCSRC     */
		SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
		SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_IO|SYSCTL_RCC_MOSCDIS;
		
		/* 5- Clear the PWRDN   */
		SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2 ;
		
		/* 6- Select the desired system divider (SYSDIV) */
		u32_SISDIV_Value= gu32_Clock_Value << SYSCTL_RCC_SYSDIV_S;
		SYSCTL_RCC_R &=~SYSCTL_RCC_SYSDIV_M;
		SYSCTL_RCC_R |= (u32_SISDIV_Value );
		SYSCTL_RCC2_R &=~SYSCTL_RCC2_SYSDIV2_M;
		SYSCTL_RCC2_R |= (u32_SISDIV_Value);
		
		/* 7- Clear the USESYS	*/
		SYSCTL_RCC_R |=SYSCTL_RCC_USESYSDIV;
		/* 8- Wait PLL          */
      //while (SYSCTL_RIS_R >>6 &1) ;
		
		/* 9- Enable use of the PLL by clearing the BYPASS bit in RCC/RCC2 */
		SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2 ;
		SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS; 
	}
	if (CLOCK_SOURCE == EXTERNAL_CLK_SOURCE)
	{
		//for future use
	}
	
	/* Enable Clock Gates */
	//For each iteration we get the Peripheral index and found the corresponding Enable gate mask and register offset of it
	for(u8_Loop_Counter = 0; u8_Loop_Counter <NUM_OF_ENABLED_PRIPHERALS_GATES; u8_Loop_Counter++)
	{
		u8_Peripheral_Index = Sys_CLK_CfgArr[u8_Loop_Counter];
		*( reg_type32_t ) ( Sys_CLK_MaskArr[u8_Peripheral_Index][REG_OFFSET] + u32_Base_Address ) &= ~Sys_CLK_MaskArr[u8_Peripheral_Index][PERIPHERAL_GATE];
		*( reg_type32_t ) ( Sys_CLK_MaskArr[u8_Peripheral_Index][REG_OFFSET] + u32_Base_Address ) |=  Sys_CLK_MaskArr[u8_Peripheral_Index][PERIPHERAL_GATE];
	
	}

}

	
