#include <gint/display.h>
#include <gint/keyboard.h>
#include "setlevel.h"
#include "drawlevel.h"
#include "collide.h"

#include "define.h"

int main(void)
{
	dclear(C_WHITE);
	int player_x = 20, player_y = 20;
	char level[351];
	char gravity = 0; //0 down 1 up
	char check = 0;
	int id_level = 1;
	set_level(id_level, level, &player_x, &player_y);
	draw_level(level);
	while(1)
	{
		draw_level(level);
		draw_player(player_x,player_y);
		
		dprint(150,100,C_GREEN,"%d",player_x);
		dprint(150,120,C_GREEN,"%d",player_y);

		dprint(320,120,C_GREEN,"%d",collide_solid(player_x, player_y, level, gravity));
		
		dprint(300,120,C_GREEN,"%c",level[(int)((player_x-1)/16)+(int)((player_y-1)/16*25)]); //top left
		dprint(300,140,C_GREEN,"%c",level[(int)((player_x+PLAYER_HEIGHT)/16)+(int)((player_y-1)/16*25)]); //top right
		dprint(300,160,C_GREEN,"%c",level[(int)(player_x/16)+(int)((player_y+PLAYER_HEIGHT)/16*25)]); //bottom left
		dprint(300,180,C_GREEN,"%c",level[(int)((player_x+PLAYER_HEIGHT)/16)+(int)((player_y+PLAYER_HEIGHT)/16*25)]); //bottom right
		
		dupdate();
		
		pollevent();
		if(keydown(KEY_RIGHT))
		{
			player_x+=PLAYER_SPEED;
			if(player_x>=388) player_x=-4;

		}
		else if(keydown(KEY_LEFT))
		{
			player_x-=PLAYER_SPEED;
			if(player_x<-9) player_x=384;
		}
		if(keydown(KEY_SHIFT) && !check && collide_solid(player_x, player_y, level, gravity))
		{
			if(!gravity) gravity=1;
			else gravity=0;
			check=1;
		}
		else if(!keydown(KEY_SHIFT) && check) check=0;
		if(keydown(KEY_EXIT)) break;
		switch (collide_solid(player_x, player_y, level, gravity))
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
	}
	return 0;
}
