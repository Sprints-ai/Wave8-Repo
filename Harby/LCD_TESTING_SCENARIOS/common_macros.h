/*
 * common_macros.h
 *
 *  Created on: Jan 20, 2020
 *      Author: Youssef Harby
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Left shift a register by a certain amount of times */
#define LEFT_SHIFT(BYTE, NUMBER_OF_TIMES)		(BYTE << NUMBER_OF_TIMES)

/* Right shift a register by a certain amount of times */
#define RIGHT_SHIFT(BYTE, NUMBER_OF_TIMES)		(BYTE >> NUMBER_OF_TIMES)

/* The upper nibble of a register (or a byte) */
#define UPPER_NIBBLE_OF(BYTE)					(BYTE & 0xF0)

/* The lower nibble of a register (or a byte) */
#define LOWER_NIBBLE_OF(BYTE)					(BYTE & 0x0F)

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

#endif /* COMMON_MACROS_H_ */
