#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Set a certain bit in any register */
#define SET_BIT(REG,MASK) REG|=(MASK)

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,MASK) REG &= ~(MASK)

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

//for error handling
#define ERROR_STATUS	uint8_t
#define E_OK			1
#define E_NOK			0

#define NULL_PTR		(-1)
#define NO_INIT			(-2)
#define MUL_INIT		(-3)
#define STOP_NO_START	(-4)
#define INVALID_PARAM	(-5)
#define MUL_STOP		(-6)
#define MUL_START		(-7)
#define FULL_BUFFER		(-8)

#endif
