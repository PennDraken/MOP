#define MOVE_SPEED 1

//SYS_TICK
#define STK_CTRL ((volatile unsigned int *)(0xE000E010))
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))
#define STK_VAL ((volatile unsigned int *)(0xE000E018))

//GPIO
#define GPIO_D (*((volatile PGPIO) 0x40020c00)) // keypad
#define GPIO_E (*((volatile PGPIO) 0x40021000))
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
//DEF. ----------------------------------------------------

//GLOBAL VARIABLES--------------------------------------
int SCREEN_WIDTH = 128;
int SCREEN_HEIGHT = 64;
int SQUARE_WIDTH = 4; // height becomes 16, width is 32


//STARTUP--------------------------------------------------
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}
//STARTUP--------------------------------------------------

//GRPAPHICS DRIVERS----------------------------
//OBS! graphic_init. sets up port E for usage
__attribute__((naked))
void graphic_initalize(void)
{
	__asm volatile(" .HWORD 0xDFF0\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_set(int x, int y)
{
	__asm volatile(" .HWORD 0xDFF2\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void)
{
	__asm volatile(" .HWORD 0xDFF1\n");
	__asm volatile(" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y)
{
	__asm volatile(" .HWORD 0xDFF3\n");
	__asm volatile(" BX LR\n");
}
//GRAPHICS DRIVERS----------------------------

//INIT----------------------------------------
void init_app(void) {
	// starta klockorna
	*((unsigned long *) 0x40023830) = 0x18;
	//keypad
	GPIO_D.moder = 0x55000000;
	GPIO_D.otyper = 0;
	GPIO_D.pupdr = 0xAA0000;
	GPIO_D.ospeedr = 0xFF000000;
}
//INIT----------------------------------------

//DELAY------------------------------
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
	us = us / 1000;
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
//DELAY----------------------------

//FUNC. keyb------------------------
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
//helpfunc
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
//FUNC. keyb------------------------

//Custom TYPE DECL.-----------------------------
typedef struct
{
	unsigned char x, y;
}	POINT;

#define MAX_POINTS 30

typedef struct
{
	int numpoints;
	int sizex;
	int sizey;
	POINT px[ MAX_POINTS ];
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
//Custom TYPE DECL.-----------------------------

//HELPER FUNCTIONS---------------------------
int random(int min, int max) {
	// gives a random number between min and max
	
	return 2;
}



//HELPER FUNCTIONS---------------------------



//OBJECT-----------------------------
//general methods
void draw_object(POBJECT obj)
{
	int numpixels = obj -> geo -> numpoints;
	for(int i = 0; i < numpixels; i++)
	{
		unsigned char x = obj -> geo -> px[i].x + (obj -> posx) * SQUARE_WIDTH;
		unsigned char y = obj -> geo -> px[i].y + (obj -> posy) * SQUARE_WIDTH;
		graphic_pixel_set(x, y);
	}
}

void clear_object(POBJECT obj)
{
	int numpixels = obj -> geo -> numpoints;
	for(int i = 0; i < numpixels; i++)
	{ 
		unsigned char x = obj -> geo -> px[i].x + (obj -> posx) * SQUARE_WIDTH;
		unsigned char y = obj -> geo -> px[i].y + (obj -> posy) * SQUARE_WIDTH;
		graphic_pixel_clear(x, y);
	}
}

void set_object_speed(POBJECT obj, int x, int y)
{
	obj -> dirx = x;
	obj -> diry = y;
}

//snake methods
void move_snakeobject(POBJECT obj)
{
	clear_object(obj);
	int numpixels = obj -> geo -> numpoints;
	//deside new pos. by adding dir coordinates to list of points
	obj -> posx += obj -> dirx;
	obj -> posy += obj -> diry;
	
	draw_object(obj);
}

//apple methods
void move_appleobject(POBJECT obj)
{
	// moves apple object to a random position
	clear_object(obj);
	int numpixels = obj -> geo -> numpoints;
	obj -> posx = random(0, SCREEN_WIDTH / SQUARE_WIDTH);
	obj -> posy = random(0, SCREEN_WIDTH / SQUARE_WIDTH);

	
	draw_object(obj);
}
//OBJECTS-----------------------------

//DEFINED OBJ.------------------------
GEOMETRY snake_geometry =
{
	12, // total pixels
	4,4, // width & height	
	{
		{0,0},{1,0},{2,0},{3,0},
		{0,1},{3,1},
		{0,2},{3,2},
		{0,3},{1,3},{2,3},{3,3},

}
};

static OBJECT snake =
{
	&snake_geometry, //geometri
	0,0,		//init riktnings cord
	5, 2,		//start pos.
	draw_object,
	clear_object,
	move_snakeobject,
	set_object_speed
};

GEOMETRY apple_geometry = 
{
	12,
	7,1,
	{
		{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},
		{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
	}
};

static OBJECT apple =
{
	&apple_geometry, //geometri
	4,1,		//init riktnings cord
	1,3,		//start pos.
	draw_object,
	clear_object,
	move_appleobject,
	set_object_speed
};
//DEFINED OBJ.------------------------

//FUNC.-------------------------------
int pixel_overlap(POBJECT o1, POBJECT o2) {
  int offset1x = o1->posx;
  int offset1y = o1->posy;
  int offset2x = o2->posx;
  int offset2y = o2->posy;
  for (int i = 0; i < o1->geo->numpoints; i++) {
    for (int j = 0; j < o2-> geo->numpoints; j++)
      if ((offset1x + o1->geo->px[i].x == offset2x + o2->geo->px[j].x) &&
        (offset1y + o1->geo->px[i].y == offset2y + o2->geo->px[j].y)) return 1;
  }
  return 0;
}

char object_collides(POBJECT o1, POBJECT o2)
{	
	// objects collides
	if (o1 -> posx == o2 -> posx && o1->posy == o2->posy) {
		return 1;
	}
	
	// creature outside bounds (very specific)
	if  (o2 -> posx < 1 ||    
		128 < o2 -> posx + o2 -> geo -> sizex ||
		o2 -> posy < 1 ||    
		64 < o2 -> posy + o2 -> geo -> sizey)
			return 1;
	return 0;
}
//FUNC.--------------------------------

//MAIN------------------------------
void main(void)
{
	char c;
	POBJECT appleobj = &apple;
	POBJECT snakeobj = &snake;
	POBJECT[] snarr = &snake[];
	
	init_app();
	graphic_initalize();
	graphic_clear_screen();
	appleobj -> move(appleobj); // puts apple at random location
	
	while (1) {
		snakeobj -> move(snakeobj);
		appleobj -> draw(appleobj);
		c = keyb();
		
		switch (c) { // movement
			// right
			case 6: snakeobj  -> set_speed(snakeobj, MOVE_SPEED, 0); break;
			// left
			case 4: snakeobj  -> set_speed(snakeobj, -MOVE_SPEED, 0); break;
			// up
			case 2: snakeobj  -> set_speed(snakeobj, 0, -MOVE_SPEED); break;
			// down
			case 8: snakeobj  -> set_speed(snakeobj, 0, MOVE_SPEED); break;
		}
		
		if (object_collides(appleobj, snakeobj)) {
			appleobj -> posx = appleobj -> posx + 3;
			
			// appleobj -> move(appleobj); // puts apple at random location
		}
		delay_milli(1);
	}
	delay_milli(1000);
	graphic_clear_screen();
}
