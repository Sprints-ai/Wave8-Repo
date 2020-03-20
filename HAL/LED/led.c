/*
 * led.c
 *
 * Created: 18/01/2020 01:13:48 ص
 *  Author: TOSHIBA
 */ 
#include "led.h"

u8_ERROR_STATUS_t Led_Init (En_LedNumber_t en_led_id) 
{
	u8_ERROR_STATUS_t u8_LED_ErrorState = E_OK;
	switch(en_led_id){
		case LED_0:;
			gstr_DIO_Cfg_t str_Led0_DIO_Cfg={LED_0_GPIO,LED_0_BIT,OUTPUT};
			DIO_init(&str_Led0_DIO_Cfg);
		 break;
		 
		 case LED_1:;
			 gstr_DIO_Cfg_t str_Led1_DIO_Cfg={LED_1_GPIO,LED_1_BIT,OUTPUT};
			 DIO_init(&str_Led1_DIO_Cfg);
		 break;
		 
		  case LED_2:;
			  gstr_DIO_Cfg_t str_Led2_DIO_Cfg={LED_2_GPIO,LED_2_BIT,OUTPUT};
			  DIO_init(&str_Led2_DIO_Cfg);
		  break;
		  case LED_3:;
			   gstr_DIO_Cfg_t str_Led3_DIO_Cfg={LED_3_GPIO,LED_3_BIT,OUTPUT};
			   DIO_init(&str_Led3_DIO_Cfg);
		   break;
	}
	return u8_LED_ErrorState;
}

u8_ERROR_STATUS_t Led_On(En_LedNumber_t en_led_id)
{
	
	u8_ERROR_STATUS_t u8_LED_ErrorState = E_OK;

	switch(en_led_id){
		
		case LED_0:
		DIO_Write(LED_0_GPIO,LED_0_BIT,HIGH);
		break;
		
		case LED_1:
		DIO_Write(LED_1_GPIO,LED_1_BIT,HIGH);
		break;
		
		case LED_2:
		DIO_Write(LED_2_GPIO,LED_2_BIT,HIGH);
		break;
		case LED_3:
		DIO_Write(LED_3_GPIO,LED_3_BIT,HIGH);
		break;
	} 
	return u8_LED_ErrorState;
 }
 
 u8_ERROR_STATUS_t Led_Off(En_LedNumber_t en_led_id){
	 
	u8_ERROR_STATUS_t u8_LED_ErrorState = E_OK;
	 switch(en_led_id){
		 
		 case LED_0:
			DIO_Write(LED_0_GPIO,LED_0_BIT,LOW);
		 break;
		 
		 case LED_1:
			DIO_Write(LED_1_GPIO,LED_1_BIT,LOW);
		 break;
		 
		 case LED_2:
			DIO_Write(LED_2_GPIO,LED_2_BIT,LOW);
		 break;
		 case LED_3:
			DIO_Write(LED_3_GPIO,LED_3_BIT,LOW);
		 break;
	 }
	 
	 return u8_LED_ErrorState;
 }

u8_ERROR_STATUS_t Led_Toggle(En_LedNumber_t en_led_id)
{
	
	u8_ERROR_STATUS_t u8_LED_ErrorState = E_OK;
	
	switch(en_led_id){
		
		case LED_0:
			 DIO_Toggle(LED_0_GPIO,LED_0_BIT);
		break;
		
		case LED_1:
			DIO_Toggle(LED_1_GPIO,LED_1_BIT);
		break;
		
		case LED_2:
			DIO_Toggle(LED_2_GPIO,LED_2_BIT);
		break;
		case LED_3:
			DIO_Toggle(LED_3_GPIO,LED_3_BIT);
		break;
	}
	

	return u8_LED_ErrorState;	
}


