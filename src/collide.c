#include "collide.h"
#include "define.h"

#define DEAD_COLLISION 3 //make the collision with the deadly block less effective

char collide(int x, int y, char level[], char gravity, char block) //detect if player is in a block
{
	if(((level[(int)(x/16) + (int)((y/16) * 25)] == block || 
	level[(int)((x + PLAYER_HEIGHT)/16) + (int)((y/16) * 25)] == block) && gravity) ||
	((level[(int)(x/16) + (int)((y + PLAYER_HEIGHT)/16) * 25] == block || 
	level[(int)((x + PLAYER_HEIGHT)/16) + (int)((y + PLAYER_HEIGHT)/16) * 25] == block) && !gravity)) return 1;
	return 0;
}

char collide_solid(int x, int y, char level[], char gravity)
{
	return collide(x, y, level, gravity, '1')
	|| collide(x, y, level, gravity, '3')
	|| collide(x, y, level, gravity, '4')
	|| collide(x, y, level, gravity, 'c')
	|| collide(x, y, level, gravity, 'C');
}

char collide_dead(int x, int y, char level[])
{
	return collide_point(x + DEAD_COLLISION, y + DEAD_COLLISION, level, 'd') || 
	collide_point(x + PLAYER_HEIGHT - DEAD_COLLISION, y + DEAD_COLLISION, level, 'd') || 
	collide_point(x + DEAD_COLLISION, y + PLAYER_HEIGHT - DEAD_COLLISION, level, 'd') || 
	collide_point(x + PLAYER_HEIGHT - DEAD_COLLISION, y + PLAYER_HEIGHT - DEAD_COLLISION, level, 'd');
}

char collide_point(int x, int y, char level[], char block)
{
	return (level[(int)(x/16) + (int)(y/16) * 25] == block);
}

char collide_end(int x, int y, char level[], char gravity)
{
	return collide(x, y, level, gravity, 'e');
}
