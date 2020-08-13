#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/clock.h>
#include <gint/timer.h>
#include <gint/std/string.h>

#include "setlevel.h"
#include "drawlevel.h"
#include "collide.h"
#include "menu.h"
#include "times.h"
#include "define.h"

#define ACCELERATION 0.2
#define MAX_VSPD 9.0

int main(void);

int callback(volatile int *frame_elapsed)
{
    *frame_elapsed = 1;
    return TIMER_CONTINUE;
}

void game(int *id_level, char mode)
{
	volatile int frame_elapsed = 1;
	int timer = timer_setup(TIMER_ANY, 1000000/FPS, callback, &frame_elapsed);
	timer_start(timer);
	
	char game_loop = 1;
	unsigned int frame = 0;
	int framelevel = 0;
	int player_x = 20, player_y = 20;
	char level[351];
	char gravity = 0; //0 down 1 up
	char check = 0;
	char blackout = 0;
	int start_x;
	int start_y;
	
	unsigned int coin = 0;
	char check_coin = 0;
	
	int appear = 10;
	int disappear = 13;
	
	float vspd = 1.0;
	int vert_spd = 1;
	extern bopti_image_t img_speedrun;
	
	set_level(*id_level, level, &start_x, &start_y, &gravity, &appear, &disappear);
	player_x = start_x;
	player_y = start_y;
	draw_level(level);
	while(game_loop)
	{
		while(!frame_elapsed) sleep();
		frame_elapsed = 0;
		
		frame++;
		framelevel++;
		if(!(frame%2))
		{
			draw_level(level);
			if(blackout) draw_blackout(player_x, player_y);
			draw_player(player_x,player_y);
			if(!mode) draw_timer(frame);
			else draw_timer(framelevel);
		
		if(*id_level==1 && !mode)
		{
			dprint(85,180,C_RGB(245,245,0),"SHIFT");
			dprint(167,19,C_RGB(110,110,110),"Ne touchez pas ces blocs !");
			dprint(162,160,C_RGB(110,110,110),"Les clefs agissent");
			dprint(162,173,C_RGB(110,110,110),"sur certains blocs");
			dprint(315,115,C_RGB(110,110,110),"Bravo !");
		}
			dprint(150,100,C_GREEN,"%d",player_x);
			dprint(150,120,C_GREEN,"%d",player_y);
			if(!mode) dprint_opt(340, 0, C_RGB(255,190,0), C_BLACK, DTEXT_LEFT, DTEXT_TOP, "Coin : %d", coin);
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
		}
		
		pollevent();
		//Right collision
		if(keydown(KEY_RIGHT))
		{
			if(!collide_solid(player_x+PLAYER_SPEED, player_y, level, gravity)) player_x+=PLAYER_SPEED;
			else if(!collide_solid(player_x+1, player_y, level, gravity)) player_x+=1;
			if(player_x>=388) player_x=-4;

		}
		//Left collision
		else if(keydown(KEY_LEFT))
		{
			if(!collide_solid(player_x-PLAYER_SPEED, player_y, level, gravity)) player_x-=PLAYER_SPEED;
			else if(!collide_solid(player_x-1, player_y, level, gravity)) player_x-=1;
			if(player_x<-9) player_x=384;
		}
		//Action key
		if(keydown(KEY_SHIFT) && !check && ((collide_solid(player_x, player_y-1, level, gravity) && gravity) || (collide_solid(player_x, player_y+1, level, gravity) && !gravity)))
		{
			if(!gravity) gravity=1;
			else gravity=0;
			check=1;
		}
		else if(!keydown(KEY_SHIFT) && check) check=0;
		//Gravity
		if(!gravity)
		{
			if(!collide_solid(player_x, player_y+vert_spd+1, level, gravity))
			{
				if (vspd<MAX_VSPD) vspd+=ACCELERATION;
				vert_spd = vspd;
				player_y+=vert_spd;
			}
			else if(!collide_solid(player_x, player_y+vert_spd, level, gravity))
			{
				vspd-=ACCELERATION;
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
			if(!collide_solid(player_x, player_y-vert_spd-1, level, gravity))
			{
				if (vspd<MAX_VSPD) vspd+=ACCELERATION;
				vert_spd = vspd;
				player_y-=vert_spd;
			}
			else if(!collide_solid(player_x, player_y-vert_spd, level, gravity))
			{
				vspd-=ACCELERATION;
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
		//Collide with red block
		if(collide_dead(player_x, player_y, level))
		{
			vspd = 1;
			player_x = start_x;
			player_y = start_y;
			if(check_coin) coin--;
			check_coin = 0;
			set_level(*id_level, level, &start_x, &start_y, &gravity, &appear, &disappear);
			blackout = 0;
			framelevel = 0;
		}
		//Collide with the end
		if(collide_end(player_x, player_y, level, gravity))
		{
			if(!mode) *id_level+=1;
			if(mode)
			{
				break;
			}
			check_coin = 0;
			set_level(*id_level, level, &start_x, &start_y, &gravity, &appear, &disappear);
			player_x = start_x;
			player_y = start_y;
			blackout = 0;
			framelevel=0;
		}
		if(collide(player_x, player_y, level, gravity, 'k')) //Collide with key1 = disappearance of blocks
		{
			for (int i = 0; level[i]!='\0' ; i++) 
			{
				if(level[i]=='3') level[i]='0';
				if(level[i]=='k') level[i]='0';
			}
		}
		if(collide(player_x, player_y, level, gravity, 'K')) //Collide with key2 = appearance of blocks
		{
			for (int i = 0; level[i]!='\0' ; i++) 
			{
				if(level[i]=='a') level[i]='4';
				if(level[i]=='K') level[i]='0';
			}
		}
		if(collide(player_x, player_y, level, gravity, 't') && !check_coin) //Collide with coin
		{
			for (int i = 0; level[i]!='\0' ; i++) 
			{
				if(level[i]=='t') 
				{
					level[i]='0';
					break;
				}
			}
			check_coin=1;
			coin++;
		}
		if(collide(player_x, player_y, level, gravity, 'b')) //Collide with blackout block
		{
			for (int i = 0; level[i]!='\0' ; i++) 
			{
				if(level[i]=='b') 
				{
					level[i]='0';
					break;
				}
			}
			blackout=1;
		}
		if(level[((player_x+6)/16)+((player_y+6)/16)*25] == 'l') //Collide with change block
		{
			int x = 0;
			int y = 0;
			char level2[351] = { 0 };
			int j = 0;
			level[((player_x+6)/16)+((player_y+6)/16)*25] = 'P';
			for (int i = 349; i!=-1 ; i--) 
			{
				level2[j]=level[i];
				j++;
			}
			del_level(level);
			strncpy(level,level2,351);
			del_level(level2);
			int i = 0;
			while (i!=350)
			{
				switch(level[i])
				{
					case 'P':
						player_x = x;
						player_y = y;
						level[i]='0';
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
			if(!gravity) gravity=1;
			else gravity=0;
		}
		
		if(collide(player_x, player_y+vert_spd+2, level, gravity, 'B') && vspd>=5.0) //Damaged block 
		{
			if(level[((player_x)/16)+((player_y+25)/16)*25]=='B') level[((player_x)/16)+((player_y+25)/16)*25]='0';
			if(level[((player_x+17)/16)+((player_y+25)/16)*25]=='B' && collide_point(player_x+15, player_y+22, level, 'B')) level[((player_x+17)/16)+((player_y+25)/16)*25]='0';
			vspd=1.0;
		}
		if(collide(player_x, player_y-vert_spd-2, level, gravity, 'B') && vspd>=5.0) //Damaged block
		{
			if(level[((player_x)/16)+((player_y-vert_spd-2)/16)*25]=='B') level[((player_x)/16)+((player_y-vert_spd-2)/16)*25]='0';
			if(level[((player_x+17)/16)+((player_y-vert_spd-2)/16)*25]=='B' && collide_point(player_x+15, player_y-12, level, 'B')) level[((player_x+17)/16)+((player_y-vert_spd-2)/16)*25]='0';
			vspd=1.0;
		}
		
		if((framelevel/FPS)>disappear) for (int i = 0; level[i]!='\0' ; i++) if(level[i]=='c') level[i]='0'; //after x seconds blocks disappear
		if((framelevel/FPS)>appear) for (int i = 0; level[i]!='\0' ; i++) if(level[i]=='m') level[i]='C'; //after x seconds blocks appear
		
		if(player_y>=212) player_y=-4;
		if(player_y<-6) player_y=212;
		
		//Menu
		if(keydown_any(KEY_EXIT, KEY_MENU, 0))
		{
			char menu_loop = 1;
			char selected = 0;
			int Y_POS = 18;
			while(menu_loop)
			{
				clearevents();
				dclear(C_WHITE);
				draw_level(level);
				draw_player(player_x,player_y);
				dimage(0,0,&img_speedrun);
				selected += keydown(KEY_DOWN) - keydown(KEY_UP);
				if (selected == 2) selected = 0;
				else if (selected == -1) selected = 1;
				dtext(32, Y_POS, C_BLACK, "CONTINUE");
				if(!mode) dtext(32, Y_POS + 12, C_BLACK, "MENU");
				else dtext(32, Y_POS + 12, C_BLACK, "SPEEDRUN MENU");
				dtext(16, Y_POS + (selected * 12), C_BLACK, ">");
				dprint(180, 45, C_RGB(83,255,0), "LEVEL : %d", *id_level);
				dprint(320, 8, C_RGB(255,178,0), "COIN : %d", coin);
				dupdate();
				if (keydown_any(KEY_SHIFT, KEY_EXE, 0))
				{
					switch (selected)
					{
						case 0:
							menu_loop = 0;
							break;
						case 1:
							menu_loop = 0;
							game_loop = 0;
							break;
					}
				}
				while (keydown_any(KEY_UP, KEY_DOWN, 0)) clearevents();
			}
		}
	}
	timer_stop(timer);
	//when a level is quit
	if(mode)
	{
		if(game_loop)
		{
			dclear(C_WHITE);
			dprint_opt(198, 112, C_WHITE, C_BLACK, DTEXT_LEFT, DTEXT_TOP, "%u.%02u",(framelevel)/FPS, (framelevel)%FPS);
			check_medal(framelevel, *id_level);
			dupdate();
			sleep_ms(5000);
		}
		if(!speed_menu(id_level)) 
		{
			mode = 1;
			game(id_level, mode);
		}
		else main();
	}
	if(!mode) main();
}

int main(void)
{	
	char mode = 0;
	int valeur = start_menu();
	if(!valeur) //normal game (level selection)
	{
		int id_level = 1;
		if(!speed_menu(&id_level)) 
		{
			mode = 1;
			game(&id_level, mode);
		}
		else main();
	}
	else if(valeur==1)
	{
		int id_level = 1;
		mode = 0;
		game(&id_level, mode);
	}
	return 0;
}
