#include "collide.h"
#include "define.h"

void collide(int x, int y, char level[], char gravity, int *hor, int *vert, char block) //detect if a block is colliding when changing gravity
{
	if((level[(int)(x/16)+(int)((y-1)/16*25)] == block || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y-1)/16*25)] == block) && gravity) //return true if player is touching a block on the bottom of him
	{
		*vert=1;
	}
	else if((level[(int)(x/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block || 
	level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block) && !gravity) //return true if player is touching a block on top of him
	{
		*vert=1;
	}
	else *vert=0;
	
	if(level[(int)((x+PLAYER_HEIGHT)/16)+(int)(y/16*25)] == block ||
	level[(int)((x+PLAYER_HEIGHT)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block) //return if player is next to a block on his right
	{
		*hor=1;
	}
	else if(level[(int)((x-1)/16)+(int)(y/16*25)] == block ||
	level[(int)((x-1)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block) //return if player is next to a block on his left
	{
		*hor=2;
	}
	else *hor=0;
}

void collide_solid(int x, int y, char level[], char gravity, int *hor, int *vert)
{
	collide(x, y, level, gravity, hor, vert, '2'); //Truc étrange ici, les blocs 2 (rouges) agissent bizarrement
	if(!*vert || !*hor) collide(x, y, level, gravity, hor, vert, '1');
}
