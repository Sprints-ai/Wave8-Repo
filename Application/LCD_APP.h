/*
 * LCD_APP.h
 *
 * Created: 18/03/2020 12:20:50 م
 *  Author: TOSHIBA
 */ 


#ifndef LCD_APP_H_
#define LCD_APP_H_
#include "../Infrastructure/std_types.h"

#define INIT_DONE 0xff
/*  ANSWER MODE */
#define RIGH_ANSWER				1
#define WRONG_ASWER				2
u8_ERROR_STATUS_t QuestionGame_Init(void);
u8_ERROR_STATUS_t QuestionGame_RUN(void);


#endif /* LCD_APP_H_ */