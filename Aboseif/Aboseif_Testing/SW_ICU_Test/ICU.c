/*
 * ICU.c
 *
 * Created: 2020-02-18 12:12:39 PM
 *  Author: EbrahimOseif
 */ 


/************************************************************************/
/*				               Includes                                 */
/************************************************************************/

#include "ICU.h"


/************************************************************************/
/*				 Global / Static Variables						       */
/************************************************************************/

volatile uint32_t * gu32_timeCount = 0 ;  /* null */
volatile uint16_t gu16_RiseToRise = 0; /* dont initialize global with zero cause of overhead on startup code*/

volatile uint16_t gu16_RiseToFall = 0;
/* follow code guideline naming vars */

uint16_t TICK_TIME = 0 ;
volatile uint8_t gu8_OVFs = 0;

#define  CPU_F		16
#define  Prescaler	1024

/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/


 Icu_cfg_s Icu_Cfg ={
	ICU_CH2,       	  /* To choose the External Interrupt number */
	ICU_TIMER_CH0     /* To choose the Timer number */	
};



//static void extInt_CBK_Func(void);

/************************************************************************/
/*				          Functions' IMPLEMENTATION                     */
/************************************************************************/

/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_u8_status							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg){
	 
	 ERROR_STATUS u8_status = E_OK;
	 
     /*
	  TIMER initialize to count during edges
     */
		if (Icu_Cfg == NULL)
		{
			u8_status = E_NOK;
		}
		else{
        Timer_cfg_s str_Timer_cfg = {
        	Icu_Cfg->ICU_Ch_Timer,
        	TIMER_MODE,
        	TIMER_INTERRUPT_MODE,
        	TIMER_PRESCALER_1024
        };
        
		 TICK_TIME = Prescaler / CPU_F;
		 
	 u8_status = Timer_Init(&str_Timer_cfg);
	 
	 u8_status = Timer_Start(Icu_Cfg->ICU_Ch_Timer, 0);
	
/*
	external interrupts to sense the edges
*/
			
			u8_status = EXT_INT_Enable(Icu_Cfg->ICU_Ch_No);
			u8_status = EXT_INT_SetEdge(EXT_INT2_RISING_EDGE);
			
//			set_callback(extInt_CBK_Func);
	}
	return u8_status;
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
 * Return 		: value of type ERROR_u8_status							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between 2 edges				       *
 ***************************************************************************/

ERROR_STATUS Icu_ReadTime(uint8_t Icu_Channel,
						  uint8_t Icu_EdgeToEdge,
						  uint16_t* Icu_Time)
{
	ERROR_STATUS u8_status = E_OK;
	
	
		switch(Icu_Channel){
			
			case ICU_TIMER_CH2:
			case ICU_TIMER_CH1:
			break;
			
			case ICU_TIMER_CH0:
			
			
					switch(Icu_EdgeToEdge){
						
						case ICU_RISE_TO_RISE:
								
								*Icu_Time = gu16_RiseToRise *TICK_TIME;
						break;
						case ICU_RISE_TO_FALL:
						
								*Icu_Time = gu16_RiseToFall *TICK_TIME ;

						break;
						case ICU_FALE_TO_RISE:
						
								*Icu_Time = (gu16_RiseToRise - gu16_RiseToFall)* TICK_TIME;
						break;
						
						default: 
								u8_status = E_NOK;
					}
	
			break;
			
			default:
					u8_status = E_NOK;
			}
		return u8_status;
}


/* External Interrupt 2 vector */

ISR(INT2_vect)
{
	static volatile uint8_t edgeDetect = EXT_INT2_RISING_EDGE;
	
		switch(edgeDetect){
			
	            case EXT_INT2_RISING_EDGE :
	            
	            		
	            		Timer_Start(ICU_TIMER_CH0, 0);
	            	
						Timer_GetValue(ICU_TIMER_CH0, &gu16_RiseToRise);	

	            		EXT_INT_Disable(ICU_CH2);
	            		EXT_INT_SetEdge(EXT_INT2_FALLING_EDGE);
	            		EXT_INT_Enable(ICU_CH2);


	            		//MCUCSR = ~ 0x40;
	            		edgeDetect = EXT_INT2_FALLING_EDGE;
	            
	            	  break;
					  
	            case  EXT_INT2_FALLING_EDGE:
	            
	            	Timer_GetValue(ICU_TIMER_CH0, &gu16_RiseToFall);
	            
	            	EXT_INT_Disable(ICU_CH2);
	            	EXT_INT_SetEdge(EXT_INT2_RISING_EDGE);
	            	EXT_INT_Enable(ICU_CH2);
	            	
	            	//MCUCSR |= 0x40;
	            	edgeDetect = EXT_INT2_RISING_EDGE;
					
					/*PORTC_DIR = 0xff;
					PORTC_DATA = gu16_RiseToFall;*/
	            
				break;
	            	
					default: break;
		}
		
}

/*timer overflow vector */

ISR(TIMER0_OVF_vect){
	
gu8_OVFs++;
//Timer_Stop(0);

}
