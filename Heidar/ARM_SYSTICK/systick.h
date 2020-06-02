/*
 * systick.h
 *
 *      Author: Abdallah Heidar
 */

#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#define SYSTICK_BASE_ADDRESS				0xE000E010

#define SYSTICK_ENABLE						1
#define SYSTICK_ENABLE_INT     				2
#define SYSTICK_CLK_SRC_SYS					4
#define SYSTICK_CLK_SRC_PIOSC_DIV4			0
#define SYSTICK_CLK_KHZ    			   	 	16000

typedef struct
{
	uint32_t SYSTICK_CTRL;
	uint32_t SYSTICK_RELOAD;
	uint32_t SYSTICK_CURRENT;
}ST_SYSTICK_TYPE;

#define SYSTICK_REG		((volatile ST_SYSTICK_TYPE*)(SYSTICK_BASE_ADDRESS))

void SYSTICK_Init(uint32_t au32_msCounts);
void SYSTICK_setCallBack(void (*pCallback)(void));

#endif