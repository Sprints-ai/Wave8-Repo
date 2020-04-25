

/*****************************************************************************/
/*					SysCtr.c												 */	
/*****************************************************************************/
#include "std_types.h"
#include "SysCtr_Lcfg.h"
#include "MCU_HW.h"

#define BYPASS2_BIT  11
#define USESYS_BIT 22
#define USECRR2_BIT 31
#define XTEL_CLEAR_MASK 0x000007C0
#define OSCSRC2_CLEAR_MASK 0x00000070
#define DIV400_BIT 30
#define SYSDIV_CLAER_MASK 0x1F800000
#define PLLLRIS_BIT_MASK 0x00000040
#define FIRST_RCGC_ADD_REG 0x400FE600
#define RCGC_REG(OFFSET) *(uint32_t *)(FIRST_RCGC_ADD_REG + OFFSET)


void SysCtr_init(void)
{
	uint8_t counter ,offset ,RCGC_BIT_NO = 0 ;
	uint32_t RCGC_Reg_Address ;
	/* TODO: Set Desired System Clock  */
	
	/*clear usesys and set bypass2 to start modifing */
	CLEAR_BIT(RCC,USESYS_BIT);

	SET_BIT(RCC2,BYPASS2_BIT);
	

	/* set the useccr2 bit in RCC2 */
	SET_BIT(RCC,USECRR2_BIT);
	
	/* set the OSCSRC2 value with 0x0  to use main OSC */
	RCC2 = RCC2 &(~(OSCSRC2_CLEAR_MASK)) ;

	
	/* set the xtel in the RCC with 0x15 for 16 Mhz */
	RCC = (RCC &(~(XTEL_CLEAR_MASK)))| 0x00000150 ;

	
	/*SET DIV400 0x1 */
	SET_BIT(RCC2,DIV400_BIT);
	
	/* xxxx set SYSDIV TO VALUE OF DEVISIROR-1 equation xxxx 22-> 28 */
	
	ClkFreq--;
	RCC2 = (RCC2 &(~(SYSDIV_CLAER_MASK))) ;
	RCC2 |= ClkFreq<<22;
	
	
	/*poll on the LOCK in the RIS register */
	
	while (!(RIS&PLLLRIS_BIT_MASK));
	
	/* clear BYPASS with 0x0 to use PLL to enable the PLL */
		CLEAR_BIT(RCC2,BYPASS2_BIT);

	
	/*TODO: Enable Clock Gates */
	
	for(counter=0; counter <NUM_OF_PRIPHERALS ;counter++)
	{
		/* here where we update the register addres to the next module */
		if(counter == 2||counter ==8||counter ==14||
			counter ==15||counter ==16||counter ==24||
			counter ==28||counter ==32||counter ==33||
			counter ==35||counter ==37||counter ==38||
			counter ==40||counter ==42||counter ==49)
		{
			offset+=4 ;
			RCGC_Reg_Address = RCGC_REG(offset) ;
			RCGC_BIT_NO = ZERO ;
		}else if (counter == 43)
		{
			offset+=14 ;
			RCGC_Reg_Address = RCGC_REG(offset) ;
			RCGC_BIT_NO = ZERO ;
		}
		/* check for each if needed enabling */
		if( CfgArr[counter]== ENABLE)
		{
			SET_BIT(RCGC_Reg_Address,RCGC_Reg_Address);
		}
		/*increment the bit number to acceses the next fuild for each module*/
		RCGC_BIT_NO++;
	}
	
}
