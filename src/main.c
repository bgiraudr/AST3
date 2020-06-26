#include <gint/display.h>
#include <gint/keyboard.h>
#include "setlevel.h"
#include "drawlevel.h"
#include "collide.h"

#define PLAYER_SPEED 2
#define PLAYER_GRAVITY 5
#define PLAYER_HEIGHT 12

int main(void)
{
	dclear(C_WHITE);
	int player_x=30, player_y=35;
	char level[351];
	char gravity = 0; //0 down 1 up
	int id_level = 1;
	set_level(id_level,level);
	draw_level(level);
	while(1)
	{
		dupdate();
		pollevent();
		if(keydown(KEY_RIGHT))
		{
			player_x+=PLAYER_SPEED;
			if(player_x>390) player_x=0;

		}
		else if(keydown(KEY_LEFT))
		{
			player_x-=PLAYER_SPEED;
			if(player_x<-9) player_x=386;
		}
		else if(keydown(KEY_SHIFT))
		{
			gravity = 1;
		}
		else if(keydown(KEY_ALPHA))
		{
			gravity = 0;
		}
		if(keydown(KEY_EXIT))
		{
			break;
		}
		if (collide(player_x, player_y, '1', gravity, level)==0)
		{
			player_y+=PLAYER_GRAVITY;
		}
		else if (collide(player_x, player_y, '1', gravity, level)==1)
		{
			player_y-=PLAYER_GRAVITY;
		}
		draw_level(level);
		draw_player(player_x,player_y);
		dprint(100,100,C_BLACK,"%d",(int)(player_x/16));
		dprint(100,150,C_BLACK,"%d",(int)(player_y/16));
		dprint(150,100,C_BLACK,"%d",player_x);
		dprint(150,150,C_BLACK,"%d",player_y);
		dprint(150,200,C_BLACK,"%d",(int)(player_x/16)+(int)(player_y/16)*25+25);
		dprint(100,180,C_BLACK,"%c",level[(int)(player_x/16)+(int)(player_y/16)*25+25]);
		dprint(120,180,C_BLACK,"%c",level[(int)(player_x/16)+(int)(player_y/16)*25-25]);
	}
	return 0;
}
