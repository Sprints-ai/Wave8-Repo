/*
*	File name: DIO.c
*	Author : Hazem
*
*/

/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/
#include "DIO.h"


/************************************************************************/
/*				 APIs IMPLEMENTATION			        				*/
/************************************************************************/


/**************************************************************************/
/*Func_Name:DIO_init*/
/*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction*/
/*Output: No output*/
/*Return:Error status*/
/*Description: This function can set the direction of a full port, a nibble or even one pin.*/
/******************************************************************************************/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{/*ERROR RET VARIBALE*/ 
   ERROR_STATUS  EROR=E_OK;
 /*check if the pointer is not null*/  
   if(DIO_info!=NULL)
   {
 /*choose any PORT*/ 
      switch(DIO_info->GPIO)
      {
         case GPIOA:
               if(DIO_info->dir==OUTPUT)
               PORTA_DIR|=(DIO_info->pins);
               else if(DIO_info->dir==INPUT)
               PORTA_DIR&=~(DIO_info->pins);
               else
               EROR=E_NOK;
               break;
         case GPIOB:
               if(DIO_info->dir==OUTPUT)
               PORTB_DIR|=(DIO_info->pins);
               else if(DIO_info->dir==INPUT)
               PORTB_DIR&=~(DIO_info->pins);
               else
               EROR=E_NOK;
               break;
         case GPIOC:
               if(DIO_info->dir==OUTPUT)
               PORTC_DIR|=(DIO_info->pins);
               else if(DIO_info->dir==INPUT)
               PORTC_DIR&=~(DIO_info->pins);
               else
               EROR=E_NOK;
               break;
         case GPIOD:
               if(DIO_info->dir==OUTPUT)
               PORTD_DIR|=(DIO_info->pins);
               else if(DIO_info->dir==INPUT)
               PORTD_DIR&=~(DIO_info->pins);
               else
               EROR=E_NOK;
               break;
         default:
               EROR=E_NOK;
               break;
         
      }   
   }
   else
   {
      EROR=E_NOK;
   }
   
   
   return EROR;
}
/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: No output
*In/Out: No In/Out
*Return:Error Status
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value)
{ 
/*ERROR RET VARIBALE*/  
   ERROR_STATUS EROR=E_OK;
  /*choose any PORT*/  
   switch (GPIO)
   {
      case GPIOA:
            if(value==HIGH)
            PORTA_DATA|=pins;
            else if(value==LOW)
            PORTA_DATA&=~(pins);
            else
            EROR=E_NOK;
            break;
      case GPIOB:
            if(value==HIGH)
            PORTB_DATA|=pins;
            else if(value==LOW)
            PORTB_DATA&=~(pins);
            else
            EROR=E_NOK;
            break;
      case GPIOC:
            if(value==HIGH)
            PORTC_DATA|=pins;
            else if(value==LOW)
            PORTC_DATA&=~(pins);
            else
            EROR=E_NOK;
            break;
      case GPIOD:
            if(value==HIGH)
            PORTD_DATA|=pins;
            else if(value==LOW)
            PORTD_DATA&=~(pins);
            else
            EROR=E_NOK;
            break;
     /*if the channel is wrong */          
      default:
            EROR=E_NOK;
            break;
   }


   return EROR;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*					- HIGH
*					- LOW
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/

ERROR_STATUS DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data)
{  /*ERROR RET VARIBALE*/
   ERROR_STATUS ERROR=E_OK;
 /*choose any PORT*/  
   switch(GPIO)
   {
      case GPIOA:
            if((PORTA_PIN&pins)==pins)
            *data=HIGH;
            else
            *data=LOW;
            break;
      case GPIOB:
            if((PORTB_PIN&pins)==pins)
            *data=HIGH;
            else
            *data=LOW;
            break;
      case GPIOC:
            if((PORTC_PIN&pins)==pins)
            *data=HIGH;
            else
            *data=LOW;
            break;
      case GPIOD:
            if((PORTD_PIN&pins)==pins)
            *data=HIGH;
            else
            *data=LOW;
            break;
 /*if the channel is wrong */           
      default:
            ERROR=E_NOK;
            break;
   }

   
   return ERROR;
}


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8_t GPIO, uint8_t pins)
{  /*ERROR RET VARIBALE*/
   ERROR_STATUS EROR=E_OK;
   
   switch (GPIO)
   {
      case GPIOA:
            PORTA_DATA^=pins;
            break;
      case GPIOB:
            PORTB_DATA^=pins;
            break;
      case GPIOC:
           PORTC_DATA^=pins;
           break;
      case GPIOD:
          PORTD_DATA^=pins;
          break;
      default:
          EROR=E_NOK;
          break;
   }


   return EROR;
   
}