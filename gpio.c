/*
* gpio.c
*
* Created: 17/01/2020 01:12:53 م
*  Author: mo
*/
#include "gpio.h"
#include "std_types.h"
#include "registers.h"
void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	/**
	* Description: set the port value (which is PORT register)
	* @param port: portID and takes the following values
	* 				- 0 -> GPIOA
	* 				- 1 -> GPIOB
	* 				- 2 -> GPIOC
	* 				- 3 -> GPIOD
	* @param value: set the port value and takes the following values
	* 				- 0x00 -> Low
	* 				- 0xff -> High
	*/

	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DIR = u8_direction;
		break;
		
		case GPIOB:
		PORTB_DIR = u8_direction;
		break;
		
		case GPIOC:
		PORTC_DIR = u8_direction;
		break;
		
		case GPIOD:
		PORTD_DIR = u8_direction;
		break;
	}
	/*
	switch case will determine which port to be used
	PS:No Default Needed
	*/

}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
	
	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DATA = u8_value;
		break;
		
		case GPIOB:
		PORTB_DATA = u8_value;
		break;
		
		case GPIOC:
		PORTC_DATA = u8_value;
		break;
		
		case GPIOD:
		PORTD_DATA = u8_value;
		break;
	}
	
	
	
}
void gpioPortToggle(uint8_t u8_port)
{
	
	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DATA ^= HIGH;
		break;
		
		case GPIOB:
		PORTB_DATA ^= HIGH;
		break;
		
		case GPIOC:
		PORTC_DATA ^= HIGH;
		break;
		case GPIOD:
		PORTD_DATA ^= HIGH;
		break;
		
	}
	
	
	
}

uint8_t gpioPortRead(uint8_t u8_port)
{
	uint8_t u8_portValue=0;
	
	switch (u8_port)
	{	
		case GPIOA:
		u8_portValue=PORTA_PIN ;
		break;
		
		case GPIOB:
		u8_portValue=PORTB_PIN ;
		break;
		
		case GPIOC:
		u8_portValue=PORTC_PIN ;
		break;
		
		case GPIOD:
		u8_portValue=PORTD_PIN ;
		break;
		
	}

	return 	u8_portValue;
}


/**
* Description: set selected pins (more than one pin [ORed]) direction
*
* @param port: portID and takes the following values
* 				- 0 -> GPIOA
* 				- 1 -> GPIOB
* 				- 2 -> GPIOC
* 				- 3 -> GPIOD
* @param pins: the selected pins the user need to set its direction and takes
* 				any member from the enum EN_bits:
* 				- BIT0
* 				- BIT1
* 				- BIT2
* 				- BIT3
* 				- BIT4
* 				- BIT5
* 				- BIT6
* 				- BIT7
*
* @param direction: set the pins direction and takes the following values
* 				- 0x00 -> Input
* 				- 0xff -> Output
*/
void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
	switch(u8_port)
	{
		case GPIOA:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTA_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTA_DIR |=(u8_pins);
			}
		}
		break;
		
		case GPIOB:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTB_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTB_DIR |=(u8_pins);
			}
		}
		break;
		
		case GPIOC:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTC_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTC_DIR |=(u8_pins);
			}
		}
		break;
		
		case GPIOD:
		{
			switch (u8_direction)
			{
				case INPUT:
				PORTD_DIR &=(~u8_pins);
				break;
				
				case OUTPUT:
				PORTD_DIR |=(u8_pins);
			}
		}
		break;
	}
}

void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	switch(u8_value){
		case LOW:
		{
			switch (u8_port)
			{	
				case GPIOA:
				PORTA_DATA &= ~(u8_pins);   
				break;
				
				case GPIOB:
				PORTB_DATA &= ~(u8_pins);
				break;
				
				case GPIOC:
				PORTC_DATA &= ~(u8_pins);
				break;
				
				case GPIOD:
				PORTD_DATA &= ~(u8_pins);
				break;
				
			}
			break;
		}
		case HIGH:{
			switch (u8_port)
			{	
				case GPIOA:
				PORTA_DATA |=(u8_pins);
				break;
				
				case GPIOB:
				PORTB_DATA |=(u8_pins);
				break;
				
				case GPIOC:
				PORTC_DATA |=(u8_pins);
				break;
				
				case GPIOD:
				PORTD_DATA |=(u8_pins);
				break;
				
			}
			break;
		}

		
	}

}
void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
	switch (u8_port)
	{	
		case GPIOA:
		PORTA_DATA ^=(u8_pins);
		break;
		
		case GPIOB:
		PORTB_DATA ^=(u8_pins);
		break;
		
		case GPIOC:
		PORTC_DATA ^=(u8_pins);
		break;
		
		case GPIOD:
		PORTD_DATA ^=(u8_pins);
		break;
		
	}
	
	
	
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
	uint8_t u8_pinValue = 0;
	switch (u8_port)
	{	
		case GPIOA:
		u8_pinValue=PORTA_PIN & u8_pin;
		break;
		case GPIOB:
		u8_pinValue=PORTB_PIN & u8_pin;
		break;
		case GPIOC:
		u8_pinValue=PORTC_PIN & u8_pin;
		break;
		case GPIOD:
		u8_pinValue=PORTD_PIN & u8_pin;
		break;
	}
	if(u8_pinValue)
	{
		u8_pinValue = 1;
	}
	return u8_pinValue;
}