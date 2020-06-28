#include "collide.h"
#include "define.h"
#include <gint/display.h>

int collide_vert(int x, int y, char level[], char gravity) //detect if a block is colliding when changing gravity
{
	if((level[(int)(x/16)+(int)((y-1)/16*25)] != '0' || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y-1)/16*25)] != '0') && gravity) //return true if player is touching a block on top of him
	{
		return 1;
	}
	else if((level[(int)(x/16)+(int)((y+PLAYER_HEIGHT)/16*25)] != '0' || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y+PLAYER_HEIGHT)/16*25)] != '0') && !gravity) //return true if player is touching a block on the bottom of him
	{
		return 1;
	}
	else return 0;
}

int collide_hor(int x, int y, char level[]) //detect if a block is colliding with the player when going left or right
{
	if(level[(int)((x+PLAYER_HEIGHT)/16)+(int)(y/16*25)] != '0' ||
	level[(int)((x+PLAYER_HEIGHT)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] != '0') //return if player is next to a block on his right
	{
		return 1;
	}
	else if(level[(int)((x-1)/16)+(int)(y/16*25)] != '0' ||
	level[(int)((x-1)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] != '0') //return if player is next to a block on his left
	{
		return 2;
	}
	else return 0;
}
