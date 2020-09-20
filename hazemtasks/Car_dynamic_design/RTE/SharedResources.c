/*
 * SharedResources.c
 *
 * Created: 3/30/2020 12:45:31 PM
 *  Author: Reem
 */ 
#include "SharedResources.h"

static uint16_t gu16_Distance;

void SharedRes_Init(void)
{
	gu16_Distance=0;
}
void SharedRes_setDistanceVal(uint16_t Distance)
{
	gu16_Distance = Distance;
	
}

void SharedRes_getDistanceVal(uint16_t *Distance)
{
	*Distance = gu16_Distance;
}