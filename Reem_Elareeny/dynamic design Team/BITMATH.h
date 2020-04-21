/*
 * BITMATH.h
 *
 * Created: 1/30/2020 12:42:28 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_

#define SET_BIT(VAR,BITNO)			  VAR|= (1<<BITNO)

#define CLR_BIT(VAR,BITNO)			  VAR&=~(1<<BITNO)

#define TOG_BIT(VAR,BITNO)  		  VAR^= (1<<BITNO)

#define GET_BIT(VAR,BITNO) 			  ((VAR>>BITNO)&0x01)

#define ASSIGN_BIT(VAR,BITNO,VAL)	  VAR =(VAR&(~(1<<BITNO))) | (VAL<<BITNO)

#endif /* BITMATH_H_ */