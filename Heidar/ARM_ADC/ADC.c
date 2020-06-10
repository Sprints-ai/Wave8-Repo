/*
 * ADC.c
 *
 *      Author: Abdallah Heidar
 */

#include "std_types.h"
#include "ADC.h"

uint8_t gu8_ainVar = 0;
uint8_t gu8_adcBlock = 0; 

EnmADCError_t  ADC_Init(uint8_t au8_adcBlock , uint8_t au8_inputAnalogPin)
{
    EnmADCError_t err_var = ADC_INIT_SUCCESS;
    if( (au8_inputAnalogPin <= ADC_AIN11) && (au8_adcBlock == ADC_BLOCK0 || au8_adcBlock == ADC_BLOCK1) )
    {
        RCC_REG = ENABLE_PLL_SYSDIV_BY_16_DISABLE_MAIN_OSC;
        RCGCGPIO_REG = ENABLE_GPIO_CLK;
        switch (au8_inputAnalogPin)
        {
            case ADC_AIN0:
                SET_BIT(GPIOE_AFSEL_REG, AIN0_PE3);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN0_PE3);
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN0_PE3);
                gu8_ainVar = ADC_AIN0;                  
                break;
            case ADC_AIN1:
                SET_BIT(GPIOE_AFSEL_REG, AIN1_PE2);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN1_PE2);
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN1_PE2);
                gu8_ainVar = ADC_AIN1;                
                break;
            case ADC_AIN2:
                SET_BIT(GPIOE_AFSEL_REG, AIN2_PE1);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN2_PE1);
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN2_PE1);
                gu8_ainVar = ADC_AIN2;                
                break;
            case ADC_AIN3:
                SET_BIT(GPIOE_AFSEL_REG, AIN3_PE0);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN3_PE0); 
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN3_PE0);
                gu8_ainVar = ADC_AIN3;               
                break;
            case ADC_AIN4:
                SET_BIT(GPIOD_AFSEL_REG, AIN4_PD3);
                CLEAR_BIT(GPIOD_GPIODEN_REG, AIN4_PD3);
                SET_BIT(GPIOD_GPIOAMSEL_REG, AIN4_PD3);
                gu8_ainVar = ADC_AIN4;                
                break;
            case ADC_AIN5:
                SET_BIT(GPIOD_AFSEL_REG, AIN5_PD2);
                CLEAR_BIT(GPIOD_GPIODEN_REG, AIN5_PD2);
                SET_BIT(GPIOD_GPIOAMSEL_REG, AIN5_PD2);
                gu8_ainVar = ADC_AIN5;                                
                break;
            case ADC_AIN6:
                SET_BIT(GPIOD_AFSEL_REG, AIN6_PD1);
                CLEAR_BIT(GPIOD_GPIODEN_REG, AIN6_PD1);
                SET_BIT(GPIOD_GPIOAMSEL_REG, AIN6_PD1);
                gu8_ainVar = ADC_AIN6;                                
                break;
            case ADC_AIN7:
                SET_BIT(GPIOD_AFSEL_REG, AIN7_PD0);
                CLEAR_BIT(GPIOD_GPIODEN_REG, AIN7_PD0);
                SET_BIT(GPIOD_GPIOAMSEL_REG, AIN7_PD0);
                gu8_ainVar = ADC_AIN7;                                
                break;
            case ADC_AIN8:
                SET_BIT(GPIOE_AFSEL_REG, AIN8_PE5);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN8_PE5);
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN8_PE5);
                gu8_ainVar = ADC_AIN8;                                
                break;
            case ADC_AIN9:
                SET_BIT(GPIOE_AFSEL_REG, AIN9_PE4);
                CLEAR_BIT(GPIOE_GPIODEN_REG, AIN9_PE4);
                SET_BIT(GPIOE_GPIOAMSEL_REG, AIN9_PE4);
                gu8_ainVar = ADC_AIN9;                                
                break;
            case ADC_AIN10:
                SET_BIT(GPIOB_AFSEL_REG, AIN10_PB4);
                CLEAR_BIT(GPIOB_GPIODEN_REG, AIN10_PB4);
                SET_BIT(GPIOB_GPIOAMSEL_REG, AIN10_PB4);
                gu8_ainVar = ADC_AIN10;                                
                break;
            case ADC_AIN11:
                SET_BIT(GPIOB_AFSEL_REG, AIN11_PB5);
                CLEAR_BIT(GPIOB_GPIODEN_REG, AIN11_PB5);
                SET_BIT(GPIOB_GPIOAMSEL_REG, AIN11_PB5);
                gu8_ainVar = ADC_AIN11;                                                
                break;
            default:
                /* TODO */
                break;
        }

        switch (au8_adcBlock)
        {
            case ADC_BLOCK0:
                SET_BIT(RCGADC_REG , ADC_BLOCK0_BIT0);
                ADC0_INPUT_CTRL_REG -> ADCACTSS  = 0;
                ADC0_INPUT_CTRL_REG -> ADCEMUX   = 0;
                ADC0_INPUT_CTRL_REG -> ADCSSMUX0 = gu8_ainVar;
                ADC0_INPUT_CTRL_REG -> ADCACTSS  = ENABLE_SEQUENCER0;
                gu8_adcBlock = ADC_BLOCK0;  
                break;
            case ADC_BLOCK1:
                SET_BIT(RCGADC_REG , ADC_BLOCK1_BIT1);
                ADC1_INPUT_CTRL_REG -> ADCACTSS = 0;
                ADC1_INPUT_CTRL_REG -> ADCEMUX  = 0;
                ADC1_INPUT_CTRL_REG -> ADCSSMUX0 = gu8_ainVar;
                ADC1_INPUT_CTRL_REG -> ADCACTSS  = ENABLE_SEQUENCER0;
                gu8_adcBlock = ADC_BLOCK1;                
                break;
            default:
                /* TODO */
                break;    
        }
    }
    else
    {
        err_var = ADC_INIT_FAILED;
    }

    return err_var;
}

EnmADCError_t  ADC_readValue(uint16_t* pu16_adcValue)
{
    EnmADCError_t err_var = ADC_OPERATION_SUCCESS;
    
    if(pu16_adcValue == NULL)
    {
        err_var = ADC_PASSING_NULL_PTR;
    }
    else
    {
        if(gu8_adcBlock == ADC_BLOCK0)
        {
            if( GET_BIT((ADC0_INPUT_CTRL_REG -> ADCACTSS), ADC_BUSY_BIT) )
            {
               err_var = ADC_BUSY; 
            }
            else
            {
                ADC0_INPUT_CTRL_REG -> ADCPSSI = SEQUENCER0_BEGIN;
                while(GET_BIT((ADC0_INPUT_CTRL_REG -> ADCACTSS), ADC_BUSY_BIT));
                *pu16_adcValue = ADC0_INPUT_CTRL_REG -> ADCSSFIFO0;
            }
        }
        else if(gu8_adcBlock == ADC_BLOCK1)
        {
            if( GET_BIT((ADC1_INPUT_CTRL_REG -> ADCACTSS), ADC_BUSY_BIT) )
            {
               err_var = ADC_BUSY; 
            }
            else
            {
                ADC1_INPUT_CTRL_REG -> ADCPSSI = SEQUENCER0_BEGIN;
                while(GET_BIT((ADC1_INPUT_CTRL_REG -> ADCACTSS) , ADC_BUSY_BIT));
                *pu16_adcValue = ADC1_INPUT_CTRL_REG -> ADCSSFIFO0;
            }            
        }
        else
        {
            err_var = ADC_BLOCK_NOT_VALID;
        }
    }
    return err_var;
}
