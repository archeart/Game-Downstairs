#include "gamelib.h"
#include "gamedef.h"

#define starty  59
#define startx  4
#define xleng  192
#define yleng  202

extern int sec, min, unit, cnt; 
extern bool alive;


int stepwidth = 40;
int stepheight = 5;

Man Curman, Oldman;
Step Curstep[MaxSteps], Oldstep[MaxSteps];
int stepfront, steprear, Oldfront, Oldrear;
int bspeed;


void clear_step(void){
	int i, j, k;
	int x, x1, y;
	for (i = Oldfront; i < Oldrear; i++){
		x = Oldstep[i].pos.x >> frac;
		y = Oldstep[i].pos.y >> frac;
		x1 = Curstep[i].pos.x >> frac;
		if (x == x1)
			continue;
		for (j = 0; j < 40; j++)
		for (k = 3; k < 5; k++){/*been modified*/
			if (x+k > 0) 
				draw_pixel_vm(x+startx+k, y+starty+j, black);
			}
		if (Oldstep[i].type == Thorny)
			for (j = 0; j < 40; j++)
				if (x-1 > 0) 
					draw_pixel_vm(x+startx-1, y+starty+j, black);
		}
}

void draw_step(void){
	int i, j, k;
	int x, y, x1, cl;

	for (i = stepfront; i < steprear; i++){
		x = Curstep[i].pos.x >> frac;
		y = Curstep[i].pos.y >> frac;
		x1 = Oldstep[i].pos.x >> frac;
		if (x == x1)
			continue;

		if (Curstep[i].type == Thorny)
			cl = yellow;
		else if (Curstep[i].type == Roll)
			cl = white;
		else if (Curstep[i].type == Spring)
			cl = lightgreen;
		else cl = grey;

		for (j = 0; j < 40; j++)
		for (k = 0; k < 2; k++)
			if (x+k > 0) draw_pixel_vm(x+startx+k, y+starty+j, cl);
			
		if (Curstep[i].type == Thorny){
			for (j = 1; j < 38; j+=3){
				if (x-2 > 0) draw_pixel_vm(x+startx-2, y+starty+j, yellow);
				if (x-1 > 0) draw_pixel_vm(x+startx-1, y+starty+j, yellow);
				}
			}
			
	}
}

void clear_man(void){
	int i, j, x, y;
	x = (Oldman.pos.x >> frac) - 10;
	y = (Oldman.pos.y >> frac) - 5;
	for (i = 0; i < 10; i++)
		for (j = 1; j < 9; j++){
			if (x+i > 0 && y+j < 140)
			draw_pixel_vm(x+i+startx, y+j+starty, black);
			}
}

void draw_man(void){
	int i, j;
	int x, y;
	if (alive){
		x = (Curman.pos.x >> frac) - 10;
		y = (Curman.pos.y >> frac) - 5;
		for (i = 0; i < 10; i++)
			for (j = 1; j < 9; j++)
 				if (x+i <= 190 && x+i > 0)
				draw_pixel_vm(x+startx+i, y+starty+j, android[i][j]);
		}

	cputint(Curman.blood, 14, 30, white);
	if (alive)
		cputs("alive", 16, 27, white);
	else {
		cputs("dead.", 16, 27, white);
		cputc('0', 14, 30, white);
		}
}


void draw_frame(void){
	int wally = 200;
	Color Framecolor = blue;

	int i, j;

	for (i = startx; i < startx + xleng; i++)
		draw_pixel(i, starty, Framecolor);
	for (i = startx; i < startx + xleng; i++)
		draw_pixel(i, starty + yleng, Framecolor);
	for (i = starty; i < starty + yleng; i++)
		draw_pixel(startx, i, Framecolor);
	for (i = starty; i < starty + yleng; i++)
		draw_pixel(startx + xleng, i, Framecolor);
	for (i = startx; i < startx + xleng; i++)
		draw_pixel(i, wally, Framecolor);
		}

void draw_liter(void){
	cputs("level", 6, 27, white);
	cputs("0", 7, 30, white);

	cputs("time", 9, 27, white);
	cputs("00:00", 10, 27, white);

	cputs("blood", 13, 27, white);
}

void init_game(){
	int pos1 = 70, pos2 = 110, pos3 = 150;
	int mapox = 60, mapoy = 70;/*lowest mid position;*/
	Oldfront = 0;
	Oldrear = 3;
	stepfront = 0;
	steprear = 3;

	unit = 0; sec = 0; min = 0; cnt = 0;
/*	if (Curstep[0].pos.x != 128)
		prints("......");
		*/
	

	bspeed = (30  << frac) / Freq;

	Curstep[0].pos.x = pos1 << frac;
	Curstep[0].pos.y = 50 << frac;
	Curstep[0].speed = (30 << frac) / Freq;
	Curstep[0].type = 1;

	if (Curstep[0].speed != bspeed)
		prints("-o-");

	Curstep[1].pos.x = pos2 << frac; 
	Curstep[1].pos.y = 25 << frac;
	Curstep[1].speed = Curstep[0].speed;
	Curstep[1].type = 1;

	Curstep[2].pos.x = pos3 << frac; 
	Curstep[2].pos.y = 75 << frac;
	Curstep[2].speed = Curstep[0].speed;
	Curstep[2].type = 2;

	Oldman.pos.x = 170 << frac; Oldman.pos.y = 130 << frac;
	Curman.pos.x = Curstep[0].pos.x; Curman.pos.y = mapoy << frac;
	Curman.vel.x = Curstep[0].speed; 
	Curman.vel.y = 0;
	Curman.state = Stand; Curman.stone = stepfront;
	Curman.blood = 9;
	/*
	if (Curman.vel.x == 0)
		prints("wrong");
		*/

	draw_step();
	draw_frame();
	draw_liter();
	draw_man();

}
