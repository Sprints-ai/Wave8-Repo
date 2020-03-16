#include "../MCAl/DIO.h"
#include "pushButtonConfig.h"
#include "pushButton.h"
#include <avr/io.h>


#define BUTTON0_PRESSED			1
#define BUTTON1_PRESSED			2


ERROR_STATUS pushButtonInit(En_buttonId_t en_butotn_id){

	DIO_Cfg_s DIO_Button_CFG ;

	switch(en_butotn_id){
	case BTN_0:

		DIO_Button_CFG.GPIO = BTN_0_GPIO ;
		DIO_Button_CFG.pins = BTN_0_BIT ;
		DIO_Button_CFG.dir = INPUT ;
		DIO_init(&DIO_Button_CFG);

		break;
	case BTN_1:

		DIO_Button_CFG.GPIO = BTN_1_GPIO ;
		DIO_Button_CFG.pins = BTN_1_BIT ;
		DIO_Button_CFG.dir = INPUT ;
		DIO_init(&DIO_Button_CFG);

		break;
	}
	return E_OK;

}

ERROR_STATUS pushButtonGetStatus(En_buttonId_t en_butotn_id , En_buttonStatus_t * state){


	uint8_t au8_button_state ;
	static uint8_t au8_buttonPreState = FALSE  ;
	uint8_t au8_buttonFinalState = FALSE ;
	static uint8_t au8_counter0 = ZERO ;
	static uint8_t au8_counter1 = ZERO ;

	switch (au8_buttonPreState )
	{
	case FALSE :
		switch(en_butotn_id)
		{
		case BTN_0:
			au8_counter0 = 0;
			DIO_Read(BTN_0_GPIO,BTN_0_BIT,&au8_button_state);

			if (au8_button_state == 1)
			{
				au8_counter0++;
				au8_buttonPreState = BUTTON0_PRESSED ;
			}
			else{

				au8_buttonPreState = FALSE ;
			}
			break;
		case BTN_1:
			au8_counter1 = 0;
			DIO_Read(BTN_1_GPIO,BTN_1_BIT,&au8_button_state);

			if(au8_button_state == 1)
			{
				au8_counter1++;
				au8_buttonPreState = BUTTON1_PRESSED;
			}
			else{
				au8_buttonPreState = FALSE ;
			}
			break;
		}
		break;
		case BUTTON0_PRESSED :

			/* -------------------------------------------------------------------*/

			au8_counter0++;
			if (au8_counter0 > 2)
			{
				au8_buttonPreState = FALSE ;

				switch(en_butotn_id){
				case BTN_0:
					DIO_Read(BTN_0_GPIO,BTN_0_BIT,&au8_button_state);

					if (au8_button_state == 1)
					{
						au8_buttonFinalState = TRUE ;
					}
					else
					{
						au8_buttonFinalState = FALSE ;
					}
					break;
				case BTN_1:
					break;
				}/* end switch button ID*/
			}/* end of if counter>25*/
			break;
		case BUTTON1_PRESSED :
			au8_counter1++;
			if (au8_counter1 > 2)
			{
				au8_buttonPreState = FALSE ;

				switch(en_butotn_id){
				case BTN_0:
					break;
				case BTN_1:
					DIO_Read(BTN_1_GPIO,BTN_1_BIT,&au8_button_state);

					if(au8_button_state == 1)
					{
						au8_buttonFinalState = TRUE;
					}
					else
					{
						au8_buttonFinalState = FALSE ;
					}
					break;
				}/* end switch button ID*/
			}/* end of if counter>25*/
			break;

	}

	* state =  au8_buttonFinalState ;

	return E_OK;
}

