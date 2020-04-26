#ifndef __NVIC_H__
#define __NVIC_H__

/******************************************************************/
/*					General macros								  */
/******************************************************************/

#define NVIC_REG_BYTES		4
#define NVIC_PRI_BYTES		35
#define NVIC_BASE_ADDRESS	0xE000E100

/******************************************************************/
/*					NVIC used data types						  */
/******************************************************************/

/*NVIC registers*/
typedef struct
{
	uint32_t EN_ARR[NVIC_REG_BYTES];
	uint32_t DIS_ARR[NVIC_REG_BYTES];
	uint32_t PEND_ARR[NVIC_REG_BYTES];
	uint32_t UPEND_ARR[NVIC_REG_BYTES];
	uint32_t ACTIVE_ARR[NVIC_REG_BYTES];
	uint32_t PRI_ARR[NVIC_PRI_BYTES];
}ST_NVIC_TYPE;

/*Pointer tp the struct first location*/
#define NVIC_REG		((volatile ST_NVIC_TYPE*)(NVIC_BASE_ADDRESS))

/******************************************************************/
/*					NVIC functions' prototypes					  */
/******************************************************************/

/*
 *	Description: Enables certain interrupt in NVIC.
 *  @param(IN) : ID of the interrupt to be enabled
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void NVIC_EnableInt(uint8_t au8_intID);

/*
 *	Description: Disables certain interrupt in NVIC.
 *  @param(IN) : ID of the interrupt to be disabled
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void NVIC_DisableInt(uint8_t au8_intID);

/*
 *	Description: Changes certain interrupt in NVIC mode from unpending to pending.
 *  @param(IN) : ID of the interrupt to be pended
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void NVIC_PendInt(uint8_t au8_intID);

/*
 *	Description: Changes certain interrupt in NVIC mode from pending to unpending.
 *  @param(IN) : ID of the interrupt to be unpended
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void NVIC_UnPendInt(uint8_t au8_intID);

/*
 *	Description: Set certain interrupt priority.
 *  @param(IN) : ID of the interrupt
 * 				 Priority of the interrupt (0[Highest] to 7[Lowest])
 * 	@param(OUT): N/A
 *  @param(I/O): N/A
 *  @ret: N/A
 */
void NVIC_SetIntPriority(uint8_t au8_intID , uint8_t au8_intPriority);

#endif
