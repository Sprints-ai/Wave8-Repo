/*
 * BCM.c
 *
 * Created: 3/3/2020 1:45:32 AM
 *  Author: Ema
 */
/*- INCLUDES ----------------------------------------------*/
#include "BCM.h"
/*- LOCAL MACROS ------------------------------------------*/

/*- STATIC FUNCTIONS PROTOTYPES ---------------------------*/
 BCMError_t BCM_SENDDONE(void);
 void BCM_SENDCHECKSUMDONE(void);
 BCMError_t bcm_RX(void);

 /*- LOCAL Data types --------------------------------------*/

  /*- GLOBAL STATIC VARIABLES -------------------------------*/
typedef volatile struct ARRAY_CONTROL{
   uint8_t bcm_id;
   uint16_t BCM_SIZE;
   uint8_t  BCM_CHECK_SUM;
   uint8_t bcm_buffer_state ;
   uint16_t BCM_size;
   uint8_t *garray;
   uint8_t *gu_buffer_ptr;
   volatile uint8_t bcm_state ;
   BCM_SEND_CBKFUNCOMP gf_aftersend;
   volatile uint8_t buffer_index ;
   }gstr_bcm_control;

   static uint8_t BCM_init_state = NO_INIT;

 gstr_bcm_control  gstr_bcm_control_array;
 /*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
BCMError_t BCM_init(Bcm_Cfg_ST *Bcm_cfg_st)
{
    BCMError_t  retVal = E_OK;

    if(Bcm_cfg_st == NULL)
    {
        retVal = NULL_PTR;
        BCM_init_state = NO_INIT;
    }
    else
    {
        gstr_bcm_control_array.bcm_state=BCM_IDLE;
        SPI_ConfigType status;

	switch(Bcm_cfg_st->BCM_Mode)
	{
		case USART_MODE:
		{
			USART_Config ST_Config={USART_BAUDRATE,TX_ENABLE,RX_ENABLE,NO_DOUBLE_SPEED,DATA_SIZE_8,PARITY_DISABLE,STOP_1BIT,ASYNCH};
			USART_init(&ST_Config);
		}
        break;
		case BCM_SPI_MODE:
		{
			switch(Bcm_cfg_st->SPI_Mode)
			{
                case BCM_SPI_MASTER:
                {
                    status.ClockRateSelect=SPI_F_OSC_16;
                    status.MasterSlaveSelect=SPI_MASTER;
                    status.Mode=SPI_INTERRUPT_ENABLED;
                    SPI_init(&status);
                }
                break;
				case BCM_SPI_SLAVE:
                {
                    status.ClockRateSelect=SPI_F_OSC_16;
                    status.MasterSlaveSelect=SPI_SLAVE;
                    status.Mode=SPI_INTERRUPT_ENABLED;
                    SPI_init(&status);
                }
                break;
                default:
                {
                    retVal = INVALID_PARAM;
                }
                break;
			}
		}
		break;
        default:
        {
            retVal = INVALID_PARAM;
        }
        break;
	}
    }

    if(retVal == E_OK)
    {
        BCM_init_state = BCM_INIT_DONE;
    }
    return retVal;
}


BCMError_t BCM_recieve(uint8_t *Buffer_ptr,BCM_recieve_cbk CBKFUN)
{
    BCMError_t retVal = E_OK;

    if(Buffer_ptr == NULL)
    {
        retVal = NULL_PTR;
    }
    else
    {
        gstr_bcm_control_array.bcm_state = BCM_RECEIVE;
        gstr_bcm_control_array.bcm_buffer_state = BCM_BUFFER_LOCK;
        gstr_bcm_control_array.gu_buffer_ptr = Buffer_ptr;
        SPI_setCallBack(bcm_RX);
    }

	return retVal;
}


void BCM_RX_dispatcher(void)
{
	switch(gstr_bcm_control_array.bcm_state)
	{
		case BCM_IDLE:
		{
			gstr_bcm_control_array.bcm_buffer_state = BCM_BUFFER_UNLOCK;
		}
		break;
		case BCM_RECEIVE:
		{
			gstr_bcm_control_array.bcm_buffer_state = BCM_BUFFER_LOCK;
		}
		break;
		case BCM_RECIEVE_COMPLETE:
		{
			if ((gstr_bcm_control_array.buffer_index == (gstr_bcm_control_array.BCM_SIZE-1)) && (gstr_bcm_control_array.BCM_CHECK_SUM == gstr_bcm_control_array.gu_buffer_ptr[gstr_bcm_control_array.buffer_index]))
			{
				gstr_bcm_control_array.bcm_state = RX_COMPLETE;
				gstr_bcm_control_array.bcm_buffer_state = BCM_BUFFER_UNLOCK;
			}
			else
			{
				gstr_bcm_control_array.bcm_state = RX_ERROR;
			}
			gstr_bcm_control_array.buffer_index = 0;
		}
		break;
		case RX_COMPLETE:
		{
			gstr_bcm_control_array.bcm_state = BCM_IDLE;
		}
		break;
		case RX_ERROR:
		{
			gstr_bcm_control_array.bcm_state = BCM_IDLE;
		}
		break;
		default:
		break;
	}
}

BCMError_t bcm_RX(void)
{
    BCMError_t retVal = E_OK;

	if (gstr_bcm_control_array.bcm_buffer_state == BCM_BUFFER_LOCK)
	{
		if(gstr_bcm_control_array.buffer_index < 3)
		{
			switch (gstr_bcm_control_array.buffer_index)
			{
				case 0:
				{
					gstr_bcm_control_array.bcm_id += SPI_receivebyte();
                    gstr_bcm_control_array.buffer_index;
                }
				break;
				case 1:
				{
					gstr_bcm_control_array.bcm_buffer_state += ((SPI_receivebyte())-'0');
                    gstr_bcm_control_array.buffer_index;
				}
				break;
				case 2:
				{
					gstr_bcm_control_array.bcm_buffer_state += ((SPI_receivebyte())-'0');
                    gstr_bcm_control_array.buffer_index;
				}
				break;
				default:
				    retVal = BCM_RX_ERROR;
                break;
			}
		}

		else
		if ((gstr_bcm_control_array.bcm_id - '0') == BCM_ID_)
		{
			if (gstr_bcm_control_array.buffer_index < (gstr_bcm_control_array.BCM_SIZE-CHECK_SUM_INDEX))
			{
				gstr_bcm_control_array.gu_buffer_ptr[gstr_bcm_control_array.buffer_index] = SPI_receivebyte();
				gstr_bcm_control_array.BCM_CHECK_SUM+= gstr_bcm_control_array.gu_buffer_ptr[gstr_bcm_control_array.buffer_index];
			}

			if (gstr_bcm_control_array.buffer_index == (gstr_bcm_control_array.BCM_SIZE-1))
			{
				gstr_bcm_control_array.gu_buffer_ptr[gstr_bcm_control_array.buffer_index] = SPI_receivebyte();	// receive check sum
				gstr_bcm_control_array.bcm_state = BCM_RECIEVE_COMPLETE;
			}
        }
        else
        {
            retVal = BCM_RX_ERROR;
        }
    }

    return retVal;
}


BCMError_t BCM_Send(BCM_SEND_CBKFUNCOMP CBKFUN,uint8_t* BUFFER,uint16_t size)
{
     BCMError_t retVal = E_OK;

     if(BUFFER == NULL || CBKFUN == NULL)
     {
        retVal = NULL_PTR;
     }
     else
     {
         /*global_static_variable*/
        gstr_bcm_control_array.gf_aftersend=CBKFUN;
        gstr_bcm_control_array.BCM_size=size;
        gstr_bcm_control_array.garray=BUFFER;
        gstr_bcm_control_array.bcm_id=BCM_ID_;
        gstr_bcm_control_array.BCM_SIZE=size;
        gstr_bcm_control_array.bcm_state=BCM_TXSEND;
        gstr_bcm_control_array.BCM_CHECK_SUM=0;
        for(uint16_t i=0;i<size;i++)
        {
            gstr_bcm_control_array.BCM_CHECK_SUM+=BUFFER[i]+1;
        }
     }

     return retVal;
 }

void BCM_TX_dispatcher(void)
{
    switch(gstr_bcm_control_array.bcm_state)
    {
       case BCM_IDLE:
	   {
		   gstr_bcm_control_array.bcm_buffer_state=BCM_BUFFER_UNLOCK;
	   }
	      break;
       case BCM_TXSEND:
       {
            SPI_setCallBack(BCM_SENDDONE);

            if(gstr_bcm_control_array.buffer_index==0)
            {
                SPI_sendByte(gstr_bcm_control_array.bcm_id);
            }
            else if(gstr_bcm_control_array.buffer_index==1)
            {
                SPI_sendByte((uint8_t)gstr_bcm_control_array.BCM_size);
            }
            else if(gstr_bcm_control_array.buffer_index==2)
            {
                SPI_sendByte((uint8_t)(gstr_bcm_control_array.BCM_size>>8));
            }
            else
            {
                SPI_sendByte(gstr_bcm_control_array.garray[gstr_bcm_control_array.buffer_index-3]);
            }
            gstr_bcm_control_array.buffer_index++;
            gstr_bcm_control_array.bcm_state=BCM_TXSENDING;
       }
       break;
       case BCM_TXSENDING:
	   {
            if(gstr_bcm_control_array.buffer_index==13)
            {
                SPI_sendByte(gstr_bcm_control_array.BCM_CHECK_SUM);
                gstr_bcm_control_array.bcm_state=BCM_TXCOMPLETE;
            }
	   }
       break;
       case BCM_TXCOMPLETE:
       {
        SPI_setCallBack(BCM_SENDCHECKSUMDONE);
       }
       break;
       default:
       break;
    }
}

BCMError_t BCM_SENDDONE(void)
{
    BCMError_t  retVal = E_OK;

    gstr_bcm_control_array.bcm_state=BCM_TXSEND;

    return retVal;
}

void BCM_SENDCHECKSUMDONE(void)
{
    gstr_bcm_control_array.bcm_state=BCM_IDLE;
}

BCMError_t BCM_DINIT(void)
{
    BCMError_t retVal = E_OK;

    if(BCM_init_state == BCM_INIT_DONE)
    {
        gstr_bcm_control_array.bcm_buffer_state=0;
        gstr_bcm_control_array.BCM_CHECK_SUM=0;
        gstr_bcm_control_array.bcm_id=0;
        gstr_bcm_control_array.BCM_SIZE=0;
        gstr_bcm_control_array.bcm_state=0;
    }
    else
    {
        retVal = NO_INIT;
    }

    return retVal;

}




