/*
 * UltraSonic_test.h
 *
 * Created: 2/22/2020 5:18:51 PM
 *  Author: mahmo
 */ 


#ifndef ULTRASONIC_TEST_H_
#define ULTRASONIC_TEST_H_

#include <stdio.h>
#include "../../common_macros.h"
#include "../../std_types.h"
#include "../../HAL/UltraSonic/ultraSonic.h"


void US_Init_test(void);
void Us_Trigger_test(void);
void Us_Module_Test(void);
void Us_GetDistance_Test(void);
#endif /* ULTRASONIC_TEST_H_ */