/*
 * timers.c
 *
 * Created: 1/20/2020 11:06:28 PM
 *  Author: ahmed
 */ 
#include "timers.h"
#include "interrupt.h"
#include "led.h"
#include "gpio.h"

En_timer0perscaler_t en_gprescal0= T0_NO_CLOCK ;
En_timer1perscaler_t en_gprescal1= T1_NO_CLOCK ;
En_timer2perscaler_t en_gprescal2= T2_NO_CLOCK ;

uint8_t u8_gTCNT0PreloadValue;

/***************************************************************************************/
/*																				       */
/*							Timer0 functions implementation                            */                  
/*                                                                                     */
/***************************************************************************************/
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{
	en_gprescal0 = en_prescal;
	
	switch (en_mode)
	{
		case T0_NORMAL_MODE:
		TCCR0 |= T0_NORMAL_MODE;
		break;
		
		case T0_COMP_MODE:
		TCCR0 |= T0_COMP_MODE;
		break;
	}
	
	switch (en_OC0)
	{
		case T0_OC0_TOGGLE:
		TCCR0 |= T0_OC0_TOGGLE;
		break;
		
		case T0_OC0_SET:
		TCCR0 |= T0_OC0_SET;
		break;
		
		case T0_OC0_CLEAR:
		TCCR0 |= T0_OC0_CLEAR;
		break;
		
		case T0_OC0_DIS:
		TCCR0 |= T0_OC0_DIS;
		
	}
	
	/*switch (en_prescal)
	{
		case T0_NO_CLOCK:
		TCCR0 |= T0_NO_CLOCK;
		break;
		
		case T0_PRESCALER_NO:
		TCCR0 |= T0_PRESCALER_NO;
		break;
		
		case T0_PRESCALER_8:
		TCCR0 |= T0_PRESCALER_8;
		break;
		
		case T0_PRESCALER_64:
		TCCR0 |= T0_PRESCALER_64;
		break;
		
		case T0_PRESCALER_256:
		TCCR0 |= T0_PRESCALER_256;
		break;
		
		case T0_PRESCALER_1024:
		TCCR0 |= T0_PRESCALER_1024;
		break;
		
	}*/
	
	switch (en_interruptMask)
	{
		case T0_POLLING:
		TIMSK |= T0_POLLING;
		break;
		
		case T0_INTERRUPT_NORMAL:
		TIMSK |= T0_INTERRUPT_NORMAL;
		break;
		
		case T0_INTERRUPT_CMP:
		TIMSK |= T0_INTERRUPT_CMP;
		break;
		
		case T0_ALL_INTERRUPT:
		TIMSK |= T0_ALL_INTERRUPT;
		break;
	}
	
	TCNT0 = u8_initialValue;
	OCR0  = u8_outputCompare;
	
}

void timer0Set(uint8_t u8_value)
{
	TCNT0 = u8_value;
}

uint8_t timer0Read(void)
{
	return TCNT0;
}

void timer0Stop(void)
{
	T0_STOP;
	en_gprescal0 = T0_NO_CLOCK;
}

void timer0Start(void)
{
	if (en_gprescal0 != T0_NO_CLOCK)
		TCCR0|=en_gprescal0;
}

void timer0DelayMs(uint16_t u16_delay_in_ms)
{
	uint32_t u32_OVFCounter;
	uint8_t  u8_ISRCount=1;
	u8_gTCNT0PreloadValue=48;
	TCNT0 = u8_gTCNT0PreloadValue;
	
	timer0Start();
	
	for (u32_OVFCounter=0;u32_OVFCounter<(8*u16_delay_in_ms);u32_OVFCounter++)
	{
		
		while (!TOV0);
		u8_ISRCount++;
		if(u8_ISRCount == 8)
		{
			u8_gTCNT0PreloadValue=48;
			u8_ISRCount=1;
		}
		//TIFR |= (TIFR<<0);
		TIFR &= 0xFF;	
	}
	
	timer0Stop();
}

void timer0DelayUs(uint32_t u32_delay_in_us)
{
	uint32_t u32_OVFCounter;
	u8_gTCNT0PreloadValue=254;
	TCNT0 = u8_gTCNT0PreloadValue;
	
	timer0Start();
	for (u32_OVFCounter=0;u32_OVFCounter<(u32_delay_in_us);u32_OVFCounter++)
	{
		while (!TOV0);
		TIFR |= (TIFR<<0);
	}

	timer0Stop();
}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{
	OCR0 = u8_dutyCycle;
	switch(u8_frequency)
	{
		case F_8000:
		if (en_gprescal0!=T0_NO_CLOCK || en_gprescal0!=T0_PRESCALER_8)
		{
			timer0Stop();
			en_gprescal0 = T0_PRESCALER_8;
		}
		timer0Start();
		break;
		
		case F_1000:
		if (en_gprescal0!=T0_NO_CLOCK || en_gprescal0!=T0_PRESCALER_64)
		{
			timer0Stop();
			en_gprescal0 = T0_PRESCALER_64;
		}		
		timer0Start();
		break;
		
		case F_250:
		if (en_gprescal0!=T0_NO_CLOCK || en_gprescal0!=T0_PRESCALER_256)
		{
			timer0Stop();
			en_gprescal0 = T0_PRESCALER_256;
		}	
		timer0Start();	
		break;
		
		case F_60:
		if (en_gprescal0!=T0_NO_CLOCK || en_gprescal0!=T0_PRESCALER_1024)
		{
			timer0Stop();
			en_gprescal0 = T0_PRESCALER_1024;
		}
		timer0Start();
		break;
	}
}

/***************************************************************************************/
/*																				       */
/*							Timer1 functions implementation                            */
/*                                                                                     */
/***************************************************************************************/

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
{
	en_gprescal1= en_prescal;
	TCCR1|= (en_mode | en_OC | en_prescal | en_interruptMask);
	TCNT1 = u16_initialValue;
	OCR1A = u16_outputCompareA;
	OCR1B = u16_outputCompareB;
	ICR1  = u16_inputCapture;
}

void timer1Set(uint16_t u16_value)
{
	TCNT1 = u16_value;
}

uint16_t timer1Read(void)
{
	return TCNT1;
}

void timer1Start(void)
{
	if (en_gprescal1 != T1_NO_CLOCK)
		TCCR1 |= en_gprescal1;
}

void timer1Stop(void)
{
	T1_STOP;
	en_gprescal1= T1_NO_CLOCK;
}
/***************************************************************************************/
/*																				       */
/*							Timer2 functions implementation                            */
/*                                                                                     */
/***************************************************************************************/

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask)
{
	en_gprescal2 = en_prescal;
	TCCR2|= (en_mode | en_OC |T2_NO_CLOCK| en_interruptMask);
	switch (u8_assynchronous)
	{
		case ASSYNC:
		ASSR &= ASSYNC;
		
		case SYNC:
		ASSR |= SYNC;
	}
	
	TCNT2 = u8_initialValue;
	OCR2  = u8_outputCompare;
	
}

void timer2Set(uint8_t u8_a_value)
{
	TCNT2 = u8_a_value;
}

uint8_t timer2Read(void)
{
	return TCNT2;
}
void timer2Start(void)
{
	if (en_gprescal2 != T2_NO_CLOCK)
		TCCR2 |= en_gprescal2;
}
void timer2Stop(void)
{
	T2_STOP;
	en_gprescal2 = T2_NO_CLOCK;
}
void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency)
{
	OCR2 = u8_dutyCycle;
	switch(u8_frequency)
	{
		case F_8000:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_8)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_8;
		}
		timer2Start();		
		break;
		
		case F_2000:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_32)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_32;
		}
		timer2Start();
		break;
		
		case F_1000:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_64)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_64;
		}
		timer2Start();		
		break;
		
		case F_500:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_128)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_128;
		}
		timer2Start();		
		break;
		
		case F_250:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_256)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_256;
		}
		timer2Start();		
		break;
		
		case F_60:
		if (en_gprescal2!=T2_NO_CLOCK || en_gprescal2!=T2_PRESCALER_1024)
		{
			timer2Stop();
			en_gprescal2 = T2_PRESCALER_1024;
		}
		timer2Start();		
		break;
	}
}

InterruptServiceRoutine(TIMER2_OVF_vect)
{
	
}

InterruptServiceRoutine(TIMER2_COMP_vect)
{
		
}