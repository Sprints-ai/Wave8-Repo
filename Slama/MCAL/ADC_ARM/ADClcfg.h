/*
 * ADClcfg.h
 *
 *  Created on: Apr 26, 2020
 *      Author: ahmed
 */

#ifndef MCAL_ADCLCFG_H_
#define MCAL_ADCLCFG_H_

/*Includes*/
#include "./SERVICES/std_types.h"
#include "PerRegs.h"

/*ADC_MACROS*/

/*ADC_RESET_VALUES*/
#define ADC_RESET_VALUES (0x00000000)

/*Number of channels to be used*/
#define CHANNELS_USED_NUM (1)
#define ADC_USED (1)

/*ADC Modules Defines*/
#define ADC1_CK (1)
#define ADC2_CK (2)
#define ADC3_CK (3)

/*Chnls Macros*/
#define ADC_CHNL_0 (0)
#define ADC_CHNL_1 (1)
#define ADC_CHNL_2 (2)
#define ADC_CHNL_3 (3)
#define ADC_CHNL_4 (4)
#define ADC_CHNL_5 (5)
#define ADC_CHNL_6 (6)
#define ADC_CHNL_7 (7)
#define ADC_CHNL_8 (8)
#define ADC_CHNL_9 (9)
#define ADC_CHNL_10 (10)
#define ADC_CHNL_11 (11)
#define ADC_CHNL_12 (12)
#define ADC_CHNL_13 (13)
#define ADC_CHNL_14 (14)
#define ADC_CHNL_15 (15)
#define ADC_CHNL_16 (16)

/*Resolution Macros*/
#define ADC_CR1_RESOLUTION_SHIFT (24)

#define ADC_CR1_RESOLUTION_12 (0)
#define ADC_CR1_RESOLUTION_10 (1)
#define ADC_CR1_RESOLUTION_8 (2)
#define ADC_CR1_RESOLUTION_6 (3)

/*DISC Mode Macros*/
#define ADC_CR1_DISC_REGULAR_SHIFT (13)

#define ADC_CR1_DISC_1_CHNL (0)
#define ADC_CR1_DISC_2_CHNL (1)
#define ADC_CR1_DISC_3_CHNL (2)
#define ADC_CR1_DISC_4_CHNL (3)
#define ADC_CR1_DISC_5_CHNL (4)
#define ADC_CR1_DISC_6_CHNL (5)
#define ADC_CR1_DISC_7_CHNL (6)
#define ADC_CR1_DISC_8_CHNL (7)


/*DISC Mode Control Macros*/
#define ADC_CR1_DISC_INJECT_SHIFT (12)

#define ADC_CR1_DISC_INJEC_ON (1)
#define ADC_CR1_DISC_INJEC_OFF (0)

/*SCAN Mode Status*/
#define ADC_CR1_SCAN_SHIFT (8)

#define ADC_CR1_SCAN_ON (1)
#define ADC_CR1_SCAN_OFF (0)

/*Interrupt Macros*/
#define ADC_CR1_IRQ_SHIFT (5)

#define ADC_CR1_IRQ_ON (1)
#define ADC_CR1_IRQ_OFF (0)

/*Triggers Polarity*/
#define ADC_CR2_POLARITY_SHIFT (28)

#define ADC_CR2_NO_TRIGGER (0)
#define ADC_CR2_TIGGER_RISING_EDGE (1)
#define ADC_CR2_TIGGER_FALLING_EDGE (2)
#define ADC_CR2_TIGGER_RISINGFALLING_EDGE (3)

/*Software Start*/
#define ADC_CR2_SOFTWARE_SHIFT (30)

#define ADC_CR2_SOFTWARE_START (1)
#define ADC_CR2_NO_SOFTWARE_START (0)

/*External Trigger Source Regular Group*/
#define ADC_CR2_EXSEL_SHIFT (24)

#define ADC_CR2_TRIGGER_TIMER1_CC1 (0)
#define ADC_CR2_TRIGGER_TIMER1_CC2 (1)
#define ADC_CR2_TRIGGER_TIMER1_CC3 (2)
#define ADC_CR2_TRIGGER_TIMER2_CC2 (3)
#define ADC_CR2_TRIGGER_TIMER2_CC3 (4)
#define ADC_CR2_TRIGGER_TIMER2_CC4 (5)
#define ADC_CR2_TRIGGER_TIMER2_TRGO (6)
#define ADC_CR2_TRIGGER_TIMER3_CC1 (7)
#define ADC_CR2_TRIGGER_TIMER3_TRGO (8)
#define ADC_CR2_TRIGGER_TIMER4_CC4 (9)
#define ADC_CR2_TRIGGER_TIMER5_CC1 (10)
#define ADC_CR2_TRIGGER_TIMER5_CC2 (11)
#define ADC_CR2_TRIGGER_TIMER5_CC3 (12)
#define ADC_CR2_TRIGGER_TIMER8_CC1 (13)
#define ADC_CR2_TRIGGER_TIMER8_TRGO (14)
#define ADC_CR2_TRIGGER_EXTI11 (15)

/*Align Macros*/
#define ADC_CR2_ALIGN_SHIFT (11)

#define ADC_CR2_RIGHT_ALIGN (0)
#define ADC_CR2_LEFT_ALIGN (1)

/*Continous macros*/
#define ADC_CR2_CONT_SHIFT (1)

#define ADC_CR2_CONT_MODE (1)
#define ADC_CR2_SINGLE_MODE (0)

/*ADC On/Off*/
#define ADC_CR2_ON_SHIFT (0)

#define ADC_CR2_ON (1)
#define ADC_CR2_OFF (0)

/*Sampling macros*/
#define ADC_SMP_3_CYCLES (0)
#define ADC_SMP_15_CYCLES (1)
#define ADC_SMP_28_CYCLES (2)
#define ADC_SMP_56_CYCLES (3)
#define ADC_SMP_84_CYCLES (4)
#define ADC_SMP_112_CYCLES (5)
#define ADC_SMP_144_CYCLES (6)
#define ADC_SMP_480_CYCLES (7)

/*Alignment Macros*/
#define ADC_CR2_ALIGN_SHIFT (11)

#define ADC_RIGHT_ALIGNMENT (0)
#define ADC_LEFT_ALIGNMENT (1)

/*Length Macros*/
#define ADC_LENGTH_SHIFT (20)

#define ADC_SQR1_1_CONV (0)
#define ADC_SQR1_2_CONV (1)
#define ADC_SQR1_3_CONV (2)
#define ADC_SQR1_4_CONV (3)
#define ADC_SQR1_5_CONV (4)
#define ADC_SQR1_6_CONV (5)
#define ADC_SQR1_7_CONV (6)
#define ADC_SQR1_8_CONV (7)
#define ADC_SQR1_9_CONV (8)
#define ADC_SQR1_10_CONV (9)
#define ADC_SQR1_11_CONV (10)
#define ADC_SQR1_12_CONV (11)
#define ADC_SQR1_13_CONV (12)
#define ADC_SQR1_14_CONV (13)
#define ADC_SQR1_15_CONV (14)
#define ADC_SQR1_16_CONV (15)

/*Continous _ single Mode Macros*/
#define ADC_CONTINOUS_SHIFT (1)

#define ADC_CR2_CONTINOUS_MODE (1)
#define ADC_CR2_SINGLE_MODE (0)

/*ADC Modes Macro*/


/*ADC_Init Struct*/
typedef struct{
uint8_t Chnl_Used[CHANNELS_USED_NUM];
str_ADCCH_t * ADC_Module;
uint8_t ADC_Module_Used_CK;
uint8_t CHnl_Len;
uint8_t ADC_Num;
uint8_t Bit_Alignment:1;
uint8_t Continous_Mode:1;
uint8_t Software_Trig;
uint8_t Scan_Mode;
uint8_t Disc_Mode;
uint8_t Irq_State;
uint8_t Resolution;
uint8_t Sample_Time;
uint8_t Conv_Trigger;
uint8_t Trigger_Polarity;
uint8_t ADC_Mode;
uint8_t Conv_Delay;
}str_ADCCFG_t;

/*array of config Externed*/
extern str_ADCCFG_t ADC_Conf[ADC_USED];

#endif /* MCAL_ADCLCFG_H_ */
