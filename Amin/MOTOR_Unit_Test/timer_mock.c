#include "Timer_mock.h"

static uint8  gu8_timer0PreScaler=0;
static uint8  gu8_timer1PreScaler=0;
static uint8  gu8_timer2PreScaler=0;

 /*Describtion: this function init the timer with user configs timer 0,1,2 and timer mode and prescaler   */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg){
    ERROR_STATUS retval=E_OK;
    uint8 timer_ch=Timer_cfg->Timer_CH_NO;
    uint8 timer_mode=Timer_cfg->Timer_Mode;
    uint8 timer_polinterupt=Timer_cfg->Timer_Polling_Or_Interrupt;
    uint8 prescaler=Timer_cfg->Timer_Prescaler;
    if(Timer_cfg!=NULL){
switch(timer_ch){
case TIMER_CH0:
switch(timer_polinterupt){
	case TIMER_POLLING_MODE	:
	    retval&=E_OK;
	break;
	case TIMER_INTERRUPT_MODE:
	    retval&=E_OK;
	break;
	default:
        retval&=E_NOK;
}
switch (prescaler){
	case TIMER_NO_CLOCK:
	gu8_timer0PreScaler=T0_NO_CLOCK;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_NO:
	gu8_timer0PreScaler=T0_PRESCALER_NO;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_8:
	gu8_timer0PreScaler=T0_PRESCALER_8;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_32:
	retval&=E_NOK;
	break;
	case TIMER_PRESCALER_64:
	gu8_timer0PreScaler=T0_PRESCALER_64;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_128:
	retval&=E_NOK;
	break;
	case TIMER_PRESCALER_256:
	gu8_timer0PreScaler=T0_PRESCALER_256;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_1024:
	gu8_timer0PreScaler=T0_PRESCALER_1024;
	retval&=E_OK;
	break;
	default:
        retval&=E_NOK;
}
break;


case TIMER_CH1:

switch(timer_polinterupt){
	case TIMER_POLLING_MODE	:
    retval&=E_OK;
	break;
	case TIMER_INTERRUPT_MODE:
    retval&=E_OK;
	break;
	default:
        retval&=E_NOK;
}
switch (prescaler){
	case TIMER_NO_CLOCK:
	gu8_timer1PreScaler=T1_NO_CLOCK;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_NO:
	gu8_timer1PreScaler=T1_PRESCALER_NO;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_8:
	gu8_timer1PreScaler=T1_PRESCALER_8;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_32:
    retval&=E_NOK;
	break;
	case TIMER_PRESCALER_64:
	gu8_timer1PreScaler=T1_PRESCALER_64;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_128:
	retval&=E_NOK;
	break;
	case TIMER_PRESCALER_256:
	gu8_timer1PreScaler=T1_PRESCALER_256;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_1024:
	gu8_timer1PreScaler=T1_PRESCALER_1024;
	retval&=E_OK;
	default:
        retval&=E_NOK;
}
break;


case TIMER_CH2:
switch(timer_polinterupt){
	case TIMER_POLLING_MODE	:
	    retval&=E_OK;
	break;
	case TIMER_INTERRUPT_MODE:
	    retval&=E_OK;
	break;
	default:
        retval&=E_NOK;
}
switch (prescaler){
	case TIMER_NO_CLOCK:
	gu8_timer2PreScaler=T2_NO_CLOCK;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_NO:
	gu8_timer2PreScaler=T2_PRESCALER_NO;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_8:
	gu8_timer2PreScaler=T2_PRESCALER_8;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_32:
    gu8_timer2PreScaler=T2_PRESCALER_32;
    retval&=E_OK;
	break;
	case TIMER_PRESCALER_64:
	gu8_timer2PreScaler=T2_PRESCALER_64;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_128:
	gu8_timer2PreScaler=T2_PRESCALER_128;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_256:
	gu8_timer2PreScaler=T2_PRESCALER_256;
	retval&=E_OK;
	break;
	case TIMER_PRESCALER_1024:
	gu8_timer2PreScaler=T2_PRESCALER_1024;
	retval&=E_OK;
	break;
	default:
        retval&=E_NOK;
}
break;
}}else{
retval=NULL_PTR_ERROR;
}

return retval;
}


 /*Describtion: this function start the  timer by appling clock to it   */
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count){
ERROR_STATUS retval=E_OK;
switch(Timer_CH_NO){
case TIMER_CH0:
	if(Timer_Count>0&&Timer_Count<256){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;
case TIMER_CH1:

	if(Timer_Count>0&&Timer_Count<16336){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;

case TIMER_CH2:
	if(Timer_Count>0&&Timer_Count<16336){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;
default:
    retval&=E_NOK;
}
return retval;
}



 /*Describtion: this function set value for timer in case of compare match mode  */
ERROR_STATUS Timer_SetValue(uint8 Timer_CH_NO, uint16 Data){
	ERROR_STATUS retval=E_OK;
switch(Timer_CH_NO){
case TIMER_CH0:
	if(Data>0&&Data<256){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;
case TIMER_CH1:

	if(Data>0&&Data<16336){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;

case TIMER_CH2:
	if(Data>0&&Data<16336){
       retval&=E_OK;
	}else{
	    retval&=E_NOK;
	}
break;
default:
    retval&=E_NOK;
}
return retval;
}

 /*Describtion: this function stop timer fby applying no clock  */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO){
    ERROR_STATUS retval=E_OK;
switch(Timer_CH_NO){
case TIMER_CH0:
    retval&=E_OK;
break;

case TIMER_CH1:
     retval&=E_OK;
break;

case TIMER_CH2:
retval&=E_OK;
break;

default:
    retval&=E_NOK;
}
return retval;
}


