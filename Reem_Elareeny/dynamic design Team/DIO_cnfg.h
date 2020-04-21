/*
 * DIO_cnfg.h
 *
 * Created: 2/15/2020 11:04:26 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef DIO_CNFG_H_
#define DIO_CNFG_H_


/************************************************************************/
/*				                    INCLUDES	                 		         */
/************************************************************************/
#include "../Infrastructure/std_types.h"

/************************************************************************/
/*					        	CONFIGURATIONS TYPEDEF                       	*/
/************************************************************************/
typedef struct DIO_Cfg_s
{
	uint8_t GPIO;
	uint8_t pins;
	uint8_t dir;
}DIO_Cfg_t;



#endif /* DIO_CNFG_H_ */