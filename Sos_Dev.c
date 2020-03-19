
 
 /*********************************************
 *				Includes  					 *
 ********************************************/
 #include "std_types.h"
 #include "Sos.h"
 
/*********************************************
*				Defines  					 *
********************************************/
#define	FIRSTPIN	0x01
#define	SECONDPIN	0x02
#define	THIRDPIN	0x04

#define	Task1Delay	250
#define	Task2Delay	250
#define	Task3Delay	250

#define	Task1Priodicity		1
#define	Task2Priodicity		1
#define	Task3Priodicity		1

#define	Task1Priority		1
#define	Task2priority		0
#define	Task3priority		2

#define	Task1InitCNTValue	0
#define	Task2InitCNTValue	0
#define	Task3InitCNTValue	0

#define Zero	0
#define ONE		1
#define TWO		2 

 /*********************************************
 *	   Function Implementation  	       	  *
 ********************************************/
 
/**function One tooglr the first pin in portA**/
void func1(void)
{
	
	PORTA_DATA^=FIRSTPIN;
}

/**function two toogle the second pin pin in portA**/
void func2(void)
{
	PORTA_DATA^=SECONDPIN;
}

/**function Three toogle the third pin in portA**/
void func3(void)
{
	PORTA_DATA^=THIRDPIN;
}

/********************************************
 *				CBK_Functions                *
 *********************************************/
 
Sos_cfg_start Sos_cfg_start_Fun1 = {Task1Delay,Task1Priodicity,Task1InitCNTValue,Task1Priority,func1};
 
Sos_cfg_start Sos_cfg_start_Fun2 = {Task2Delay,Task2Priodicity,Task2InitCNTValue,Task2priority,func2};
 
Sos_cfg_start Sos_cfg_start_Fun3 = {Task3Delay,Task3Priodicity,Task3InitCNTValue,Task3priority,func3};
 
/******static global Array of Call Back Structure functions*******/
 static Sos_cfg_start Sos_CBK_Arr_Struct[No_of_CBK];
 
 /*******gu8_Sos_Ch_TimerNo to store the channel timer********/
 static uint8_t gu8_Sos_Ch_TimerNo;
 /************index of the array of structure***************/
 static uint8_t arr_counter;
 
 static uint8_t gu8_MaxArrCounter;
 /********* Sos_FLag_Fun variable store no of timer ticks************/
 volatile uint16_t Sos_FLag_Fun = ONE;
 /********* Sos_FLag_Fun Array store no of timer ticks************/
 volatile uint16_t Sos_Flag_Arr[No_of_CBK];
 
	 
 uint8_t x= Zero;	 
 /********************************************
 *			  Function Implementation        *
 *********************************************/
 /**
 * Func			: Sos_Init
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (timer channel ,resolution of the Sos)
 */
 uint8_t Sos_Init(const Sos_ConfigType * ConfigPtr){
	 /**Error store of the error of the function**/
	 uint8_t Err_status  = E_OK;
	 
	 /**Initialize PORTA Direction**/
	 PORTA_Init();
	 
	 if (ConfigPtr == NULL)
	 {
		 Err_status = NULL_PTR;
	 } 
	 else
	 {
		 //create an object for timer structure
		 Timer_Cfg_S Timer_Cfg;
		 
		 //Declaring gu8_Sos_Ch_TimerNo to store timer channel
		 gu8_Sos_Ch_TimerNo  = ConfigPtr->Sos_Ch_Timer;
		 
		 //Definition of timer
		 Timer_Cfg.Timer_CH_NO = gu8_Sos_Ch_TimerNo;
		 Timer_Cfg.Timer_Mode  = Zero;
		 Timer_Cfg.Timer_Polling_Or_Interrupt = T2_INTERRUPT_NORMAL;   //T2_INTERRUPT_NORMAL=0x40;
		 Timer_Cfg.Timer_Prescaler = T2_PRESCALER_64;
		 Timer_Init(&Timer_Cfg);
	 }
	return Err_status;
 }
 
 
 /**
 * Func			: Create_Task
 * Input		: Pointer to a structure of type contains the Sos_delay ,Sos_periodicity and call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Start the Sos (one shot or period , delay time, call back function)
 */

uint8_t Create_Task(Sos_cfg_start * Sos_StartPtr){
	/**Error store of the error of the function**/
	uint8_t Err_Status =E_OK;
	/**check if the ptr passed is null**/
	if (Sos_StartPtr==NULL)
	{
		Err_Status=NULL_PTR;
	} 
	else
	{
		/**check the value of the priiority of the next task and storre it**/
	arr_counter = Sos_StartPtr->Sos_Periority;
		/*****Fill  the elements of the array to start the  tasks ******/
	Sos_CBK_Arr_Struct[arr_counter] = *Sos_StartPtr;
	
		/**store the max number of the elements of the array**/
	if (gu8_MaxArrCounter<arr_counter)
	{	/**In case the enter number was highest than exist in array**/
		gu8_MaxArrCounter = arr_counter;
	} 
	else
	{
		// do nothing
	}
	
	//start timer to count delay
	Timer_Start(gu8_Sos_Ch_TimerNo,Zero);
			
	}
	
	/**return the error stutua of the function**/
	return Err_Status;
}
 /**
 * Func			: Sos_Run
 * Input		: Pointer to a pointer to array of Call Back Structure functions
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: 
 */
 
 uint8_t Sos_Run(){
		/**Error store of the error of the function**/
		uint8_t Err_Status = E_OK;
		
		/**check if the flag of te isr is set**/
		if (Sos_FLag_Fun == ONE)
		{
			/**Increment the counter of the tasks**/
			Sos_CBK_Arr_Struct[Zero].Sos_Counter++;
			Sos_CBK_Arr_Struct[ONE].Sos_Counter++;
			Sos_CBK_Arr_Struct[TWO].Sos_Counter++;
			Sos_FLag_Fun=Zero;
		} 
		else
		{
			//do Nothing
		}
		
		if (gu8_MaxArrCounter==0)
		{
			/**handle the errror as embty buffer there is no elements exist in gthe buffer**/
			Err_Status = EMPTY_BUFFER;
		} 
		else
		{
			/**loop on the created tasks to perform it**/
		for (uint8_t i=Zero; i<=gu8_MaxArrCounter ; i++)
		{
			
			if (Sos_CBK_Arr_Struct[i].Sos_Counter==Sos_CBK_Arr_Struct[i].Sos_delay)
			{
								
				Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr();
				Sos_CBK_Arr_Struct[i].Sos_Counter=0;
				
				if (Sos_CBK_Arr_Struct[i].Sos_periodicity == Zero)
				{
					/**Delete task in case it has one shot periodicity**/
					Delete_Task(Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr);
				} 
				else
				{
					//do Nothing
				}
			} 
			else
			{
				//do Nothing
			}
		}
			}
			
		/**return the error of the function**/	
	  return Err_Status;
 }

 
/**
 * Func			: Sos_Stop
 * Input		: Pointer to a structure of type  call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: stop(call back function)
 */
 
void Delete_Task (void(*ptr)(void)){
	
	/***********initilaize arr_counter**********/
	 uint8_t S_Arr_counter; 
	 //arr_counter
	 for(S_Arr_counter = Zero;S_Arr_counter<gu8_MaxArrCounter;S_Arr_counter++){
		
		if(Sos_CBK_Arr_Struct[S_Arr_counter].Sos_Cbk_ptr==ptr){
			
			Sos_CBK_Arr_Struct[S_Arr_counter] = Sos_CBK_Arr_Struct[gu8_MaxArrCounter];
			
			Sos_CBK_Arr_Struct[gu8_MaxArrCounter].Sos_Cbk_ptr = NULL;
			Sos_CBK_Arr_Struct[gu8_MaxArrCounter].Sos_delay = Zero;
			Sos_CBK_Arr_Struct[gu8_MaxArrCounter].Sos_Periority =Zero;
			Sos_CBK_Arr_Struct[gu8_MaxArrCounter].Sos_periodicity = Zero;
			
			/*************Decrement the structures of the array*******************/
			gu8_MaxArrCounter--;
			
		} 
	 }
 }
 
/**
 * Func			: Sos_DeInit
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Deinitialize shall uninitialized the hardware timer module.
 */
 
 
void Sos_DeInit( ){
	 
	//Timer_Stop(gu8_Sos_Ch_TimerNo); 
	 x=Zero;
	for(uint8_t i=0;i<gu8_MaxArrCounter;i++){
		/**Deinitialize all the parameter of the task**/
		Sos_CBK_Arr_Struct[i].Sos_delay = Zero;
		Sos_CBK_Arr_Struct[i].Sos_Periority = Zero;
		Sos_CBK_Arr_Struct[i].Sos_periodicity = Zero;
		Sos_CBK_Arr_Struct[i].Sos_Cbk_ptr = NULL;
	}
 }

 
 

 