/*
 * PWM_Cfg.h
 *
 * Created: 2/17/2020 2:56:16 PM
 *  Author: Reem
 */ 


#ifndef PWM_CFG_H_
#define PWM_CFG_H_

/************************************************/
/*       PWM CHANNEL 1A & 1B Definitions        */
/************************************************/
//Phase correct Mode
#define T1_PHASE_CORRECT_PWM           0X0210

//Clear on match
#define T1_OC1A_CLEAR                  0x8000
#define T1_OC1B_CLEAR                  0x2000

//TIMER 1 Prescales masks
#define T1_PWM_CLK_NO_MASK             0xF8
#define T1_PWM_PRESCALE_NO_MASK        0x0001
#define T1_PWM_PRESCALE_8_MASK         0x0002
#define T1_PWM_PRESCALE_64_MASK        0x0003
#define T1_PWM_PRESCALE_256_MASK       0x0004
#define T1_PWM_PRESCALE_1024_MASK      0x0005

//TIMER 1 Prescales Values
#define T1_PWM_CLK_NO                  0
#define T1_PWM_PRESCALE_NO             1
#define T1_PWM_PRESCALE_8              8
#define T1_PWM_PRESCALE_64             64
#define T1_PWM_PRESCALE_256            256
#define T1_PWM_PRESCALE_1024           1024

#endif /* PWM_CFG_H_ */