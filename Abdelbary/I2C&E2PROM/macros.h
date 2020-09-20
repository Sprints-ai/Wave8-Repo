
/**
* @file macros.h
* @brief set and clear macros and get high nibble and low nibble .  
* @author Islam Mohamed.
*/

#ifndef _MACROS_H
#define _MACROS_H

#include "std_types.h"


#define FCPU	  16000000UL
#define  ZERO     0
#define	 ONE	  1
#define  NEW_LINE	0x0D
#define SET_BIT(number,bit)			((number)|=((1)<<(bit)))
#define CLEAR_BIT(number,bit)		((number)&=(~((1)<<(bit))))
#define TOGGLE(number,bit)			((number) ^ ((1)<<(bit)))
#define SET_MASK(number,Mask)       ((number)|=(Mask))
#define CLEAR_MASK(number,Mask)     ((number)&=(~(Mask)))
#define TOGGLE_MASK(number,Mask)    ((number) ^= (Mask))
#define BIT_IS_SET(number,bit)  ((number)&(1<<(bit)))
#define BIT_IS_CLEARD(number,bit)   (!((number)&(1<<(bit))))
#define MASK_IS_SET(number,mask)	((number)&(mask))

#define HIGH_NIBBLE(hVar,var) hVar= (var & 0xf0) >> 4  // hVar will hold value of high nibble of var

#define LOW_NIBBLE(lVar,var) lVar= (var & 0x0f) // lVar will hold the value of low nibble of var
 
#define CLR_BIT(var, bit) var &= (~(1<<bit))


#define TOG_BIT(var, bit) var ^= (1<<bit)

#endif 

