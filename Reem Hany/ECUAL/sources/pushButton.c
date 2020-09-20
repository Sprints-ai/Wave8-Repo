#include "../../MCAL/includes/DIO.h"
#include "../includes/pushButtonConfig.h"
#include "../includes/pushButton.h"


void pushButtonInit(En_buttonId_t en_butotn_id){
	strDIO_Cfg_s astrDioCfg;
	switch(en_butotn_id){
		case BTN_0:
			astrDioCfg.GPIO = BTN_0_GPIO;
			astrDioCfg.pins = BTN_0_BIT;
			astrDioCfg.dir = INPUT;
			DIO_init(&astrDioCfg);
			DIO_Write(BTN_0_GPIO,BTN_0_BIT,HIGH);
			
			
			break;
		case BTN_1:
			astrDioCfg.GPIO = BTN_1_GPIO;
			astrDioCfg.pins = BTN_1_BIT;
			astrDioCfg.dir = INPUT;
			DIO_init(&astrDioCfg);
			DIO_Write(BTN_1_GPIO,BTN_1_BIT,HIGH);
			
			break;
		case BTN_2:
			astrDioCfg.GPIO = BTN_2_GPIO;
			astrDioCfg.pins = BTN_2_BIT;
			astrDioCfg.dir = INPUT;
			DIO_init(&astrDioCfg);
			DIO_Write(BTN_2_GPIO,BTN_2_BIT,HIGH);
			
			break;
		case BTN_3:
			astrDioCfg.GPIO = BTN_3_GPIO;
			astrDioCfg.pins = BTN_3_BIT;
			astrDioCfg.dir = INPUT;
			DIO_init(&astrDioCfg);
			DIO_Write(BTN_3_GPIO,BTN_3_BIT,HIGH);
			
			break;
	}
}
En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id){
	uint8_t au8_value;
	switch(en_butotn_id){
		case BTN_0:
		DIO_Read(BTN_0_GPIO,BTN_0_BIT,&au8_value);
		
		break;
		case BTN_1:
		DIO_Read(BTN_1_GPIO,BTN_1_BIT,&au8_value);
		
		break;
		case BTN_2:
		DIO_Read(BTN_2_GPIO,BTN_2_BIT,&au8_value);
		
		break;
		case BTN_3:
		DIO_Read(BTN_3_GPIO,BTN_3_BIT,&au8_value);
		
		break;
	}
		if (ZERO==au8_value)
		{
			return Released;
		}
		else
		{
			return Pressed;
		}
}


