/*
 * tester.h
 *
 * Created: 3/13/2020 9:21:04 AM
 *  Author: mahmo
 */ 


#ifndef TESTER_H_
#define TESTER_H_
#include <stdio.h>
#include "../../common_macros.h"
#include "../../std_types.h"
#include "../../HAL/UltraSonic/ultraSonic.h"
#include "stubFunction.h"
#include "../TMU_test/TMU_test.h"
#include "../SOS_test/SOS_test.h"
#include "../Us_test/UltraSonic_test.h"
#include "../BCM_test/BCM_test.h"
#include "../SPI_test/SPI_test.h"
#define TEST_PARAMTER		0
#define EXPECTED_RETURN		1
#define TEST_PARAMTER_AND_RET_VALUE	2


void checkTestCase(sint16_t s16_expected_return , sint16_t s16_fun_return,uint8_t * u8_testCaseNumber);
void compareValue(sint16_t s16_expected_value , sint16_t s16_return_value,uint8_t * u8_testCaseNumber);

void parameter_test2(sint16_t as16_testParamter[][TEST_PARAMTER_AND_RET_VALUE],uint8_t u8_size ,ERROR_STATUS (*callB_fun)(sint16_t),sint16_t s16_startValue,
sint16_t s16_endValue,sint16_t s16_SamplesNum, sint16_t ERROR_VALUE ,uint8_t u8_useSamplesFlag,uint8_t * u8_testCaseNumber);

void parameter_test(uint8_t* u8_testParamterValues,uint8_t u8_size ,ERROR_STATUS (*callB_fun)(uint8_t), sint16_t ERROR_VALUE,uint8_t * u8_testCaseNumber);
void test();
#endif /* TESTER_H_ */