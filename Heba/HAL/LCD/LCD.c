/*
 * LCD.c
 *
 * Created: 14/03/2020 06:50:57 م
 *  Author: TOSHIBA
 */ 
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include  "../../Infrastructure/softwareDelay.h"
#define   F_CPU    16000000UL
#include "Util/delay.h"

#define   RS_DISPLAY_DATA		0x02
#define   RS_INSTRUCTION_CODE   0xFD 
#define   RW_WRITE_SELECTION    0xFB
#define   WRITE_COMMAND			0x08
#define   WRITE_DATA			0x0A
#define   LCD_UNINIT			0
#define	  LCD_INIT				1
#define	  LCD_UPPER_NUBBLE      0xF0
#define   LCD_LOWER_NUBBLE		4
#define   END_OF_DATA           '\0'
#define	  SECOND_ROW			16
#define	  END_OF_LCD_DISPLAY	32		

#define	LCD_4_MODE_INIT			0x02
#define LCD_2LINE_5X7_MASK		0x28
#define LCD_CURSOR_ON			0x0E
#define LCD_CLEAR_COMMAND       0x01
#define SECOND_ROW_ADDRESS_COMMAND	0xC0
#define LCD_INCRUMENT_MODE		0x06
	
#define MAX_LCD_INIT_COMMAND     4
#define  LCD_IDLE_STATE                0 
#define  LCD_WRITE_STATE        1
#define	 LCD_WAIT_COUNT_STATE		  2
#define  LCD_INIT_DONE_STATE			 3
#define LCD_WRITE_COMMAND_COMPLET_STATE  4
#define LCD_INIT_COUNTER_STATE			5
#define GET_NEXT_CHAR_STATE             6
#define  STR_CALL_WRITE              1

static uint8_t u8_LCD_INIT = LCD_UNINIT ;
static uint8_t u8_LCD_InitStatus = LCD_IDLE_STATE;
static uint8_t u8_LCD_CommandCounter;
static uint8_t u8_LCD_WriteStringStatus=LCD_WRITE_STATE;// I want it to performed once  
static uint8_t u8_StringFun_Call_write;


u8_ERROR_STATUS_t LCD_init (void){
	u8_ERROR_STATUS_t u8_LCD_ErrorState=E_OK;
	static uint8_t u8_LCD_InitCounter=0;
	static uint8_t au8_LCD_Command[]={LCD_4_MODE_INIT,LCD_2LINE_5X7_MASK,LCD_CURSOR_ON,LCD_CLEAR_COMMAND,LCD_INCRUMENT_MODE};

	switch(u8_LCD_InitStatus)
	{
		case LCD_IDLE_STATE:;
			gstr_DIO_Cfg_t str_LCD_ControlPortCfg={LCD_CONTROL_PORT,RS_LCD_PIN|RW_LCD_PIN|EN_LCD_PIN,OUTPUT};
			gstr_DIO_Cfg_t str_LCD_DataPortCfg={LCD_DATA_PORT,LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,OUTPUT};
			DIO_init(&str_LCD_ControlPortCfg);
			DIO_init(&str_LCD_DataPortCfg);
			u8_LCD_InitCounter++;//it should be the count of ISR 
			u8_LCD_InitStatus = LCD_INIT_COUNTER_STATE;
			//_delay_ms(80);
		break;
		case LCD_INIT_COUNTER_STATE:
		if(u8_LCD_InitCounter==40)
		u8_LCD_InitStatus = LCD_WRITE_STATE;
		else 
		u8_LCD_InitCounter++;
		break;
		case LCD_WRITE_STATE:
		LCD_WriteCommand(au8_LCD_Command[u8_LCD_CommandCounter]);
		
		break;
		
// 		case LCD_WAIT_COMMAND_STATE:		
// 		break;
		
		case LCD_WRITE_COMMAND_COMPLET_STATE:
		if(u8_LCD_CommandCounter==MAX_LCD_INIT_COMMAND)
		{
			//u8_LCD_InitStatus = LCD_INIT_DONE_STATE;
			u8_LCD_INIT = LCD_INIT;
			u8_LCD_ErrorState=LCD_INIT_DONE;
		}
		else
		{
			u8_LCD_InitStatus = LCD_WRITE_STATE;
			u8_LCD_CommandCounter++;
		}
		break;

		default:
		break;
	}

return u8_LCD_ErrorState;		

}
	

u8_ERROR_STATUS_t LCD_WriteCommand (const uint8_t u8_Command){
	u8_ERROR_STATUS_t u8_LCD_ErrorState=E_OK;
	
	if (u8_LCD_INIT == LCD_UNINIT ){
		// error : LCD uniit
	}
	else 
	{
			static uint8_t u8_LCD_WriteCommandStatus=LCD_WRITE_STATE;
			//static uint8_t u8_LCD_CommandCounter=0;
			switch (u8_LCD_WriteCommandStatus)
			{
				case LCD_WRITE_STATE:
				DIO_Write (LCD_CONTROL_PORT,RS_LCD_PIN|RW_LCD_PIN|EN_LCD_PIN,WRITE_COMMAND);
				DIO_Write (LCD_DATA_PORT,LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,(u8_Command&LCD_UPPER_NUBBLE));
				//_delay_ms(1);
				DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,LOW);
				DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,HIGH);
				DIO_Write (LCD_DATA_PORT,LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,(u8_Command<<LCD_LOWER_NUBBLE));
				//_delay_ms(1);
				DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,LOW);
				//_delay_us(25);
				//u8_LCD_InitStatus =  LCD_WRITE_COMMAND_COMPLET_STATE;
				u8_LCD_WriteCommandStatus = LCD_WAIT_COUNT_STATE;
				break;
				
				case LCD_WAIT_COUNT_STATE:
				
				u8_LCD_WriteCommandStatus = LCD_WRITE_STATE;
				u8_LCD_InitStatus =  LCD_WRITE_COMMAND_COMPLET_STATE;

				break;
				
				default:
				break;
			}
	}

	return u8_LCD_ErrorState;
	
}



u8_ERROR_STATUS_t LCD_WriteString (const uint8_t* pu8_data){//how to to prevent  the from sending data before finsh the first one 
	u8_ERROR_STATUS_t u8_LCD_ErrorState=E_OK;
	if (u8_LCD_INIT == LCD_UNINIT ){
		// error : LCD uniit
	}
	else
	{
		static uint8_t u8_count = 0;
	
		switch(u8_LCD_WriteStringStatus){
			case LCD_WRITE_STATE:

			if ( pu8_data[u8_count] != END_OF_DATA)
			{
				u8_StringFun_Call_write = STR_CALL_WRITE;
			
				LCD_WriteChar (pu8_data[u8_count]);
			
			}
			else{
			
				u8_LCD_ErrorState=LCD_WRITE_STRING_DONE;//write complete
				u8_count=0;
			}
			break;
			case GET_NEXT_CHAR_STATE:
			u8_count++;
			if(u8_count ==END_OF_LCD_DISPLAY){
				//error End of LCD display
			}
			else 
			{	if (u8_count==SECOND_ROW)
				{
					LCD_WriteCommand(SECOND_ROW_ADDRESS_COMMAND);
				}
				u8_LCD_WriteStringStatus = LCD_WRITE_STATE ;
				break;
			}
			
		}
	}
	
	
return u8_LCD_ErrorState;
}


u8_ERROR_STATUS_t LCD_clear (void)
{	u8_ERROR_STATUS_t u8_LCD_ErrorState=E_OK;
	LCD_WriteCommand (LCD_CLEAR_COMMAND);
	return u8_LCD_ErrorState;
}

u8_ERROR_STATUS_t LCD_WriteChar (const uint8_t u8_data){
	u8_ERROR_STATUS_t u8_LCD_ErrorState = E_OK;
	static uint8_t u8_LCD_WriteStatus = LCD_WRITE_STATE;
	static uint8_t u8_LCD_WriteCounter = 0;

	switch(u8_LCD_WriteStatus)
	{
		case LCD_WRITE_STATE:
		
			DIO_Write (LCD_CONTROL_PORT,RS_LCD_PIN|RW_LCD_PIN|EN_LCD_PIN,WRITE_DATA	);
			DIO_Write (LCD_DATA_PORT,LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,(u8_data&LCD_UPPER_NUBBLE));
			//_delay_ms(1);
			DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,LOW);
		
			DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,HIGH);
			DIO_Write (LCD_DATA_PORT,LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN,(u8_data<<LCD_LOWER_NUBBLE));
			//_delay_ms(1);
			DIO_Write (LCD_CONTROL_PORT,EN_LCD_PIN,LOW);
			u8_LCD_WriteCounter++;
			u8_LCD_WriteStatus = LCD_WAIT_COUNT_STATE;
			//_delay_ms(2);
		break;
		case LCD_WAIT_COUNT_STATE:
			u8_LCD_WriteCounter ++ ;
			if(u8_LCD_WriteCounter==3)
			{
				if (u8_StringFun_Call_write == STR_CALL_WRITE)
				{
		
					u8_LCD_WriteStringStatus = GET_NEXT_CHAR_STATE;
					u8_StringFun_Call_write = 0;
				}
		
				u8_LCD_WriteStatus = LCD_WRITE_STATE;
			}
		break;
		default:
		break;
	}
	return u8_LCD_ErrorState;
}