/*
 * mymakros.h
 *
 * Created: 20-Jan-20 4:59:34 PM
 *  Author: ahmed
 */ 


#ifndef MYMAKROS_H_
#define MYMAKROS_H_

/*Set any bit at any register by knowing it's number*/
#define SET_BIT(REG,BIT) (REG |=(1<<BIT)) 

/*Clear any bit at any register by knowing it's number*/
#define CLEAR_BIT(REG,BIT) (REG &= (~(1<<BIT))) 

/*ask about any bit*/
#define BIT_IS_SIT(REG,BIT) (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

#define F_CPU (16000000)

#endif /* MYMAKROS_H_ */