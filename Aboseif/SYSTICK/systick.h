/*
 * systick.h
 *
 * Created: 2020-04-03 12:20:42 AM
 *  Author: EbrahimOseif
 */


#ifndef __SYSTICK_H__
#define __SYSTICK_H__


/******************************************************************/
/*					General macros								  */
/******************************************************************/

#define SYSTICK_BASE_ADDRESS			0xE000E010

#define SYSTICK_ENABLE					1
#define SYSTICK_ENABLE_INT     			2
#define SYSTICK_CLK_SRC_SYS				4
#define SYSTICK_CLK_SRC_PIOSC_DIV4		0
#define SYSTICK_CLK_KHZ    			    16000


/******************************************************************/
/*					SystemTick used data types					  */
/******************************************************************/

/*SystemTick registers*/

typedef struct
{
	uint32_t SYSTICK_CTRL;
	uint32_t SYSTICK_RELOAD;
	uint32_t SYSTICK_CURRENT;
	
}ST_SYSTICK_TYPE;

/*Pointer tp the struct first location*/

#define SYSTICK_REG		((volatile ST_SYSTICK_TYPE*)(SYSTICK_BASE_ADDRESS))

/******************************************************************/
/*						 functions' prototypes					  */
/******************************************************************/

void SYSTICK_init(uint32_t au32_Ms_Counts);

void SYSTICK_setCallBack(void (*pcallback)(void));

#endif