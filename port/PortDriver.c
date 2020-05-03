
/*****************************************************************************/
/*					Port.c												 */	
/*****************************************************************************/

#include "../std_types.h"
#include "MCU_hw.h"
#include "PorDriver.h"

//  Channel -> pins 
#define NUM_OF_CHANNELS_IN_PORT							8

#define NUM_OF_PORTS 									6
#define CHANNEL_ENABLE									1
#define GPIO_UNLOCK_MASK								0x4C4F434B
#define GPIO_LOCK_MASK									0x0
#define COMMIT_MASK										(0xff)
#define PortDriver_Channel_Function_X_ADC 0xffffffff

static uint32_t au32_BaseAddr[NUM_OF_PORTS] = {BASE_ADDRESS_A,   
										BASE_ADDRESS_B,
										BASE_ADDRESS_C,
										BASE_ADDRESS_D,
										BASE_ADDRESS_E,
				  					    BASE_ADDRESS_F};	

#define Clr_Bit(REGISTER,BIT_NUM) (REGISTER&=~(1<<BIT_NUM))		 								
#define Set_Bit(REGISTER,BIT_NUM) (REGISTER|=(1<<BIT_NUM))			 								
void PortDriver_init(void)
{
	uint8_t u8_PortActivatingIndex = 0;
	
	PortDriver_PortNumType PortNum ;  
	
	PortDriver_ChannelType ChannelNum; 
				
	PortDriver_Channel_DirectionType	Channel_Direction;
	PortDriver_Channel_Current_mAType	Channel_Current_mA;
	PortDriver_Channel_SlewRateType		Channel_SlewRate;
	PortDriver_Channel_AttachmentType	Channel_Attachment;
	PortDriver_Channel_FunctionType		Channel_Function;
	PortDriver_Channel_ExtiType			Channel_Exti;

	
	uint8_t ChannelOffset;	 //  Get the pin  number (position) 	
	
	for(u8_PortActivatingIndex =0;u8_PortActivatingIndex <NUM_OF_ACTIVATED_CHANNELS;u8_PortActivatingIndex ++)
	{
		ChannelNum = PortDriver_CfgArr[u8_PortActivatingIndex].Channel;
		
		Channel_Direction  = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_Direction;
		Channel_Current_mA = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_Current_mA;
		Channel_SlewRate   = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_SlewRate;
		Channel_Attachment = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_Attachment;
		Channel_Function   = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_Function;
		Channel_Exti       = PortDriver_CfgArr[u8_PortActivatingIndex].PortDriver_Channel_Exti;

		// Get the Port number to chose crosepponding basse
		
		PortNum = ChannelNum / NUM_OF_CHANNELS_IN_PORT;
		
		ChannelOffset = ChannelNum % NUM_OF_CHANNELS_IN_PORT;
		
		ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOLOCK = GPIO_UNLOCK_MASK ;
		
	//ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOCR = (1 << ChannelOffset) ;
		ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOCR = COMMIT_MASK ;
		
		
		switch (Channel_Direction){
			 
			case PortDriver_Channel_Direction_INPUT  :
			
				Clr_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIODIR,ChannelOffset);
			
			break;
			
			case PortDriver_Channel_Direction_OUTPUT :
			
				Set_Bit(ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIODIR,ChannelOffset);
			  
			break;   
			
			default:
			 // error state 
			break;
		}
		
		if ((Channel_Current_mA <= 0) && (Channel_Current_mA) >3){
			
			Set_Bit(*((reg_type32_t)(& ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIODR2R) + Channel_Current_mA),ChannelOffset);
			
		} 
		else {
			//error state
		}
		
		switch (Channel_SlewRate){
			 
			case PortDriver_Channel_SlewRate_Disable	  :
			    
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOSLR,ChannelOffset);
			
			break;
			
			case  PortDriver_Channel_SlewRate_Enable	 :
			
				Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOSLR,ChannelOffset);
				
			break;   
																						
			default:
			 // error state 
			break;
		}
		
		switch (Channel_Attachment){
	
			case PortDriver_Channel_Attachment_NotConnected  :
			
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOODR,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOPUR,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOPDR,ChannelOffset);
				
			break;
			
			case  PortDriver_Channel_Attachment_openDrain	:
			
				Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOODR,ChannelOffset);
				
			break;
			
			case PortDriver_Channel_Attachment_PullupRes:
					
					Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOPUR,ChannelOffset);
					
			break;
			
			case PortDriver_Channel_Attachment_PullDownRes :
				
					Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOPDR,ChannelOffset);
				
			break ;
			
			default :
				 //error state
			break;
			
		}
		
		 if(Channel_Function == PortDriver_Channel_Function_X_DIO )
		 {
			 Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOAFSEL,ChannelOffset);
			 Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIODEN,ChannelOffset);
			 
			 
		 }
		else if(Channel_Function == PortDriver_Channel_Function_X_ADC )
		{
			Set_Bit(ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOAFSEL,ChannelOffset);
			Clr_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIODEN,ChannelOffset);
			Set_Bit(ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOAMSEL,ChannelOffset);
		}
		else 
		{
			
			Set_Bit(ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOAFSEL,ChannelOffset);
		    Set_Bit(ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIODEN,ChannelOffset);//

			ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOPCTL = (((ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOPCTL)& ~(Channel_Function)) |Channel_Function);
		}
		
		Set_Bit(ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOICR,ChannelOffset);
		
	  	switch (Channel_Exti){
			

			case PortDriver_Channel_Exti_Disable :
			
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);
				
			break ;
			
			case  PortDriver_Channel_Exti_RisingEdge :
			
			
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIS,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIBE,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIEV,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);
				
			    
			
			break;
			
			case  PortDriver_Channel_Exti_FallingEdge:
			
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIS,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIBE,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIEV,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);

			
			break;
			
			
			case  PortDriver_Channel_Exti_BothEdge :
			
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIS,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIBE,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);

			break;
			
			case PortDriver_Channel_Exti_LowLevel :
				
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIS,ChannelOffset);
				Clr_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIEV,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);


			break;
			
			case PortDriver_Channel_Exti_HighLevel:
				
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIS,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIEV,ChannelOffset);
				Set_Bit( ACTINATING_PORT (au32_BaseAddr[PortNum]).GPIOIM,ChannelOffset);
				


			break;
			
			default :
				//error state
			break;
			
			
		}									 	

	ACTINATING_PORT(au32_BaseAddr[PortNum]).GPIOLOCK = GPIO_LOCK_MASK ;
	}

}







