#ifndef _DECLARATIONS_H
#define _DECLARATIONS_H

/*
 * Macros
 */
#define SIMULATOR
#define MAX_SNAKE_PIXELS 512*12
#define TAIL_INCREMENT 10
#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 16
#define SQUARE_WIDTH 4 // height becomes 16, width is 32
//sys_tick
#define STK_CTRL ((volatile unsigned int *)(0xE000E010))
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))
#define STK_VAL ((volatile unsigned int *)(0xE000E018))
//gpio
#define GPIO_D (*((volatile PGPIO) 0x40020c00)) // keypad
#define GPIO_E (*((volatile PGPIO) 0x40021000))
// Timer 6
#define TIM6_CR1	((volatile unsigned short *) 0x40001000)
#define TIM6_CNT	((volatile unsigned short *) 0x40001024)
#define TIM6_ARR	((volatile unsigned short *) 0x4000102C)
#define	UDIS	(1<<1)
#define CEN		(1<<0)


/*
 * User defined types
 */
 //gpio
typedef volatile struct {	
unsigned int moder;
unsigned short int otyper;
unsigned short int Reserved0;
unsigned int ospeedr;
unsigned int pupdr;
unsigned char idrLow;
unsigned char idrHigh;
unsigned short int Reserved1;
unsigned char odrLow;
unsigned char odrHigh;
unsigned short int Reserved2;
unsigned int bsrr;
unsigned short int lckr;
unsigned short int Reserved3;
unsigned int afrl;
unsigned int afrh;
} GPIO, *PGPIO;

//objects
typedef struct
{
	unsigned char x, y;
}	POINT;



typedef struct
{
	int numpoints;
	int sizex;
	int sizey;
	POINT px[ MAX_SNAKE_PIXELS ];
}	GEOMETRY, *PGEOMETRY;

typedef struct tObj
{
	PGEOMETRY geo;
	int dirx, diry;
	int posx, posy;
	void (* draw) (struct tObj *);
	void (* clear) (struct tObj *);
	void (* move) (struct tObj *);
	void (* set_speed) (struct tObj *, int, int);
}	OBJECT, *POBJECT;

/*
 * Function Prototypes
 */
 
 //delay
 void delay_250ns();
 void delay_micro(unsigned int us);
 void delay_milli(unsigned int ms);
 //randomizer
 int random_number(int min, int max);
 //keyboard
 unsigned char keyb();
 //ascii
 int write_ascii(char line1[], char line2[]);

#endif