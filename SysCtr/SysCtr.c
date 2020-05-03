
/*****************************************************************************/
/*					SysCtr.c												 */	
/*****************************************************************************/
//#include <stdio.h>
#include "MCU_hw.h"
#include "SysCtr.h"
#include "SysCtr_Cfg.h"
#include "SysCtr_Lcfg.h"

#define EEPROM_DONE 				0
#define ENABLE_MAIN_SOURCE_CLK 		0
#define XTAL_16MH					0x15
#define MAIN_OSR_SELECT				0x0
#define PLL_DISABLE 				1
#define DISABLE_SYS_DIV  			0
#define MAIN_SOURCE_DIVISOR 		1
#define SYSDIV_INIT 				2
#define PLL_ENABLE 					0
#define ENABLE_SYS_DIV				1
#define PLL_SOURCE_DIVISOR			0	
#define ENABLE_RCC2_WRITING 		1
#define ENABLE_DIVISOR_by_2_TO_PLL 	0	
#define PPL_DIVIDE_2 				200
#define PLL_UNLOCKED 				0
#define DISABLE_RCC2_WRITING 		0
#define ZERO 						0
#define CLK_GATE_REG_MAP		    8//
#define CLK_GATE_ENABLE 			(uint32_t)1
void SysCtr_init(void)
{
	
	//uint8_t u8_sysdiv_Value = SYSDIV_INIT;  
	uint8_t u8_ClkGateCounter = ZERO ,u8_RegisterIndex = ZERO , u8_BitIndex =ZERO;
	
	// Ensure EEPROW Fish its working  //
	
	//while( EEDONE_Reg.gstr_EEDONE_Bit_Reg.WORKING == EEPROM_DONE );

	//The system clock is derived from the OSC source and divided by the divisor
	RCC_REG.str_RCC_Bit_Reg.BYPASS=MAIN_SOURCE_DIVISOR;
	// disable system divisor 
	RCC_REG.str_RCC_Bit_Reg.USESYSDIV= DISABLE_SYS_DIV; 
	
		// Select crystal 
	RCC_REG.str_RCC_Bit_Reg.XTAL = XTAL_16MH;
//	RCC_REG.str_RCC_Bit_Reg.XTAL =ENABLE_MAIN_SOURCE_CLK; 
	
	
	// Enable main source clk
	RCC_REG.str_RCC_Bit_Reg.MOSCDIS =ENABLE_MAIN_SOURCE_CLK;
	
	//Slect main sources as system clk
	RCC_REG.str_RCC_Bit_Reg.OSCSRC =MAIN_OSR_SELECT; 
	
	// disable The PLL
	RCC_REG.str_RCC_Bit_Reg.PWRDN = PLL_DISABLE ; 
		
	#if SysCtr_Clock_Hz == Fre_16_MHZ 
//	while (RIS_REG.gstr_RIS_Bit_Reg.USBPLLLRIS == PLL_UNLOCKED) ;
	//The system clock is derived from the OSC source and divided by the divisor
	RCC_REG.str_RCC_Bit_Reg.BYPASS = MAIN_SOURCE_DIVISOR; 
	
	#else 
	
	// change to RCC2 Register 
	RCC2_REG.str_RCC2_Bit_Reg.USERCC2 = ENABLE_RCC2_WRITING;	
	
	//Set the divisor value 
	RCC2_REG.str_RCC2_Bit_Reg.SYSDIV2 = (PPL_DIVIDE_2 / SysCtr_Clock_Hz ); 
	
	// Devide pll/2
	RCC2_REG.str_RCC2_Bit_Reg.DIV400 = ENABLE_DIVISOR_by_2_TO_PLL; //NOT SOURE 
	// change to RCC Register 
	RCC2_REG.str_RCC2_Bit_Reg.USERCC2 = DISABLE_RCC2_WRITING;	
	// Enable system divisor 
	RCC_REG.str_RCC_Bit_Reg.USESYSDIV = ENABLE_SYS_DIV; 
	//// Enable The PLL
//	RCC_REG.str_RCC_Bit_Reg.PWRDN = PLL_ENABLE ; 
	
	//WAIT TO PLL BE STABLE 
	//while (RIS_REG.gstr_RIS_Bit_Reg.USBPLLLRIS == PLL_UNLOCKED) ;
	
		// change to RCC2 Register 
	RCC2_REG.str_RCC2_Bit_Reg.USERCC2 = ENABLE_RCC2_WRITING;	
    //The system clock is derived from the PLL  and divided by the divisor
	
	RCC2_REG.str_RCC2_Bit_Reg.BYPASS2 = PLL_SOURCE_DIVISOR; 	

	
	 #endif 

	/*TODO: Enable Clock Gates */
	for(; u8_ClkGateCounter < NUM_OF_PRIPHERALS ; u8_ClkGateCounter++)
	{
		 u8_RegisterIndex = (SysCtr_EnableArr[u8_ClkGateCounter] / CLK_GATE_REG_MAP); 
		 
		 u8_BitIndex = (SysCtr_EnableArr[u8_ClkGateCounter] % CLK_GATE_REG_MAP); 
		
	//	*((&(RCGCWD_REG)+ u8_RegisterIndex))|=  (CLK_GATE_ENABLE << u8_BitIndex) ;

		//*(((volatile uint32_t *)(&(ClkGate_Reg.RCGCWD)))+ u8_RegisterIndex)|=  (CLK_GATE_ENABLE << u8_BitIndex) ;
		(*((&(ClkGate_Reg.RCGCWD))+ u8_RegisterIndex))|=  (CLK_GATE_ENABLE << u8_BitIndex) ;
			
	}
	
	
	
}


/*int main (){
		
		
		ClkGate_Reg_t str_variable;
		uint32_t u32_var;
		str_variable.RCGCWD = 9;
		str_variable.RCGCTIMER =5;
		u32_var= *((uint32_t *)(&(str_variable.RCGCWD)+1)) ;
		printf("%d\n%d",str_variable.RCGCWD,u32_var);
		RIS_Reg_t str_variable;
		uint32_t u32_var;
		str_variable.gu32_RIS_Reg = 1;
		u32_var =str_variable.gu32_RIS_Reg;
		
		printf("%d\n",u32_var);

		str_variable.gstr_RIS_Bit_Reg.BOR1RIS = 1;
		u32_var =str_variable.gu32_RIS_Reg;
		
		printf("%d",str_variable.gstr_RIS_Bit_Reg.BOR1RIS);
		
		
		
		return 0;
	}*/
