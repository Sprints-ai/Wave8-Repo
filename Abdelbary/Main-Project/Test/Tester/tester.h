/*
 * tester.h
 *
 * Created: 3/13/2020 9:21:04 AM
 *  Author: mahmo
 */ 


#ifndef TESTER_H_
#define TESTER_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../common_macros.h"
#include "../../std_types.h"
#include "stubFunction.h"
#include "../../ServiceLayer/Error_Handler/SystemErrors.h"

#define TEST_PARAMTER		0
#define EXPECTED_RETURN		1
#define TEST_PARAMTER_AND_RET_VALUE	2


#define TEST_PANAR_HEADER	0
#define TEST_PANAR_FOOTER	1
#define TEST_PANAR_FUN_NAME	2
#define MAX_LINE_SIZE       100
#define MAX_TEST            100
#define MAX_PARAMTER_SIZE   50
#define TEST_CBF_NAME		0
#define TEST_CBF_ADD		1
#define TOTAL_PAD			30

typedef ERROR_STATUS(*CBF)(sint16_t);
typedef struct gstr_testFunPtr
{
	const char* pu8_funName;
	CBF		 testFunCallback_t; /* in milesec */
}gstr_testFunPtr_t;


int testModule(const char * u8_filePath,gstr_testFunPtr_t gstr_testFunPtr[],uint8_t u8_CBF_arraySize,uint8_t* u8_testCaseCounter);
void PrintHeader(uint8_t* u8_buffer,uint8_t u8_type);

void checkTestCase(sint16_t s16_expected_return , sint16_t s16_fun_return,uint8_t * u8_testCaseNumber);
void compareValue(sint16_t s16_expected_value , sint16_t s16_return_value,uint8_t * u8_testCaseNumber);

void parameter_test2(sint16_t as16_testParamter[][TEST_PARAMTER_AND_RET_VALUE],uint8_t u8_size ,ERROR_STATUS (*callB_fun)(sint16_t),sint16_t s16_startValue,
sint16_t s16_endValue,sint16_t s16_SamplesNum, sint16_t ERROR_VALUE ,uint8_t u8_useSamplesFlag,uint8_t * u8_testCaseNumber);

void parameter_test(uint8_t* u8_testParamterValues,uint8_t u8_size ,ERROR_STATUS (*callB_fun)(uint8_t), sint16_t ERROR_VALUE,uint8_t * u8_testCaseNumber);
void test();

#endif /* TESTER_H_ */