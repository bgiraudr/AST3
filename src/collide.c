#include "collide.h"
#include "define.h"

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
	return collide(x, y, level, gravity, '1') || collide(x, y, level, gravity, '2');
}
