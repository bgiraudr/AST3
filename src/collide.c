#include "collide.h"
#include "define.h"
#include <gint/display.h>

int collide(int x, int y, char block, char level[], char gravity)
{
	if((level[(int)(x/16)+(int)((y-1)/16*25)] == block || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y-1)/16*25)] == block) && gravity) //return true if player is touching a block on top of him
	{
		return 1;
	}
	else if((level[(int)(x/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block) && !gravity) //return true if player is touching a block on the bottom of him
	{
		return 2;
	}
	else return 0;
}

int collide_solid(int x, int y, char block, char level[])
{
	if(level[(int)((x+PLAYER_HEIGHT+1)/16)+(int)(y/16*25)] == block ||
	level[(int)((x+PLAYER_HEIGHT+1)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block) //return if player is next to a block on his right
	{
		return 1;
	}
	else if(level[(int)((x-1)/16)+(int)(y/16*25)] == block ||
	level[(int)((x-1)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block) //return if player is next to a block on his left
	{
		return 2;
	}
	else return 0;
}
