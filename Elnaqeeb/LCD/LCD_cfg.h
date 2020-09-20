/*
 * LCD_cfg.h
 *
 * Created: 3/14/2020 12:19:11 PM
 *  Author: Ahmed
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/************************************************************************/
/*						LCD Basic configurations                        */
/************************************************************************/

/*LCD data modes*/
#define DATA_8BIT_MODE		(1)
#define DATA_4BIT_MODE		(2)

/*Selected data mode*/
#define LCD_DATA_MODE		(DATA_4BIT_MODE)

/*LCD control port*/
#define LCD_CTRL_PORT		(GPIOA)

/*LCD control pins*/
#define LCD_RS_PIN			(PIN1)
#define LCD_RW_PIN			(PIN2)
#define LCD_EN_PIN			(PIN3)

/*LCD data port*/
#define LCD_DATA_PORT		(GPIOA)

/*LCD data pins*/
#define LCD_DATA_PIN0		(PIN0)
#define LCD_DATA_PIN1		(PIN1)
#define LCD_DATA_PIN2		(PIN2)
#define LCD_DATA_PIN3		(PIN3)
#define LCD_DATA_PIN4		(PIN4)
#define LCD_DATA_PIN5		(PIN5)
#define LCD_DATA_PIN6		(PIN6)
#define LCD_DATA_PIN7		(PIN7)

#endif /* LCD_CFG_H_ */