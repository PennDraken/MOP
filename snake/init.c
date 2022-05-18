#include "declarations.h"

// starta klockorna
//	*((unsigned long *) 0x40023830) = 0x18;
 void init_keypad() 
 {
	GPIO_D.moder = 0x55000000;
	GPIO_D.otyper = 0;
	GPIO_D.pupdr = 0xAA0000;
	GPIO_D.ospeedr = 0xFF000000;
}

void init_ascii()
{
	GPIO_E.moder = 0x55555555;
	GPIO_E.pupdr = 0x55550000;
	GPIO_E.otyper = 0;
}

void init_timer6()
{
	*TIM6_CR1 &= ~CEN; //stoppa räknarmodul
	*TIM6_ARR = 0xFFFF; //sätt räknarreg. till maxvärde
	*TIM6_CR1 |= (CEN|UDIS); //inget update-event
	//starta räknarmodul
}

void init_app()
{
	init_keypad();
	init_ascii();
	init_timer6();
}