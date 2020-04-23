/*
 * DIO.c
 *
 * Created: 2/15/2020 4:50:16 PM
 *  Author: Ahmed Amin
 */
#include "DIO_mock.h"

 /*Describtion: this function initialize the gpio direction for specific direction  */
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info){
    ERROR_STATUS retval=E_OK;
    uint8 gpio=DIO_info->GPIO;
    uint8 pins= DIO_info->pins;
    uint8 direction=DIO_info->dir;

    if(DIO_info!=NULL){
	 if(gpio==GPIOA||gpio==GPIOD||gpio==GPIOC||gpio==GPIOB){
            retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
	  if(pins>=BIT0&&pins<=0xFF){
	 retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
	 if(direction==LOW||direction==HIGH){
	 retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
    }
    else{
     retval=NULL_PTR_ERROR;
     }
	 return retval;
 }

  /*Describtion: this function write the gpio pin  */
 ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value){
ERROR_STATUS retval=E_OK;
	 if(GPIO==GPIOA||GPIO==GPIOB||GPIO==GPIOC||GPIO==GPIOD){
            retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
	   if(pins>=BIT0&&pins<=BIT7){
	 retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
	  if(value==LOW||value==HIGH){
	 retval&=E_OK;
	 }else{
	     retval&=E_NOK;
	 }
	 return retval;
 }



