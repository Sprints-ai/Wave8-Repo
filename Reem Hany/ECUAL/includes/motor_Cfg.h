/*
 * motor_Cfg.h
 *
 * Created: 2/17/2020 11:35:27 PM
 *  Author: Reem
 */ 


#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_
#include "../../MCAL/includes/DIO.h"

/*********************************************
 	       Motor1 Configuration  			 *
 ********************************************/

#define MOTOR1_EN_PORT GPIOD
#define MOTOR1_EN_PIN  BIT5

/*********************************************
 	       Motor2 Configuration  			 *
 ********************************************/

#define MOTOR2_EN_PORT GPIOD
#define MOTOR2_EN_PIN  BIT4

/*********************************************
 	   Motor1 Directions Configuration  	 *
 ********************************************/

#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)
#define MOTOR_OUT_1A_BIT	(BIT2)
#define MOTOR_OUT_1B_BIT	(BIT3)


/*********************************************
 	   Motor2 Directions Configuration  	 *
 ********************************************/

#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)
#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)


#endif /* MOTOR_CFG_H_ */