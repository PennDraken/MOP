#include "declarations.h"
/*
 * SYS_TICK
 */
void delay_250ns( void )
{
/* SystemCoreClock = 168000000 */
	*STK_CTRL = 0;
	*STK_LOAD = ( (168/4) -1 );
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while( (*STK_CTRL & 0x10000 )== 0 );
	*STK_CTRL = 0;
}

void delay_micro(unsigned int us)
{
#ifdef SIMULATOR
	us = us/1000;
	us++;
#endif
	while( us > 0 )
	{
		for(int i = 0; i<4; i++) delay_250ns();
		us--;
	}
}

void delay_milli(unsigned int ms) {
	while( ms > 0 )
	{
		delay_micro(100);
		ms--;
	}
}

/*
 * TIM6 for randomizing number
 */
 int random_number(int min, int max)
 {
	short random = (char) *TIM6_CNT;
	unsigned char c = random % (max-min+1) + min; 
	return c;
 }
