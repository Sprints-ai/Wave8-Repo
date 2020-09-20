/*
 * SPI_test.h
 *
 * Created: 3/24/2020 10:58:40 PM
 *  Author: mahmo
 */ 


#ifndef SPI_TEST_H_
#define SPI_TEST_H_
#include "../Tester/stubFunction.h"
#include "../Tester/tester.h"
#include "../../MCAL/Communication/SPI/spi.h"

void SPI_Module_Test(void);
void SPI_init_test(void);
void spi_enable_test(void);
void SPI_sendData_test(void);
void SPI_getData_test(void);


#endif /* SPI_TEST_H_ */