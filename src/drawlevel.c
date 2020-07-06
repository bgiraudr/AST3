#include "drawlevel.h"
#include <gint/std/string.h>
#include <gint/display.h>
#include "define.h"

extern bopti_image_t img_solid_0; //solid block
extern bopti_image_t img_coin; //facultative coin
extern bopti_image_t img_dead; //dead block
extern bopti_image_t img_player; //player
extern bopti_image_t img_end; //end of level
extern bopti_image_t img_key1; //key 1
extern bopti_image_t img_keyblock; //block link to the key1

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
			case '1': //solid block
				dimage(x,y,&img_solid_0);
				break;
			case 't': //coin (treasure)
				dimage(x,y,&img_coin);
				break;
			case 'd': //dead block
				dimage(x,y,&img_dead);
				break;
			case 'e': //end of level
				dimage(x,y,&img_end);
				break;
			case '3': //block link to the key1
				dimage(x,y,&img_keyblock);
				break;
			case 'k': //key1
				dimage(x,y,&img_key1);	
				break;
			case '4': //block link to the key2
				dimage(x,y,&img_keyblock);
				break;
			case 'K': //key2
				dimage(x,y,&img_key1);
				break;
			case 'c': //chrono blocks
				dimage(x,y,&img_keyblock);
				break;
			case 'C': //chrono blocks
				dimage(x,y,&img_keyblock);
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

void draw_timer(unsigned int frame)
{
	dprint_opt(0, 0, C_WHITE, C_BLACK, DTEXT_LEFT, DTEXT_TOP, "%u.%02u",(frame)/FPS, (frame)%FPS);
}
