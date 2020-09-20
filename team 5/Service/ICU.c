/*
 * ICU.c
 *
 * Created: 2/18/2020 11:59:36 AM
 *  Author: MENA
 */ 
#include "ICU.h"

#define SwICU_EdgeRisiging 0
#define SwICU_EdgeFalling 1

#define  INT2_EN_GPIO GICR
#define  INT2_EN_BIT 5

#define  INT2_EDGE_GPIO MCUCSR
#define  INT2_EDGE_BIT 6
#define  tickTimeUs 64

#define MAX_NO_TICKS 256

uint8_t g_interruptCH_No = 0 ;
static volatile uint8_t g_interruptEdge ;
static volatile uint8_t g_timerCH ;
static volatile uint8_t g_fallingEdgeFlag = FALSE ;
static  uint8_t g_ovf_flag = FALSE ;



/**************************************************************************
 * Function 	: SetExternal_INT_Edge                                     *
 * Input 		: SwICU_Edge  the edge mode for the icu  
 
				interruptCH_No   ->  ICU_CH0							    *
								 ->   ICU_CH1							    *
							     ->   ICU_CH1							  *
 * Return 		: value of type ERROR_STATUS							  *
 * 				 					  *
 * Description  : set the edge mode of the external interrupt 			  *
 * 																		  *
 **************************************************************************/


static ERROR_STATUS SetExternal_INT_Edge( uint8_t SwICU_Edge ,uint8_t interruptCH_No ){
	uint8_t a_u8_error_state = E_OK ;
	 
	DIO_Cfg_s dioCfg_INT2;
	switch(interruptCH_No){
		case ICU_CH0 :
		break;
		case ICU_CH1:
		break;
		case ICU_CH2:
			
			
			dioCfg_INT2.GPIO = GPIOB;
			dioCfg_INT2.pins = BIT2;
			dioCfg_INT2.dir =INPUT;
			
			a_u8_error_state |= DIO_init(&dioCfg_INT2);
			
			
			if(SwICU_Edge== ICU_RISE_TO_FALL){
				
				SET_BIT(INT2_EDGE_GPIO , INT2_EDGE_BIT);
				}
			else if(SwICU_Edge== ICU_FALE_TO_RISE)
				CLEAR_BIT(INT2_EDGE_GPIO , INT2_EDGE_BIT);
			else
				a_u8_error_state |= E_NOK ;
			break;
		default:
			a_u8_error_state |= E_NOK ;
		
	}
	return a_u8_error_state  ;
}


/**************************************************************************
 * Function 	: SetExternal_INT_Edge                                     *
 * Input 		: SwICU_Edge  the edge mode for the icu  
 
				interruptCH_No   ->  ICU_CH0							    *
								 ->   ICU_CH1							    *
							     ->   ICU_CH1							  *
 * Return 		: value of type ERROR_STATUS							  *
 * 				 					  *
 * Description : enable the external interrupt and enable global interrupt*
 * 																		  *
 **************************************************************************/


static ERROR_STATUS SetExternal_INT_enable( uint8_t SwICU_Edge ,uint8_t interruptCH_No ){

	uint8_t a_u8_error_state = E_OK ;
	
	/*		initialize global interrupt				*/
		sei();
	
		switch(interruptCH_No){
			case ICU_CH0 :
			break;
			case ICU_CH1:
			break;
			case ICU_CH2:
				INT2_EN_GPIO |= 1 << INT2_EN_BIT ;
			break;
			default:
			a_u8_error_state |= E_NOK ;
	
		}
		return a_u8_error_state ;
}

/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				                                     					  *
 **************************************************************************/

ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg){
	
		uint8_t a_u8_error_state = E_OK ;

	
		Timer_cfg_s Timer_cfg ;
		
		if (Icu_Cfg == NULL)
		{
			a_u8_error_state |= E_NOK;
		}else{
			
			g_interruptCH_No = Icu_Cfg->ICU_Ch_No ;

			
			switch(Icu_Cfg->ICU_Ch_Timer){
				case ICU_TIMER_CH0 :
				
				Timer_cfg.Timer_CH_NO = TIMER_CH0 ;
				Timer_cfg.Timer_Mode = TIMER_MODE ;
				Timer_cfg.Timer_Polling_Or_Interrupt = TIMER_POLLING_MODE ;
				Timer_cfg.Timer_Prescaler = TIMER_PRESCALER_1024 ;
				
				// timer initialization 
				
				a_u8_error_state |=Timer_Init(&Timer_cfg);
				
				break;
				case ICU_TIMER_CH1 :
				a_u8_error_state |= E_NOK ;
				break;
				case ICU_TIMER_CH2 :
				a_u8_error_state |= E_NOK ;
				break;
				default:
				a_u8_error_state |= E_NOK ;
				
			}
			
		}
		
		
		return a_u8_error_state  ;
}


/***************************************************************************
 * Function		: Icu_ReadTime
 * Input		: 
 *				Icu_Channel --> ICU timer channel
 *									- ICU_TIMER_CH0
 *									- ICU_TIMER_CH1
 *									- ICU_TIMER_CH2
 *				Icu_EdgeToEdge -- > edges to calculate pusle time between:
 *									- ICU_RISE_TO_RISE
 *									- ICU_RISE_TO_FALL
 *									- ICU_FALE_TO_RISE					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/

ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel, uint8_t Icu_EdgeToEdge, uint32_t * Icu_Time){
	
	uint8_t a_u8_error_state = E_OK ;

	uint16_t no_of_ticks = 0 ;
	uint16_t timerOfTicks_Us  ;
	//set edge and channel global  to update and use in ISR
	
	g_interruptEdge = SwICU_EdgeRisiging;
	g_timerCH = Icu_Channel ;
	
	
	switch(Icu_Channel){
			case ICU_TIMER_CH0:
			
			a_u8_error_state |= SetExternal_INT_Edge(Icu_EdgeToEdge,g_interruptCH_No);
			a_u8_error_state |= SetExternal_INT_enable(Icu_EdgeToEdge,g_interruptCH_No) ;
			
			break;
			case ICU_TIMER_CH1 :
			break;
			case ICU_TIMER_CH2 :
			break;
			default:
			a_u8_error_state |= E_NOK ;
	}
	
	/* poll on the falling edge occurrence*/  
	while(!g_fallingEdgeFlag) ;
	
	
	a_u8_error_state |= Timer_GetValue(g_timerCH ,&no_of_ticks) ;
	a_u8_error_state |= Timer_GetStatus(TIMER_CH0 ,&g_ovf_flag );
	
	/*check if an ovf take place to add to time*/
	
	if (g_ovf_flag == TRUE)
	{
		no_of_ticks=MAX_NO_TICKS;
	}
	
	g_ovf_flag = FALSE ;
	
	
			/*calculate the timer of pulse in microsecond */
			
	timerOfTicks_Us = no_of_ticks * tickTimeUs ;
	
	*Icu_Time = timerOfTicks_Us ;
	
	return a_u8_error_state ;
}




ISR(INT2_vect){
	
	switch (g_interruptEdge){
			
          /*rising*/	
		  	
			case SwICU_EdgeRisiging :
			
		
				switch(g_timerCH){
					case ICU_TIMER_CH0 :
				
					Timer_Start(TIMER_CH0,MAX_NO_TICKS);
				
					/*update the control to start at falling edge*/
					INT2_EDGE_GPIO &= ~(1<<INT2_EDGE_BIT) ;
				
					g_interruptEdge = SwICU_EdgeFalling;
					break;
					default:
						break; 
				
					}
			
				break;
					/*falling*/
			
			case SwICU_EdgeFalling :
			
				
				switch(g_timerCH){
				
					case ICU_TIMER_CH0 :
				
					Timer_Stop(TIMER_CH0);
				
					//update the control to start at raising edge
				
					INT2_EDGE_GPIO |= 1<<INT2_EDGE_BIT ;
				
					g_interruptEdge = SwICU_EdgeRisiging;
					g_fallingEdgeFlag = TRUE ;
					break;
					default:
						break ;
					}
	break;
}
}