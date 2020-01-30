/*
* softwareDelay.c
*
* Created: 17/01/2020 03:54:09 م
*  Author: mo
*/
#include "softwareDelay.h"

void softwareDelayMs(uint32_t u32_delay_in_ms)
{
	uint32_t u32_factorizedCounter;
	
	for(u32_factorizedCounter=(u32_delay_in_ms * 1300);u32_factorizedCounter>0;u32_factorizedCounter--);
}