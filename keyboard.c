#include "gamelib.h"

bool left_key = FALSE;
bool right_key = FALSE;
bool up_key = FALSE;
bool down_key = FALSE;
bool esc_key = FALSE;
bool p_key = FALSE;

void keyboard_int(void);

void init_keyboard(void) {
	memory_write(0, 9*4, (uint_16)keyboard_int);
	memory_write(0, 9*4+2, SEGMENT);
	}

void keyboard_handle(void) {
	unsigned int code = in_byte(0x60);
	unsigned int val = in_byte(0x61);
	out_byte(0x61, val | 0x80);
	out_byte(0x61, val);
	out_byte(0x20, 0x20);

	if (code == 75) left_key = TRUE;
	else if (code == 203) left_key = FALSE;
	else if (code == 77) right_key = TRUE;
	else if (code == 205) right_key = FALSE;
	else if (code == 72) up_key = TRUE;
	else if (code == 200) up_key = FALSE;
	else if (code == 80) down_key = TRUE;
	else if (code == 208) down_key = FALSE;
	else if (code == 1) esc_key = TRUE;
	else if (code == 129) esc_key = FALSE;
	else if (code == 25) p_key = TRUE;
	else if (code == 153) p_key = FALSE;
	}
