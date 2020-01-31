/*
 * interrupt.c
 *
 * Created: 1/29/2020 7:02:09 PM
 *  Author: ahmed
 */ 
#include "registers.h"
#include "timers.h"
#include "interrupt.h"
#include "gpio.h"
#include "led.h"
#include "SwICU.h"
#include "BITMATH.h"
#include "softwareDelay.h"

volatile static uint8_t flag=0;

void EXTI_Init(uint8_t u8_INTNo , uint8_t u8_sense)
{
	GICR |= u8_INTNo;
	
	switch (u8_INTNo)
	{
		case INT0:
		{
			switch(u8_sense)
			{
				case INT0_LOW_LEVEL:
				MCUCR &= !(INT0_RISING_EDGE);
				break;
				
				default:
				MCUCR |= u8_sense;
				break;
			}
		}
		break;
		
		case INT1:
		{
			switch(u8_sense)
			{
				case INT1_LOW_LEVEL:
				MCUCR &= !(INT1_RISING_EDGE);
				break;
				
				default:
				MCUCR|=u8_sense;
			}
		}
		break;
		
		case INT2:
		{
			switch(u8_sense)
			{
				case INT2_FALLING_EDGE:
				MCUCSR &= !(INT2_RISING_EDGE);
				break;
				
				case INT2_RISING_EDGE:
				MCUCSR |= INT2_RISING_EDGE;
				break;
			}
		}
		break;
	}
}

void EXTI_DEInit(void)
{
	MCUCR &=0x00;
	MCUCSR &=0x00;
	GICR &=0x00;
}

InterruptServiceRoutine(INT0_vect)
{
	/*switch (flag)
	{
		case 0:
		timer0Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		flag=1;
		break;
		
		case 1:
		timer0Stop();
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		flag=0;
		break;
	}*/
}

InterruptServiceRoutine(INT1_vect)
{
	
}

InterruptServiceRoutine(INT2_vect)
{	
	switch (flag)
	{
		case 0:
		timer0Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		flag=1;
		break;
		
		case 1:
		timer0Stop();
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		flag=0;
		break;
	}
	
}