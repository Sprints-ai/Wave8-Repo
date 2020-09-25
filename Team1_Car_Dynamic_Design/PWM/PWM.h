/***************************************************/
/* Layer: MCAL                                     */
/* Module: PWM                                     */
/* File: PWM.h                                     */
/* Author: Ahmed Ashraf                                  */
/* Description: PWM header file                    */
/***************************************************/

#ifndef __PWM_H__
#define __PWM_H__

/************************************************************************/
/*                              General macros                          */
/************************************************************************/

#define		PWM_CH0							(0)
#define		PWM_CH1							(1)
#define		PWM_CH2							(2)
#define		PWM_CH3							(3)

#define		PWM_31KHZ_FREQ					(0)
#define		PWM_4KHZ_FREQ					(1)
#define		PWM_1KHZ_FREQ					(2)
#define		PWM_500HZ_FREQ					(3)
#define		PWM_245HZ_FREQ					(4)
#define		PWM_120HZ_FREQ					(5)
#define		PWM_30HZ_FREQ					(6)

#define		E_OK							(1)
#define		E_NOK							(-1)

/************************************************************************/
/*                            User defined data types                   */
/************************************************************************/

typedef sint8_t	ERROR_STATUS;

/************************************************************************/
/*                      PWM Functions prototypes                        */
/************************************************************************/

/*********************************************************************************/
/* Function: ERROR_STATUS pwm_Init(uint8_t Channel);					         */
/* Type: public                                                                  */
/* Input parameters: PWM channel 												 */
/* Return type : Function ERROR_STATUS                                           */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/
ERROR_STATUS pwm_Init(uint8_t PWM_Channel);

/*******************************************************************************************/
/* Function: ERROR_STATUS pwm_Start(uint8_t PWM_Channel, uint8_t Duty, uint8_t Frequency); */
/* Type: public																			   */
/* Input parameters: PWM channel, Duty cycle(0:255), PWM signal frequency			   	   */
/* Return type : Function ERROR_STATUS                                                     */
/*                                                                                         */
/* Description: starts the PWM on the dedicated channel with the required duty             */
/*				cycle and frequency                                                        */
/*-------------------------------------------------------                                  */
/*(IN timer 0) there are only 5 available Frequencies:                                     */
/*-------------------------------------------------------                                  */
/*Frequency (NO-Prescaler) --> 31,250HZ                                                    */
/*Frequency (Prescaler 8) --> 3,906HZ                                                      */
/*Frequency (Prescaler 64) --> 490HZ                                                       */
/*Frequency (Prescaler 256) --> 122HZ                                                      */
/*Frequency (Prescaler 1024) --> 31HZ                                                      */
/*--------------------------------------------------------                                 */
/*(IN timer 2) there are only 7 available Frequencies:                                     */
/*-------------------------------------------------------                                  */
/*Frequency (NO-Prescaler) --> 31,250HZ                                                    */
/*Frequency (Prescaler 8) --> 3,906HZ                                                      */
/*Frequency (Prescaler 32) --> 980HZ                                                       */
/*Frequency (Prescaler 64) --> 490HZ                                                       */
/*Frequency (Prescaler 128) --> 245HZ                                                      */
/*Frequency (Prescaler 256) --> 122HZ                                                      */
/*Frequency (Prescaler 1024) --> 31HZ                                                      */
/*-------------------------------------------------------                                  */
/*((all this calculations are for phase correct mode))                                     */
/*all this calculation for F_CPU 16MHz                                                     */
/*******************************************************************************************/
ERROR_STATUS pwm_Start(uint8_t PWM_Channel, uint8_t Duty, uint8_t Frequency);

/********************************************************************************************/
/* Function: ERROR_STATUS pwm_Update(uint8_t PWM_Channel, uint8_t Duty, uint8_t Frequency); */
/* Type: public                                                                             */
/* Input parameters: PWM channel, Duty cycle(0:255), PWM signal frequency                   */
/* Return type : Function ERROR_STATUS                                                      */
/*                                                                                          */
/* Description: updates the duty cycle and frequency of the dedicated channel               */
/********************************************************************************************/
ERROR_STATUS pwm_Update(uint8_t PWM_Channel, uint8_t Duty, uint8_t Frequency);

/*********************************************************************************/
/* Function: ERROR_STATUS pwm_Stop(uint8_t PWM_Channel);                         */
/* Type: public                                                                  */
/* Input parameters: PWM channel                                                 */
/* Return type : Function ERROR_STATUS                                           */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the pre-scaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/
ERROR_STATUS pwm_Stop(uint8_t PWM_Channel);

#endif /* __PWM_H__ */