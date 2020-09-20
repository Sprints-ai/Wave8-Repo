/*
 * stubFunction.h
 *
 * Created: 3/13/2020 12:09:01 PM
 *  Author: mahmo
 */ 


#ifndef STUBFUNCTION_H_
#define STUBFUNCTION_H_
#include "tester.h"
#include "../../MCAL/Timers/Timer.h"
#include "../../HAL/UltraSonic/ultraSonic.h"
#include "../../MCAL/Communication/UART/uart.h"
#include "../../MCAL/Communication/SPI/spi.h"
extern  sint16_t gu8_Timer_Init_fun_status;
extern  sint16_t gu8_Timer_Start_fun_status;
extern  sint16_t gu8_Timer_DeInit_status;

#ifndef GCC
/*declare fun as weak to avoid multiple definition by linker*/
ERROR_STATUS    Timer_Init(Timer_cfg_s* Timer_cfg)__attribute__((weak)) ;
ERROR_STATUS	Timer_Start(uint8_t Timer_CH_NO, uint16_t Timer_Count)__attribute__((weak));
ERROR_STATUS	Timer_DeInit(uint8_t timer_Ch)__attribute__((weak));
#endif



#endif /* STUBFUNCTION_H_ */