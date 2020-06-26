#include "collide.h"

int collide(int x, int y, char block, char gravity, char level[])
{
	if(level[(int)(x/16)+(int)(y/16*25)+25] == block && !gravity)
	{
		return 2;
	}
	else if (level[(int)(x/16)+(int)(y/16*25)-25] == block && gravity)
		{
			return 3;
		}
	else if(!gravity) return 0;
	else return 1;
}
