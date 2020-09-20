/*
 * motorconfig.h
 *
 * Created: 2/18/2020 10:05:02 AM
 *  Author: MENA
 */ 


#ifndef MOTORCONFIG_H_
#define MOTORCONFIG_H_


#include "DIO.h"
#include "registers.h"

#define MOTOR_EN_1_GPIO		(GPIOD)
#define MOTOR_EN_1_BIT		(BIT4)

#define MOTOR_OUT_1A_GPIO	(GPIOD)
#define MOTOR_OUT_1B_GPIO	(GPIOD)
#define MOTOR_OUT_1A_BIT	(BIT3)
#define MOTOR_OUT_1B_BIT	(BIT2)


#define MOTOR_EN_2_GPIO		(GPIOD)
#define MOTOR_EN_2_BIT		(BIT5)

#define MOTOR_OUT_2A_GPIO	(GPIOD)
#define MOTOR_OUT_2B_GPIO	(GPIOD)
#define MOTOR_OUT_2A_BIT	(BIT6)
#define MOTOR_OUT_2B_BIT	(BIT7)

#endif /* MOTORCONFIG_H_ */