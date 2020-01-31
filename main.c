/*
 * SWICU_Challenge.c
 *
 * Created: 1/29/2020 5:50:35 PM
 * Author : ahmed
 */ 

#include "std_types.h"
#include "gpio.h"
#include "registers.h"
#include "timers.h"
#include "interrupt.h"
#include "led.h"
#include "SwICU.h"
#include "USSensor.h"
#include "BITMATH.h"
#include "softwareDelay.h"

int main(void)
{
	
	uint8_t u8_Ticks;               /*unsigned 8 bit variable to store the number of ticks of TCNT0 in it*/ 
	volatile uint8_t u8_distance=0; /*unsigned 8 bit variable to store the distance measured by the ultra sonic sensor*/
	
	/****************************************/
	/*                                      */
	/*		     LEDs initialization        */
	/*								        */
	/****************************************/
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	
	/*enabling global interrupt*/
	ENABLE_GINT;
	
	/*initializing the ultrasonic sensor*/
	USSensor_init();
	
	while (1)
	{
		/*sending the trigger signal*/
		USSensor_Trigger();
		
		/*reading the value in the TCNT0*/
		SwICU_Read(&u8_Ticks);
		
		/*calculating the distance according to the value of TCNT0*/
		u8_distance = USSensor_getDistance(u8_Ticks);
		
		/*mapping the distance on the 4 LEDs*/
		PORTB_DATA &= 0x0F;
		PORTB_DATA |= (u8_distance<<4);
	}
    return 0;
}

