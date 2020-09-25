/************************************************************************/
/*                               Includes                               */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "PWM.h"

/************************************************************************/
/*                            General macros				            */
/************************************************************************/
#define     TIMER_CNT_CLK_STOP              (0xF8)

/************************************************************************/
/*		         Important registers bits    		        			*/
/************************************************************************/

/*CLK control bits*/
#define     TCCR0_CS00                      (0)
#define     TCCR0_CS01                      (1)
#define     TCCR0_CS02                      (2)

#define     TCCR1B_CS10                     (0)
#define     TCCR1B_CS11                     (1)
#define     TCCR1B_CS12                     (2)

#define     TCCR2_CS20                      (0)
#define     TCCR2_CS21                      (1)
#define     TCCR2_CS22                      (2)

/*Timer mode control bits*/
#define     TCCR0_WGM00                     (6)
#define     TCCR0_WGM01                     (3)

#define     TCCR1A_WGM10                    (0)
#define     TCCR1A_WGM11                    (1)
#define     TCCR1B_WGM12                    (3)
#define     TCCR1B_WGM13                    (4)

#define     TCCR2_WGM20                     (6)
#define     TCCR2_WGM21                     (3)

/*OC pins control bits*/
#define     TCCR0_COM00						(4)
#define     TCCR0_COM01						(5)

#define     TCCR1A_COM1B0					(4)
#define     TCCR1A_COM1B1					(5)
#define     TCCR1A_COM1A0					(6)
#define     TCCR1A_COM1A1					(7)

#define     TCCR2_COM20						(4)
#define     TCCR2_COM21						(5)

/************************************************************************/
/*                 PWM channels pins configuration                      */
/************************************************************************/

#define		PWM_CH0_PORT					(PORTB_DIR)
#define		PWM_CH0_PIN						(3)
#define		PWM_CH1_PORT					(PORTD_DIR)
#define		PWM_CH1_PIN						(4)
#define		PWM_CH2_PORT					(PORTD_DIR)
#define		PWM_CH2_PIN						(5)
#define		PWM_CH3_PORT					(PORTD_DIR)
#define		PWM_CH3_PIN						(7)

/************************************************************************/
/*                        PWM functions                                 */
/************************************************************************/
ERROR_STATUS pwm_Init(uint8_t au8_PWM_Channel)
{
	ERROR_STATUS err_var = E_OK;
	
	switch(au8_PWM_Channel)
	{
		case PWM_CH0:			
			/*Choosing phase correct PWM mode*/
			SET_BIT(TCCR0 , TCCR0_WGM00);
			CLEAR_BIT(TCCR0 , TCCR0_WGM01);
			
			/*Choosing non-inverted mode*/
			CLEAR_BIT(TCCR0 , TCCR0_COM00);
			SET_BIT(TCCR0 , TCCR0_COM01);
			
			/*Setting OC pin as output*/
			SET_BIT(PWM_CH0_PORT , PWM_CH0_PIN);
			break;
		
		case PWM_CH1:
			/*Choosing phase correct PWM mode*/
			SET_BIT(TCCR1A , TCCR1A_WGM10);
			CLEAR_BIT(TCCR1A , TCCR1A_WGM11);
			CLEAR_BIT(TCCR1B , TCCR1B_WGM12);
			CLEAR_BIT(TCCR1B , TCCR1B_WGM13);

			/*Choosing non-inverted mode*/
			CLEAR_BIT(TCCR1A , TCCR1A_COM1B0);
			SET_BIT(TCCR1A , TCCR1A_COM1B1);
			
			/*Setting OC pin as output*/
			SET_BIT(PWM_CH1_PORT , PWM_CH1_PIN);
			break;
			
		case PWM_CH2:
			/*Choosing phase correct PWM mode*/
			SET_BIT(TCCR1A , TCCR1A_WGM10);
			CLEAR_BIT(TCCR1A , TCCR1A_WGM11);
			CLEAR_BIT(TCCR1B , TCCR1B_WGM12);
			CLEAR_BIT(TCCR1B , TCCR1B_WGM13);

			/*Choosing non-inverted mode*/
			CLEAR_BIT(TCCR1A , TCCR1A_COM1A0);
			SET_BIT(TCCR1A , TCCR1A_COM1A1);
		
			/*Setting OC pin as output*/
			SET_BIT(PWM_CH2_PORT , PWM_CH2_PIN);
			break;

		case PWM_CH3:
			/*Choosing phase correct PWM mode*/
			SET_BIT(TCCR2 , TCCR2_WGM20);
			CLEAR_BIT(TCCR2 , TCCR2_WGM21);

			/*Choosing non-inverted mode*/
			CLEAR_BIT(TCCR2 , TCCR2_COM20);
			SET_BIT(TCCR2 , TCCR2_COM21);
		
			/*Setting OC pin as output*/
			SET_BIT(PWM_CH3_PORT , PWM_CH3_PIN);
			break;
			
		default: err_var = E_NOK;				
	}	
	
	return err_var;
}

ERROR_STATUS pwm_Start(uint8_t au8_PWM_Channel, uint8_t au8_Duty, uint8_t au8_Frequency)
{
	ERROR_STATUS err_var = E_OK;
	
	switch(au8_PWM_Channel)
	{
		case PWM_CH0:
			/*Setting the duty cycle*/
			OCR0 = au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR0 , TCCR0_CS02);
					CLEAR_BIT(TCCR0 , TCCR0_CS01);
					SET_BIT(TCCR0 , TCCR0_CS00);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR0 , TCCR0_CS02);
					SET_BIT(TCCR0 , TCCR0_CS01);
					CLEAR_BIT(TCCR0 , TCCR0_CS00);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    SET_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);				
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    CLEAR_BIT(TCCR0 , TCCR0_CS00);					
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);					
					break;	
				
				default: err_var = E_NOK;					
			}
			break;

		case PWM_CH1:
			/*Setting the duty cycle*/
			OCR1B = (uint16_t)au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;
				
				default: err_var = E_NOK;
			}
			break;

		case PWM_CH2:
			/*Setting the duty cycle*/
			OCR1A = (uint16_t)au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;
				
				default: err_var = E_NOK;
			}
			break;

		case PWM_CH3:
			/*Setting the duty cycle*/
			OCR2 = au8_Duty;
		
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_1KHZ_FREQ:
					/*Setting pre-scaler to 32*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_245HZ_FREQ:
					/*Setting pre-scaler to 128*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;
			
				default: err_var = E_NOK;
			}
			break;
			
		default: err_var = E_NOK;	
	}
	
	return err_var;	
}

ERROR_STATUS pwm_Update(uint8_t au8_PWM_Channel, uint8_t au8_Duty, uint8_t au8_Frequency)
{
	ERROR_STATUS err_var = E_OK;
	
	switch(au8_PWM_Channel)
	{
		case PWM_CH0:
			/*Setting the duty cycle*/
			OCR0 = au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR0 , TCCR0_CS02);
					CLEAR_BIT(TCCR0 , TCCR0_CS01);
					SET_BIT(TCCR0 , TCCR0_CS00);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR0 , TCCR0_CS02);
					SET_BIT(TCCR0 , TCCR0_CS01);
					CLEAR_BIT(TCCR0 , TCCR0_CS00);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    SET_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);				
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    CLEAR_BIT(TCCR0 , TCCR0_CS00);					
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);					
					break;	
				
				default: err_var = E_NOK;					
			}
			break;

		case PWM_CH1:
			/*Setting the duty cycle*/
			OCR1B = (uint16_t)au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;
				
				default: err_var = E_NOK;
			}
			break;

		case PWM_CH2:
			/*Setting the duty cycle*/
			OCR1A = (uint16_t)au8_Duty;
			
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					CLEAR_BIT(TCCR1B , TCCR1B_CS12);
					SET_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					CLEAR_BIT(TCCR1B , TCCR1B_CS10);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR1B , TCCR1B_CS12);
					CLEAR_BIT(TCCR1B , TCCR1B_CS11);
					SET_BIT(TCCR1B , TCCR1B_CS10);
					break;
				
				default: err_var = E_NOK;
			}
			break;

		case PWM_CH3:
			/*Setting the duty cycle*/
			OCR2 = au8_Duty;
		
			switch(au8_Frequency)
			{
				case PWM_31KHZ_FREQ:
					/*Setting pre-scaler to 1*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_4KHZ_FREQ:
					/*Setting pre-scaler to 8*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_1KHZ_FREQ:
					/*Setting pre-scaler to 32*/
					CLEAR_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_500HZ_FREQ:
					/*Setting pre-scaler to 64*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_245HZ_FREQ:
					/*Setting pre-scaler to 128*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					CLEAR_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_120HZ_FREQ:
					/*Setting pre-scaler to 256*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					CLEAR_BIT(TCCR2 , TCCR2_CS20);
					break;

				case PWM_30HZ_FREQ:
					/*Setting pre-scaler to 1024*/
					SET_BIT(TCCR2 , TCCR2_CS22);
					SET_BIT(TCCR2 , TCCR2_CS21);
					SET_BIT(TCCR2 , TCCR2_CS20);
					break;
			
				default: err_var = E_NOK;
			}
			break;
			
		default: err_var = E_NOK;	
	}
		
	return err_var;
}

ERROR_STATUS pwm_Stop(uint8_t au8_PWM_Channel)
{
	ERROR_STATUS err_var = E_OK;
	
	/*Disconnecting the given channel ID from port operation*/
	switch(au8_PWM_Channel)
	{
		case PWM_CH0:
			CLEAR_BIT(TCCR0 , TCCR0_COM00);
			CLEAR_BIT(TCCR0 , TCCR0_COM01);
			break;
			
		case PWM_CH1:
			CLEAR_BIT(TCCR1A , TCCR1A_COM1B0);
			CLEAR_BIT(TCCR1A , TCCR1A_COM1B1);
			break;

		case PWM_CH2:
			CLEAR_BIT(TCCR1A , TCCR1A_COM1A0);
			CLEAR_BIT(TCCR1A , TCCR1A_COM1A1);
			break;

		case PWM_CH3:
			CLEAR_BIT(TCCR2 , TCCR2_COM20);
			CLEAR_BIT(TCCR2 , TCCR2_COM21);
			break;
			
	}
	return err_var;
}