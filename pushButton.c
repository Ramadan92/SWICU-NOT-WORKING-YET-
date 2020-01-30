/*
* pushButton.c
*
* Created: 17/01/2020 05:27:05 pm
*  Author: ahmed
*/
#include "pushButton.h"
#include "pushButtonConfig.h"
#include "timers.h"
void pushButtonInit(En_buttonId_t en_butotn_id)
{
	
	switch(en_butotn_id)
	{
		case BTN_0:
		gpioPinDirection(BTN_0_GPIO,BTN_0_BIT,INPUT);
		break;

		case BTN_1:
		gpioPinDirection(BTN_1_GPIO,BTN_1_BIT,INPUT);
		break;

		case BTN_2:
		gpioPinDirection(BTN_2_GPIO,BTN_2_BIT,INPUT);
		break;

		case BTN_3:
		gpioPinDirection(BTN_3_GPIO,BTN_3_BIT,INPUT);
		break;
	}

}

En_buttonStatus_t pushButtonGetStatus(En_buttonId_t en_butotn_id)
{
	En_buttonStatus_t En_buttonStatus_Response;
	uint8_t u8_gpioPinRead_Return=0;
	switch(en_butotn_id)
	{
		case BTN_0:
		timer0Stop();
		timer0Set(0);
		timer0DelayMs(50);
		u8_gpioPinRead_Return = gpioPinRead(BTN_0_GPIO,BTN_0_BIT);
		break;
		
		case BTN_1:
		timer0Stop();
		timer0Set(0);
		timer0DelayMs(50);
		u8_gpioPinRead_Return = gpioPinRead(BTN_1_GPIO,BTN_1_BIT);
		break;
		
		case BTN_2:
		timer0Stop();
		timer0Set(0);
		timer0DelayMs(50);
		u8_gpioPinRead_Return = gpioPinRead(BTN_2_GPIO,BTN_2_BIT);
		break;
		
		case BTN_3:
		timer0Stop();
		timer0Set(0);
		timer0DelayMs(50);
		u8_gpioPinRead_Return = gpioPinRead(BTN_3_GPIO,BTN_3_BIT);
		break;
	}
	if (u8_gpioPinRead_Return)
	{
		En_buttonStatus_Response = Released;
	}
	else
	{
		En_buttonStatus_Response = Pressed;
	}
	return En_buttonStatus_Response;
}