#include "collide.h"

int collide(int x, int y, char block, char level[], char gravity)
{
	if((level[(int)(x/16)+(int)((y-1)/16*25)] == block || 
	level[(int)((x+12)/16)+(int)((y-1)/16*25)] == block) && !gravity)
	{
		return 1;
	}
	else if((level[(int)(x/16)+(int)((y+12)/16*25)] == block || 
	level[(int)((x+12)/16)+(int)((y+12)/16*25)] == block) && gravity)
	{
		return 1;
	}
	else return 0;
}
