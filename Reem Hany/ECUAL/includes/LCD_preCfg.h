/*
 * LCD_Cfg.h
 *
 * Created: 3/13/2020 6:10:54 PM
 *  Author: Reem
 */ 


#ifndef LCD_PRECFG_H_
#define LCD_PRECFG_H_
#include "../../MCAL/includes/DIO.h"

#define ENABLE                             1
#define DISABLE                            0

#define _4_BIT_MODE                        ENABLE
#define _8_BIT_MODE                        DISABLE

#define LCD_PORT                           GPIOA

#define LCD_RS                             BIT1
#define LCD_RW                             BIT2
#define LCD_EN                             BIT3

#define LCD_DATA_4                         BIT4
#define LCD_DATA_5                         BIT5
#define LCD_DATA_6                         BIT6
#define LCD_DATA_7                         BIT7	

#define _LCD_4BIT_INIT_CMD                 0x02
#define _LCD_4BIT_INIT_1_CMD               0x33
#define _LCD_4BIT_INIT_2_CMD               0x32
#define _LCD_2_LINE_CMD                    0x28
#define _LCD_CURSOR_OFF_CMD                0x0C
#define _LCD_CURSOR_SHIFT_TO_RIGHT_CMD     0x06
#define _LCD_CLR                           0x01

#define _LCD_INIT_STATE				       0
#define _LCD_INIT_STATE1				   1
#define _LCD_INIT_STATE2				   2
#define _LCD_INIT_STATE3				   3
#define _LCD_INIT_STATE4				   4

#define _LCD_WRITE_STATE1				   5
#define _LCD_WRITE_STATE2				   6
#define _LCD_WRITE_STATE3				   7
#define _LCD_WRITE_STATE4				   8

#define _LCD_IDLE                          0
#define _LCD_BUSY                          1

#define DDRAM                              0x80
#define LINE_1_FIRST_CHAR                  0x00
#define LINE_1_LAST_CHAR_POS               15
#define LINE_2_FIRST_CHAR                  0x40
#define LINE_2_LAST_CHAR_POS               31

#define _LCD_BUFFER_LOCKED                 1
#define _LCD_BUFFER_UNLOCKED               0

#define _LCD_WRITE_DONE                    5
#endif /* LCD_PRECFG_H_ */