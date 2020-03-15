#ifndef SOS_H_
#define SOS_H_
/*
 * File		: Sos.h
 * Author	: M.Ramadan
 */

/*********************************************
 *				Includes  					 *
 ********************************************/
 #include "Timer.h"
 #include "Sos_cfg.h"


/*********************************************
 *				Defines  					 *
 ********************************************/
 #define No_of_CBK    3
 
 #define E_OK    0
 #define E_NOK   1
 
 /*********************************************
 *				Error Handling  			 *
 ********************************************/
 #define	NULL_PTR					2
 #define	MODULE_UNITIALIZED			3
 #define	MULTIPLE_INIYIALIZATION		4
 #define	STOP_WITH_START				5
 #define	INVALID_PARAMETER			6
 #define	MULTIPLE_STOP				7
 #define	MULTIPLE_START				8
 #define	FULL_BUFFER					9
 #define	EMPTY_BUFFER				10

 #define	T2_INTERRUPT_NORMAL			0x40
/************************************************************************/
/*			  Structures Declaration		                            */
/************************************************************************/
typedef struct Sos_cfg_start
{	
	/** delay of the task**/
	uint16_t Sos_delay;
	/**periodicity of the task**/
	uint16_t Sos_periodicity;
	/**counter of the task**/
	uint16_t Sos_Counter;
	/**task priority**/
	uint16_t Sos_Periority;
	// Sos_Cbk_ptr then use data type
	void (*Sos_Cbk_ptr)(void);
}Sos_cfg_start;
 
/************************************************************************/
/*			  Structures Definitions		                            */
/************************************************************************/ 
extern Sos_cfg_start Sos_cfg_start_Fun1;
extern Sos_cfg_start Sos_cfg_start_Fun2;
extern Sos_cfg_start Sos_cfg_start_Fun3; 
  

 /*********************************************
 *	  	   Function prototypes				 *
 ********************************************/
 
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
 
 
 uint8_t Sos_Init(const Sos_ConfigType * ConfigPtr );
 
/**
 * Func			: Create_Task
 * Input		: Pointer to a structure of type contains the Sos_delay ,Sos_periodicity and call back function
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: Initialize (timer channel ,resolution of the Sos)
 */

uint8_t Create_Task(Sos_cfg_start * Sos_StartPtr); 
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
 
 void Delete_Task();
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
 uint8_t Sos_Run();
 
 /**
 * Func			: Sos_DeInit
 * Input		: Pointer to a structure of type Sos_cfg_Init contains the Sos channel timer and resolution
 * Output
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful				
 *
 * Description	: De initialize (timer channel ,resolution of the Sos)
 */
 void Sos_DeInit(void);
 
 
 #endif