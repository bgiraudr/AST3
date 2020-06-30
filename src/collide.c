#include "collide.h"
#include "define.h"

char collide(int x, int y, char level[], char gravity, char block) //detect if a block is colliding
{
	if(((level[(int)(x/16)+(int)((y-1)/16*25)] == block || level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y-1)/16*25)] == block) && gravity) || //si le bloc d'au dessus est "block"
	((level[(int)(x/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block || level[(int)((x+PLAYER_HEIGHT-1)/16)+(int)((y+PLAYER_HEIGHT)/16*25)] == block) && !gravity) || //si le bloc d'en dessus est "block"
	(level[(int)((x+PLAYER_HEIGHT)/16)+(int)(y/16*25)] == block || level[(int)((x+PLAYER_HEIGHT)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block) || //si le bloc de gauche est "block"
	(level[(int)((x-1)/16)+(int)(y/16*25)] == block || level[(int)((x-1)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)] == block)) return 1;//si le bloc de droite est "block"
	return 0;
}

char collide_solid(int x, int y, char level[], char gravity)
{
	return collide(x, y, level, gravity, '1') || collide(x, y, level, gravity, '2');
}
