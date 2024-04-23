/*
 * AP_Main.c
 *
 *  Created on: Apr 23, 2024
 *      Author: k1min
 */

#include "AP_Main.h"

Button_t Button_1, Button_2, Button_3;
LED_t LED_1, LED_2, LED_3;

uint8_t modeState;
//extern uint32_t timeTick;

uint32_t timeTick;

void SystickCallback()
{
	if(timeTick != 0)
		timeTick--;
}

void sys_init()
{
	button_init(&Button_1, GPIOC, GPIO_PIN_10);
	button_init(&Button_2, GPIOC, GPIO_PIN_11);
	button_init(&Button_3, GPIOC, GPIO_PIN_12);

	LED_init(&LED_1, GPIOC, GPIO_PIN_8);
	LED_init(&LED_2, GPIOC, GPIO_PIN_6);
	LED_init(&LED_3, GPIOC, GPIO_PIN_5);

	modeState = defaultLED;
}

void modeStateCheck()
{
	if (button_getState(&Button_1) == ACT_PUSHED)
	{
		modeState = LED1_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
	if (button_getState(&Button_2) == ACT_PUSHED)
	{
		modeState = LED2_3_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
	if (button_getState(&Button_3) == ACT_PUSHED)
	{
		modeState = LED1_3_ON;
		LED_OFF(&LED_1);
		LED_OFF(&LED_2);
		LED_OFF(&LED_3);
	}
}
void modeStateRun()
{
	switch (modeState)
	{
		case LED1_ON:
			if (timeTick != 0)
				return;
			LED_toggle(&LED_1);
			LED_OFF(&LED_2);
			LED_OFF(&LED_3);
			timeTick = 200;
			break;

		case LED2_3_ON:
			if (timeTick != 0)
				return;
			LED_toggle(&LED_2);
			LED_toggle(&LED_3);
			LED_OFF(&LED_1);
			timeTick = 100;
			break;

		case LED1_3_ON:
			if (timeTick != 0)
				return;
			LED_toggle(&LED_1);
			LED_toggle(&LED_3);
			LED_OFF(&LED_2);
			timeTick = 1000;
			break;

		case defaultLED:
			if (timeTick != 0)
				return;
			LED_toggle(&LED_1);
			LED_toggle(&LED_2);
			LED_toggle(&LED_3);
			timeTick = 500;
			break;
	}
}

int APMain()
{
	sys_init();

	while (1)
	{
		modeStateCheck();
		modeStateRun();
	}
}
