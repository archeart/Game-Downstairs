#ifndef _GAMELIB_H_
#define _GAMELIB_H_

#define int_16 int
#define int_8 char
#define uint_16 unsigned int
#define uint_8 unsigned char
#define bool uint_8
#define Color int

#define TRUE 1
#define FALSE 0
#define SEGMENT 0x8000
#define Freq 25 

#define black 0x0
#define blue 0x1
#define green 0x2
#define red 0x4
#define silver 0x7
#define grey 0x8
#define yellow 14
#define white 15 
#define lightgreen 10
#define lightred 12

#define Stand 1
#define Jump 2
#define Sprup 3

#define Halwid 4

#define Normal 1
#define Thorny 2
#define Roll 3
#define Spring 4

#define frac 5

void cli(void);
void sti(void);
void idle(void);
void out_byte(uint_16 port, uint_8 data);
uint_8 in_byte(uint_16 port);

void memory_write(uint_16, uint_16, uint_16);


void printc(char);
void movecur(int, int);
void coloc(char, Color);
void prints(char*);
void printint(int);
void cputc(unsigned char, int, int, Color);
void cputs(char*, int, int, Color);
void cputint(int, int, int, Color); 
int rand(void);
int abs(int);



void draw_pixel(int, int, Color);
void draw_pixel_vm(int, int, Color);
void draw_step(void);
void draw_step2(void);
void draw_frame(void);
void draw_man(void);
void clear_man(void);
void clear_step(void);

void init_timer(void);
void init_keyboard(void);
void init_game(void);
void init_graphics(void);

void init_game(void);
void run_game_logic(void);

extern bool timer_fired, need_refresh, alive;
extern bool left_key, right_key, up_key, down_key, esc_key, p_key;
extern int bspeed;
extern int android[10][10];

#endif

