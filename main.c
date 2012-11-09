#include "gamelib.h"
#include "gamedec.h"

#define Play 0
#define Midd 1
#define Pause 2

extern bool alive;
extern int level;


void main(void){
	
	int cnt = 0;
	int mode = Play;

	cli();
	init_timer();
	init_keyboard();
	init_graphics();
	init_game();
	sti();

	while (TRUE) {
		if (esc_key){
			cli();
			init_graphics();
			init_game();
			alive = TRUE;
			mode = Play;
			level = 0;
			sti();
		}
		if (timer_fired){
			if (mode == Play)
				run_game_logic();
		}
		if (!alive & mode == Play){
			idle();
			init_graphics();
			mode = Midd;
			if (level >= 100){
				cputs("Well Done! Real Man. ^_^", 10, 8, lightred);
				cputs("Press ESC to play again", 11, 7, lightred);
			}
			else{
				cputs("If you want to be a Man", 10, 8, grey);
				cputs("Press ESC to try again.", 11, 8, grey);	
				alive = TRUE;
			}
		}
		if (p_key && mode == Play){
			mode = Pause;
			idle();idle();
		}	
		else if (p_key && mode == Pause){
			mode = Play;
			idle();idle();
		}


		idle();
		}
}
