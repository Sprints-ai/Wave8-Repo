/*
 * CarStaticDesign.c
 *
 * Created: 2/17/2020 10:00:07 AM
 * Author : mahmo
 */ 

#include "ServiceLayer/SOS/SOS.h"
#include "MCAL/Communication/UART/uart.h"
#include "MCAL/Communication/SPI/spi.h"
#include "ServiceLayer/SystemFunctions.h"
#include "HAL/LCD/char_lcd.h"
#include "HAL/LCD/char_lcd.h"
#include "HAL/PushButton/pushButton.h"
/*main program compiled using AVR32-GCC*/
#ifndef GCC
#define  NEW_LINE	0x0D
#define BUFFER_SIZE	100
#define YES			1
#define NO			0
#define MAX_QUESTIONS 5
#define	STATE_QUESTIONS 0
#define STATE_SCORE		1
#define LCD_MID        8

static  uint8_t gu8_gameState;
static uint8_t gu8_question1[]	 = "WELL U PRESS YES";
static uint8_t gu8_question2[]	 = "GRT NOW PRESS N0";
static uint8_t gu8_question3[]	 = " UR DOIN GREAT!?";
static uint8_t gu8_question4[]	 = "   R U AWSME!   ";
static uint8_t gu8_question5[]	 = "    YES U R     ";
static uint8_t gu8_options[]	 = "  YES      NO   ";
static uint8_t gu8_upperScoreScreen[] = "======SCORE========";
static uint8_t gu8_lowerScoreScreen[] = "-------------------";
static uint8_t gu8_answers[]   = {YES,NO,YES,YES,YES};
static uint8_t gu8_questionCounter;
static uint8_t* gu8_questions[5] = {gu8_question1,gu8_question2,gu8_question3,gu8_question4,gu8_question5};



void lcdCBF()
{
	static uint8_t u8_firstTime = FALSE;
	if(!u8_firstTime)
	{
		gu8_questionCounter = ZERO;
		LCD_setNewBuffer(gu8_questions[gu8_questionCounter],gu8_options);
		u8_firstTime = TRUE;
	}
	lcd_dispatcher();
}

void gamedispatcher()
{ 
	static uint8_t u8_score  = ZERO;
	uint8_t YesButton		 = BTN_0;
	uint8_t NoButton		 = BTN_1;
	uint8_t YesButtonPressed = Released;
	uint8_t NoButtonPressed  = Released;
	
	switch(gu8_gameState)
	{
		case  STATE_QUESTIONS:
			pushButtonPressed(YesButton,&YesButtonPressed);
			pushButtonPressed(NoButton,&NoButtonPressed);
			if ((YesButtonPressed == Pressed || NoButtonPressed == Pressed) && gu8_questionCounter < MAX_QUESTIONS)
			{
				if (YesButtonPressed == Pressed && gu8_answers[gu8_questionCounter] == YES)
				{
					u8_score++;
				}
				
				else if(NoButtonPressed == Pressed && gu8_answers[gu8_questionCounter] == NO)
				{
					u8_score++;
				}
				gu8_questionCounter++;
				/*load next question*/
				LCD_setNewBuffer(gu8_questions[gu8_questionCounter],gu8_options);
			}
			/*display score*/
			if(gu8_questionCounter == MAX_QUESTIONS)
				gu8_gameState = STATE_SCORE;
		break;
		case STATE_SCORE:
		gu8_lowerScoreScreen[LCD_MID] = u8_score+ '0'; 
			LCD_setNewBuffer(gu8_upperScoreScreen,gu8_lowerScoreScreen);
		break;
	}
	
	{
		
	}
	
	
	
}
void sos(void)
{
	sei();
	SOS_Init(&SOS_linkCfg);
	pushButtonInit(BTN_0);
	pushButtonInit(BTN_2);
	
	SOS_createTask(0,lcdCBF,2,PERIODIC,2);
	SOS_createTask(1,gamedispatcher,50,PERIODIC,1);

	while(1)
	{
		SOS_run();
	}
}

	

int main(void)
{
	sos();
	return 0 ;
}
#endif

/*for gcc compiler used in unit-testing*/
#ifdef GCC

#include "Application/Steering/Steering.h"
#include "Application/CarSm/car_sm.h"
#include "Test/Tester/tester.h"
#include "ServiceLayer/TMU/TMU.h"

int main(void)
{
	test();
	return 0;
}
#endif // _DEBUG