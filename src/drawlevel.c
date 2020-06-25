#include "drawlevel.h"
#include <gint/std/string.h>
#include <gint/display.h>
#include <gint/keyboard.h>

extern bopti_image_t img_solid_0;
extern bopti_image_t img_solid_1;
extern bopti_image_t img_player;

void draw_player(int x, int y)
{
	dimage(x,y,&img_player);
}
void draw_level(char level[])
{
	dclear(C_WHITE);
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int i = 0;
	while (i!=strlen(level))
	{
		switch(level[i])
		{
			case '1':
				dimage(x,y,&img_solid_0);
				break;
			case '2':
				dimage(x,y,&img_solid_1);
				break;
		}
		x+=16;
		if(x==16*25)
		{
			x=0;
			y+=16;
		}
		i++;
	}
}
