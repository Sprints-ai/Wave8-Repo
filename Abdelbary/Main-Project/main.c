/*
 * CarStaticDesign.c
 *
 * Created: 2/17/2020 10:00:07 AM
 * Author : mahmo
 */ 



/*main program compiled using AVR32-GCC*/
#ifndef GCC

#include "Application/Steering/Steering.h"
#include "Application/CarSm/car_sm.h"
#include "Test/Us_test/UltraSonic_test.h"
#include "ServiceLayer/TMU/TMU.h"
#include "ServiceLayer/SOS/SOS.h"
#include "MCAL/Communication/UART/uart.h"
#include "MCAL/Communication/SPI/spi.h"
#include "ServiceLayer/BCM/BCM.h"
#include "ServiceLayer/SystemFunctions.h"
#include "HAL/LCD/char_lcd.h"
#include "HAL/PushButton/pushButton.h"
#include "interrupt.h"


/*FOR LCD*/
#define YES			1
#define NO			0
#define MAX_QUESTIONS 5
#define	STATE_QUESTIONS 0
#define STATE_SCORE		1
#define LCD_MID        8


#define  NEW_LINE	0x0D
#define BUFFER_SIZE	100

#define TASK_DELY_CAR   12  /*for car dynamic design delay*/
STATIC	uint8_t buffer[BUFFER_SIZE];
STATIC	uint8_t lock1 = UNLOCK;
uint8_t u8_counter = ZERO;

/*for lcd game*/
STATIC  uint8_t gu8_gameState;
STATIC uint8_t gu8_question1[]	 = "WELL U PRESS YES";
STATIC uint8_t gu8_question2[]	 = "GRT NOW PRESS N0";
STATIC uint8_t gu8_question3[]	 = " UR DOIN GREAT!?";
STATIC uint8_t gu8_question4[]	 = "   R U AWSME!   ";
STATIC uint8_t gu8_question5[]	 = "    YES U R     ";
STATIC uint8_t gu8_options[]	 = "  YES      NO   ";
STATIC uint8_t gu8_upperScoreScreen[] = "======SCORE========";
STATIC uint8_t gu8_lowerScoreScreen[] = "-------------------";
STATIC uint8_t gu8_answers[]   = {YES,NO,YES,YES,YES};
STATIC uint8_t gu8_questionCounter;
STATIC uint8_t* gu8_questions[5] = {gu8_question1,gu8_question2,gu8_question3,gu8_question4,gu8_question5};

void bcm_ReciveNotifier(ERROR_STATUS status);
void bcm_SenderNotifier(ERROR_STATUS status);
gstr_BCM_Task_cfg_t gstr_BCM_ReciverTask_cfg = {buffer,&lock1,bcm_ReciveNotifier,ZERO,BCM_SPI_CHANAL,BCM_RECIVER};
gstr_BCM_Task_cfg_t gstr_BCM_SenderTask_cfg = {buffer,&lock1,bcm_SenderNotifier,ZERO,BCM_SPI_CHANAL,BCM_SENDER};


/*********************************************LCD******************************************************/

void lcdCBF()
{
	STATIC uint8_t u8_firstTime = FALSE;
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
	STATIC uint8_t u8_score  = ZERO;
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

void LCD_project(void)
{
		pushButtonInit(BTN_0);
		pushButtonInit(BTN_2);

		SOS_createTask(0,lcdCBF,2,PERIODIC,2);
		SOS_createTask(1,gamedispatcher,50,PERIODIC,1);
}

/***************************************************************************************************/



void toogle_led(void)
{
	 PORTA_DIR = 0xff;
	
	 PORTA_DATA ^= 0x01;
}

void toogle_led2(void)
{
	PORTA_DIR = 0xff;
	
	PORTA_DATA ^= 0x02;
}
void toogle_led3(void)
{
	PORTA_DIR = 0xff;
	
	PORTA_DATA ^= 0x04;
}
STATIC uint8_t shared;

uint8_t BCM_Reciver_sendTX(void)
{
	return shared;
}

void BCM_Reciver_reciveRX(uint8_t u8_sentData)
{
	shared = u8_sentData+1;
	UartTX_Enable();
}

uint8_t BCM_Sender_sendTX(void)
{
	return shared;
}

void BCM_Sender_reciveRX(uint8_t u8_sentData)
{
	/*shared = u8_sentData+1;
	UartTX_Enable();*/
	/*
	*	-send recived data to buffer
	*	-increment counter
	*/

	if (u8_sentData == NEW_LINE)
	{
		gstr_BCM_SenderTask_cfg.size = u8_counter;
		u8_counter = ZERO;
		BCM_setup(&gstr_BCM_SenderTask_cfg);
	}
	else
	{
		buffer[u8_counter]= u8_sentData;
		u8_counter++;
	}
	

}


/*
void spiCBF(void)
{
	static char i=0;
	SPI_sendData(i);
	i++;
}*/

void bcm_ReciveNotifier(ERROR_STATUS status)
{
	/*resetup for next round*/
	uint8_t u8_count = ZERO;
	/*send bytes throught u uart*/
	for (;u8_count < status ; u8_count++)
	{
		while(UDR_ReadyStatus() != TRUE);
		shared = buffer[u8_count];
		UartTX_Enable();
	}
		while(UDR_ReadyStatus() != TRUE);
		shared = NEW_LINE;
		UartTX_Enable();
	lock1 = UNLOCK;
	gstr_BCM_SenderTask_cfg.lock = &lock1;
	BCM_setup(&gstr_BCM_ReciverTask_cfg);
}

void bcm_SenderNotifier(ERROR_STATUS status)
{
	lock1 = UNLOCK;
}

void BCM_Sender(void)
{
	gstr_BCM_cfg_t bcm_cfg={BCM_SPI_CHANAL,BCM_SENDER};
	BCM_init(&bcm_cfg);
	
    gstr_uart_cfg_t uart_cfg = {BCM_Sender_sendTX,BCM_Sender_reciveRX};
	Uart_Init(&uart_cfg);
	sei();
	


	while(1)
	{
	/*	SPDR = 0XFF;
	_delay_ms(10);*/
		BCM_TX_dispatcher();

	}
}

void BCM_Rceiver(void)
{
	gstr_uart_cfg_t uart_cfg = {BCM_Reciver_sendTX,BCM_Reciver_reciveRX};
	Uart_Init(&uart_cfg);
	
	gstr_BCM_cfg_t bcm_cfg={BCM_SPI_CHANAL,BCM_RECIVER};
	BCM_init(&bcm_cfg);	

	BCM_setup(&gstr_BCM_ReciverTask_cfg);
	sei();
	TMU_Init(&TMU_linkCfg);
	
	TMU_start(0,toogle_led,5,PERIODIC);
	TMU_start(1,toogle_led2,10,PERIODIC);
	TMU_start(2,toogle_led3,20,PERIODIC);
	PORTA_DATA |= 0x30;
	PORTA_DIR |=0xff;
	while(1)
	{
	/*	SPDR = 0XFF;
	_delay_ms(10);*/
	PORTA_DATA &=~(0x20);
	PORTA_DATA |=0x10;
	BCM_RX_dispatcher();
	TMU_dispatcher();
	PORTA_DATA &=~(0x10);
	PORTA_DATA |=0x20;
	MCUCR &=~(1<<SM0) & ~(1<<SM1) & ~(1<<SM2);\
	MCUCR |= (1<<SE);
	__asm__ __volatile__("sleep" "\n\t" :: );
	}
}

void carUsTask()
{
	Us_dispatcher();
}

void carStateMachineTask()
{
	Car_SM_Update_dispatcher();
}

void sos(void)
{
	sei();
/*
	PORTA_DIR = 0xff;
*/
	SOS_Init(&SOS_linkCfg);
	Car_SM_Init();
/*
	SOS_createTask(0,toogle_led,5,PERIODIC,3);
	SOS_createTask(1,toogle_led2,5,PERIODIC,1);
	SOS_createTask(2,toogle_led3,5,PERIODIC,2);
*/
	//LCD_project();
	SOS_createTask(0,carUsTask,TASK_DELY_CAR,PERIODIC,0);
	SOS_createTask(1,carStateMachineTask,TASK_DELY_CAR,PERIODIC,1);

	while(1)
	{
		SOS_run();
	}
}



int main(void)
{
/*
	gstr_uart_cfg_t uart_cfg = {sendTX,reciveRX};
	Uart_Init(&uart_cfg);*/
	/*UartWriteTx('a');
	while(1)
	{
		uint8_t string[] = "mahmoud";
		uint8_t u8_count = ZERO;
		while (string[u8_count])
		{
			if (u8_TXComplteFlag)
			{
				UartWriteTx(string[u8_count]);
				u8_count++;
			}
		}
	}
	*/
	/*TMU_Init(&TMU_linkCfg);
	//Us_Module_Test();
	TMU_start(1,toogle_led,3,PERIODIC);
	TMU_start(2,toogle_led2,6,PERIODIC);
	/ *TMU_Stop(1);
	TMU_Stop(2);* /
	
	//TMU_DeInit();
	while (1)
	{
		TMU_dispatcher();
	}
	/ *sei();
	Car_SM_Init();
	
    while (1) 
    {
		Car_SM_Update();
    }* /*/
	//PORTB_DIR = 0xff;
	
	/*gstrSPI_spi_satus_t sp_status;
	sp_status.spi_mod			 = SPI_MASTER_MOD;
	sp_status.spi_opration_mod	 = SPI_INT_MOD;
	sp_status.spi_prescaler		 = SPI_PRESCALER_128;
	sp_status.spi_speed_mod		 = SPI_NORMAL_SPEED;
	sp_status.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
	sp_status.spi_data_order	 = SPI_DATA_ORDER_LSB;
	sp_status.spi_cbf		     = spi;
	SPI_init(&sp_status);
	
	SPI_sendData(0);
*/
	sos();
	//BCM_Rceiver();
	//BCM_Sender();
	return 0 ;
}
#endif

/*for gcc compiler used in unit-testing*/
#ifdef GCC

#include "Application/Steering/Steering.h"
#include "Application/CarSm/car_sm.h"
#include "Test/Tester/tester.h"
#include "ServiceLayer/TMU/TMU.h"
#include "Test/Car_sm_test/car_sm_test.h"
#include "Test/BCM_test/BCM_test.h"	
#include "Test/SPI_test/SPI_test.h"
#include "Test/LCD_test/LCD_test.h"
#include "Test/SOS_test/SOS_test.h"
#include "Test/TMU_test/TMU_test.h"
#include "Test/Us_test/UltraSonic_test.h"
int main(void)
{
	#ifdef TMU_TEST
	TMU_Module_run_test();
	#elif  ULTRA_SONIC
	Us_Module_Test();
	#elif  BCM_TEST
	BCM_Module_Test();
	#elif  SOS_TEST
	SOS_Module_run_test();
	#elif  SPI_TEST
	SPI_Module_Test();
	#elif CAR_SM_TEST
	car_sm_test();
	#elif DUMMY_TEST
	uint8_t* u8_testFilePath = "F:/Carier/Embedded/Sprints/CarStaticDesign-Slave/CarStaticDesign/Test/Tester/tests.txt";
	gstr_testFunPtr_t gstr_testFunPtr[] = {{"dummy",dummy},{"dummy2",dummy2}};
	uint8_t u8_counter = ZERO;
	testModule(u8_testFilePath,gstr_testFunPtr,2,&u8_counter);
	#endif
	return 0;
}
#endif // _DEBUG