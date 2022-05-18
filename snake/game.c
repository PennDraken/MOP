#include "declarations.h"

/*
 * STARTUP
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}

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
//VARIABLES-----------------------------------
unsigned int points = 0; // tail size (food eaten)


//VARIABLES-----------------------------------

//GRAPHICS DRIVERS----------------------------
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
void move_snake(POBJECT snakeO)
{
	//deside new pos. by adding dir coordinates to list of points
	clear_object(snakeO);
	snakeO-> posx += snakeO-> dirx;
	snakeO-> posy += snakeO-> diry;
	draw_object(snakeO);
	delay_milli(100);
}

//apple methods
void move_apple(POBJECT appleO)
{
	clear_object(appleO);
	appleO -> posx = random_number(1, SCREEN_WIDTH);
	appleO -> posy = random_number(1, SCREEN_HEIGHT);
	draw_object(appleO);
}
//OBJECTS-----------------------------

//DEFINED OBJ.------------------------
//SNAKE HEAD
GEOMETRY snake_geometry =
{
	12, // total pixels
	1,1, // width & height	
	{

		{0,0},{1,0},{2,0},{3,0},
		{0,1},{1,1},{2,1},{3,1},
		{0,2},{1,2},{2,2},{3,2},
		{0,3},{1,3},{2,3},{3,3},

}
};

static OBJECT snake =
{
	&snake_geometry, //geometri
	-MOVE_SPEED,0,		//init riktnings cord
	6*SCREEN_WIDTH/8, SCREEN_HEIGHT/2,		//start pos.
	draw_object,
	clear_object,
	move_snake,
	set_object_speed
};
//SNAKE HEAD
//APPLE
GEOMETRY apple_geometry = 
{
	12,
	1,1,
	{
		{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},
		{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
	}
};

static OBJECT apple =
{
	&apple_geometry, //geometri
	0,0,		//init riktnings cord
	SCREEN_WIDTH/4, SCREEN_HEIGHT/2,		//start pos.
	draw_object,
	clear_object,
	move_apple,
	set_object_speed
};
//APPLE
//SNAKE TAIL
GEOMETRY tail_geometry =
{
	16, // total pixels
	1,1, // width & height	
	{
		{0,0},{1,0},{2,0},{3,0},
		{0,1},{3,1},
		{0,2},{3,2},
		{0,3},{1,3},{2,3},{3,3},

	}
};

static POBJECT create_tail(POBJECT obj, int x, int y) {
	//obj -> geo = &snake_geometry;
	obj -> posx = 2;
	obj -> posy = y;
	obj -> dirx = 0;
	obj -> diry = 0;
	obj -> draw = draw_object;
	obj -> clear = clear_object;
	obj -> move = move_snake;
	obj -> set_speed = set_object_speed;
	return obj;
}
//SNAKE TAIL
//DEFINED OBJ.------------------------

//collision detection-------------------------------
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
}
//FUNC.-------------------------------
char game_over(POBJECT snake)
{
	if
	(snake->posx < 0 ||
	 snake->posx > SCREEN_WIDTH ||
	 snake->posy < 0 ||
	 snake->posy > SCREEN_HEIGHT)
	{
		 return 1;
	}else return 0;
}

//MAIN------------------------------
void main(void)
{
	char c;
	POBJECT appleO = &apple;
	POBJECT snake_head = &snake;
	// POBJECT snake_tail = snake_body;
	POBJECT tail[3];
	tail[0] = create_tail(tail[0], 2, 2);
	draw_object(tail[0]);
	
//DEFINED OBJ.------------------------
	
	init_app();
	graphic_initalize();
	graphic_clear_screen();
	
	appleO -> draw(appleO);
	while (!game_over(snake_head)) 
	{
		snake_head -> move(snake_head);
		c = keyb();
		switch (c) { // movement
			// right
			case 6: snake_head -> set_speed(snake_head, MOVE_SPEED, 0); break;
			// left
			case 4: snake_head -> set_speed(snake_head, -MOVE_SPEED, 0); break;
			// up
			case 2: snake_head -> set_speed(snake_head, 0, -MOVE_SPEED); break;
			// down
			case 8: snake_head -> set_speed(snake_head, 0, MOVE_SPEED); break;
		}
		
		if(object_collides(snake_head, appleO))
		{
			appleO -> move(appleO);
			points++;
		}
	}
	delay_milli(1000);
	graphic_clear_screen();
	write_ascii("Game over", "");
}
