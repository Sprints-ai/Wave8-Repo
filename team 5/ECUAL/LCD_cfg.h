/*
 * LCD_cfg.h
 *
 * Created: 3/15/2020 11:53:12 AM
 *  Author : MENNA
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define LCD_PORT GPIOA 
#define LCD_RS BIT1
#define LCD_R_W BIT2
#define LCD_EN BIT3 
#define LCD_DATA BIT4|BIT5|BIT6|BIT7 

#define DATA_MODE_4_BIT 0x02 
#define DATA_MODE_2_LINE_4_BIT 0x28

#define CURSOR_ON 0x0E
#define CLEAR_SCREEN 0x01 

#define SET_CURSOR_LOCATION 0x80 






#endif /* LCD_CFG_H_ */