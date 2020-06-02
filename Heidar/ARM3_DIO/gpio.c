/*
 * gpio.c
 *
 *      Author: Abdallah Heidar
 */

#include "gpiolcfg.h"
#include "gpio.h"
 
#define MODE_MASK 		(3)
#define SPEED_MASK 		(3)
#define PUPDR_MASK 		(3)
#define OTYPER_MASK 	(1)
#define AF_CONFIG_BITS 	(4)
#define AF_MASK 		(0xF)

#define BITS_2 			(2)
 
#define ADRESS_OFFSET 		(0x400)
#define BSRRL_BITS_OFFSET 	(15)

ERROR_STATUS  GPIO_Init(void)
{
    uint8_t counter;

    ERROR_STATUS ERR_STATE = E_OK;

    for(counter = 0; counter < PINS_NUM ; counter++)
    {
    	RCC->AHB1ENR |= arr_PinCfg[counter].GPIO_CLOCK;

    	uint8_t Pin = arr_PinCfg[counter].Gpio_Pin;

        arr_PinCfg[counter].GPIO_USED->MODER &= ~
        		(MODE_MASK<<((Pin)*BITS_2));
        arr_PinCfg[counter].GPIO_USED->MODER |=
        		(arr_PinCfg[counter].Gpio_Mode << ((Pin)*BITS_2));

        arr_PinCfg[counter].GPIO_USED->OSPEEDR &= ~
        			(SPEED_MASK<<((Pin)*BITS_2));
        arr_PinCfg[counter].GPIO_USED->OSPEEDR |=
        			(arr_PinCfg[counter].Gpio_Speed << ((Pin)*BITS_2));

        arr_PinCfg[counter].GPIO_USED->PUPDR &= ~
        			(PUPDR_MASK<<((Pin)*BITS_2));
        arr_PinCfg[counter].GPIO_USED->PUPDR |=
        			(arr_PinCfg[counter].Gpio_PullDirection << ((Pin)*BITS_2));

        arr_PinCfg[counter].GPIO_USED->OTYPER &= ~
        			(OTYPER_MASK<<(Pin));
        arr_PinCfg[counter].GPIO_USED->OTYPER |=
        			(arr_PinCfg[counter].Gpio_OpenD_PushPull << (Pin));

        arr_PinCfg[counter].GPIO_USED->AFR[(Pin) / 2] &= ~
        		(AF_MASK << (counter *(Pin % 2)));
        arr_PinCfg[counter].GPIO_USED->AFR[Pin / 2] |=
                		(arr_PinCfg[counter].Gpio_Af << (counter *(Pin % 2)));
    }
    return ERR_STATE;
}

ERROR_STATUS GPIO_Write(uint8_t port , uint16_t pins, uint16_t val)
{
    ERROR_STATUS ERR_STATE = E_OK;

    GPIO_PTR portAddress = NULL;
    switch(port)
    {
    case GPIOA_PORT:
    	portAddress = GPIOA;
		break;
    case GPIOB_PORT:
    	portAddress = GPIOB;
		break;
    case GPIOC_PORT:
    	portAddress = GPIOC;
		break;
    case GPIOD_PORT:
    	portAddress = GPIOD;
		break;
    case GPIOE_PORT:
    	portAddress = GPIOE;
		break;
    case GPIOH_PORT:
    	portAddress = GPIOH;
		break;
    default:
    	ERR_STATE = ERROR_DIO_BASE+ERROR_INVALID_PORT;
		break;
    }
    if(ERR_STATE==E_OK)
    {
    	portAddress->BSRR = (pins << BSRRL_BITS_OFFSET);
    	portAddress->BSRR = pins & val;
    }
    return ERR_STATE;
}

ERROR_STATUS GPIO_Read(uint8_t port, uint16_t pins, uint16_t *ptrValue)
{
	ERROR_STATUS ERR_STATE = E_OK;
	switch(port)
	{
		case GPIOA_PORT:
	    	*ptrValue=(GPIOA->IDR & pins);
			break;
	    case GPIOB_PORT:
	    	*ptrValue=(GPIOB->IDR & pins);
			break;
	    case GPIOC_PORT:
	    	*ptrValue=(GPIOC->IDR & pins);
			break;
	    case GPIOD_PORT:
	    	*ptrValue=(GPIOD->IDR & pins);
			break;
	    case GPIOE_PORT:
	    	*ptrValue=(GPIOE->IDR & pins);
			break;
	    case GPIOH_PORT:
	    	*ptrValue=(GPIOH->IDR & pins);
			break;
	    default:
	    	ERR_STATE=ERROR_DIO_BASE + ERROR_INVALID_PORT;
			break;
	}
	return ERR_STATE;
}
