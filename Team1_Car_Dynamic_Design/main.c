/*
 * main.c
 *
 * Created: 3/30/2020 3:50:05 AM
 *  Author: Ahmed
 */ 


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include "std_types.h"
#include "SOS.h"
#include "car_sm.h"

int main(void)
{
	Car_SM_Init();
	SOS_run();
	
	while(1);
	
	return 0;
}