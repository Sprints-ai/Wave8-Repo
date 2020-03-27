/*
 * ERROR.h
 *
 * Created: 2020-03-26 11:05:40 AM
 *  Author: EbrahimOseif
 */


#include "testing.h"


/* Test Data preparation */

			/* DIO INIT DATA */

	DIO_Cfg_s* null_ptr = NULL;

	DIO_Cfg_s DIO_init_Valid_Data[4] = {{GPIOA,BIT1,HIGH},{GPIOB,BIT3,LOW},{GPIOC,BIT5,HIGH},{GPIOD,BIT7,LOW}};

	DIO_Cfg_s DIO_init_IN_valid_Data[3] = {{-1,BIT0,HIGH},{GPIOB,-1,LOW},{GPIOC,BIT7,-1}};

			/* DIO WRITE DATA */

	DIO_Cfg_s DIO_Write_Valid_Data[4] = {{GPIOA,BIT1,HIGH},{GPIOB,BIT3,LOW},{GPIOC,BIT5,HIGH},{GPIOD,BIT7,LOW}};

	DIO_Cfg_s DIO_Write_IN_valid_Data[3] = {{-1,BIT0,HIGH},{GPIOB,-1,LOW},{GPIOC,BIT7,-1}};

			/* DIO READ DATA */


	DIO_Cfg_s DIO_Read_Valid_Data[4]={{GPIOA,BIT1,HIGH},{GPIOB,BIT3,LOW},{GPIOC,BIT5,HIGH},{GPIOD,BIT7,LOW}};

	DIO_Cfg_s DIO_Read_IN_valid_Data[3]={{-1,BIT0,HIGH},{GPIOB,-1,LOW},{GPIOC,BIT7,-1}};

			/* DIO TOGGLE DATA */

	DIO_Cfg_s DIO_Toggle_Valid_Data[4]={{GPIOA,BIT1,HIGH},{GPIOB,BIT3,LOW},{GPIOC,BIT5,HIGH},{GPIOD,BIT7,LOW}};

	DIO_Cfg_s DIO_Toggle_IN_valid_Data[3]={{-1,BIT0,HIGH},{GPIOB,-1,LOW},{GPIOC,BIT7,-1}};


	/* testing API IMPLEMENTATION */

    ERROR_STATUS Testing_DIO_init(DIO_Cfg_s *DIO_info){

        return DIO_init(DIO_info);
    }

    ERROR_STATUS Testing_DIO_Write (uint8_t GPIO, uint8_t pins, uint8_t value){

      return DIO_Write(GPIO, pins, value);
    }

    ERROR_STATUS Testing_DIO_Read (uint8_t GPIO,uint8_t pins, uint8_t *data){


        return DIO_Read(GPIO, pins, data);
    }

    ERROR_STATUS Testing_DIO_Toggle (uint8_t GPIO, uint8_t pins){

       return DIO_Toggle(GPIO, pins);
    }
