/*
 * SwICU.c
 *
 * Created: 1/29/2020 8:47:09 PM
 *  Author: ahmed
 */ 
#include "registers.h"
#include "gpio.h"
#include "SwICU.h"
#include "interrupt.h"
#include "timers.h"
#include "led.h"
#include "BITMATH.h"
#include "softwareDelay.h"

volatile static uint8_t u8_gsense=0xFF;
extern En_timer0perscaler_t en_gprescal0;


void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge)
{
	//timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_1024,0,0,SYNC,T2_POLLING);
	timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_1024,0,0,T0_POLLING);
	switch(a_en_inputCaptureEdge)
	{
		case SwICU_EdgeFalling:
		EXTI_Init(INT2,INT2_FALLING_EDGE);
		u8_gsense = INT2_FALLING_EDGE;
		break;
		
		case SwICU_EdgeRisiging:
		EXTI_Init(INT2,INT2_RISING_EDGE);
		u8_gsense = INT2_RISING_EDGE;
		break;
	}
}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge)
{
	
	//CLR_BIT(GICR,5);
	
	switch(a_en_inputCaptureEdgeedge)
	{
		
		case SwICU_EdgeFalling:
		MCUCR &= !(INT2_RISING_EDGE);
		u8_gsense = INT2_FALLING_EDGE;
		break;
		
		case SwICU_EdgeRisiging:
		MCUCR |= INT2_RISING_EDGE;
		u8_gsense = INT2_RISING_EDGE;
		break;
	}
	//SET_BIT(GIFR,5);
	//SET_BIT(GICR,5);
	
}

void SwICU_Read(volatile uint8_t* a_pu8_capt)
{
	
	while (u8_gsense!=INT2_FALLING_EDGE);
	while (u8_gsense!=INT2_RISING_EDGE);
	*a_pu8_capt = TCNT0;
	TCNT0=0;
	EXTI_Init(INT2,INT2_RISING_EDGE);
}

void SwICU_Stop(void)
{
	timer0Stop();
}

void SwICU_Start(void)
{
	EXTI_Init(INT2,u8_gsense);
	timer0Start();
}


