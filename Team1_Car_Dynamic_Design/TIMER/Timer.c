/************************************************************************/
/*                          Includes                                    */
/************************************************************************/

#include "std_types.h"
#include "registers.h"
#include "Timer.h"

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

/*Timer interrupt enable/disable bits*/
#define     TIMSK_TOIE0                     (0)
#define     TIMSK_OCIE0                     (1)

#define     TIMSK_TOIE1                     (2)
#define     TIMSK_OCIE1B                    (3)
#define     TIMSK_OCIE1A                    (4)
#define     TIMSK_TICIE1                    (5)

#define     TIMSK_TOIE2                     (6)
#define     TIMSK_OCIE2                     (7)

/*Timer interrupt flag bits*/

#define		TIFR_OCF0						(1)
#define		TIFR_OCF1A						(4)
#define		TIFR_OCF2						(7)

/*Global variables used in setting timer channels pre-scaler*/
static uint8_t gu8_timer0_prescaler = 0;
static uint8_t gu8_timer1_prescaler = 0;
static uint8_t gu8_timer2_prescaler = 0;

/*Init and DeInit flags*/
static uint8_t gu8_init_flag = 0;
static uint8_t gu8_deInit_flag = 0;

/************************************************************************/
/*                          Timer functions                             */
/************************************************************************/

ERROR_STATUS Timer_Init(uint8_t au8_Timer_CH_NO, uint8_t au8_Timer_mode, uint8_t au8_Timer_prescaler, uint8_t au8_Timer_INT_mode)
{
    ERROR_STATUS err_var = E_OK;
	
	/*Checking the timer is initialized before or not*/
	if (gu8_init_flag)
	{
		err_var = E_NOK;
	} 
	else
	{
		/*Switching for timer channels*/
		switch (au8_Timer_CH_NO)
		{
			/*Choosing channel 0 (Timer0)*/
			case TIMER_CH0:
            
				/*Setting Timer0 pre-scaler*/
				gu8_timer0_prescaler = au8_Timer_prescaler;
            
				/*CTC mode*/
				SET_BIT(TCCR0 , TCCR0_WGM01);
				CLEAR_BIT(TCCR0 , TCCR0_WGM00);
            
				/*Choosing timer mode*/
				switch(au8_Timer_mode)
				{
					case TIMER_MODE:
						/*DO nothing*/
						break;
                
					case COUNTER_RISING_MODE:
						/*Adjusting counting on rising mode*/
						SET_BIT(TCCR0 , TCCR0_CS02);
						SET_BIT(TCCR0 , TCCR0_CS01);
						SET_BIT(TCCR0 , TCCR0_CS00);
						break;    

					case COUNTER_FALLING_MODE:
						/*Adjusting counting on falling mode*/
						SET_BIT(TCCR0 , TCCR0_CS02);
						SET_BIT(TCCR0 , TCCR0_CS01);
						CLEAR_BIT(TCCR0 , TCCR0_CS00);
						break;    

					default: err_var = E_NOK;
				}
			
				/*Choosing whether the timer is polling or interrupt mode*/
				switch (au8_Timer_INT_mode)
				{
					case TIMER_POLLING_MODE:
						/*Disable the OCR Interrupt*/
						CLEAR_BIT(TIMSK , TIMSK_OCIE0);
						break;

					case TIMER_INTERRUPT_MODE:
						/*Enable the OCR Interrupt*/
						SET_BIT(TIMSK , TIMSK_OCIE0);
						break;

					default:
						err_var = E_NOK;
						break;
				}
				break;

			case TIMER_CH1:
            
				/*Setting Timer1 pre-scaler*/
				gu8_timer1_prescaler = au8_Timer_prescaler;

				/*CTC mode*/
				CLEAR_BIT(TCCR1A , TCCR1A_WGM10);
				CLEAR_BIT(TCCR1A , TCCR1A_WGM11);
				SET_BIT(TCCR1B , TCCR1B_WGM12);
				CLEAR_BIT(TCCR1B , TCCR1B_WGM13);

				/*Choosing timer mode*/
				switch(au8_Timer_mode)
				{
					case TIMER_MODE:
						/*Do nothing*/
						break;
                
					case COUNTER_RISING_MODE:
						/*Adjusting counting on rising mode*/
						SET_BIT(TCCR1B , TCCR1B_CS12);
						SET_BIT(TCCR1B , TCCR1B_CS11);
						SET_BIT(TCCR1B , TCCR1B_CS10);
						break;    

					case COUNTER_FALLING_MODE:
						/*Adjusting counting on falling mode*/
						SET_BIT(TCCR1B , TCCR1B_CS12);
						SET_BIT(TCCR1B , TCCR1B_CS11);
						CLEAR_BIT(TCCR1B , TCCR1B_CS10);
						break;    

					default: err_var = E_NOK;
				}
			
				/*Choosing whether the timer is polling or interrupt mode*/
				switch (au8_Timer_INT_mode)
				{
					case TIMER_POLLING_MODE:
						/*Disable the OCR interrupt*/
						CLEAR_BIT(TIMSK , TIMSK_OCIE1A);
						break;

					case TIMER_INTERRUPT_MODE:
						/*Enable the OCR interrupt*/
						SET_BIT(TIMSK , TIMSK_OCIE1A);
						break;

					default: err_var = E_NOK;
				}
				break;
			
			case TIMER_CH2:

				/*Setting timer2 pre-scaler*/
				gu8_timer2_prescaler = au8_Timer_prescaler;

				/*CTC mode*/
				SET_BIT(TCCR2 , TCCR2_WGM21);
				CLEAR_BIT(TCCR2 , TCCR2_WGM20);
			
				/*Choosing the timer mode*/	
				switch(au8_Timer_mode)
				{
					case TIMER_MODE:
						/*Do nothing*/
						break;
                
					case COUNTER_RISING_MODE:
						err_var = E_NOK;
						break;    

					case COUNTER_FALLING_MODE:
						err_var = E_NOK;
						break;    

					default: err_var = E_NOK;
				}
			
				/*Choosing whether the timer is polling or interrupt mode*/
				switch (au8_Timer_INT_mode)
				{
					case TIMER_POLLING_MODE:
						/*Disable the OCR interrupt*/
						CLEAR_BIT(TIMSK , TIMSK_OCIE2);
						break;

					case TIMER_INTERRUPT_MODE:
						/*Enable the OCR interrupt*/
						SET_BIT(TIMSK , TIMSK_OCIE2);
						break;

					default: err_var = E_NOK;
				}
				break;   
        
			default:
				err_var = E_NOK;
		}
		
		/*Rising the init flag and resetting the de-init one*/
		gu8_init_flag++;
		gu8_deInit_flag = 0;	
	}

    return err_var;
}

ERROR_STATUS Timer_DeInit(void)
{
	ERROR_STATUS err_var = E_OK;
	
	/*Checking the timer is de-initialized before or not*/
	if (gu8_deInit_flag)
	{
		err_var = E_NOK;
	} 
	else
	{
		/*Resetting three timer channels control registers*/
		TCCR0 = 0;
		TCCR1 = 0;
		TCCR2 = 0;
		
		/*Rising the de-init flag and resetting the init one*/
		gu8_deInit_flag++;
		gu8_init_flag = 0;		
	}
	
	return err_var;	
}

ERROR_STATUS Timer_Start(uint8_t au8_Timer_CH_NO, uint16_t au16_Timer_Count)
{
    ERROR_STATUS err_var = E_OK;
	
	/*Choosing which channel you want to start*/
    switch (au8_Timer_CH_NO)
    {   
        case TIMER_CH0:
			/*Validating timer0 maximum value*/
			if(au16_Timer_Count > TIMER_CH0_MAX_VAL)
			{
				/*Setting the OCR value to the maximum counts*/
	           OCR0 = TIMER_CH0_MAX_VAL;
			   err_var = E_NOK; 						
			}
			else
			{
				/*Setting the OCR value*/
				OCR0 = (uint8_t)au16_Timer_Count;
			}
			
			/*Starting the specified timer with specified pre-scaler*/
            switch (gu8_timer0_prescaler)
            {
                case TIMER_NO_CLOCK:
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    CLEAR_BIT(TCCR0 , TCCR0_CS00);
                    break;

                case TIMER_PRESCALER_NO:
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);
                    break;

                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    SET_BIT(TCCR0 , TCCR0_CS01);
                    CLEAR_BIT(TCCR0 , TCCR0_CS00);
                    break;

                case TIMER_PRESCALER_64:
                    CLEAR_BIT(TCCR0 , TCCR0_CS02);
                    SET_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);
                    break;

                case TIMER_PRESCALER_256:
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    CLEAR_BIT(TCCR0 , TCCR0_CS00);
                    break;

                case TIMER_PRESCALER_1024:
                    SET_BIT(TCCR0 , TCCR0_CS02);
                    CLEAR_BIT(TCCR0 , TCCR0_CS01);
                    SET_BIT(TCCR0 , TCCR0_CS00);
                    break;

                default: err_var = E_NOK;
            }
            break;

        case TIMER_CH1:
            
            /*Setting the OCR value*/
            OCR1A = au16_Timer_Count;
			
			/*Starting the specified timer with specified pre-scaler*/
            switch(gu8_timer1_prescaler)
            {
                case TIMER_NO_CLOCK:
                    CLEAR_BIT(TCCR1B , TCCR1B_CS12);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS11);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                case TIMER_PRESCALER_NO:
                    CLEAR_BIT(TCCR1B , TCCR1B_CS12);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS11);
                    SET_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR1B , TCCR1B_CS12);
                    SET_BIT(TCCR1B , TCCR1B_CS11);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                case TIMER_PRESCALER_64:
                    CLEAR_BIT(TCCR1B , TCCR1B_CS12);
                    SET_BIT(TCCR1B , TCCR1B_CS11);
                    SET_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                case TIMER_PRESCALER_256:
                    SET_BIT(TCCR1B , TCCR1B_CS12);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS11);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                case TIMER_PRESCALER_1024:
                    SET_BIT(TCCR1B , TCCR1B_CS12);
                    CLEAR_BIT(TCCR1B , TCCR1B_CS11);
                    SET_BIT(TCCR1B , TCCR1B_CS10);
                    break;

                default: err_var = E_NOK;

            }
            break;

        case TIMER_CH2:
			/*Validating timer0 maximum value*/
			if(au16_Timer_Count > TIMER_CH2_MAX_VAL)
			{
				/*Setting the OCR value to the maximum counts*/
				OCR2 = TIMER_CH2_MAX_VAL;
				err_var = E_NOK;
			}
			else
			{
				/*Setting the OCR value*/
				OCR2 = (uint8_t)au16_Timer_Count;		
			}
            
			/*Starting the specified timer with specified pre-scaler*/
            switch(gu8_timer2_prescaler)
            {
                case TIMER_NO_CLOCK:
                    CLEAR_BIT(TCCR2 , TCCR2_CS22);
                    CLEAR_BIT(TCCR2 , TCCR2_CS21);
                    CLEAR_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_NO:
                    CLEAR_BIT(TCCR2 , TCCR2_CS22);
                    CLEAR_BIT(TCCR2 , TCCR2_CS21);
                    SET_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR2 , TCCR2_CS22);
                    SET_BIT(TCCR2 , TCCR2_CS21);
                    CLEAR_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_32:
                    CLEAR_BIT(TCCR2 , TCCR2_CS22);
                    SET_BIT(TCCR2 , TCCR2_CS21);
                    SET_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_64:
                    SET_BIT(TCCR2 , TCCR2_CS22);
                    CLEAR_BIT(TCCR2 , TCCR2_CS21);
                    CLEAR_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_128:
                    SET_BIT(TCCR2 , TCCR2_CS22);
                    CLEAR_BIT(TCCR2 , TCCR2_CS21);
                    SET_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_256:
                    SET_BIT(TCCR2 , TCCR2_CS22);
                    SET_BIT(TCCR2 , TCCR2_CS21);
                    CLEAR_BIT(TCCR2 , TCCR2_CS20);
                    break;

                case TIMER_PRESCALER_1024:
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

ERROR_STATUS Timer_Stop(uint8_t au8_Timer_CH_NO)
{
    ERROR_STATUS err_var = E_OK;
	
	switch(au8_Timer_CH_NO)
	{
		case TIMER_CH0:
			/*Waiting until the time passes*/
			while(!GET_BIT(TIFR,TIFR_OCF0));
			
			/*Clearing the timer flag*/
			SET_BIT(TIFR,TIFR_OCF0);
			
			/*Stopping the timer*/
			TCCR0 &= TIMER_CNT_CLK_STOP;
			break;	

		case TIMER_CH1:
			/*Waiting until the time passes*/
			while(!GET_BIT(TIFR,TIFR_OCF1A));
		
			/*Clearing the timer flag*/
			SET_BIT(TIFR,TIFR_OCF1A);
			
			/*Stopping the timer*/
			TCCR1B &= TIMER_CNT_CLK_STOP;			
			break;

		case TIMER_CH2:
			/*Waiting until the time passes*/
			while(!GET_BIT(TIFR,TIFR_OCF2));
		
			/*Clearing the timer flag*/
			SET_BIT(TIFR,TIFR_OCF2);
			
			/*Stopping the timer*/
			TCCR2 &= TIMER_CNT_CLK_STOP;			
			break;
			
		default: err_var = E_NOK;						
	}
	
    return err_var;
}

ERROR_STATUS Timer_GetStatus(uint8_t au8_Timer_CH_NO, bool* Data)
{
    ERROR_STATUS err_var = E_OK;
	
	if (Data != NULL)
	{
		switch(au8_Timer_CH_NO)
		{
			case TIMER_CH0:
			
				/*Checking whether timer flag is raised or not*/
				if(GET_BIT(TIFR,TIFR_OCF0))
				{
					*Data = TIMER_FLAG_RAISED;
				}
				else
				{
					*Data = TIMER_FLAH_NOT_RAISED;
				}
				break;

			case TIMER_CH1:

				/*Checking whether timer flag is raised or not*/
				if(GET_BIT(TIFR,TIFR_OCF0))
				{
					*Data = TIMER_FLAG_RAISED;
				}
				else
				{
					*Data = TIMER_FLAH_NOT_RAISED;
				}
				break;

			case TIMER_CH2:

				/*Checking whether timer flag is raised or not*/
				if(GET_BIT(TIFR,TIFR_OCF0))
				{
					*Data = TIMER_FLAG_RAISED;
				}
				else
				{
					*Data = TIMER_FLAH_NOT_RAISED;
				}
				break;
			
			default: err_var = E_NOK;	
		}	
		
	} 
	else
	{
		/*The used pointer is NULL*/
		err_var = E_NOK;
	}
    return err_var;
}

ERROR_STATUS Timer_GetValue(uint8_t au8_Timer_CH_NO, uint16_t* pu16_Data)
{
    ERROR_STATUS err_var = E_OK;
	
	if (pu16_Data != NULL)
	{
		switch(au8_Timer_CH_NO)
		{
			case TIMER_CH0:
			
				/*Getting timer value*/
				*pu16_Data = (uint16_t)TCNT0;
				break;

			case TIMER_CH1:

				/*Getting timer value*/
				*pu16_Data = TCNT1;
				break;

			case TIMER_CH2:
	
				/*Getting timer value*/
				*pu16_Data = (uint16_t)TCNT2;
				break;
		
			default: err_var = E_NOK;
		}
	} 
	else
	{
		/*The used pointer is NULL*/
		err_var = E_NOK;
	}

    return err_var;
}

ERROR_STATUS Timer_SetValue(uint8_t au8_Timer_CH_NO, uint16_t au16_Data)
{
    ERROR_STATUS err_var = 0;
	
	switch(au8_Timer_CH_NO)
	{
		case TIMER_CH0:
		
			/*Setting timer value*/
			TCNT0 = (uint8_t)au16_Data;
			break;

		case TIMER_CH1:

			/*Setting timer value*/
			TCNT1 = au16_Data;
			break;

		case TIMER_CH2:
		
			/*Setting timer value*/
			TCNT2 = (uint8_t)au16_Data;
			break;
		
		default: err_var = E_NOK;
	}
	
    return err_var;
}