#ifndef __SYSTEM_TICK_H__
#define __SYSTEM_TICK_H__

/******************************************************************/
/*					General macros								  */
/******************************************************************/

#define SYSTICK_BASE_ADDRESS	0xE000E010

/******************************************************************/
/*					SystemTick used data types					  */
/******************************************************************/

/*SystemTick registers*/
typedef struct
{
	uint32_t STCTRL;
	uint32_t STRELOAD;
	uint32_t STCURRENT;
}ST_SYSTICK_TYPE;

/*Pointer tp the struct first location*/
#define STCK_REG		((volatile ST_SYSTICK_TYPE*)(SYSTICK_BASE_ADDRESS))

/******************************************************************/
/*					SystemTick functions' prototypes			  */
/******************************************************************/

/*
 *	Description: Initializes system tick module.
 *  @param(IN) : System timer tick time in milliseconds 
 *               (single tick time = (1/FCLK) in seconds)
 *               (Minimum  time in ms = 0 * single tick time || Maximum time in ms = ((2^24)-1) * single tick time)
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void STICK_init(uint32_t au32_tickTimeMs);

/*
 *	Description: Set call back function to System tick interrupt.
 *  @param(IN) : Pointer to call back function
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void STICK_setCallBack(void (*pcallback)(void));

#endif
