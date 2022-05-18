#include "declarations.h"

#define B_E      0x40
#define B_SELECT 4
#define B_RW     2
#define B_RS     1

//ASCII------------------------------
void ascii_ctrl_bit_set ( char x )
{
	char c;
	c = GPIO_E.odrLow;
	GPIO_E.odrLow = B_SELECT | x | c;
}

void ascii_ctrl_bit_clear ( char x )
{
	char c;
	c = GPIO_E.odrLow;
	c = c & ~x;
	GPIO_E.odrLow = B_SELECT | c;
}
//time sensitive functions
void ascii_write_controller ( unsigned char c )
{
	//delay 40ns (small delay, no need)
	ascii_ctrl_bit_set(B_E);
	GPIO_E.odrHigh = c;
	delay_250ns();
	ascii_ctrl_bit_clear(B_E);
	//delay 10ns
}

char ascii_read_controller ( void )
{
	char c;
	ascii_ctrl_bit_set(B_E);
	delay_250ns;
	delay_250ns;
	c=GPIO_E.idrHigh;
	ascii_ctrl_bit_clear(B_E);
	return c;
}
//other
void ascii_write_cmd( unsigned char c ) 
{
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(c);
}

void ascii_write_data( unsigned char c ) 
{
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(c);
}

unsigned char ascii_read_status ( void )
{
	char c;
	GPIO_E.moder = 0x00005555;
	ascii_ctrl_bit_set(B_RW);
	ascii_ctrl_bit_clear(B_RS);
	c = ascii_read_controller();
	
	GPIO_E.moder = 0x55555555;
	return c;
}

unsigned char ascii_read_data ( void )
{
	GPIO_E.moder &= 0x0000FFFF;
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_set(B_RW);
	char c = ascii_read_controller();
	GPIO_E.moder |= 0x55550000;
	return c;
}

void ascii_command( unsigned char command )
{
	while( (ascii_read_status() & 0x80) == 0x80 ){}
	delay_micro(8);
	ascii_write_cmd(command);
}

void ascii_init (void) {
	// function set (2 rows and font size)
	ascii_command(0x38);
	delay_micro(39);
	// turn on display & cursor constant
	ascii_command(0xE);
	delay_micro(39);
	// clear screen
	ascii_command(1);
	delay_milli(2);
	//adressing with inc.
	ascii_command(6);
	delay_micro(39);
}

void ascii_write_char(char c)
{
	while( (ascii_read_status() & 0x80) == 0x80 ){}
	delay_micro(8);
	ascii_write_data(c);
	delay_micro(43);
}

void ascii_gotxy(unsigned char row, unsigned char column)
{
	char adr = row-1;
	if(column == 2) adr = adr + 0x40;
	ascii_write_cmd ( 0x80 | adr );
}
/*
 * main function
 */
int write_ascii(char line1[], char line2[])
{
	char *s;
	ascii_init();
	ascii_gotxy(1,1);
	s = line1;
	while( *s ) {
		ascii_write_char(*s++);
	}
	ascii_gotxy(1,2);
	s = line2;
	while( *s ) {
		ascii_write_char(*s++);
	}
	return 0;
}
