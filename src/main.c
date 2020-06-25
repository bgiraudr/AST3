#include <gint/display.h>
#include <gint/keyboard.h>
#include "setlevel.h"
#include "drawlevel.h"

#define PLAYER_SPEED 2

int main(void)
{
	dclear(C_WHITE);
	int player_x=0, player_y=0;
	char level[477];
	int id_level = 1;
	set_level(id_level,level);
	draw_level(level);
	draw_player(player_x,player_y);
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
		else if(keydown(KEY_UP))
		{
			player_y-=PLAYER_SPEED;
			if(player_y<-9) player_y=219;
		}
		else if(keydown(KEY_DOWN))
		{
			player_y+=PLAYER_SPEED;
			if(player_y>219) player_y=-9;
		}
		if(keydown(KEY_EXIT))
		{
			break;
		}
		draw_level(level);
		draw_player(player_x,player_y);
	}
	return 1;
}
