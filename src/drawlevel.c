#include "drawlevel.h"
#include <gint/std/string.h>
#include <gint/display.h>
#include "define.h"
#include "times.h"

#define VISIBLE_RECT 35

extern bopti_image_t img_solid_0; //solid block
extern bopti_image_t img_coin; //facultative coin
extern bopti_image_t img_dead; //dead block
extern bopti_image_t img_player; //player
extern bopti_image_t img_end; //end of level
extern bopti_image_t img_key1; //key 1
extern bopti_image_t img_blackout; //blackout
extern bopti_image_t img_chrono1; //chronoblock
extern bopti_image_t img_chrono2; //chronoblock 2
extern bopti_image_t img_key2; //key 2
extern bopti_image_t img_damaged; //damaged block
extern bopti_image_t img_chock; //chock block
extern bopti_image_t img_switch; //switch block
extern bopti_image_t img_ice; //switch block
extern bopti_image_t img_appear; //appear block

extern bopti_image_t img_endscreen;

void draw_player(int x, int y, char type)
{
	dsubimage(x,y,&img_player, 12*(type-1),0,12,12, DIMAGE_NONE);
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
				dsubimage(x,y,&img_key1,0,0,16,16,DIMAGE_NONE);
				break;
			case 'k': //key1
				dsubimage(x,y,&img_key1,16,0,16,16,DIMAGE_NONE);
				break;
			case 'a': //block link to the key2 when it's not powered on
				dsubimage(x,y,&img_key2,0,0,16,16,DIMAGE_NONE);
				break;
			case '4': //block link to the key2
				dsubimage(x,y,&img_key2,16,0,16,16,DIMAGE_NONE);
				break;
			case 'K': //key2
				dsubimage(x,y,&img_key2,32,0,16,16,DIMAGE_NONE);
				break;
			case 'c': //chrono blocks
				dimage(x,y,&img_chrono1);
				break;
			case 'C': //chrono blocks
				dsubimage(x,y,&img_chrono2,16,0,16,16,DIMAGE_NONE);
				break;
			case 'b': //blackout blocks
				dimage(x,y,&img_blackout);
				break;
			case 'B': //damaged block
				dimage(x,y,&img_damaged);
				break;
			case 'l': //chock blocks
				dimage(x,y,&img_chock);
				break;
			case 'i': //ice blocks
				dimage(x,y,&img_ice);
				break;
			case 'S': //chock blocks
				dimage(x,y,&img_switch);
				break;
			case 'h': //void appear blocks
				dsubimage(x,y,&img_appear,0,0,16,16,DIMAGE_NONE);
				break;
			case 'y': //void appear blocks
				dsubimage(x,y,&img_appear,0,0,16,16,DIMAGE_NONE);
				break;
			case 'H': //appear blocks
				dsubimage(x,y,&img_appear,16,0,16,16,DIMAGE_NONE);
				break;
			case 'm': //chronoappear blocks
				dsubimage(x,y,&img_chrono2,0,0,16,16,DIMAGE_NONE);
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

void draw_blackout(int x, int y)
{
	x+=5;
	y+=5;
	drect(0, 0, 395, y-VISIBLE_RECT, C_BLACK); //top rect
	drect(0, y-VISIBLE_RECT, x-VISIBLE_RECT, y+VISIBLE_RECT, C_BLACK); //left rect
	drect(x+VISIBLE_RECT, y-VISIBLE_RECT, 395, y+VISIBLE_RECT, C_BLACK); //right rect
	drect(0, y+VISIBLE_RECT, 395, 223, C_BLACK); //bottom rect
}

void draw_timer(unsigned int frame)
{
	dprint_opt(0, 0, C_WHITE, C_BLACK, DTEXT_LEFT, DTEXT_TOP, "%u.%02u",(frame)/FPS, (frame)%FPS);
}

void draw_end(int framelevel, int id_level)
{
	float framefloat = framelevel;
	dimage(144,60,&img_endscreen);
	dprint_opt(220, 115, C_WHITE, C_BLACK, DTEXT_LEFT, DTEXT_TOP, "%d", framelevel);
	dprint(166, 87, C_RED, "%.2j",(int)(framefloat/FPS*100));
	check_medal(framelevel, id_level, 178, 140);
	dupdate();
}
