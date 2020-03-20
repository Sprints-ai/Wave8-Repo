/*
 * LCD_Cfg.h
 *
 * Created: 14/03/2020 06:51:55 م
 *  Author: TOSHIBA
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_


/*				Determent  LCD control pins					  */


/*		LCD register selection pin		*/
#define LCD_CONTROL_PORT		GPIOA
#define  RS_LCD_PIN				PIN1
#define  RW_LCD_PIN				PIN2
#define  EN_LCD_PIN				PIN3

////////////////////////////////////////////////////////////////


/*				Determent  LCD Data pins					 */

#define  LCD_DATA_PORT			GPIOA
#define  LCD_D4_PIN				PIN4
#define  LCD_D5_PIN				PIN5
#define  LCD_D6_PIN				PIN6
#define  LCD_D7_PIN				PIN7


#endif /* LCD_CFG_H_ */