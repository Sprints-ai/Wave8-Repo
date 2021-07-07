/*
 * CFile1.c
 *
 * Created: 10/03/2020 11:58:58 م
 *  Author: TOSHIBA
 */ 
#include "../../Infrastructure/registers.h"
#include "interrupt.h"

void DIS_EN_G_INT(void){
	SREG &= ~(GLOBAL_INTERRUPT_MASK);
}
void EN_G_INT(void){
	SREG |= GLOBAL_INTERRUPT_MASK;
}