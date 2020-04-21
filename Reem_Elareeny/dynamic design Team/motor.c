/*
 * motor.c
 *
 * Created: 2/18/2020 3:07:07 PM
 *  Author: Ema
 */

#include "motor.h"

/************************************************************************/
/*				               Global Var                               */
/************************************************************************/
static uint8_t Motor1_flag = FALSE;
static uint8_t Motor2_flag = FALSE;
static uint8_t Motor1_Init_flag = FALSE;
static uint8_t Motor2_Init_flag = FALSE;


ERROR_STATUS Motor_Init(uint8_t Motor_Number)
{
	ERROR_STATUS ERROR= E_OK;

	/*setting the direction of all motors pins*/
	DIO_Cfg_t dio_cfg_Mot1A = {MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,OUTPUT};
	ERROR = DIO_init(&dio_cfg_Mot1A);
	DIO_Cfg_t dio_cfg_Mot1B = {MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,OUTPUT};
	ERROR = DIO_init(&dio_cfg_Mot1B);

	DIO_Cfg_t dio_cfg_Mot2A = {MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,OUTPUT};
	ERROR = DIO_init(&dio_cfg_Mot2A);
	DIO_Cfg_t dio_cfg_Mot2B = {MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,OUTPUT};
	ERROR = DIO_init(&dio_cfg_Mot2B);

	switch(Motor_Number)
	{
		case MOTOR_1:
		Motor1_Init_flag = TRUE;
		break;
		case MOTOR_2:
		Motor2_Init_flag = TRUE;
		break;
		default:
		ERROR = ERROR_INVALID_PARAMETER;
		break;
	}
	return ERROR;
}

ERROR_STATUS Motor_Direction(uint8_t Motor_Number, uint8_t Motor_Direction)
{
	ERROR_STATUS ERROR = E_OK;

	/*Setting the direction of the motors by changing the polarity through A and B*/
	switch(Motor_Number){

		case MOTOR_1:
        if(Motor1_Init_flag == TRUE)
        {
            switch(Motor_Direction){
			case MOTOR_STOP:
			DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,0);
			break;

			case MOTOR_FORWARD:
			DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,HIGH);
			DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,HIGH);
			DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,0);
			break;

			case MOTOR_BACKWARD:

			DIO_Write(MOTOR_EN_1_GPIO,MOTOR_EN_1_BIT,HIGH);
			DIO_Write(MOTOR_OUT_1A_GPIO,MOTOR_OUT_1A_BIT,0);
			DIO_Write(MOTOR_OUT_1B_GPIO,MOTOR_OUT_1B_BIT,HIGH);
			break;

			default:
			ERROR = ERROR_INVALID_PARAMETER;
			break;
		}
        }
        else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
		break;
		case MOTOR_2:
        if(Motor2_Init_flag == TRUE)
        {
            switch(Motor_Direction){
			case MOTOR_STOP:
			DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,0);
			break;

			case MOTOR_FORWARD:
			DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,HIGH);
			DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,HIGH);
			DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,0);
			break;

			case MOTOR_BACKWARD:
			DIO_Write(MOTOR_EN_2_GPIO,MOTOR_EN_2_BIT,HIGH);
			DIO_Write(MOTOR_OUT_2A_GPIO,MOTOR_OUT_2A_BIT,0);
			DIO_Write(MOTOR_OUT_2B_GPIO,MOTOR_OUT_2B_BIT,HIGH);
			break;

			default:
			ERROR = ERROR_INVALID_PARAMETER;
			break;
		}
        }
		else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
		break;
		default:
		ERROR = ERROR_INVALID_PARAMETER;
		break;
	}

	return ERROR;
}

ERROR_STATUS Motor_Start(uint8_t Motor_Number, uint8_t Mot_Speed)
{
	ERROR_STATUS ERROR = E_OK;

	Pwm_Cfg_s pwm_cfg_CH1A = {PWM_CH1A,PWM_PRESCALER_64};
	Pwm_Cfg_s pwm_cfg_CH1B = {PWM_CH1B,PWM_PRESCALER_64};

	/*Start the motor by starting the pwm with the required speed*/
	switch(Motor_Number)
	{
		case MOTOR_1:
        if(Motor1_Init_flag == TRUE)
        {
            ERROR = Pwm_Init(&pwm_cfg_CH1A);
            ERROR = Pwm_Start(PWM_CH1A,Mot_Speed,/*200*/ F_120); //Reem
            Motor1_flag = MOTOR_STARTED;
        }
        else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
		break;
		case MOTOR_2:
        if(Motor1_Init_flag == MOTOR_INITIALIZED)
        {
            ERROR = Pwm_Init(&pwm_cfg_CH1B);
            ERROR = Pwm_Start(PWM_CH1B,Mot_Speed,/*200*/ F_120); //Reem
            Motor2_flag = MOTOR_STARTED;
        }
        else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
		break;
		default:
		ERROR = ERROR_INVALID_PARAMETER;
		break;
	}

	return ERROR;
}

ERROR_STATUS Motor_SpeedUpdate(uint8_t Motor_Number, uint8_t Speed)
{
	ERROR_STATUS ERROR = E_OK;

    switch(Motor_Number)
    {
        case MOTOR_1:
        if(Motor1_flag == TRUE)
        {
            ERROR = Pwm_Start(PWM_CH1A,Speed,/*200*/ F_120); //Reem
        }
        else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
        break;
        case MOTOR_2:
        if(Motor2_flag == TRUE)
        {
            ERROR = Pwm_Start(PWM_CH1B,Speed,/*200*/ F_120); //Reem
        }
        else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
        break;
        default:
        ERROR = ERROR_INVALID_PARAMETER;
        break;
    }

	return ERROR;
}

ERROR_STATUS Motor_Stop(uint8_t Motor_Number)
{
	ERROR_STATUS ERROR = E_OK;

	/*stop the motor by stoping the pwm*/
	switch(Motor_Number)
	{
		case MOTOR_1:
        if(Motor1_flag == TRUE)
        {
            Pwm_Stop(PWM_CH1A);
            Motor1_flag = MOTOR_STOP;
        }
		else
        {
            ERROR = ERROR_STOP_WITHOUT_START;
        }
		break;

		case MOTOR_2:
        if(Motor2_flag == TRUE)
        {
            Pwm_Stop(PWM_CH1B);
            Motor2_flag = MOTOR_STOP;
        }
		else
        {
            ERROR = ERROR_MODULE_NOT_INITIALIZED;
        }
		break;
		default:
		ERROR = ERROR_INVALID_PARAMETER;
		break;
	}

	return ERROR;
}

ERROR_STATUS Motor_GetStatus(uint8_t Motor_Number, uint8_t* Mot_status)
{
	ERROR_STATUS ERROR = E_OK;

    if(Mot_status == NULL)
    {
        ERROR = ERROR_NULL_POINTER;
    }
    else
    {
        switch(Motor_Number)
        {
            case MOTOR_1:
            *Mot_status = Motor1_Init_flag;
            break;
            case MOTOR_2:
            *Mot_status = Motor2_Init_flag;
            break;
            default:
            ERROR = ERROR_INVALID_PARAMETER;
            break;
        }
    }

	return ERROR;
}
