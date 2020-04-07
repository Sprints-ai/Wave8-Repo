/*
 * NVIC.c
 *
 * Created: 4/7/2020 10:10 AM
 *  Author: Ema
 */

#include"mcu_hw.h"
#include"STD_Types.h"
#include"NVIC.h"
#include"NVIC_Cfg.h"

extern NVIC_CfgType NVIC_CfgArr[];

void NVIC_init(void)
{
	uint8_t NVIC_IntNum;
	uint8_t NVIC_Group_Priority;
	uint8_t	NVIC_SubGroup_Priority;
	uint8_t INT_PR_Slot;
	uint8_t INT_EN_Slot;

    /****get the address of NVIC_EN_REG as it's the base address of INT_EN_REG****/
    uint32_t *ST_NVIC_EN_ptr = (uint32_t*)(&NVIC_EN_REG);

    /****get the address of NVIC_PR_REG as it's the base address of INT_PR_REG****/
    uint32_t *ST_NVIC_PR_ptr = (uint32_t*)(&NVIC_PR_REG);

	/*TODO Set Combination in APINT  xxx xxy xyy yyy*/

	for(int i=0; i<NUM_OF_ACTIVATED_INTERRUPTS; i++)
	{
		NVIC_IntNum = NVIC_CfgArr[i].IntNum;
		NVIC_Group_Priority = NVIC_CfgArr[i].Group_Priority;
		NVIC_SubGroup_Priority = NVIC_CfgArr[i].SubGroup_Priority;

		/*TODO Enable Interrupt */
		/***INT_EN_SLOT reprsents ENx***/
        INT_EN_Slot = NVIC_IntNum /32;
		*ST_NVIC_EN_ptr += INT_EN_Slot;
		*ST_NVIC_EN_ptr = (ENABLE<<NVIC_IntNum);

		/*TODO Set Priority Group/SubGroup*/
		/***INT_PR_SLOT reprsents PRIx***/
		INT_PR_Slot = NVIC_IntNum/4;
        ST_NVIC_PR_ptr += (NVIC_IntNum/4);
        *ST_NVIC_PR_ptr = ((NVIC_Group_Priority|NVIC_SubGroup_Priority)<<(5+(8*INT_PR_Slot)));

	}
}
