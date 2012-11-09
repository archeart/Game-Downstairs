#include "gamelib.h"
#define MaxSteps 1000 

typedef struct{
	int x, y;
	}coord;

typedef struct{
	int state, blood, stone;
	coord pos, vel;
	bool dir;
	}Man;

typedef struct{
	int type;
	int speed;
	coord pos;
	}Step;

