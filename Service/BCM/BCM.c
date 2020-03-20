/*
 * BCM.c
 *
 * Created: 3/2/2020 7:32:11 PM
 *  Author: mahmo
 */ 
#include "BCM.h"

/*	/binary search on lower bound value <= value
*
*
*/


#define UNINT_CHANNEL_UNDONE        0

#define UNINT_CHANNEL_DONE           1
               
#define STATE_IDLE					0
#define STATE_SENDING_BYTE			1
#define STATE_SEN_BYTE_COMPLETE		2
#define STATE_FRAM_SEND_COMLETE		3
#define STATE_FINISED				4

/*for reciver*/
#define STATE_RECIVING_HEAEDER		5
#define STAE_RECIVING_FRAME	        7
#define	STATE_FRAM_RECIVE_COMPLETE	6
#define STATE_ERROR					9
#define STATE_CHEAKING_HEADER       11




#define BCM_FRAM_HEADER_OVERHEAD	4 /*4 bytes added to user data buffer*/
#define BCM_FRAME_SIZE              4
#define ONE_BYTE					1
#define TWO_BYTE                    2
#define BUFFER_SIZE_ELEM			2
/*USE THESE VALUES FOR gas8_init_cbanals_staus ARRAY*/
#define BCM_CHANAL_UNINTALIZED		-1
#define BCM_CHANAL_NO_TASKS			 0

#define BCM_RECIVING_ID					0
#define BCM_RECIVING_DATA_SIZE			2
#define BCM_MAX_RECIVING_BUFFER_SIZE	50

#define BCM_FRAM_SIZE_LOWER_NIBBLE		1
#define BCM_FRAM_SIZE_HIGH_NIBBLE		2
#define SHIFT_8							8
#define BCM_FRAM_SIZE_INDX				3
#define BCM_DATA_START_POS				3

/*macros for frame elements size*/
#define BCM_FRAM_ELEMENT_ONE			0
#define BCM_FRAM_ELEMENT_TWO			1
#define BCM_FRAM_ELEMENT_THREE			2
#define BCM_FRAM_ELEMENT_FOUR			3
#define ZERO                            0
#define ONE								1
typedef struct bcm_taskControlBlock{
	gstr_BCM_Task_cfg_t* bcmTask;/*user configuration*/
	uint8_t  u8_taskStatus;/*idle,sending,complete_sending*/
	uint8_t  u8_counter; /*counter to point to BCM_FRAM_POINTER to send 0 ,1 ,2 ,3 */
	uint8_t  u8_byteCounter; /*for each frame loop on its bytes*/
	uint8_t  u8_checkSum;/*hold sum of the bytes*/
	uint16_t u8_BCM_framSize;/*data size +2 bytes for numOfBytes + 1byte for BCM_ID +1 byte for checksum*/
	
	uint8_t* apu8_BCM_Frame[BCM_FRAME_SIZE];  
	//element not pointer 
}bcm_taskControlBlock_t;


static sint8_t gas8_init_chanals_stauts[BCM_MAX_CHANALS][BCM_MODES];		/*num of tasks in each comm chanal for uinit chanals value is -1*/
static bcm_taskControlBlock_t g3astr_BCM_Tasks[BCM_MAX_CHANALS][BCM_MODES]; /*for each comm chanal hold the max number of tasks*/
volatile static uint8_t gau8_BCM_FrameElementSize[BCM_FRAME_SIZE];
volatile static uint8_t gau8_BCM_RecivingBuffer[BCM_MAX_RECIVING_BUFFER_SIZE];/*buffer to recive data in*/
volatile static uint8_t u8_bufferCounter = ZERO;
static uint8_t u8_BCM_Id;/*to hold predetermined bcm_id*/




static void BCM_spiReciveCBF(void)
{
	/*	-check for task status 
	*		-if task status == Idle state 
	*			-change the state to receving header 
	*	-check buffer counter 
	*        - if buffer counter <  BCM max buffer size
	*           -receives data
	*        - else 
	*          -Do nothing 
	*/
	bcm_taskControlBlock_t* pstr_currentTask =&g3astr_BCM_Tasks[BCM_SPI_CHANAL][BCM_RECIVER];
	
	if(pstr_currentTask->u8_taskStatus == STATE_IDLE ){
		pstr_currentTask->u8_taskStatus = STATE_RECIVING_HEAEDER;
	}
	
	
	if(u8_bufferCounter<BCM_MAX_RECIVING_BUFFER_SIZE)
	{
		uint8_t u8_data;
		SPI_getData(&u8_data);
		SPI_sendData(u8_data+1);
		gau8_BCM_RecivingBuffer[u8_bufferCounter] = u8_data;
		u8_bufferCounter++;
		
	}
}


static void BCM_spiSentCBF(void)
{
	/*	-check for task status 
	*		-if task status == sending byte 
	*			-get data to send and send it
	*			-change state to send byte complete
	*		-else do nothing
	*/
	static uint8_t u8_SPI_TaskIndx = ZERO;
	/*get status*/
	uint8_t state ;
	uint8_t loop_counter = ZERO;
	do 
	{
			state = (g3astr_BCM_Tasks[BCM_SPI_CHANAL][BCM_SENDER].u8_taskStatus);
			u8_SPI_TaskIndx++;
			u8_SPI_TaskIndx = (u8_SPI_TaskIndx%(gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER]));
			loop_counter++;
	} while (state != STATE_SENDING_BYTE && loop_counter < (gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER]));
	
	/*check for status*/
	/*get data and send it*/

	if(state == STATE_SENDING_BYTE)
	{

		(g3astr_BCM_Tasks[BCM_SPI_CHANAL][BCM_SENDER].u8_taskStatus = STATE_SEN_BYTE_COMPLETE);
	}
	
}

static uint8_t bcm_uartSend()
{

	/*implement call back fun*/
}


static void bcm_uartResive(uint8_t value)
{
	/*implement call back fun*/
}

u8_ERROR_STATUS_t BCM_init(gstr_BCM_cfg_t* pstr_bcm_cfg )
{
	/*
	*	1-check for errors
	*	2-switch on chanal
	*	3-switch on mode
	*/
	u8_ERROR_STATUS_t u8_fun_status = E_OK;
	static  uint8_t u8_UninitChannelFlag = UNINT_CHANNEL_UNDONE;
	
	if(pstr_bcm_cfg ==  NULL)
	{
		u8_fun_status = BCM_MODULE_ERR+NULL_PTR_ERROR;
	}
	else
	{
		/*
		*	1-loop on chanals to make them unitalized
		*
		*/
		gstr_uart_cfg_t srt_uart_cfg;
		gstrSPI_spi_satus_t str_sip_cfg;
		uint8_t u8_count = ZERO;
		uint8_t u8_chanaModCounter = ZERO;
		
		/*unitailize all chanals*/
		//////////////////////////////
		
		if (u8_UninitChannelFlag == UNINT_CHANNEL_UNDONE){
			
			for(;u8_chanaModCounter < BCM_MODES ; u8_chanaModCounter++)
				for (u8_count = ZERO;u8_count<BCM_MAX_CHANALS ; u8_count++)//  u8_count = ZERO add it ,it will cause multip;e reuninit
					(gas8_init_chanals_stauts[u8_count][u8_chanaModCounter]) = BCM_CHANAL_UNINTALIZED;
			u8_UninitChannelFlag =UNINT_CHANNEL_DONE;
			
		}
		/////////////////////////////////
		 
		
		
		switch(pstr_bcm_cfg->chanal)
		{
			case BCM_UART_CHANAL: 
				/*configure uart*/
			    srt_uart_cfg.uartTXCBF = bcm_uartSend;
				srt_uart_cfg.uartRXCBF = bcm_uartResive;
				switch(pstr_bcm_cfg->mode)
				{
					case BCM_SENDER:
					break;
					case BCM_RECIVER:
					break;
					default: /*error state*/
					u8_fun_status = (BCM_MODULE_ERR+INVALAD_PARAMETER);
					break;
				}
				Uart_Init(&srt_uart_cfg);			
			break;
			case BCM_SPI_CHANAL:
				switch(pstr_bcm_cfg->mode)
				{
					/*
					*	-initalize module
					*	-make module init and has zero tasks
					*
					*/
					case BCM_SENDER:
						if (gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER]!= BCM_CHANAL_UNINTALIZED){
							u8_fun_status = (BCM_MODULE_ERR+MODULE_NOT_INITALIZED);
						}
						else{
							str_sip_cfg.spi_mod			     = SPI_MASTER_MOD;
							str_sip_cfg.spi_opration_mod	 = SPI_INT_MOD;
							str_sip_cfg.spi_prescaler		 = SPI_PRESCALER_128;
							str_sip_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
							str_sip_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
							str_sip_cfg.spi_data_order	     = SPI_DATA_ORDER_LSB;
							str_sip_cfg.spi_cbf		         = BCM_spiSentCBF;
							
							SPI_init(&str_sip_cfg);
							spi_enable();
						}
						
					break;
					case BCM_RECIVER:
					if (gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_RECIVER]!= BCM_CHANAL_UNINTALIZED){
						u8_fun_status = (BCM_MODULE_ERR+MODULE_NOT_INITALIZED);
					}
					
					else {
						
						str_sip_cfg.spi_mod			 = SPI_SLAVE_MOD;
						str_sip_cfg.spi_opration_mod	 = SPI_INT_MOD;
						str_sip_cfg.spi_prescaler		 = SPI_PRESCALER_128;
						str_sip_cfg.spi_speed_mod		 = SPI_NORMAL_SPEED;
						str_sip_cfg.spi_sampling_mod	 = SPI_SAMPLING_MOD_0;
						str_sip_cfg.spi_data_order	 = SPI_DATA_ORDER_LSB;
						str_sip_cfg.spi_cbf		     = BCM_spiReciveCBF;
						
						SPI_init(&str_sip_cfg);
					}
						
					break;
					default: /*error state*/
					u8_fun_status = (BCM_MODULE_ERR+INVALAD_PARAMETER);
					break;
				}
				/*set spi chanal with zero tasks*/
				(gas8_init_chanals_stauts[BCM_SPI_CHANAL][pstr_bcm_cfg->mode]) = BCM_CHANAL_NO_TASKS;
				/*set size for each element in au8_BCM_FrameElementSize */
				gau8_BCM_FrameElementSize[BCM_FRAM_ELEMENT_ONE]   = ONE_BYTE;
				gau8_BCM_FrameElementSize[BCM_FRAM_ELEMENT_TWO]   = TWO_BYTE;
				gau8_BCM_FrameElementSize[BCM_FRAM_ELEMENT_THREE] = ZERO;
				gau8_BCM_FrameElementSize[BCM_FRAM_ELEMENT_FOUR]  = ONE_BYTE;  
			break;
			case BCM_I2C_CHANAL:
			break;
			default: /*error state*/
				u8_fun_status = (BCM_MODULE_ERR+INVALAD_PARAMETER);
			break;
		}
		
	}

	return u8_fun_status;
}


u8_ERROR_STATUS_t BCM_setup(gstr_BCM_Task_cfg_t* str_BCM_TaskCfg)
{
	u8_ERROR_STATUS_t u8_fun_status = E_OK;
		
	if (str_BCM_TaskCfg == NULL)
	{
		u8_fun_status = BCM_MODULE_ERR+NULL_PTR_ERROR;
	}
	else
	{
		/*
		*	-set all bcm task control configration
		*	-set task in its position
		*	-increment number of task for specified chanal
		*	-lock on buffer
		*	-send first byte to start transition
		*/
		if( (str_BCM_TaskCfg->chanal     != BCM_UART_CHANAL) 
		     && (str_BCM_TaskCfg->chanal != BCM_SPI_CHANAL)
		     && (str_BCM_TaskCfg->chanal != BCM_I2C_CHANAL) ){
				 
				u8_fun_status = (BCM_MODULE_ERR+INVALAD_PARAMETER);
		}
			else{
				if((str_BCM_TaskCfg->mode != BCM_SENDER) && (str_BCM_TaskCfg->mode != BCM_RECIVER)){
					
					u8_fun_status = (BCM_MODULE_ERR+INVALAD_PARAMETER);
				}
				else{
					
					bcm_taskControlBlock_t* currentTask = &g3astr_BCM_Tasks[str_BCM_TaskCfg->chanal][str_BCM_TaskCfg->mode];
		
					currentTask->bcmTask = (str_BCM_TaskCfg);
					currentTask->u8_taskStatus = STATE_IDLE;
					/*currentTask->u8_taskStatus = STATE_FINISED;*/
					currentTask->u8_checkSum = ZERO;
					currentTask->u8_counter = ZERO;
					currentTask->u8_byteCounter = ZERO;
					currentTask->u8_BCM_framSize = *(str_BCM_TaskCfg->size) + BCM_FRAM_HEADER_OVERHEAD;	
		
					u8_BCM_Id =BCM_SPI_ID;/*load bcm id*/

					gau8_BCM_FrameElementSize[BCM_FRAM_ELEMENT_THREE]=*str_BCM_TaskCfg->size;	/*load buffer size taken from user*/
		

					currentTask->apu8_BCM_Frame[BCM_FRAM_ELEMENT_ONE]= &u8_BCM_Id;
					currentTask->apu8_BCM_Frame[BCM_FRAM_ELEMENT_TWO]=(uint8_t *)&(currentTask->u8_BCM_framSize);
					currentTask->apu8_BCM_Frame[BCM_FRAM_ELEMENT_THREE]=currentTask->bcmTask->buffer;
					currentTask->apu8_BCM_Frame[BCM_FRAM_ELEMENT_FOUR]=&(currentTask->u8_checkSum);
		
		
					/*set task in its chanal and its pos*/
					//(g3astr_BCM_Tasks[str_BCM_TaskCfg->chanal][str_taskController.bcmTask->mode][(gas8_init_chanals_stauts[str_BCM_TaskCfg->chanal][str_taskController.bcmTask->mode])]) = str_taskController;
		
					/*increment number of tasks for this chanal _uncomment this file for multiple sending_*/
					//(gas8_init_chanals_stauts[str_BCM_TaskCfg->chanal][currentTask->bcmTask->mode])++;
					(gas8_init_chanals_stauts[str_BCM_TaskCfg->chanal][currentTask->bcmTask->mode])= ONE;/*will be removed*/
					
					/*lock the buffer*/
					*(str_BCM_TaskCfg->lock) = LOCK;
		
					switch(str_BCM_TaskCfg->chanal)
					{
						case BCM_SPI_CHANAL:
							switch(str_BCM_TaskCfg->mode)
							{
								case BCM_SENDER:
						
								break;
								case BCM_RECIVER:
									spi_enable();
								break;
							}
						break;
						case BCM_I2C_CHANAL:
						break;
						case BCM_UART_CHANAL:
						break;
					}
				}
					
			}
		}
			
	return u8_fun_status;
}

u8_ERROR_STATUS_t BCM_RX_dispatcher()
{

	u8_ERROR_STATUS_t u8_fun_error_status = E_OK;
	PORTA_DIR=1;
	uint8_t u8_BCM_chanalIndx =ZERO;
	for (;u8_BCM_chanalIndx < BCM_MAX_CHANALS ; u8_BCM_chanalIndx++)
	{
		u8_fun_error_status = E_OK;

		if(((gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]) != BCM_CHANAL_UNINTALIZED ) 
		&& ((gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]) != BCM_CHANAL_NO_TASKS)) /*chanal init and task exist*/
		 { 
			// 			/*loop thought tasks in chanal*/
			// 			uint8_t u8_taskINdxr = ZERO;
			// 			for (;u8_taskINdxr < (gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_RECIVER]);u8_taskINdxr++)
			// 			{
			// 			/*get state and current task buffer counter and data to send*/
			
			bcm_taskControlBlock_t* pstr_currentTask =  &g3astr_BCM_Tasks[u8_BCM_chanalIndx][BCM_RECIVER];
			switch(u8_BCM_chanalIndx)
			{
				case BCM_SPI_CHANAL:
				
				switch(pstr_currentTask->u8_taskStatus)
				{
					case STATE_IDLE:
					
					break;
					
					case STATE_RECIVING_HEAEDER:
					
					/*check if we received the frame id and  size*/

					if(u8_bufferCounter>=BCM_FRAM_SIZE_INDX)
					{
						pstr_currentTask->u8_taskStatus = STATE_CHEAKING_HEADER;
					}
					break;
					
					case STATE_CHEAKING_HEADER:
					
					pstr_currentTask->u8_BCM_framSize = ZERO;
					pstr_currentTask->u8_BCM_framSize = (gau8_BCM_RecivingBuffer[BCM_FRAM_SIZE_HIGH_NIBBLE]<<SHIFT_8);
					pstr_currentTask->u8_BCM_framSize |= gau8_BCM_RecivingBuffer[BCM_FRAM_SIZE_LOWER_NIBBLE];
					
					/*check received frame id = to BCM ID*/
					if (gau8_BCM_RecivingBuffer[ZERO]!=BCM_SPI_ID)
					{
						pstr_currentTask->u8_taskStatus=STATE_ERROR;
					}
					else  /*check  received frame size <= to BCM buffer size*/
					
					{     
						
						if(pstr_currentTask->u8_BCM_framSize > BCM_MAX_RECIVING_BUFFER_SIZE )
						{
							pstr_currentTask->u8_taskStatus = STATE_ERROR;
						}
						else
						{
							pstr_currentTask->u8_taskStatus = STAE_RECIVING_FRAME;
						}
					}
					
					break;
					
					case STAE_RECIVING_FRAME:
					
					if(u8_bufferCounter >= pstr_currentTask->u8_BCM_framSize )
					{
						
						spi_disable();

						if(u8_bufferCounter <= BCM_MAX_RECIVING_BUFFER_SIZE )
						{
							
							pstr_currentTask->u8_taskStatus = STATE_FRAM_RECIVE_COMPLETE;
							
						}
						
						
						else
						{
							pstr_currentTask->u8_taskStatus = STATE_ERROR;
						}
						
					}
					
					break;
					
					case STATE_FRAM_RECIVE_COMPLETE:
					
					pstr_currentTask->u8_taskStatus = STATE_FINISED;
					u8_bufferCounter = ZERO;
					
					break;
					
					case STATE_ERROR :
					
					break;
					
					case STATE_FINISED:;
					*pstr_currentTask->bcmTask->size=  (pstr_currentTask->u8_BCM_framSize - BCM_FRAM_HEADER_OVERHEAD);
					
					uint8_t u8_counter = ZERO;
					
					/*COPY DATA TO USER BUFFER*/
					for (;u8_counter < *pstr_currentTask->bcmTask->size ;u8_counter++)
					{
						pstr_currentTask->bcmTask->buffer[u8_counter] = gau8_BCM_RecivingBuffer[u8_counter+BCM_DATA_START_POS];
					}
					//u8_fun_error_status=OK;
					gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_RECIVER]--;
					*pstr_currentTask->bcmTask->lock = UNLOCK;
					PORTA_DIR=u8_fun_error_status;
					pstr_currentTask->bcmTask->bcm_cbf(u8_fun_error_status);
					*pstr_currentTask->bcmTask->size=ZERO;
					
					break;
					default:
					break;
				}
				
				
				break;
				
				
				
				case BCM_UART_CHANAL:
				break;
				case BCM_I2C_CHANAL:
				break;
				default:
				break;
			}
			
			
			/*}*/
			TCNT0=u8_fun_error_status;
		}
		 
		 
		else
		{
			u8_fun_error_status = BCM_MODULE_ERR + MODULE_NOT_INITALIZED;
		}
		
				TCNT2=u8_fun_error_status;

	}
return u8_fun_error_status;
 }
u8_ERROR_STATUS_t BCM_TX_dispatcher()
	{
		u8_ERROR_STATUS_t u8_fun_error_status = E_OK;
		/*loop through three chanal
		* -for initialized chanal loop through it's tasks
		* -for each task set task check for it's status
		*	-if chanal is initiated
		*		loop thought chanal tasks
		*			 switch on chanal
		*			 case spi:
		*				 switch case on task state
		*					-case idle
		*						- send first byte through spi
		*						- change state to sending byte
		*					-case sendByteCompleted
		*						-increment task buffer counter
		*						-if last byte in buffer
		*							-change state to frame send complete
		*						-else
		*							-change state to sending byte
		*					-case sending byte
		*						-do nothing
		*						-case frame send complete
		*						-unlock buffer, change state to completed,call back notifier function
		*/
		
		uint8_t u8_BCM_chanalIndx =ZERO;
	
		/*dispatcher can serve only one request for each chanal at one super loop, recored task num to serve*/
		/*loop for each chanal on TX TASKS and serve only one task*/
		for (;u8_BCM_chanalIndx < BCM_MAX_CHANALS ; u8_BCM_chanalIndx++)
					if((gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_SENDER]) != BCM_CHANAL_UNINTALIZED 
					&& (gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_SENDER]) != BCM_CHANAL_NO_TASKS) /*chanal init and task exist*/
					{
						/*loop thought tasks in chanal*/
						//uint8_t u8_taskINdxr = ZERO;
	
						//for (;u8_taskINdxr < (gas8_init_chanals_stauts[u8_BCM_chanalIndx][BCM_SENDER]);u8_taskINdxr++)
						//{
							/*get state and current task buffer counter and data to send*/
							bcm_taskControlBlock_t* pstr_currentTask =  &g3astr_BCM_Tasks[u8_BCM_chanalIndx][BCM_SENDER];
							uint8_t data =  *(pstr_currentTask->apu8_BCM_Frame[pstr_currentTask->u8_counter]+pstr_currentTask->u8_byteCounter); /*get data if counter didn't reach end of buffer*/
							TCNT2=gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER];
							switch(u8_BCM_chanalIndx)
							{
								/*	-case idle
								*		- send first byte through SPI
								*		- change state to sending byte
								*	-case sendByteCompleted
								*		-increment task buffer counter
								*		-if last byte in buffer
								*			-change state to frame send complete
								*		-else
								*			-change state to sending byte
								*	-case sending byte
								*		-do nothing
								*	-case frame send complete
								*		-unlock buffer, change state to completed,call back notifier function
								*/
								case BCM_SPI_CHANAL:
									switch(pstr_currentTask->u8_taskStatus)
									{
										case STATE_IDLE:
											SPI_sendData(data);
											pstr_currentTask->u8_taskStatus = STATE_SENDING_BYTE;
	
										break;
										case STATE_SENDING_BYTE:
											/*do nothing*/										  
										break;
										case STATE_SEN_BYTE_COMPLETE:
											pstr_currentTask->u8_checkSum+=data;/*load old data*/
											if (pstr_currentTask->u8_counter == BCM_FRAME_SIZE)
											{
												pstr_currentTask->u8_taskStatus = STATE_FRAM_SEND_COMLETE;
												
												
								
											}
											else /*still data to send*/
											{
												
												/*
												*	get next byte to send
												*	update state
												*/
												uint8_t size = (pstr_currentTask->u8_counter == BUFFER_SIZE_ELEM)? *(pstr_currentTask->bcmTask->size): (gau8_BCM_FrameElementSize[pstr_currentTask->u8_counter]);
												
												if (pstr_currentTask->u8_byteCounter == size-ONE)
												{
													pstr_currentTask->u8_byteCounter = ZERO;
													(pstr_currentTask->u8_counter)++;
												}
												else
												{
													(pstr_currentTask->u8_byteCounter)++;
												}
												data = *(pstr_currentTask->apu8_BCM_Frame[pstr_currentTask->u8_counter]+pstr_currentTask->u8_byteCounter);
												SPI_sendData(data);
												
												pstr_currentTask->u8_taskStatus = STATE_SENDING_BYTE;
											}
										break; 
										case STATE_FRAM_SEND_COMLETE:
										//*pstr_currentTask->bcmTask->size=ZERO;
										*pstr_currentTask->bcmTask->lock = UNLOCK;
										TCNT2=gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER];
										gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER] --;
										TCNT2=gas8_init_chanals_stauts[BCM_SPI_CHANAL][BCM_SENDER];
										pstr_currentTask->bcmTask->bcm_cbf(u8_fun_error_status);
											
										break;
										
									}
								break;
								case BCM_UART_CHANAL:
								break;
								case BCM_I2C_CHANAL:
								break;
							}
						
						//}
						
						/*update to next task to serve*/
					}
					
				else {
					u8_fun_error_status = BCM_MODULE_ERR + MODULE_NOT_INITALIZED;
				}
					
		return u8_fun_error_status;
	}
		