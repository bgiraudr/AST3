#include <gint/display.h>
#include <gint/keyboard.h>
#include "setlevel.h"
#include "drawlevel.h"
#include "collide.h"

#include "define.h"

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
		if(keydown(KEY_RIGHT) && collide_hor(player_x, player_y, level)!=1)
		{
			player_x+=PLAYER_SPEED;
			if(player_x>=388) player_x=-4;

		}
		else if(keydown(KEY_LEFT) && collide_hor(player_x, player_y, level)!=2)
		{
			player_x-=PLAYER_SPEED;
			if(player_x<-9) player_x=386;
		}
		if(keydown(KEY_EXIT))
		{
			break;
		}
		if(keydown(KEY_OPTN)) gravity=1;
		else if(keydown(KEY_VARS)) gravity=0;
		switch (collide_vert(player_x, player_y, level, gravity))
		{
			case 0:
				if(!gravity) player_y+=PLAYER_GRAVITY;
				else player_y-=PLAYER_GRAVITY;
				if(player_y>=212) player_y=-4;
				if(player_y<-6) player_y=212;
				break;
			case 1:
				if((player_y-4)%16!=0 && !gravity) player_y--;
				else if((player_y)%16!=0 && gravity) player_y++;
				break;
		}
		draw_level(level);
		draw_player(player_x,player_y);

		dprint(150,100,C_GREEN,"%d",player_x);
		dprint(150,150,C_GREEN,"%d",player_y);

		dprint(200,120,C_GREEN,"%c",level[(int)((player_x-1)/16)+(int)((player_y-1)/16*25)]); //top left
		dprint(200,140,C_GREEN,"%c",level[(int)((player_x+12)/16)+(int)((player_y-1)/16*25)]); //top right
		dprint(200,160,C_GREEN,"%c",level[(int)(player_x/16)+(int)((player_y+12)/16*25)]); //bottom left
		dprint(200,180,C_GREEN,"%c",level[(int)((player_x+12)/16)+(int)((player_y+12)/16*25)]); //bottom right
	}
	return 0;
}
