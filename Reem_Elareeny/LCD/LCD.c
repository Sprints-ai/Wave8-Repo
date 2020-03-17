/*
 * LCD.c
 *
 * Created: 3/12/2020 2:44:59 PM
 *  Author: Reem el-Areeny
 */ 
 
 #define F_CPU 16000000ul
 #include <util/delay.h>
 #include "LCD.h"
 #include "pushButton.h"
 #define COMMAND		LOW
 #define DATA			HIGH

 #define WRITE			LOW
 #define READ			HIGH

 #define YES	1
 #define NO		0

 extern uint8_t gu8_BTN0_status;
 extern uint8_t gu8_BTN1_status;

static void LCD_writeCMD (uint8_t cmd);

uint8_t count = 0;
uint8_t count2= 0;
uint8_t init_flag = FALSE;

uint8_t gu8_Question_answered = FALSE;
uint8_t gu8_current_answer;

uint8_t gu8_Q1_answer = YES;
uint8_t gu8_Q2_answer = YES;
uint8_t gu8_Q3_answer = YES;


//uint8_t str[] = "abcdefg";
char* stringsSet[] = {"question 1","string 2","answer 3","Correct","Not Correct"};

uint8_t i = 0;
uint8_t c = 'a';

void one_ms_delay(){
	count++;
}

void ms_delay(uint8_t value){
	count2 += value;
}

void LCD_init(){
	if(!init_flag){
		LCD_PORT_DIR = 0xFF;
		one_ms_delay();
		if(count == 20){
			LCD_writeCMD(0x02); /* to initialize LCD in 4-bit mode.*/
		}else if(count == 21){
			LCD_writeCMD(0x28); /* Initialization of 16X2 LCD in 4bit mode */
		}else if(count == 22){
			LCD_writeCMD(0x28); /* Initialization of 16X2 LCD in 4bit mode */
		}else if(count == 23){
			LCD_writeCMD(0x0F); /* Display ON Cursor OFF */
		}else if(count == 24){
			LCD_writeCMD(0x06); /* Entry Mode, Auto Increment cursor */
		}else if(count == 25){
			LCD_writeCMD(0x01); /* clear display */
		}else if(count == 26){
			LCD_writeCMD(0x80); /* cursor at first position */
		}else if(count == 40){
			count = INITIALLY_STARTING_WITH_ZERO;
			init_flag = TRUE;
		}
	}
}

void LCD_writeCMD(uint8_t cmd){
			LCD_DATA_PORT = cmd & 0xF0;
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
			DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,COMMAND);
			DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
// 			_delay_ms(1);
			LCD_DATA_PORT = (cmd << 4) & 0xF0;
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
			DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,COMMAND);
			DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		
}

void LCD_writeChar(uint8_t character){
	if(init_flag){
	//_delay_ms(1);
		//one_ms_delay();

			//PORTB_DATA = count2;
			LCD_DATA_PORT = character & 0xF0;
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
			DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
			DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
			//_delay_ms(1);
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
			//_delay_ms(1);
			LCD_DATA_PORT = (character << 4) & 0xF0;
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
			DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
			DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
			//_delay_ms(1);
			DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
			//_delay_ms(1);
		}
}

void LCD_writeString(){
	static uint8_t q_count = 0;
	static uint8_t count3 = 0;
	if(init_flag){
 		if(!gu8_Question_answered && q_count < 3){
			while(stringsSet[q_count][i] != NULL_CHARACTER){
				ms_delay(1);
				if(count2 >= 15){
					LCD_writeChar(stringsSet[q_count][i]);
					i++;
					count2 = 0;
				}
			}
			switch(q_count){
				case 0:
					gu8_current_answer = gu8_Q1_answer;
					break;
				case 1:
					gu8_current_answer = gu8_Q2_answer;
					break;
				case 2:
					gu8_current_answer = gu8_Q3_answer;
					break;
			}
			if(gu8_BTN0_status || gu8_BTN1_status){
				//_delay_ms(100);
				if((gu8_current_answer == YES && gu8_BTN0_status /*== Pressed*/) || (gu8_current_answer == YES /*NO*/ && gu8_BTN1_status/* == Pressed*/)){
					//PORTD_DIR = q_count;
 					//PORTD_DIR ^= OUTPUT;
					//PORTD_DIR = gu8_BTN1_status;
					LCD_writeCMD(0x01);
					gu8_Question_answered = 0;
				}else{
					//PORTB_DATA = 0xFF;
					//PORTD_DIR = INPUT;
				}
				
			
			}
		}else {
 			gu8_Question_answered = 1;
 			q_count++;
 			i = 0;	
		}
	}	
}

void LCD_writeGlobalChar(){
	if(init_flag){
		LCD_DATA_PORT = c & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		//_delay_ms(1);
		LCD_DATA_PORT = (c << 4) & 0xF0;
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,HIGH);
		DIO_Write(LCD_PORT,LCD_REGISTER_SELECT_PIN,DATA);
		DIO_Write(LCD_PORT,LCD_READ_WRITE_PIN,WRITE);
		//_delay_ms(1);
		DIO_Write(LCD_PORT,LCD_ENABLE_PIN,LOW);
		//_delay_ms(1);
	}
}

/*
void validateAnswer(){
	if(gu8_BTN0_status || gu8_BTN1_status){
		if((gu8_current_answer == YES && gu8_BTN0_status == Pressed) || (gu8_current_answer == NO && gu8_BTN1_status == Pressed)){
			// *str = stringsSet[3];
			}else{
			// *str = stringsSet[4];
		}
		gu8_Question_answered = 1;
	}
}*/