#include "led.h"
#include "ledConfig.h"
#include "gpio.h"

void Led_Init(En_LedNumber_t en_led_id){
	switch(en_led_id){
		case LED_0:
		gpioPinDirection(LED_0_GPIO, LED_0_BIT, OUTPUT);
		break;
		case LED_1:
		gpioPinDirection(LED_1_GPIO, LED_1_BIT, OUTPUT);
		break;
		case LED_2:
		gpioPinDirection(LED_2_GPIO, LED_2_BIT, OUTPUT);
		break;
		case LED_3:
		gpioPinDirection(LED_3_GPIO, LED_3_BIT, OUTPUT);
		break;
	}
}
void Led_On(En_LedNumber_t en_led_id){
	
	switch(en_led_id){
		case LED_0:
		gpioPinWrite(LED_0_GPIO, LED_0_BIT, OUTPUT);
		break;
		case LED_1:
		gpioPinWrite(LED_1_GPIO, LED_1_BIT, OUTPUT);
		break;
		case LED_2:
		gpioPinWrite(LED_2_GPIO, LED_2_BIT, OUTPUT);
		break;
		case LED_3:
		gpioPinWrite(LED_3_GPIO, LED_3_BIT, OUTPUT);
		break;
	}
}
void Led_Off(En_LedNumber_t en_led_id){
	switch(en_led_id){
		case LED_0:
		gpioPinWrite(LED_0_GPIO, LED_0_BIT,INPUT);
		break;
		case LED_1:
		gpioPinWrite(LED_1_GPIO, LED_1_BIT, INPUT);
		break;
		case LED_2:
		gpioPinWrite(LED_2_GPIO, LED_2_BIT, INPUT);
		break;
		case LED_3:
		gpioPinWrite(LED_3_GPIO, LED_3_BIT, INPUT);
		break;
	}
	
}
void Led_Toggle(En_LedNumber_t en_led_id){
	switch(en_led_id){
		case LED_0:
		gpioPinToggle(LED_0_GPIO, LED_0_BIT);
		break;
		case LED_1:
		gpioPinToggle(LED_1_GPIO, LED_1_BIT);
		break;
		case LED_2:
		gpioPinToggle(LED_2_GPIO, LED_2_BIT);
		break;
		case LED_3:
		gpioPinToggle(LED_3_GPIO, LED_3_BIT);
		break;
	}
}