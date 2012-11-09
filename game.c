#include "gamelib.h"
#include "gamedec.h"

bool timer_fired = FALSE;

int unit, sec, cnt, min, level;
int lastime = 100;
int line = 0;
bool alive = TRUE;

void update_data(void){
	unit++;
	lastime++;
	if (unit >= Freq){
		unit = 0;
		cnt = cnt + 1 ;

		if (cnt >= 9){
			cnt = 0;
			level ++;
			}
		
		if (level < 10) cputint(level, 7, 30, white);
		else cputint(level, 7, 29, white);

		sec++; 
		if (sec >= 60){
			sec = 0;
			min++;
			}
 		if (min < 10){
			cputc('0', 10, 27, white);
			cputint(min, 10, 28, white);
			}
		else cputint(min, 10, 27, white);

		cputc(':', 10, 29, white);
		if (sec < 10){
			cputc('0', 10, 30, white);
			cputc(sec+'0', 10, 31, white);
		}
		else cputint(sec, 10, 30, white);
	}
}

void update_step(void){
	int i, j, x, chance;
	Oldfront = stepfront;
	Oldrear = steprear;

	for (i = stepfront; i < steprear; i++){
		Oldstep[i].pos.x = Curstep[i].pos.x;
		Oldstep[i].pos.y = Curstep[i].pos.y;
		}

	for (i = stepfront; i < steprear; i++){
		Curstep[i].pos.x -= Curstep[i].speed;
		if (Curstep[i].pos.x + 200 <= 0)
			stepfront++;
			}

	/*rand step*/

	i = rand();
	if (lastime < 40) 
		chance = 0;
	else {
		chance = (lastime - 20);
		chance = 3 * chance * chance - 40 * chance;
	}
	if (i < chance){
		j = rand() * 1991 % 100;
		if (j < 0) j = -j;
		if (j == 0) j ++;
		Curstep[steprear].pos.x = 186 << frac;
		Curstep[steprear].pos.y = j << frac;
		Curstep[steprear].speed = Curstep[steprear-1].speed;
		Curstep[steprear].type = abs(rand()) % 5 + 1;

		if (Curstep[steprear].pos.x - Curstep[steprear-1].pos.x > 360){
			steprear++;
			lastime = 0;
			}
		}
 }

void jumpcheck(void){
	int i = Curman.stone;
	int y = Curman.pos.y >> frac, y1 = Curstep[i].pos.y >> frac;

	if (y < y1 - Halwid || y > y1 + 40 + Halwid){
		Curman.state = Jump;
		Curman.vel.x = 0;
		Curman.vel.y = 0;
		}
}

void landcheck(void){
	int i = stepfront;
	int x, x1, y, y1;
	bool flag = FALSE;
	x = Curman.pos.x >> frac;
	y = Curman.pos.y >> frac;

	for (; i < steprear; i++){
		x1 = Curstep[i].pos.x >> frac;
		y1 = Curstep[i].pos.y >> frac;
		if (x >= x1 && x <= x1 + 7 && y >= y1 - Halwid
			 && y <= y1 + 40 + Halwid && Curman.vel.x + 2 * bspeed< 0){
			 Curman.state = Stand;
			 Curman.stone = i;
			 Curman.vel.x = Curstep[i].speed;
			 Curman.pos.x = Curstep[i].pos.x;

			 if (Curstep[i].type == Thorny){
			 	Curman.blood -= 3;
			 	if (Curman.blood <= 0)
			 		alive = FALSE;
			 	}
			 else if (Curman.blood < 9)
			 	Curman.blood++;

			 if (Curstep[i].type == Roll)
			 	Curman.vel.y = bspeed << 1; 
			 else if (Curstep[i].type == Spring){
			 	Curman.vel.x = 5 * bspeed;
			 	Curman.state = Sprup;
			 }

			 flag = TRUE;
			 break;
			 }
		}
	if (!flag)
		if (Curman.vel.x + bspeed * 5 > 0){
			if (Curman.vel.x <= 0)
				Curman.vel.x -= bspeed;
			else 
				Curman.vel.x -= bspeed * 2 / 5;
		}
		
	
}


void update_man(void){
	int x, y;

	Oldman.pos.x = Curman.pos.x;
	Oldman.pos.y = Curman.pos.y;
	
	Curman.pos.x -= Curman.vel.x;
	Curman.pos.y += Curman.vel.y;

	if (left_key && right_key) ;
	else if (left_key){
		Curman.pos.y -= bspeed * 3;
/*		if (Curman.state == Stand && Curstep[Curman.stone].type == Roll)
		Curman.pos.y += bspeed;
		*/
	}
	else if (right_key)
		Curman.pos.y += bspeed * 3;


	y = Curman.pos.y >> frac;
	if (y <= Halwid+1)
		Curman.pos.y = (Halwid+1) << frac;
	else if (y + Halwid >= 140)
		Curman.pos.y = (140-Halwid) << frac;
	
	if (Curman.state == Stand)
		jumpcheck();
	else landcheck();


	x = Curman.pos.x >> frac;
	if (x > 195){
		alive = FALSE;
		Curman.pos.x = 187 << frac;
		}

	if (alive) clear_man();
	clear_step();

	draw_man();
	draw_step();

	if (x <= 11 && Curman.state != Jump){
		Curman.state = Jump;
		Curman.blood -= 3;
		if (Curman.blood <= 0)
			alive = FALSE;
		Curman.vel.x = 0;
		}
}

void run_game_logic(void){
	update_data();
	update_step();
	update_man();
	timer_fired = FALSE;
}
