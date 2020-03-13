/*
 * SOS_test.h
 *
 * Created: 2/25/2020 3:23:51 PM
 *  Author: mahmo
 */ 


#ifndef SOS_TEST_H_
#define SOS_TEST_H_

#include "../Tester/tester.h"
#include "..\..\ServiceLayer\SOS\SOS.h"
#include "../tester/stubFunction.h"

void    SOS_Init_test();
void	SOS_start_test(void);
void	SOS_deletTask_test(void);
void	SOS_dispatcher_test(void);
void	SOS_DeInit_test(void);
void    SOS_Module_run_test(void);


#endif /* SOS_TEST_H_ */