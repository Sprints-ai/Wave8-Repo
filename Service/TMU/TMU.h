/*
 * TMU.h
 *
 * Created: 24/02/2020 03:00:09 م
 *  Author: TOSHIBA
 */ 


#ifndef TMU_H_
#define TMU_H_
/*****************************************************************************************************/
/*                                        INCLUDES                                                  */
/***************************************************************************************************/
#include "../../Infrastructure/std_types.h"
#include "../../MCAL/Timer/Timer.h"
#include "TMU_Cfg.h"




/*****************************************************************************************************/
/*                                        DEFINES                                                   */
/***************************************************************************************************/
                                // TMU_TIMER _ID//
							
#define TMU_TIMER_0 TIMER_CH_0
#define TMU_TIMER_1 TIMER_CH_1
#define TMU_TIMER_2 TIMER_CH_2
                           
						   //CONSUMER_MODE//
#define ONE_SHOOT (0)
#define PERUDIC   (1)	
	
                      //ERROR_CODE//
					  
#define MODULE_ERROR_NUMBER        (20)					  
#define  ERROR_NULL_PTR            (1)	
#define  ERROR_UNILTILZED_MODULE   (2)	
#define  ERROR_MULTIPLE_INIT       (3)
#define  ERROR_EMPTY_BUFFER        (4)
#define  ERROR_INVALIDE_PARAMETAR  (5)
#define  ERROR_MULTIPLE_START      (6)
#define  ERROR_FULL_BUFFER		   (7)	
#define  ERROE_EXIST_ID            (8)	
#define  ERROR_ELEMENT_NOT_EXIST   (9)		   


/*****************************************************************************************************/
/*                                       STRUCTS                                                    */
/***************************************************************************************************/
typedef struct{ uint8_t u8_TimerID;
	            uint8_t u8_TMU_reslution;
               }strTMU_Cfg_t;
			   

	
/*****************************************************************************************************/
/*                                     TMU FUNCTIONS' PROTOTYPES	                            */
/***************************************************************************************************/
/*
 * @param: input:  strTMU_Cfg_t  *
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  Initializes the TMU   
 */
u8_ERROR_STATUS_t TMU_Init (const strTMU_Cfg_t * ConfigPtr ) ;
/*
 * @param: input:None
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :  De_initializes the TMU   
 */
u8_ERROR_STATUS_t TMU_DeInit ( void ) ;
/*
 * @param: input:  u8_consumerTime  :Delay Time 
 * @param: input:  u8_consumerMode  : Consumer Mode that takes one of (ONE_SHOT,PERIODIC)
 * @param: input:  u8_ConsumerId    : Consumer Id 
 * @param: input:  void(*consumerPointer)(void) : Pointer to function 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Creates consumer with predetermined time    
 */
u8_ERROR_STATUS_t TMU_Start_Timer(uint8_t u8_consumerTime ,uint8_t u8_consumerMode,uint8_t u8_ConsumerId,void(*consumerPointer)(void) );
/*
 * @param: input:  u8_ConsumerId    : Consumer Id 
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description : Stops consumer     
 */
u8_ERROR_STATUS_t TMU_Stop_Timer(uint8_t u8_ConsumerId);
/*
 * @param: input:  None
 * @param: output: NONE
 * @param :Input/output :None 
 * @Return : Error status 
 * Description :Determines which consumer to be called      
 */
u8_ERROR_STATUS_t TMU_Dispatcher(void);





#endif /* TMU_H_ */