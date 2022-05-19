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
unsigned int high_score = 35; // tail size (food eaten)


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

void draw_menu() {
	int numpixels = menu_geometry.numpoints;
	for(int i = 0; i < numpixels; i++)
	{
		unsigned char x = menu_geometry.px[i].x;
		unsigned char y = menu_geometry.px[i].y;
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

void drawclear_object(POBJECT obj) {
	// clears place of object and then draws it
	clear_object(obj);
	draw_object(obj);
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
	snakeO-> posx += snakeO-> dirx;
	snakeO-> posy += snakeO-> diry;
}

//apple methods
void move_apple(POBJECT appleO)
{
	appleO -> posx = random_number(1, SCREEN_WIDTH);
	appleO -> posy = random_number(1, SCREEN_HEIGHT);
}
//OBJECTS-----------------------------

//DEFINED OBJ.------------------------
//SNAKE HEAD

static OBJECT snake =
{
	&snake_geometry, //geometri
	-1,0,		//init riktnings cord
	6*SCREEN_WIDTH/8, SCREEN_HEIGHT/2,		//start pos.
	draw_object,
	clear_object,
	move_snake,
	set_object_speed
};
//SNAKE HEAD
//APPLE

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


OBJECT create_tail (int x, int y) {
	OBJECT obj = {
		&tail_geometry, //geometri
		0,0,		//init riktnings cord
		x, y,		//start pos.
		draw_object,
		clear_object,
		move_snake,
		set_object_speed
	};
	return obj;
}

void draw_objarr(OBJECT obj[], int amount) {
	// draws amount members of pobject array
	for (int i = 0; i < amount; i++) {
		draw_object(&obj[i]);
	}
}

//SNAKE TAIL
//DEFINED OBJ.------------------------

//collision detection-------------------------------

char object_collides(POBJECT o1, POBJECT o2)
{	
	// objects collides
	return (o1 -> posx == o2 -> posx && o1->posy == o2->posy);
}
//FUNC.-------------------------------
char game_over(POBJECT snake_head, OBJECT snake_tail[], int points)
{
	// out of bounds detection
	if (snake_head->posx < 0 ||
		snake_head->posx > SCREEN_WIDTH ||
		snake_head->posy < 0 ||
		snake_head->posy > SCREEN_HEIGHT) {
		return 1;
	}
	// tail detection
	for (int i=0; i<points; i++) {
		if (snake_tail[i].posx == snake_head->posx &&
			snake_tail[i].posy == snake_head->posy) {
			return 1;
		}
	}
	return 0;
}

//MAIN------------------------------
void main_menu() {
	// convert high score to char[]
	draw_menu();
	char row1[] = "High score:              ";
	char high_score_char[12];
	itoa(high_score, high_score_char, 10);
	int j = 0;
	// adds score to row1
	for (int i =12; i<20; i++) {
		row1[i] = high_score_char[j];
		j++;
	}
	// create output text
	write_ascii(row1, "Press any key:");
	while (keyb() == 0xFF);
	graphic_clear_screen();
}

void main(void)
{
	while (1) {
	//game init
	init_app();
	graphic_initalize();
	graphic_clear_screen();
	points = 0;

	//object declarations
	main_menu();
	POBJECT appleO = &apple;
	POBJECT snake_head = &snake;
	OBJECT snake_tail[16*32];	
	appleO -> draw(appleO);
	
	// game loop
	while (!game_over(snake_head, snake_tail, points)) 
	{
		// if snake eats apple
		if(object_collides(snake_head, appleO))
		{
			// move apple to random location
			move_apple(appleO);
			draw_object(appleO);
			// add new body part (s)
			for (int i = 0; i < TAIL_INCREMENT; i++) {
				snake_tail[points] = create_tail(snake_head->posx,snake_head->posy);
				// tally new size of snake by increasing points
				points++;
			}
			// write score
			char row1[] = "Score:                       ";
			char high_score_char[12];
			itoa(points, high_score_char, 10);
			int j = 0;
			// adds score to row1
			for (int i =12; i<20; i++) {
				row1[i] = high_score_char[j];
				j++;
			}
			// create output text
			write_ascii(row1, "");
		} else if (points>0) {
			// clear last piece of tail
			clear_object(&snake_tail[0]);
			// move closest tail piece to previous snake_head position
			snake_tail[points-1].posx = snake_head->posx;
			snake_tail[points-1].posy = snake_head->posy;
			// else move entire tail forward
			for (int i=0; i<points-1; i++) {
				//move_o1_o2(snake_tail[i], snake_tail[i+1]);
				snake_tail[i].posx = snake_tail[i+1].posx;
				snake_tail[i].posy = snake_tail[i+1].posy;
			}
			//draw new tail piece
			drawclear_object(&snake_tail[0]);
		}
		clear_object(snake_head);
		// move snake
		move_snake(snake_head);
		if (points>0) drawclear_object(&snake_tail[points-1]);
		drawclear_object(snake_head);
		// while systick(flag)
		for (int i=0; i<DELAY_TIME;i++) {
			//keypad input
			switch (keyb()) {
			// right
			case 6: if (snake_head->dirx!=-1) snake_head -> set_speed(snake_head, 1, 0); break;
			// left
			case 4: if (snake_head->dirx!=1) snake_head -> set_speed(snake_head, -1, 0); break;
			// up
			case 2: if (snake_head->diry!=1) snake_head -> set_speed(snake_head, 0, -1); break;
			// down
			case 8: if (snake_head->diry!=-1) snake_head -> set_speed(snake_head, 0, 1); break;
			
			// delay
			delay_milli(1);
			}
		}
	}
	// game over
	delay_milli(10);
	graphic_clear_screen();
	char* result;
	itoa(points, result, 10);
	if (points>high_score) {
		 high_score = points;
		write_ascii("New record! Score:", result);
	} else {
		write_ascii("Game over! Score:", result);
	}
	delay_milli(50);
	}
}
