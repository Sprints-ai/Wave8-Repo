/*
 * SysCtr.c
 *
 * Created: 4/7/2020 8:50 AM
 *  Author: Ema
 */

#include"mcu_hw.h"
#include"SysCtr.h"

extern uint8_t CfgArr[][NUM_OF_CHANNELS];

void SysCtr_init(void)
{
    /****get the address of RCFCTIMER as we start from it in this small implementation****/
    /****in general case we would start from RCGC_PERIPHIRALS_REGS as it contains the first address of RCGC_Regs****/
    uint32_t *ST_RCGC_ptr = (uint32_t*)(&(RCGC_PERIPHIRALS_REGS.RCGCTIMER));

	/* TODO: Set Desired System Clock  */


	/*TODO: Enable Clock Gates */
	/****i should loop over peripherals in the same order as in data sheet****/
	for(int i=0; i<NUM_OF_PERIPHERALS; i++, ST_RCGC_ptr++)
	{
	    /****j should loop over Channels in each peripheral****/
	    for(int j=0; j<NUM_OF_CHANNELS; j++)
        {
            *ST_RCGC_ptr |= ((CfgArr[i][j])<<j);
        }
	}

}
