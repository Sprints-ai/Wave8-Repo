/*
 ============================================================================
 Name        : main.c
 Author      : Muhammed Gamal
 Description : 
 ============================================================================
 */

#include "../APP/car_sm.h"
#include "../Common/softwareDelay.h"
#include "../MCAL/PWM.h"
#include "../HAL/Us.h"
#include "../MCAL/DIO.h"
#include "../MCAL/external_interrupts.h"
#include "../HAL/ICU.h"
#include "../HAL/motor.h"
#include "../APP/Steering.h"
#include "../MCAL/Timer.h"




int main(void)
{


/***************************************DIO test************************************/

	/*
	uint8_t data;
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT0,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	DIO_Write (GPIOA, BIT0, HIGH);

	DIO_Read (GPIOA,BIT0,&data);
	if(data==0)
	{
		DIO_Cfg_s DIO_stru_init2=
		{
				DIO_stru_init.GPIO=GPIOD,
				DIO_stru_init.pins=BIT0,
				DIO_stru_init.dir=OUTPUT,
		};
		DIO_init (&DIO_stru_init);

		DIO_Write (GPIOD, BIT0, HIGH);
	}
	else
	{
		DIO_Cfg_s DIO_stru_init2=
		{
				DIO_stru_init.GPIO=GPIOD,
				DIO_stru_init.pins=BIT0,
				DIO_stru_init.dir=OUTPUT,
		};
		DIO_init (&DIO_stru_init);

		DIO_Write (GPIOD, BIT0, LOW);
		DIO_Toggle (GPIOA, BIT0);
	}


	DIO_Cfg_s DIO_stru_init3=
	{
			DIO_stru_init3.GPIO=GPIOC,
			DIO_stru_init3.pins=UPPER_NIBBLE | LOWER_NIBBLE,
			DIO_stru_init3.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init3);
	DIO_Write (GPIOC, UPPER_NIBBLE | LOWER_NIBBLE, 20);
*/

/*******************************************************************************************/

	/***************************timers test********************************/
/*
	uint8_t overflowflag;
	uint16_t tcntvalue;
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=BIT0,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);

	St_TimerCfg timers_stru_init=
	{
		timers_stru_init.Timer_CH_NO=Timer_0,
		timers_stru_init.Timer_Mode=TIMER_MODE,
		timers_stru_init.Timer_Polling_Or_Interrupt=TIMER_POLLING_MODE,
		timers_stru_init.Timer_Prescaler=T0_PRESCALER_64,
	};
	Timer_Init(&timers_stru_init);

	Timer_Start(Timer_0,250);

	while(1)
	{
		Timer_GetStatus(Timer_0,&overflowflag);
		if(overflowflag==1)
		{
			Timer_Stop(Timer_0);
			DIO_Write (GPIOA, BIT0, HIGH);
			softwareDelayMs(1000);
			SET_BIT(TIFR,TOV0);      //clear the flag
		}
		else
		{
			Timer_Start(Timer_0,250);
			DIO_Write (GPIOA, BIT0, LOW);
			softwICU_TIMER_CH0areDelayMs(1000);
		}
		Timer_GetValue(Timer_0,&tcntvalue);
		TCNT1 =tcntvalue;
	}
*/

/**********************************PWM test********************************************/
/*
	Pwm_Cfg_s instans={PWM_CH1A_CH1B,PWM_PRESCALER_256};
	Pwm_Init(&instans);
	//instans.Channel=PWM_CH1B;
	//Pwm_Init(&instans);

	 Pwm_Start(PWM_CH1A_CH1B,20,T1_PHASE_CORRECT_FREQUENCY_50HZ);
	 //Pwm_Start(PWM_CH1B,30,T1_PHASE_CORRECT_FREQUENCY_50HZ);

	 while(1)
	 {

	 }
*/


	/****************ICU test*****************************/

/*
	uint32_t value;
	Icu_cfg_s instans={ICU_CH2,ICU_TIMER_CH0};
	Icu_Init(&instans);
	DIO_Cfg_s DIO_stru_init=
	{
			DIO_stru_init.GPIO=GPIOA,
			DIO_stru_init.pins=UPPER_NIBBLE|LOWER_NIBBLE,
			DIO_stru_init.dir=OUTPUT,
	};
	DIO_init (&DIO_stru_init);
	//Icu_ReadTime(Timer_0,ICU_RISE_TO_FALL,&value);
	while(1)
	{
		Icu_ReadTime(Timer_0,ICU_RISE_TO_RISE,&value);
		_delay_ms(500);
		TCNT2=value;
	}
*/

/***************************************************************************************/

	/***********************steering test*****************************/
/*
	Steering_Init();
	Steering_SteerCar(CAR_FORWARD,50);

	//Motor_Direction(MOTOR_1, MOTOR_STOP);
	//Motor_Direction(MOTOR_2,MOTOR_BACKWARD);
	//Motor_Start(MOTOR_1_2,50);

	while(1)
	{

	}
*/
/****************************************************************************************/
	/*********************ultra_sonic test******************************/
/*
	uint32_t Distance;
	uint32_t time;

	DIO_Cfg_s trigger_start=
	{
			trigger_start.GPIO=GPIOA,
			trigger_start.pins=BIT0,
			trigger_start.dir=OUTPUT,
	};
	DIO_init (&trigger_start);
	Us_Init();
	while(1)
	{

		softwareDelayMs(1);
		DIO_Write (GPIOA, BIT0, HIGH);
		softwareDelayMs(1);
		DIO_Write (GPIOA, BIT0, LOW);

		Icu_ReadTime(Timer_2,ICU_RISE_TO_FALL,&time);
		while(g8_echo_flag==0);
		g8_echo_flag=0;

		Distance=(time)/58;
		TCNT0=Distance;
	}
	*/

	/*
	uint16_t Distance;

	Us_Init();
	while(1)
	{
		Us_Trigger();
		Us_GetDistance(&Distance);
		TCNT0=Distance;
	}
*/

	/****************************************************************************/

	Car_SM_Init();

	while(TRUE)
	{
		Car_SM_Update();
	}

}
