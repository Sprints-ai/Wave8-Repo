

/* Includes */
#include "stm32f4xx.h"
#include "./MCAL/gpio.h"
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

#include "./MCAL/ADC.h"

#define HALF_ADC_READ (2000)

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
**===========================================================================
*/
int Adc_Reading = ZERO;

int main(void)
{
	mygpio_init();
	ADC_Link_Init();



	//GPIOD->BSRRH =PIN_14 ;
  /* Infinite loop */
  while (1)
  {
	  ADC_Read(&Adc_Reading , ADC_MODULE_1);

	  if(Adc_Reading>HALF_ADC_READ)
	  {
		  gpio_Write(GPIOD_PORT , PIN_14 , HIGH);
	  }
	  else
	  {
		  	gpio_Write(GPIOD_PORT , PIN_14 , LOW);
	  }
  }
}
