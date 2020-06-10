/*
 * ADC.h
 *
 *      Author: Abdallah Heidar
 */

#define SET_BIT(REG,BIT)			REG |= (1<<BIT)
#define CLEAR_BIT(REG,BIT)			REG &= ~(1<<BIT)
#define TOGGLE_BIT(REG,BIT)			REG ^= (1<<BIT)
#define GET_BIT(REG,BIT)			((REG >> BIT) & 0x01)

typedef struct
{
    uint32_t ADCACTSS;
    uint32_t ADCRIS;
    uint32_t ADCIM;
    uint32_t ADCISC;
    uint32_t ADCOSTAT;
    uint32_t ADCEMUX;
    uint32_t ADCUSTAT;
    uint32_t ADCTSSEL;
    uint32_t ADCSSPRI;
    uint32_t ADCSPC;
    uint32_t ADCPSSI;

    uint32_t byte_4_gap0;
    uint32_t byte_4_gap1;

    uint32_t ADCSAC;
    uint32_t ADCDCISC;
    uint32_t ADCCTL;

    uint32_t byte_4_gap2;
    uint32_t byte_4_gap3;

    uint32_t ADCSSMUX0;
    uint32_t ADCSSCTL0;
    uint32_t ADCSSFIFO0;
    uint32_t ADCSSFSTAT0;
    uint32_t ADCSSOP0;
    uint32_t ADCSSDC0;

    uint32_t byte_4_gap4;
    uint32_t byte_4_gap5;
    uint32_t byte_4_gap6;

    uint32_t ADCSSMUX1;
    uint32_t ADCSSCTL1;
    uint32_t ADCSSFIFO1;
    uint32_t ADCSSFSTAT1;
    uint32_t ADCSSOP1;
    uint32_t ADCSSDC1;

    uint32_t byte_4_gap7;
    uint32_t byte_4_gap8;
    uint32_t byte_4_gap9;

    uint32_t ADCSSMUX2;
    uint32_t ADCSSCTL2;
    uint32_t ADCSSFIFO2;
    uint32_t ADCSSFSTAT2;
    uint32_t ADCSSOP2;
    uint32_t ADCSSDC2;

    uint32_t byte_4_gap10;
    uint32_t byte_4_gap11;
    uint32_t byte_4_gap12;

    uint32_t ADCSSMUX3;
    uint32_t ADCSSCTL3;
    uint32_t ADCSSFIFO3;
    uint32_t ADCSSFSTAT3;
    uint32_t ADCSSOP3;
    uint32_t ADCSSDC3;
}ADC_inputCtrl_cfg;

typedef struct
{
    uint32_t ADCPP;
    uint32_t ADCPC;
    uint32_t ADCCC;
}ADC_peripheralCtrl_cfg;

#define ADC0_INPUT_CTRL_REG       ((volatile ADC_inputCtrl_cfg*)(0x40038000))
#define ADC1_INPUT_CTRL_REG       ((volatile ADC_inputCtrl_cfg*)(0x40039000))

#define ADC0_PERIPHERAL_CTRL_REG  ((volatile ADC_peripheralCtrl_cfg*)(0x40038FC0))
#define ADC1_PERIPHERAL_CTRL_REG  ((volatile ADC_peripheralCtrl_cfg*)(0x40039FC0))

#define RCC_REG                   (*(volatile uint32_t*)(0x400FE060))                  

#define RCGADC_REG                (*(volatile uint32_t*)(0x400FE638))

#define RCGCGPIO_REG              (*(volatile uint32_t*)(0x400FE608))   

#define GPIOB_AFSEL_REG           (*(volatile uint32_t*)(0x40059420))

#define GPIOD_AFSEL_REG           (*(volatile uint32_t*)(0x4005B420))

#define GPIOE_AFSEL_REG           (*(volatile uint32_t*)(0x4005C420))

#define GPIOB_GPIODEN_REG         (*(volatile uint32_t*)(0x4005951C))

#define GPIOD_GPIODEN_REG         (*(volatile uint32_t*)(0x4005B51C))

#define GPIOE_GPIODEN_REG         (*(volatile uint32_t*)(0x4005C51C))

#define GPIOB_GPIOAMSEL_REG       (*(volatile uint32_t*)(0x40059528))

#define GPIOD_GPIOAMSEL_REG       (*(volatile uint32_t*)(0x4005B528))

#define GPIOE_GPIOAMSEL_REG       (*(volatile uint32_t*)(0x4005C528))

#define ENABLE_PLL_SYSDIV_BY_16_DISABLE_MAIN_OSC        (0x07C00001)

#define ENABLE_GPIO_CLK                                 (0x0000001A)

#define ENABLE_SEQUENCER0                               (1)

#define SEQUENCER0_BEGIN                                (1) 

#define ADC_BUSY_BIT                                    (16)

typedef sint8_t EnmADCError_t;
#define ADC_INIT_SUCCESS       (-1)
#define ADC_INIT_FAILED        (-2)
#define ADC_OPERATION_SUCCESS  (-3)
#define ADC_PASSING_NULL_PTR   (-4)
#define ADC_BUSY               (-5)
#define ADC_BLOCK_NOT_VALID    (-6)

#define ADC_BLOCK0             (0)
#define ADC_BLOCK1             (1)

#define ADC_BLOCK0_BIT0        (0)
#define ADC_BLOCK1_BIT1        (1)

#define ADC_AIN0               (0)
#define ADC_AIN1               (1)
#define ADC_AIN2               (2)
#define ADC_AIN3               (3)
#define ADC_AIN4               (4)
#define ADC_AIN5               (5)
#define ADC_AIN6               (6)
#define ADC_AIN7               (7)
#define ADC_AIN8               (8)
#define ADC_AIN9               (9)
#define ADC_AIN10              (10)
#define ADC_AIN11              (11)

#define AIN0_PE3               (3)
#define AIN1_PE2               (2)
#define AIN2_PE1               (1)
#define AIN3_PE0               (0)
#define AIN4_PD3               (3)
#define AIN5_PD2               (2)
#define AIN6_PD1               (1)
#define AIN7_PD0               (0)
#define AIN8_PE5               (5)
#define AIN9_PE4               (4)
#define AIN10_PB4              (4)
#define AIN11_PB5              (5)


/*
 * @param: Initializes the ADC module.
 * @param(IN) : The choosen ADC block to be used.
 *              The choosen AIN pin to read the analog value from it.
 * @return: ADC error status.
 */
EnmADCError_t  ADC_Init(uint8_t au8_adcBlock , uint8_t au8_inputAnalogPin);

/*
 * @param: Gets the converted analog value into digital value.
 * @param(OUT): Pointer to u16 variable which will hold the converted value.
 * @return: ADC error status.
 */
EnmADCError_t  ADC_readValue(uint16_t* pu16_adcValue);