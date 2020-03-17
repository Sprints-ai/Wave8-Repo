/*
 * IdealPushButton.h
 *
 * Created: 3/16/2020 3:15:50 PM
 *  Author: ema
 */ 

#include "../Infrastructure/std_types.h"

#define IPB_EXTI_INT0	0
#define IPB_EXTI_INT1	1
#define IPB_EXTI_INT2	2

#define IPB_0_PRESSED	0
#define IPB_1_PRESSED	1
#define IPB_2_PRESSED	2

#define IPB_0_RELEASED	3
#define IPB_1_RELEASED	4
#define IPB_2_RELEASED	5

typedef struct str_IPB_Config {
	
	uint8_t u8_EXTI_Channel;
	
	}str_IPB_Config;

ERROR_STATUS IdealPushButton_Init (str_IPB_Config* IPB_Config);

ERROR_STATUS IdealPushButton_GetStatus (uint8_t* u8_Status);