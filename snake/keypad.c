#include "declarations.h"

/*
 * Helper Functions
 */
void activateRow(unsigned int row)
{
	switch(row){
		case 1: GPIO_D.odrHigh=0x10; break;
		case 2: GPIO_D.odrHigh=0x20; break;
		case 3: GPIO_D.odrHigh=0x40; break;
		case 4: GPIO_D.odrHigh=0x80; break;
		
		default: GPIO_D.odrHigh=0;
	}
}

int readCol(void)
{
	unsigned char c;
	c = GPIO_D.idrHigh;
	if(c & 8) return 4;
	if(c & 4) return 3;
	if(c & 2) return 2;
	if(c & 1) return 1;
	return 0;
}

/*
 * Main Function
 */
unsigned char keyb(void)
{
	unsigned char key[]=
	{1,2,3,0xA,4,5,6,0xB,7,8,9,0xC,0xE,0,0xF,0xD};
	int row, col;
	for(row = 1; row <= 4; row++){
		activateRow(row);
		if(col=readCol()){
			activateRow(0);
			return key[4*(row-1)+(col-1)];
		}
	}
	activateRow(0);
	return(0xFF);
}