#include "MCAL/includes/SysCtrl.h"
#include "MCAL/includes/Port.h"
#include "MCAL/includes/ADC.h"
#include "MCAL/includes/DIO.h"

#define MAX_VOLT       3.3
#define RANG1          0.825
#define RANG2          1.65
#define RANG3          2.475
#define RESOLUTION     4096.0

int main(void)
{
	uint16_t Readings[1];
	float volts;
	SysCtrl_Init();
	Port_Init();
	ADC_Init();
	while(1)
	{
		ADC_READ(Readings);
		volts=(Readings[0]*MAX_VOLT)/MAX_VOLT;
		if(volts >= ZERO && volts <= RANG1)
		{
			Dio_WriteChannel(Dio_Channel_E4,LOW);
			Dio_WriteChannel(Dio_Channel_E5,LOW);
		}
		else if(volts > RANG1 && volts <= RANG2)
		{
			Dio_WriteChannel(Dio_Channel_E4,HIGH);
			Dio_WriteChannel(Dio_Channel_E5,LOW);
		}
		else if(volts > RANG2 && volts <= RANG3)
		{
			Dio_WriteChannel(Dio_Channel_E4,LOW);
			Dio_WriteChannel(Dio_Channel_E5,HIGH);
		}
		else if(volts > RANG3 && volts <= MAX_VOLT)
		{
			Dio_WriteChannel(Dio_Channel_E4,HIGH);
			Dio_WriteChannel(Dio_Channel_E5,HIGH);
		}
	}
	return 0;
}
