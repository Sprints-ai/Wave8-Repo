
/*Includes*/

#include "gpio.h"
#include "gpiolcfg.h"

/*Register Mask*/
#define MODE_MASK (3)
#define SPEED_MASK (3)
#define PUPDR_MASK (3)
#define OTYPER_MASK (1)
#define AFR_CONFIG_BITS (4)
#define AF_MASK (0xF)

#define BITS_2 (2)


/*Offset Address*/
#define ADRESS_OFFSET (0x400)
#define BSRRL_BITS_OFFSET (15)


/*Init Gpio
 * Description : Function to init  all gpio needed once
 * Input : None but getting an external array from gpiolcfg.h
 * Output : Error if found
 */
ERROR_STATUS  mygpio_init(void)
{
    uint8_t Loop;

    /*Create Error Flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    for(Loop = 0; Loop < PINS_NUM ; Loop++)
    {
    	/*First Enable port Clock*/
    	RCC->AHB1ENR |= arr_PinCfg[Loop].GPIO_CLOCK;

    	uint8_t Pin = arr_PinCfg[Loop].Gpio_Pin;

    	/*Choose The pin Mode inseted "In , Out , Analog , AF"*/
        arr_PinCfg[Loop].GPIO_USED->MODER &= ~
        		(MODE_MASK << ((Pin)*BITS_2));
        arr_PinCfg[Loop].GPIO_USED->MODER |=
        		(arr_PinCfg[Loop].Gpio_Mode << ((Pin)*BITS_2));

        /*Output Speed Selection */
        arr_PinCfg[Loop].GPIO_USED->OSPEEDR &= ~
        			(SPEED_MASK << ((Pin)*BITS_2));
        arr_PinCfg[Loop].GPIO_USED->OSPEEDR |=
        			(arr_PinCfg[Loop].Gpio_Speed << ((Pin)*BITS_2));

        /*Choose input type Pull up or pull down*/
        arr_PinCfg[Loop].GPIO_USED->PUPDR &= ~
        			(PUPDR_MASK << ((Pin)*BITS_2));
        arr_PinCfg[Loop].GPIO_USED->PUPDR |=
        			(arr_PinCfg[Loop].Gpio_PullDirection << ((Pin)*BITS_2));

        /*Output Type "Open drain or push pull" */
        arr_PinCfg[Loop].GPIO_USED->OTYPER &= ~
        			(OTYPER_MASK << (Pin));
        arr_PinCfg[Loop].GPIO_USED->OTYPER |=
        			(arr_PinCfg[Loop].Gpio_OpenD_PushPull << (Pin));

        /*Check for AF Location then write it*/
        arr_PinCfg[Loop].GPIO_USED->AFR[(Pin) / 2] &= ~
        		(AF_MASK << (AFR_CONFIG_BITS *(Pin % 2)));
        arr_PinCfg[Loop].GPIO_USED->AFR[Pin / 2] |=
                		(arr_PinCfg[Loop].Gpio_Af << (AFR_CONFIG_BITS *(Pin % 2)));

    }

    return ERR_STATE;
}

/*GpioWrite
*Description : Function to write the desired value in pins
*Input : Port "A,B,C,D,E,H" .. PINS"0:15" .. VAL "HIGH , LOW , PORT VAL"
*OUTPUT : ERROR IF FOUND
*/
ERROR_STATUS gpio_Write(uint8_t Port , uint16_t Pins, uint16_t Val)
{
    /*Create Error Flag*/
    ERROR_STATUS ERR_STATE = E_OK;

    /*Get the base adress of selected GPIO*/
    GPIO_PTR Port_Adrress = NULL;

    switch(Port)
    {
    case GPIOA_PORT:

    	Port_Adrress = GPIOA;
     break;

    case GPIOB_PORT:

    	Port_Adrress = GPIOB;
    break;

    case GPIOC_PORT:

    	Port_Adrress = GPIOC;
    break;

    case GPIOD_PORT:

    	Port_Adrress = GPIOD;
    break;

    case GPIOE_PORT:

    	Port_Adrress = GPIOE;
    break;

    case GPIOH_PORT:

    	Port_Adrress = GPIOH;
    break;

    default:

    	ERR_STATE = ERROR_DIO_BASE + ERROR_INVALID_PORT;
    break;
    }
    if(ERR_STATE == E_OK)
    {
    	/*Write Your Value*/
    	  /*First Reinit all pins*/
    	 Port_Adrress->BSRR = (Pins << BSRRL_BITS_OFFSET);

    	  /*Write Your Val*/
    	  Port_Adrress->BSRR = Pins & Val;
    }

    /*Return*/
    return ERR_STATE;
}

/*Dio_Read
 * Description : Function to read the input values at pins
 * Input : Port and Pins to read from , output Pointer to value
 * Output : Error if found
 */
ERROR_STATUS gpio_Read(uint8_t Port , uint16_t Pins,uint16_t *Ptr_Value)
{
	/*Create error flag*/
	ERROR_STATUS ERR_STATE = E_OK;

	switch(Port)
	{
		case GPIOA_PORT:

	    	*Ptr_Value = (GPIOA->IDR & Pins);
	     break;

	    case GPIOB_PORT:

	    	*Ptr_Value = (GPIOB->IDR & Pins);
	    break;

	    case GPIOC_PORT:

	    	*Ptr_Value = (GPIOC->IDR & Pins);
	    break;

	    case GPIOD_PORT:

	    	*Ptr_Value = (GPIOD->IDR & Pins);
	    break;

	    case GPIOE_PORT:

	    	*Ptr_Value = (GPIOE->IDR & Pins);
	    break;

	    case GPIOH_PORT:

	    	*Ptr_Value = (GPIOH->IDR & Pins);
	    break;

	    default:

	    	ERR_STATE = ERROR_DIO_BASE + ERROR_INVALID_PORT;
	    break;
	}

	return ERR_STATE;
}
