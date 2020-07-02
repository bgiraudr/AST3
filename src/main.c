#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/clock.h>
#include <gint/timer.h>

#include "setlevel.h"
#include "drawlevel.h"
#include "collide.h"
#include "define.h"

#define ACCELERATION 0.4
#define MAX_VSPD 9.0

int callback(volatile int *frame_elapsed)
{
    *frame_elapsed = 1;
    return TIMER_CONTINUE;
}

int main(void)
{
	volatile int frame_elapsed = 1;
	int timer = timer_setup(TIMER_ANY, 16500, callback, &frame_elapsed);
	timer_start(timer);
	
	unsigned int frame = 0;
	int player_x = 20, player_y = 20;
	char level[351];
	char gravity = 0; //0 down 1 up
	char check = 0;
	int id_level = 1;
	int start_x;
	int start_y;
	
	float vspd = 1.0;
	int vert_spd = 1;
	
	set_level(id_level, level, &start_x, &start_y, &gravity);
	player_x = start_x;
	player_y = start_y;
	draw_level(level);
	while(1)
	{
		while(!frame_elapsed) sleep();
		frame_elapsed = 0;
		
		frame++;
		
		draw_level(level);
		draw_player(player_x,player_y);	
		draw_timer(frame);
		dprint(150,100,C_GREEN,"%d",player_x);
		dprint(150,120,C_GREEN,"%d",player_y);

		/*dprint(320,120,C_GREEN,"%d",collide_solid(player_x+1, player_y, level, gravity));
		dprint(320,140,C_GREEN,"%d",collide_solid(player_x-1, player_y, level, gravity));
		dprint(320,160,C_GREEN,"%d",collide_solid(player_x, player_y+1, level, gravity));
		dprint(320,180,C_GREEN,"%d",collide_solid(player_x, player_y-1, level, gravity));*/
		
		/*dprint(300,100,C_GREEN,"%d",collide_dead(player_x, player_y, level));
		dprint(300,120,C_GREEN,"%c",level[(int)((player_x-1)/16)+(int)((player_y-1)/16*25)]); //top left
		dprint(300,140,C_GREEN,"%c",level[(int)((player_x+PLAYER_HEIGHT+1)/16)+(int)((player_y-1)/16*25)]); //top right
		dprint(300,160,C_GREEN,"%c",level[(int)((player_x-1)/16)+(int)((player_y+PLAYER_HEIGHT+1)/16*25)]); //bottom left
		dprint(300,180,C_GREEN,"%c",level[(int)((player_x+PLAYER_HEIGHT+1)/16)+(int)((player_y+PLAYER_HEIGHT+1)/16*25)]); //bottom right*/
		
		dupdate();
		
		pollevent();
		if(keydown(KEY_RIGHT))
		{
			if(!collide_solid(player_x+PLAYER_SPEED, player_y, level, gravity)) player_x+=PLAYER_SPEED;
			else if(!collide_solid(player_x+1, player_y, level, gravity)) player_x+=1;
			if(player_x>=388) player_x=-4;

		}
		else if(keydown(KEY_LEFT))
		{
			if(!collide_solid(player_x-PLAYER_SPEED, player_y, level, gravity)) player_x-=PLAYER_SPEED;
			else if(!collide_solid(player_x-1, player_y, level, gravity)) player_x-=1;
			if(player_x<-9) player_x=384;
		}
		if(keydown(KEY_SHIFT) && !check && (collide_solid(player_x, player_y-1, level, gravity) || collide_solid(player_x, player_y+1, level, gravity)))
		{
			if(!gravity) gravity=1;
			else gravity=0;
			check=1;
		}
		else if(!keydown(KEY_SHIFT) && check) check=0;
		if(keydown(KEY_EXIT)) break;
		if(!gravity)
		{
			if(!collide_solid(player_x, player_y+vert_spd, level, gravity))
			{
				if (vspd<MAX_VSPD) vspd+=ACCELERATION;
				vert_spd = vspd;
				player_y+=vert_spd;
			}
			else if(!collide_solid(player_x, player_y+1, level, gravity))
			{
				vspd = 1;
				player_y+=1;
			}
			else vspd = 1;
		}
		else
		{
			if(!collide_solid(player_x, player_y-vert_spd, level, gravity))
			{
				if (vspd<MAX_VSPD) vspd+=ACCELERATION;
				vert_spd = vspd;
				player_y-=vert_spd;
			}
			else if(!collide_solid(player_x, player_y-1, level, gravity))
			{
				vspd = 1;
				player_y-=1;
			}
			else vspd = 1;
		}
		if(collide_dead(player_x, player_y, level))
		{
			vspd = 1;
			player_x = start_x;
			player_y = start_y;
			set_gravity(id_level, &gravity);
		}
		if(collide_end(player_x, player_y, level, gravity))
		{
			id_level++;
			set_level(id_level, level, &start_x, &start_y, &gravity);
			player_x = start_x;
			player_y = start_y;
		}
		if(player_y>=212) player_y=-4;
		if(player_y<-6) player_y=212;
	}
	timer_stop(timer);
	return 0;
}
