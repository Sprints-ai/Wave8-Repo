 #include "motor.h"
 #include "DIO_mock.h"
 #include "PWM_mock.h"
#define  MOTOR_FREQUENCY 1


 /*Describtion: this function initialize the motor direction for motor 1 and 2 and intialize the enable pin for both motors*/
 ERROR_STATUS Motor_Init(uint8 Motor_Number){
	  ERROR_STATUS retval=E_OK;
 		 DIO_Cfg_s ST_dio1;
		 DIO_Cfg_s ST_dio2;
		Pwm_Cfg_s ST_Pwm;
		  switch (Motor_Number)
		 {
		 case (MOTOR_1):
		 	/* set IN1,2,enable as digital output */
			ST_dio1.GPIO = GPIOD;
		 	ST_dio1.pins = BIT2|BIT3|BIT4;
		 	ST_dio1.dir = HIGH;
			retval&=DIO_init(&ST_dio1);
			//pwm a1
			ST_Pwm.Channel = PWM_CH1A;
		 	ST_Pwm.Prescaler = T1_PRESCALER_256;
		 	retval&=Pwm_Init(&ST_Pwm);
		 	return retval;
			break;
			case (MOTOR_2):
			/* set IN3 ,4 ,enable as digital output */
			ST_dio2.GPIO = GPIOD;
		 	ST_dio2.pins = BIT5|BIT6|BIT7;
		 	ST_dio2.dir = HIGH;
			retval&=DIO_init(&ST_dio2);
			//pwm b1
			ST_Pwm.Channel = PWM_CH1B;
		 	ST_Pwm.Prescaler = T1_PRESCALER_256;
		 	retval&=Pwm_Init(&ST_Pwm);
			return retval;
			break;
			default:
                retval=E_NOK;
		 }
 return retval; ;
 }

 /*Describtion: this function chose motor and set its direction */
 ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction){
     ERROR_STATUS retval=E_OK;
	switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				retval&=DIO_Write(GPIOD, BIT2, OUTPUT);
				retval&=DIO_Write(GPIOD, BIT3, LOW);
				retval&=E_OK;
			}
			else if(Motor_Direction == MOTOR_BACKWARD)
			{
				retval&=DIO_Write(GPIOD, BIT2, LOW);
				retval&=DIO_Write(GPIOD, BIT3, OUTPUT);
				retval&=E_OK;
			}else{
			    retval=E_NOK;
			}
			return retval;
			break;
			case (MOTOR_2):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				retval&=DIO_Write(GPIOD, BIT6, OUTPUT);
				retval&=DIO_Write(GPIOD, BIT7, LOW);
				retval&=E_OK;
			}
			else if(Motor_Direction == MOTOR_BACKWARD)
			{
				retval&=DIO_Write(GPIOD, PIN6, LOW);
				retval&=DIO_Write(GPIOD, PIN7, OUTPUT);
				retval&=E_OK;
			}else{
			    retval=E_NOK;
			}
			return retval;
			break;
			default:
                retval=E_NOK;
		}
 return retval;
 }


 /*Describtion: this function choose motor and set its direction and speed */
 ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed){
     ERROR_STATUS retval=E_OK;
	switch(Motor_Number)
		{
		case (MOTOR_1):
		    if(Mot_Speed<=100&&Mot_Speed>=0){
			retval&=Pwm_Start(PWM_CH1A, Mot_Speed, MOTOR_FREQUENCY);
			retval&=E_OK;}
			else{
                retval=E_NOK;
			}
			break;
		case (MOTOR_2):
		    if(Mot_Speed<=100&&Mot_Speed>=0){
			retval&=Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
			retval=E_OK;}
			else{
                retval=E_NOK;
			}
			break;
        default:
            retval=E_NOK;
		}
return retval;
 }


 /*Describtion: this function choose motor and update its direction and speed */
 ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed){
     ERROR_STATUS retval=E_OK;
	 switch(Motor_Number)
		{
		case (MOTOR_1):
		    if(Speed<=100&&Speed>=0){
			retval&=Pwm_Update(PWM_CH1A,Speed, MOTOR_FREQUENCY);
			retval=E_OK;}
			else{
                retval=E_NOK;
			}
			break;
		case (MOTOR_2):
		     if(Speed<=100&&Speed>=0){
			retval&=Pwm_Update(PWM_CH1B,Speed, MOTOR_FREQUENCY);
			retval&=E_OK;}
			else{
                retval=E_NOK;
			}
			break;
        default:
            retval=E_NOK;
		}
return retval;
 }




 /*Describtion: this function choose motor and stop it */

 ERROR_STATUS Motor_Stop(uint8 Motor_Number){
     ERROR_STATUS retval=E_OK;
	switch(Motor_Number)
		{
		case MOTOR_1:
			retval&=Pwm_Stop(PWM_CH1A);
			retval&=DIO_Write(GPIOD, PIN2, LOW);
			retval&=DIO_Write(GPIOD, PIN3, LOW);
			retval&=E_OK;
			break;
		case MOTOR_2:
			retval&=Pwm_Stop(PWM_CH1B);
			retval&=DIO_Write(GPIOD, PIN6, LOW);
			retval&=DIO_Write(GPIOD, PIN7, LOW);
			retval&=E_OK;
			break;
        default:
            retval=E_NOK;
			 }
         return retval;
 }


