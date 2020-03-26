/*
 * ERROR_STORE.h
 *
 * Created: 2/25/2020 1:01:06 PM
 *  Author: Khaled
 */ 


#ifndef ERROR_STORE_H_
#define ERROR_STORE_H_

#include "Errors.h"
#include "../Utilis/std_types.h"
#include "ERROR_STORE_CFG.h"
#include <stdio.h>

typedef struct str_Error_t
{
	uint8_t u8_Module_Number;
	uint8_t u8_Error_Number;
}str_Error_t;

extern void Error_Push (uint8_t Module, uint8_t Error);

void Error_Print (void);


#endif /* ERROR-STORE_H_ */