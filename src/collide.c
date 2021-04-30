#include "collide.h"
#include "define.h"

#define DEAD_COLLISION 3 // make collision with the deadly block less effective

char collide(int x, int y, char level[],
             char block) // detect if player is in a block
{
	if ((level[(int)(x / 16) + (int)((y + PLAYER_HEIGHT) / 16) * 25] ==
	         block ||
	     level[(int)((x + PLAYER_HEIGHT) / 16) +
	           (int)((y + PLAYER_HEIGHT) / 16) * 25] == block ||
	     level[(int)(x / 16) + (int)((y / 16) * 25)] == block ||
	     level[(int)((x + PLAYER_HEIGHT) / 16) + (int)((y / 16) * 25)] ==
	         block))
		return 1;
	return 0;
}

char collide_solid(int x, int y, char level[])
{
	return collide(x, y, level, '1') || collide(x, y, level, '3') ||
	       collide(x, y, level, '4') || collide(x, y, level, 'c') ||
	       collide(x, y, level, 'C') || collide(x, y, level, 'B') ||
	       collide(x, y, level, 'i') || collide(x, y, level, 'H');
}

char collide_dead(int x, int y, char level[])
{
	return collide_point(x + DEAD_COLLISION, y + DEAD_COLLISION, level,
	                     'd') ||
	       collide_point(x + PLAYER_HEIGHT - DEAD_COLLISION,
	                     y + DEAD_COLLISION, level, 'd') ||
	       collide_point(x + DEAD_COLLISION,
	                     y + PLAYER_HEIGHT - DEAD_COLLISION, level, 'd') ||
	       collide_point(x + PLAYER_HEIGHT - DEAD_COLLISION,
	                     y + PLAYER_HEIGHT - DEAD_COLLISION, level, 'd') ||
	       collide_point(x + 1, y + 1, level, 'C') ||
	       collide_point(x + PLAYER_HEIGHT - 1, y + 1, level, 'C') ||
	       collide_point(x + 1, y + PLAYER_HEIGHT - 1, level, 'C') ||
	       collide_point(x + PLAYER_HEIGHT - 1, y + PLAYER_HEIGHT - 1,
	                     level, 'C');
}

char collide_point(int x, int y, char level[], char block)
{
	return (level[(int)(x / 16) + (int)(y / 16) * 25] == block);
}

char collide_end(int x, int y, char level[])
{
	return collide(x, y, level, 'e');
}

void collide_replace(int x, int y, char level[], char collide, char replace)
{
	if (collide_point(x, y, level, collide)) {
		level[((x) / 16) + ((y) / 16) * 25] = replace;
	}
	if (collide_point(x + PLAYER_HEIGHT, y, level, collide)) {
		level[((x + PLAYER_HEIGHT) / 16) + ((y) / 16) * 25] = replace;
	}
	if (collide_point(x, y + PLAYER_HEIGHT, level, collide)) {
		level[((x) / 16) + ((y + PLAYER_HEIGHT) / 16) * 25] = replace;
	}
	if (collide_point(x + PLAYER_HEIGHT, y + PLAYER_HEIGHT, level,
	                  collide)) {
		level[((x + PLAYER_HEIGHT) / 16) +
		      ((y + PLAYER_HEIGHT) / 16) * 25] = replace;
	}
}
