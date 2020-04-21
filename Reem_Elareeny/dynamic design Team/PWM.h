/*
 * PWM.h
 *
 * Created: 2/17/2020 8:05:11 PM
 *  Author: Ehab , Ramadan , Reem , Eman
 */ 
#ifndef PWM_H_
#define PWM_H_

/*********************************/
/*            MACROS             */
/*********************************/


#include "../Infrastructure/std_types.h"
#include "../Infrastructure/registers.h"

#define		PWM_CH0						(0)
#define		PWM_CH1A						(1)
#define		PWM_CH1B						(2)
#define		PWM_CH2						(3)

		
#define		PWM_PRESCALER_NO				(0)
#define		PWM_PRESCALER_8					(1)
#define		PWM_PRESCALER_32				(2)
#define		PWM_PRESCALER_64				(3)
#define		PWM_PRESCALER_128				(4)
#define		PWM_PRESCALER_256				(5)
#define		PWM_PRESCALER_1024				(6)

#define		WGM00							(0x40)
#define		WGM01							(0x08)
#define		COM01							(0x20)
#define		COM00							(0x10)
#define		PWM_CS00							(0x01)
#define		PWM_CS01							(0x02)
#define		PWM_CS02							(0x04)
#define		OC0								(0x08)

#define		WGM10							(0x100)
#define		WMG11							(0x200)
#define		WGM12							(0x08)
#define		WGM13							(0x10)
#define		COM1A0							(0x4000)
#define		COM1A1							(0x8000)
#define		COM1B0							(0x1000)
#define		COM1B1							(0x2000)
#define		PWM_CS10							(0x01)
#define		PWM_CS11							(0x02)
#define		PWM_CS12							(0x04)
#define		OC1A							(0x20)
#define		OC1B							(0x10)

#define		WGM20							(0x40)
#define		WGM21							(0x08)
#define		COM20							(0x10)
#define		COM21							(0x20)
#define		PWM_CS20							(0x01)
#define		PWM_CS21							(0x02)
#define		PWM_CS22							(0x04)
#define		OC2							(0x80)

#define		F_31370							(31370ul)
#define		F_4000							(4000ul)
#define		F_1000							(1000ul)
#define		F_500							(500ul)
#define		F_245							(245ul)	
#define		F_120							(120ul)	
#define		F_30							(30ul)	

#define		PWM0_STOP					(TCCR0>>=3);\
										(TCCR0<<=3);

#define		PWM1_STOP					(TCCR1B>>=3);\
										(TCCR1B<<=3);

#define		PWM2_STOP					(TCCR2>>=3);\
										(TCCR2<<=3);
										
#define		BITS_8_RESOLUTION			(255ul)
#define		PERCENT						(100)

typedef struct Pwm_Cfg_s
{
	uint8_t Channel;
	uint8_t Prescaler;
}Pwm_Cfg_s;

/*********************************/
/*    FUNCTIONS DECLARATION      */
/*********************************/

/**
 * Description: Initializes the hardware PWM based on a pre-configured struct
 * @param Timer_cfg : Pointer to the configuration struct 
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg);

/**
 * Description: Starts generating the PWM signal on the corresponding pins
 * Note: Phase Correct PWM only 
 * @param Channel : The channel to generate the PWM signal on
 *							- 0 -> PWM_CH0
 *							- 1 -> PWM_CH1A
 *							- 2 -> PWM_CH1B
 *							- 3 -> PWM_CH2 
 * @param Duty : The duty cycle of the PWM signal takes values from (0~100)
 * @param Frequency : The Frequency of the PWM signal
 * for PWM_CH0 & PWM_CH1A:1B : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * for PWM_CH2 : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 1000  -> F_1000  and gives (980    Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 245   -> F_245   and gives (245    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
extern ERROR_STATUS Pwm_Start(uint8_t Channel,uint8_t Duty,uint32_t Frequency);

/**
 * Description: Updates the parameters of a previously started PWM signal
 * @param Timer_cfg : Pointer to the configuration struct 
 * @param Channel : The channel to generate the PWM signal on
 *							- 0 -> PWM_CH0
 *							- 1 -> PWM_CH1A
 *							- 2 -> PWM_CH1B
 *							- 3 -> PWM_CH2
 * @param Duty : The duty cycle of the PWM signal takes values from (0~100)
 * @param Frequency : The Frequency of the PWM signal
 * for PWM_CH0 & PWM_CH1A:1B : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * for PWM_CH2 : takes the following values :
 *						- 31370 -> F_31370 and gives (31,372 Hz)
 *						- 4000  -> F_4000  and gives (3921   Hz)
 *						- 1000  -> F_1000  and gives (980    Hz)
 *						- 500   -> F_500   and gives (490    Hz)
 *						- 245   -> F_245   and gives (245    Hz)
 *						- 120   -> F_120   and gives (122    Hz)
 *						- 30    -> F_30    and gives (31     Hz)
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
extern ERROR_STATUS Pwm_Update(uint8_t Channel,uint8_t Duty,uint32_t Frequency);

/**
 * Description: Stops a previously started PWM signal
* @param Channel : The channel to generate the PWM signal on
*							- 0 -> PWM_CH0
*							- 1 -> PWM_CH1A
*							- 2 -> PWM_CH1B
*							- 3 -> PWM_CH2
 * @return function status :
 *							- 0 -> E_NOK
 *							- 1 -> E_OK
 */
extern ERROR_STATUS Pwm_Stop(uint8_t Channel);

#endif /* PWM_H_ */