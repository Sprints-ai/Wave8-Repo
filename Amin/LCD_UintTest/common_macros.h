#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define PA0		0
#define PA1		1
#define PA2		2
#define PA3		3
#define PA4		4
#define PA5		5
#define PA6		6
#define PA7		7

#define PB0		0
#define PB1		1
#define PB2		2
#define PB3		3
#define PB4		4
#define PB5		5
#define PB6		6
#define PB7		7

#define PC0		0
#define PC1		1
#define PC2		2
#define PC3		3
#define PC4		4
#define PC5		5
#define PC6		6
#define PC7		7

#define PD0		0
#define PD1		1
#define PD2		2
#define PD3		3
#define PD4		4
#define PD5		5
#define PD6		6
#define PD7		7

#endif /* COMMON_MACROS_H_ */
