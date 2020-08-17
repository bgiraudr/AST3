#include "drawlevel.h"
#include <gint/display.h>
#include <gint/keyboard.h>
#include "setlevel.h"
#include "times.h"

char start_menu()
{
	extern bopti_image_t img_menu;
	char menu_loop = 1;
	char selection = 0;
	char buffer = 1;
	char buffer2 = 1;
	int Y_POS = 85;
	while(menu_loop)
	{
		clearevents();
		dclear(C_WHITE);
		dimage(0,0,&img_menu);
		selection += keydown(KEY_DOWN) - keydown(KEY_UP);
		if (selection == 4) selection = 0;
		else if (selection == -1) selection = 3;
		dtext(32, Y_POS, C_BLACK, "PLAY");
		dtext(32, Y_POS + 12, C_BLACK, "SPEEDRUN MODE");
		dtext(32, Y_POS + 24, C_BLACK, "CONTROL");
		dtext(32, Y_POS + 36, C_BLACK, "EXIT GAME");
		dtext(16, Y_POS + (selection * 12), C_BLACK, ">");
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			if(!buffer2) return selection;
		}
		else buffer2 = 0;
		if(keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if(!buffer) return -1;
		}
		else buffer = 0;
		while (keydown_any(KEY_UP, KEY_DOWN, 0)) clearevents();
	}
	return selection;
}

char speed_menu(int *id_level)
{
	char level[351];
	char gravity = 0; //0 down 1 up
	int start_x;
	int start_y;
	
	int appear = 10;
	int disappear = 13;
	
	char menu_loop = 1;
	char check = 1;
	extern bopti_image_t img_speedrun;
	
	while(menu_loop)
	{
		clearevents();
		dclear(C_WHITE);
		*id_level += keydown(KEY_RIGHT) - keydown(KEY_LEFT);
		if (*id_level == 16) *id_level = 1;
		else if (*id_level == 0) *id_level = 15;
		set_level(*id_level, level, &start_x, &start_y, &gravity, &appear, &disappear);
		draw_level(level);
		dimage(0,0,&img_speedrun);
		dtext(340, 214, C_BLACK, "TIME");
		dtext(190, 45, C_BLACK, "Time : ");
		dprint(80,20,C_BLACK,"Level : %d",*id_level);
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0))
		{
			if(!check)
			{
				del_level(level);
				return 0;
			}
		}
		else check = 0;
		if (keydown(KEY_F6))
		{
			draw_time(*id_level);
		}
		if (keydown(KEY_POWER))
		{
			*id_level=0;
			del_level(level);
			return 0;
		}
		if(keydown_any(KEY_EXIT, KEY_MENU, 0)) return 1;
		while (keydown_any(KEY_RIGHT, KEY_LEFT, 0)) clearevents();
	}
	return 0;
}
