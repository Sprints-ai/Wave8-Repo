/*Author : Ahmed Salama
*/

#include "MCU_hw.h"


str_NVIC volatile *NVIC = (str_NVIC *) NVIC_BASE;
str_SCB volatile *SCB = (str_SCB *) SCB_BASE;
str_Systick volatile *SYSTICK = (str_Systick *) SYSTICK_BASE;
