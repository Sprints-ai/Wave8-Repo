/*
 * US.c
 *
 *  Created: 2/17/2020 2:19:05 PM
 *  Author: Ramadan
 */ 

#define F_CPU 16000000ul

#include "Us.h"
#include "../Infrastructure/registers.h"
#include <util/delay.h>
#include "../MCAL/DIO.h"
#include "ICU (1).h"

#define U_S_Trigger_PORT	GPIOB
#define U_S_Trigger_PIN    	BIT3			//pin 3 for trigger ultrasonic signal

#define U_S_Echo_PORT   	GPIOB
#define U_S_Echo_PIN    	BIT2			//pin 2 for echo ultrasonic signal

uint32_t *Icu_Time = NULL;
/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/
volatile uint16_t distance;
//make an object from ICU configuration system to set external interrupt channel and timer channel
Icu_cfg_s Icu_cfg_US;
//make an object of structure if trigger pin
DIO_Cfg_t DIO_Cfg_US_T;
//make an object of structure if Echo pin
DIO_Cfg_t DIO_Cfg_US_E;

EnmUSError_t Us_Init(void){
	
	/***Local variable storing the error number of the function***/
	uint8_t Err_Status = E_OK;

	//Initialize trigger us config structure
	DIO_Cfg_US_T.GPIO = U_S_Trigger_PORT;
	DIO_Cfg_US_T.pins = U_S_Trigger_PIN;
	DIO_Cfg_US_T.dir  =  OUTPUT;
	
	//Initialize Echo us config structure
	DIO_Cfg_US_E.GPIO = U_S_Echo_PORT;
	DIO_Cfg_US_E.pins = U_S_Echo_PIN;
	DIO_Cfg_US_E.dir  = INPUT;
	
	//use external interrupt 2 we will pass it in IC init()
	Icu_cfg_US.ICU_Ch_No = ICU_CH2; 
	//use Timer channel 0                    
	Icu_cfg_US.ICU_Ch_Timer = ICU_TIMER_CH0; //Reem
	/*set trigger pin in ultrasonic as output pin*/
	Err_Status = DIO_init(&DIO_Cfg_US_T);

	/*set echo pin in ultrasonic as input pin __external interrupt2__*/
	Err_Status = DIO_init(&DIO_Cfg_US_E);
	
	//initiate the ICU to use it to calculate the On time of the ECHO signal
	Err_Status = Icu_Init(&Icu_cfg_US);
	
	/***return the value of the error function**/
	return Err_Status;
}


/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


EnmUSError_t Us_Trigger(void){
	/***Local variable storing the error number of the function***/
	uint8_t Err_Status = 0;
	
	Err_Status=E_OK;
	
	/*write zero on trigger input pin */
	DIO_Write(U_S_Trigger_PORT,U_S_Trigger_PIN,LOW);
	
	/*then write One to trigger pin to send wave at 40 KHZ*/
	DIO_Write(U_S_Trigger_PORT,U_S_Trigger_PIN,HIGH);
	/*wait again for 10 micro seconds*/
	_delay_us(10);
	/*After sending wave by trigger then write 0 to trigger pin again*/
	DIO_Write(U_S_Trigger_PORT,U_S_Trigger_PIN,LOW);
	
	return Err_Status;
}

/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/


EnmUSError_t Us_GetDistance(uint16_t *Distance){
	/***Local variable storing the error number of the function***/
	uint8_t Err_Status = 0;
	
	/**check if the passing pointer is null pointer ***/
	if (Distance == NULL)
	 {
		 Err_Status = NULL_PTR1;
	 }
	 else
	 {
		 /***read the value of the ICU**/
		Icu_ReadTime(ICU_TIMER_CH2,ICU_RISE_TO_FALL,Icu_Time);
		/**storing the value of icu reading***/
		*Distance = (uint16_t) ((64*(*Icu_Time))/58);      //prescaler 1024
		Err_Status=E_OK;
	 }
	 
	/***return the value of the error function**/
	return Err_Status;
}