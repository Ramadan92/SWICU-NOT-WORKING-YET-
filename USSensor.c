/*
 * USSensor.c
 *
 * Created: 1/30/2020 12:21:22 AM
 *  Author: ahmed
 */ 

#include "USSensor.h"
#include "timers.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "SwICU.h"
uint8_t USSensor_getDistance(uint8_t u8_ticks)
{
	
	uint32_t u32_pulseTime = (1024/16) * u8_ticks;
	
	fint16_t f16_distance = u32_pulseTime/58;
	
	uint8_t u8_distance = f16_distance + 0.5;
	return u8_distance  ;
}

void USSensor_Trigger(void)
{
	gpioPinWrite(GPIOB,BIT1,HIGH);
	softwareDelayMs(1);
	gpioPinWrite(GPIOB,BIT1,LOW);
}

void USSensor_init(void)
{
	gpioPinDirection(USSTrig_GPIO,USSTrig_BIT,INPUT);
	SwICU_Init(SwICU_EdgeRisiging);
}