#include "gamelib.h"

#define videoSeg 0xA000

void printc(char);
void prints(char* s){
	for (; *s; s++)
		printc(*s);
		}

void cputc(unsigned char c, int x, int y, Color p){
	movecur(x, y);
	coloc(c, p);
	}

void cputs(char* s, int x, int y, Color p){
	int i = 0;
	for (; *s; s++, i++)
		cputc(*s, x, y+i, p);
}

void intostr(int, char*);
void cputint(int n, int x, int y, Color p){
	char str[10];
	if (n < 0) {
		cputc('-', x, y, p);
		y++;
		n = -n;
	}
	intostr(n, str);
	cputs(str, x, y, p);
}

void printint(int x){
	int tmp , top = 0, st[10], i;
	char c;

	if (x == 0)
		printc('0');
	else{
		tmp = x;
		while (tmp != 0){
			st[top] = tmp % 10;
			tmp /= 10;
			top++;
			}

		for (i = top-1; i >=0; i--){
			c = st[i] + '0';
			printc(c);
			}
	}
}

void intostr(int n, char* str){
	int tmp, top = 0, st[10], i;
	if (n == 0){
		str[0] = '0';
		top = 1;
		}
	else{
		tmp = n;
		while (tmp > 0){
			st[top] = tmp % 10;
			tmp = tmp / 10;
			top++;
			}

		for (i = top-1; i >= 0; i--)
			str[i] = '0' + st[top-i-1];
			}
	str[top] = 0;
}


int floattoint(float c){
	int tmp, sign, exp, bin;
	void *q = &c;
	int *p = q;

	tmp = *p;
	sign = (tmp >> 31) & 1;
	exp = ((tmp << 1) >> 24) & 0xFF;
	exp -= 127;
	bin = ((tmp << 9) >> 25) & 0x7F;
	bin = ((bin << exp) >> 7);
	bin += 1 << exp;
	return bin;
	}

		
int rand(void){
	static int seed = 3643;
	if (left_key == TRUE)
		seed = seed * seed + seed * 5 + 14963;
	if (right_key == TRUE)
		seed = 4537 * seed + 18547;

	seed = 3727 * seed + 756;
	if (seed < 0) seed = -seed;
	return seed;
}

int abs(int x){
	if (x > 0) return x;
	else return -x;
	}

void draw_pixel_vm(int x, int y, Color c){
	int offset;
	offset = x * 320 + y;

	memory_write(videoSeg, offset, c);
	}


