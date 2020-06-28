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
		if(keydown(KEY_RIGHT) && collide_solid(player_x, player_y, '1', level)!=1)
		{
			player_x+=PLAYER_SPEED;
			if(player_x>390) player_x=0;

		}
		else if(keydown(KEY_LEFT) && collide_solid(player_x, player_y, '1', level)!=2)
		{
			player_x-=PLAYER_SPEED;
			if(player_x<-9) player_x=386;
		}
		else if(keydown(KEY_SHIFT))
		{
			player_y-=PLAYER_SPEED;
		}
		else if(keydown(KEY_ALPHA))
		{
			player_y+=PLAYER_SPEED;
		}
		if(keydown(KEY_EXIT))
		{
			break;
		}
		if(keydown(KEY_OPTN)) gravity=1;
		else if(keydown(KEY_VARS)) gravity=0;
		switch (collide(player_x, player_y, '1', level, gravity))
		{
			case 0:
				if(!gravity) player_y+=PLAYER_GRAVITY;
				else player_y-=PLAYER_GRAVITY;
				break;
			case 1 || 2:
				if((player_y-4)%16!=0 && !gravity) player_y--;
				else if((player_y)%16!=0 && gravity) player_y++;
				break;
		}
		draw_level(level);
		draw_player(player_x,player_y);
		int x = player_x;
		int y = player_y;
		dprint(150,100,C_BLACK,"%d",player_x);
		dprint(150,150,C_BLACK,"%d",player_y);
		dprint(100,180,C_BLACK,"%c",level[(int)((x+PLAYER_HEIGHT)/16)+(int)(y/16*25)]);
		dprint(120,180,C_BLACK,"%c",level[(int)((x+PLAYER_HEIGHT)/16)+(int)((y+PLAYER_HEIGHT-1)/16*25)]);
		dprint(100,120,C_BLACK,"%d",collide(player_x, player_y, '1', level, gravity));
		dprint(100,140,C_BLACK,"%d",collide_solid(player_x, player_y, '1', level));
		dprint(200,120,C_BLACK,"%c",level[(int)(x/16)+(int)(y/16*25)]);
		dprint(200,140,C_BLACK,"%c",level[(int)(x/16)+(int)((y+12)/16*25)]);
		dprint(200,160,C_BLACK,"%c",level[(int)((x+12)/16)+(int)((y+12)/16*25)]);
		dprint(200,180,C_BLACK,"%c",level[(int)((x+12)/16)+(int)(y/16*25)]);
	}
	return 0;
}
