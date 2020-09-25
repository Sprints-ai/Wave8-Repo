/*
 * Motor_cfg.h
 *  Author: Ahmed Ashraf
 *  Version: 1.0 
 */ 

#ifndef __MOTOR_CFG_H__
#define __MOTOR_CFG_H__

/************************************************************************/
/*                             Motors port configuration                */
/************************************************************************/
#define		MOTOR1_GPIO_PORT		(GPIOD)
#define		MOTOR1_GPIO_PINA		(PIN2)
#define		MOTOR1_GPIO_PINB		(PIN3)

#define		MOTOR1_GPIO_EN_PORT		(GPIOD)
#define		MOTOR1_GPIO_EN_PIN		(PIN4)
#define		MOTOR1_PWM_CHANNEL		(PWM_CH1)
#define		MOTOR1_PWM_FREQ			(PWM_30HZ_FREQ)

#define		MOTOR2_GPIO_EN_PORT		(GPIOD)
#define		MOTOR2_GPIO_EN_PIN		(PIN5)
#define		MOTOR2_PWM_CHANNEL		(PWM_CH2)
#define		MOTOR2_PWM_FREQ			(PWM_30HZ_FREQ)


#define		MOTOR2_GPIO_PORT		(GPIOD)
#define		MOTOR2_GPIO_PINA		(PIN6)
#define		MOTOR2_GPIO_PINB		(PIN7)

#endif /*__MOTOR_CFG_H__*/		