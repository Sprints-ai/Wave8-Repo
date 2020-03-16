/********************************************************************************
 *																				*
 * Module : LCD																	*
 *																				*
 * File Name : LCD_cfg.h														*
 *																				*
 * Description : Header File for pre-compile configurations of LCD Driver.		*
 *																				*
 * Author : Youssef Harby														*
 *																				*
 ********************************************************************************/

#ifndef ECUAL_LCD_CFG_H_
#define ECUAL_LCD_CFG_H_

/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

/*
 * LCD pins
 */
#define LCD_CTRL_GPIO			GPIOA
#define LCD_DATA_GPIO			GPIOA

#define RS						BIT1
#define RW 						BIT2
#define E  						BIT3

/*
 * Macros for operating mode
 */
#define DATA_BITS_MODE 4
#if(DATA_BITS_MODE == 4)
#define UPPER_PORT_BITS
#endif


#endif /* ECUAL_LCD_CFG_H_ */
