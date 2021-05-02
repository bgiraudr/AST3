#include "collide.h"
#include "define.h"
#include "util.h"

#define DEAD_COLLISION 3 // make collision with the deadly block less effective

char collide(int x, int y, char level[],
             char block) // detect if player is in a block
{
	if ((level[(int)(x / TILE_HEIGHT) +
	           (int)((y + PLAYER_HEIGHT) / TILE_HEIGHT) * LEVEL_WIDTH] ==
	         block ||
	     level[(int)((x + PLAYER_HEIGHT) / TILE_HEIGHT) +
	           (int)((y + PLAYER_HEIGHT) / TILE_HEIGHT) * LEVEL_WIDTH] ==
	         block ||
	     level[(int)(x / TILE_HEIGHT) +
	           (int)((y / TILE_HEIGHT) * LEVEL_WIDTH)] == block ||
	     level[(int)((x + PLAYER_HEIGHT) / TILE_HEIGHT) +
	           (int)((y / TILE_HEIGHT) * LEVEL_WIDTH)] == block))
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
	return (level[(int)(x / TILE_HEIGHT) +
	              (int)(y / TILE_HEIGHT) * LEVEL_WIDTH] == block);
}

char collide_end(int x, int y, char level[])
{
	return collide(x, y, level, 'e');
}

void collide_replace(int x, int y, char level[], char collide, char replace)
{
	if (collide_point(x, y, level, collide)) {
		level[((x) / TILE_HEIGHT) + ((y) / TILE_HEIGHT) * LEVEL_WIDTH] =
		    replace;
	}
	if (collide_point(x + PLAYER_HEIGHT, y, level, collide)) {
		level[((x + PLAYER_HEIGHT) / TILE_HEIGHT) +
		      ((y) / TILE_HEIGHT) * LEVEL_WIDTH] = replace;
	}
	if (collide_point(x, y + PLAYER_HEIGHT, level, collide)) {
		level[((x) / TILE_HEIGHT) +
		      ((y + PLAYER_HEIGHT) / TILE_HEIGHT) * LEVEL_WIDTH] =
		    replace;
	}
	if (collide_point(x + PLAYER_HEIGHT, y + PLAYER_HEIGHT, level,
	                  collide)) {
		level[((x + PLAYER_HEIGHT) / TILE_HEIGHT) +
		      ((y + PLAYER_HEIGHT) / TILE_HEIGHT) * LEVEL_WIDTH] =
		    replace;
	}
}

char collide_center(int x, int y, char level[], char block)
{
	if (level[(int)((x + round(PLAYER_HEIGHT / 2)) / TILE_HEIGHT) +
	          (int)((y + round(PLAYER_HEIGHT / 2)) / TILE_HEIGHT) *
	              LEVEL_WIDTH] == block) {
		return 1;
	}
	return 0;
}
