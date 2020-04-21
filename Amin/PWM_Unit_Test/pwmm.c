#include "PWM.h"
#define Max_duty 100
#define Top_value 255
#define Zero 0
#define T1_PWM_FAST 0xA108
static uint32 On_time_value=Zero;

 /*Describtion: this function initialize the  pwm for both motors 1 and 2  */
extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s *Pwm_Cfg){
	ERROR_STATUS retval=E_OK;
	Timer_cfg_s Pwm;
	if(Pwm_Cfg!=NULL){
            switch(Pwm_Cfg->Channel){
            case PWM_CH1A:
                if(Pwm_Cfg->Prescaler>=PWM_PRESCALER_NO&&Pwm_Cfg->Prescaler<=PWM_PRESCALER_1024){
	Pwm.Timer_CH_NO=TIMER_CH1;
	Pwm.Timer_Mode=TIMER_MODE;
	Pwm.Timer_Polling_Or_Interrupt=T1_POLLING;                 //T1_COMP_MODE_OCR1A_TOP;
	Pwm.Timer_Prescaler=TIMER_PRESCALER_256;
	retval&=Timer_Init(&Pwm);}
	else{
        retval=E_NOK;
	}
	break;
	case PWM_CH1B:
	     if(Pwm_Cfg->Prescaler>=PWM_PRESCALER_NO&&Pwm_Cfg->Prescaler<=PWM_PRESCALER_1024){
	Pwm.Timer_CH_NO=TIMER_CH1;
	Pwm.Timer_Mode=TIMER_MODE;
	Pwm.Timer_Polling_Or_Interrupt=T1_POLLING;                 //T1_COMP_MODE_OCR1A_TOP;
	Pwm.Timer_Prescaler=TIMER_PRESCALER_256;
	retval&=Timer_Init(&Pwm);
	}else{
        retval=E_NOK;
	}
	break;
	case PWM_CH0:
	     if(Pwm_Cfg->Prescaler>=PWM_PRESCALER_NO&&Pwm_Cfg->Prescaler<=PWM_PRESCALER_1024){
	    retval=E_OK;}
	    else{
            retval=E_NOK;
	    }
	    break;
    case PWM_CH2:
         if(Pwm_Cfg->Prescaler>=PWM_PRESCALER_NO&&Pwm_Cfg->Prescaler<=PWM_PRESCALER_1024){
	    retval=E_OK;}
	    else{
            retval=E_NOK;
	    }
        break;
    default:
        retval=E_NOK;
	}
	}else{
        retval=NULL_PTR_ERROR;
	}
	return retval;
}

 /*Describtion: this function start the  pwm for specific motor with specific speed  */
extern ERROR_STATUS Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy){
	ERROR_STATUS retval=E_OK;
	switch(Channel){
case PWM_CH0:
    if(Duty>=0&&Duty<=100){
    retval=E_OK;
    }else{
    retval=E_NOK;}
    break;
    case PWM_CH1A:
        if(Duty>=0&&Duty<=100){
      On_time_value=((Duty*Top_value)/Max_duty);
	OCR1A=On_time_value;
	OCR1B=On_time_value;
	retval&=Timer_Start(TIMER_CH1,Zero);
	TCCR1|=T1_PWM_FAST;
	retval=E_OK;}
	else{
        retval=E_NOK;
	}
	break;
	case PWM_CH2:
         if(Duty>=0&&Duty<=100){
    retval=E_OK;
    }else{
    retval=E_NOK;}
    break;
    default:
        retval=E_NOK;
	}

	return retval;
}

 /*Describtion: this function updatethe  pwm of specific motor with new speed  */
extern ERROR_STATUS Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy){
ERROR_STATUS retval=E_OK;
	switch(Channel){
case PWM_CH0:
    if(Duty>=0&&Duty<=100){
    retval=E_OK;
    }else{
    retval=E_NOK;}
    break;
    case PWM_CH1A:
        if(Duty>=0&&Duty<=100){
      On_time_value=((Duty*Top_value)/Max_duty);
	OCR1A=On_time_value;
	OCR1B=On_time_value;
	retval&=Timer_Start(TIMER_CH1,Zero);
	TCCR1|=T1_PWM_FAST;
	retval=E_OK;}
	else{
        retval=E_NOK;
	}
	break;
	case PWM_CH2:
         if(Duty>=0&&Duty<=100){
    retval=E_OK;
    }else{
    retval=E_NOK;}
    break;
    default:
        retval=E_NOK;
	}

	return retval;
}

 /*Describtion: this function stops the pwm by stopping the timer  */
extern ERROR_STATUS Pwm_Stop(uint8 Channel){
	ERROR_STATUS retval=E_OK;

	switch(Channel){
case PWM_CH0:
    retval&=Timer_Stop(TIMER_CH0);
    break;

case PWM_CH1A:
   retval&=Timer_Stop(TIMER_CH1);
    break;

    case PWM_CH2:
    retval&=Timer_Stop(TIMER_CH1);
    break;

    default:
        retval=E_NOK;
	}

	return retval;
}
