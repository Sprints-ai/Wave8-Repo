/*
 * common_Macros.h
 *
 * Created: 2/17/2020 1:39:17 PM
 *  Author: Reem
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(Reg,bit_no)				Reg |=		 (1<<bit_no)
#define CLR_BIT(Reg,bit_no)				Reg &=		~(1<<bit_no)
#define TOGGLE_BIT(Reg,bit_no)			Reg ^=		 (1<<bit_no)

#define SET_BIT_MASK(Reg,bit_mask)		Reg |=		 (bit_mask)
#define CLR_BIT_MASK(Reg,bit_mask)		Reg &=		~(bit_mask)
#define TOGGLE_BIT_MASK(Reg,bit_mask)	Reg ^=		 (bit_mask)
#define GET_BIT(Reg,pin_)				(Reg & pin_)

#define SET_NIBBLE_HIGH(Reg)            Reg |=        0b11110000
#define CLR_NIBBLE_HIGH(Reg)            Reg &=        0b00001111
#define TOGGLE_NIBBLE_HIGH(Reg)         Reg ^=        0b11110000


#define SET_NIBBLE_LOW(Reg)             Reg |=        0b00001111
#define CLR_NIBBLE_LOW(Reg)             Reg &=        0b11110000
#define TOGGLE_NIBBLE_LOW(Reg)          Reg ^=        0b00001111

#define GET_NIBBLE_LOW(Reg)	            Reg & 0b00001111
#define GET_NIBBLE_HIGH(Reg)	       (Reg & 0b11110000)>>4


#endif /* COMMON_MACROS_H_ */