#include "gamelib.h"

void timer_int(void);

void init_timer(void) {
	out_byte(0x43, 0x34);
	out_byte(0x40, 47726 % 256);
	out_byte(0x40, 47726 / 256);

	memory_write(0, 8*4, (uint_16)timer_int);
	memory_write(0, 8*4+2, SEGMENT);
	}

void timer_handle(void){
	timer_fired = TRUE;
	out_byte(0x20, 0x20);
	}
