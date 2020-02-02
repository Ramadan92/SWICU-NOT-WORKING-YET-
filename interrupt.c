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



void EXTI_Init(uint8_t u8_INTNo , uint8_t u8_sense)
{
	GICR |= u8_INTNo;
	
	switch (u8_INTNo)
	{
		case INT0:
		{
			gpioPinDirection(GPIOD,BIT2,INPUT);
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
			gpioPinDirection(GPIOD,BIT3,INPUT);
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
			gpioPinDirection(GPIOB,BIT2,INPUT);
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
	
}

InterruptServiceRoutine(INT1_vect)
{
	
}

InterruptServiceRoutine(INT2_vect)
{	
	/*Flag to switch between falling and rising edges*/
	volatile static uint8_t u8_ISRFlag=0;
	
	switch (u8_ISRFlag)
	{
		case 0:
		
		/*start the timer counter*/
		timer0Start();
		
		/*update the value of the flag*/
		u8_ISRFlag=1;
		
		/*re-configure the external interrupt's sense to be falling edge*/
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		break;
		
		case 1:
		/*stop the timer counter*/
		timer0Stop();
		
		/*disable the interrupt*/
		GICR &= ~(INT2);
		
		/*re-configure the external interrupt's sense to be rising edge*/
		MCUCSR |= 0x40;
		
		/*update the value of the flag*/
		u8_ISRFlag=0;
		
		break;
	
	}
	
}