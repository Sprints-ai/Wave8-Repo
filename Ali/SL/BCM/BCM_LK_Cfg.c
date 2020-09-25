/*
 * BCM_LK_cfg.c
 *
 * Created: 3/4/2020 7:12:57 PM
 *  Author: Az
 */ 
/*- INCLUDES --------------------------------------------------------------------------------------------------------*/
#include "BCM.h"


/*- STRUCTS ---------------------------------------------------------------------------------------------------------*/
/* BCM configuration struct -Transmit configuration - */
str_BCM_Cfg_t gstr_BCM_Transmit_Init = 
{  
   TRANSMIT,
   SPI       
};

/* BCM configuration struct - Receive configuration - */ 
str_BCM_Cfg_t gstr_BCM_Receive_Init =
{
   RECIEVE,
   SPI
         
};