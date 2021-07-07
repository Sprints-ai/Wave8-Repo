#include "../mcu_hw.h"
#include "../../utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include "SysCtr.h"

#define EIGHT     (8)

/* look up table contain the values to be set in the RCC2 register to achieve user selected clock */
static const uint8 gsau8_freqLookUpTable[] = { 4, 5, 7, 8, 9, 10, 11, 12, 13,
                                               14, 15, 16, 17, 18, 19, 20, 21,
                                               22, 23, 24, 25, 26, 27, 28, 29,
                                               30, 31, 32, 33, 34, 35, 36, 37,
                                               38, 39, 40, 41, 42, 43, 44, 45,
                                               46, 47, 48, 49, 50, 51, 52, 53,
                                               54, 55, 56, 57, 58, 59, 60, 61,
                                               62, 63, 64, 65, 66, 67, 68, 69,
                                               70, 71, 72, 73, 74, 75, 76, 77,
                                               78, 79, 80, 81, 82, 83, 84, 85,
                                               86, 87, 88, 89, 90, 91, 92, 93,
                                               94, 95, 96, 97, 98, 99, 10, 101,
                                               102, 103, 104, 105, 106, 107,
                                               108, 109, 110, 111, 112, 113,
                                               114, 115, 116, 117, 118, 119,
                                               120, 121, 122, 123, 124, 125,
                                               126, 127 };
/* the actual values of clock frequency in KHz */
static const uint32 gsau32_freqValues[] = { 0, 0, 0, 0, 80000, 66667, 0, 50000,
                                            44444, 40000, 36364, 33333, 30769,
                                            28571, 26667, 25000, 23529, 22222,
                                            21053, 20000, 19048, 18182, 17391,
                                            16667, 16000, 15385, 14815, 14286,
                                            13793, 13333, 12903, 12500, 12121,
                                            11765, 11429, 11111, 10811, 10526,
                                            10256, 10000, 9756, 9524, 9302,
                                            9091, 8889, 8696, 8511, 8333, 8163,
                                            8000, 7843, 7692, 7547, 7407, 7273,
                                            7143, 7018, 6897, 6780, 6667, 6557,
                                            6452, 6349, 6250, 6154, 6061, 5970,
                                            5882, 5797, 5714, 5634, 5556, 5479,
                                            5405, 5333, 5263, 5195, 5128, 5063,
                                            5000, 4938, 4878, 4819, 4762, 4706,
                                            4651, 4598, 4545, 4494, 4444, 4396,
                                            4348, 4301, 4255, 4211, 4167, 4124,
                                            4082, 4040, 4000, 3960, 3922, 3883,
                                            3846, 3810, 3774, 3738, 3704, 3670,
                                            3636, 3604, 3571, 3540, 3509, 3478,
                                            3448, 3419, 3390, 3361, 3333, 3306,
                                            3279, 3252, 3226, 3200, 3175, 3150,
                                            3125 };


/**
 * Function : SysCtr_init
 *
 * Description: Function initialize the clock depending on the user configuration
 * if user select MAIN OSC or internal 16MHz the PLL would be output 400MHz and then divide it to get user selected clock.
 * */
void SysCtr_init(void)
{
    /* set BYPASS high to disable PLL while initialization*/
    RCC2_REG.B.BYPASS2 = true;
    /* Enable using RCC2 register */
    RCC2_REG.B.USERCC2 = true;
    /* if external source is selected MOSCDIS should be cleared which equal OSCR     value*/
    RCC_REG.B.MOSCDIS = ((str_sysCtlCfg.u8_clockSource >> 1)
            | (str_sysCtlCfg.u8_clockSource));

    /* specify the source of clock if external, internal 16Mhz, internal 16MHz /4 or lower frequency*/
    RCC2_REG.B.OSCSRC2 = str_sysCtlCfg.u8_clockSource;

    if ((str_sysCtlCfg.u8_clockSource == MOSC) || (str_sysCtlCfg.u8_clockSource == PIOSC))
    {
        /* specify the value of crystal osc.freq. */
        RCC_REG.B.XTAL = str_sysCtlCfg.u8_crystalFreq;
        /* enable using divisor */
        RCC_REG.B.USESYSDIV = true;
        /* power up the PLL */
        RCC2_REG.B.PWRDN2 = false;
        /* disable divide the PLL output by 2 to get 400 MHz*/
        RCC2_REG.B.DIV400 = true;
        /* get the required value to set in SYSDIV field from look up table
         * to achieve selected CLK from configuration*/
        RCC2_REG.B.SYSDIV2 = gsau8_freqLookUpTable[str_sysCtlCfg.u8_sysClkFreq];
        /* wait until PLL initialized successfully  */
        while (!RIS_PLLLRIS)
        {
        }
        /* enable the PLL bus after ensure that its initialized */
        RCC2_REG.B.BYPASS2 = false;
    }
    else
    {
        /* Do Nothing */
    }

}

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
void SysCtr_prepheralClkEnable(uint16 u16_peripheral)
{
    /* use bit banding theory to get the bit address then set it by true to enable clock */
    BIT_BAND_ACCESS(RCGCBASE_ADDR + ((u16_peripheral)>>EIGHT)
            , (u16_peripheral & 0x00ff)) = true;

}

/**
 * Function: SysCtr_getSysClockFreq
 * @return: the actual value of the clock frequency by KHz
 * Description: function get the actual value of clk frequency by mapping SYSDIV2 field by look up table.
 */
uint32 SysCtr_getSysClockFreq(void)
{
    return gsau32_freqValues[RCC2_REG.B.SYSDIV2];
}



