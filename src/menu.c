#include "menu.h"
#include "define.h"
#include "util.h"
#include "drawlevel.h"
#include "save.h"
#include "setlevel.h"
#include "times.h"
#include <gint/display.h>
#include <gint/gint.h>
#include <gint/keyboard.h>

enum MenuCode start_menu(char *type)
{
	extern bopti_image_t img_menu;
	char menu_loop = 1;
	char selection = 0;
	char buffer = 1;
	char buffer2 = 1;
	int Y_POS = 85;
	while (menu_loop) {
		clearevents();
		dclear(C_WHITE);
		dimage(0, 0, &img_menu);
		selection += keydown(KEY_DOWN) - keydown(KEY_UP);
		if (selection == 4)
			selection = 0;
		else if (selection == -1)
			selection = 3;
		dtext(32, Y_POS, C_BLACK, "PLAY");
		dtext(32, Y_POS + 12, C_BLACK, "ALL MODE");
		dtext(32, Y_POS + 24, C_BLACK, "TEST LEVEL");
		dtext(32, Y_POS + 36, C_BLACK, "EXIT GAME");
		dtext(16, Y_POS + (selection * 12), C_BLACK, ">");
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			if (!buffer2)
				return selection;
		} else
			buffer2 = 0;
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if (!buffer)
				return 3;
		} else
			buffer = 0;
		if (keydown_all(KEY_5, KEY_6))
			*type = 3;
		while (keydown_any(KEY_UP, KEY_DOWN, 0))
			clearevents();
	}
	return selection;
}

char speed_menu(int *id_level)
{
	char level[351];
	char gravity = 0; // 0 down 1 up
	int start_x;
	int start_y;
	char buffer = 1;
	int appear = 10;
	int disappear = 13;
	int nbswitch = 0;
	int sto = loadtime(*id_level - 1);
	char menu_loop = 1;
	char check = 1;
	extern bopti_image_t img_speedrun;

	while (menu_loop) {
		clearevents();
		dclear(C_WHITE);
		*id_level += keydown(KEY_RIGHT) - keydown(KEY_LEFT);
		if (*id_level == LEVEL_MAX + 1)
			*id_level = 1;
		else if (*id_level == 0)
			*id_level = LEVEL_MAX;
		if (keydown(KEY_RIGHT) || keydown(KEY_LEFT))
			sto = loadtime(*id_level - 1);
		set_level(*id_level, level, &start_x, &start_y, &gravity,
		          &appear, &disappear, &nbswitch);
		draw_level(level);
		dimage(0, 0, &img_speedrun);
		if (sto != 0)
			check_medal(round(sto * 0.01 * FPS), *id_level, 335, 8);
		dtext(340, 214, C_BLACK, "TIMES");
		dtext(190, 45, C_BLACK, "Time : ");
		dprint(80, 20, C_BLACK, "Level : %d", *id_level);
		if (sto != 0)
			dprint(194, 60, C_RED, "%.2j", sto);
		else
			dprint(202, 60, C_RED, "/");
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			if (!check) {
				del_level(level);
				return 0;
			}
		} else
			check = 0;
		if (keydown(KEY_F6)) {
			draw_time(*id_level);
		}
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if (!buffer)
				return 1;
		} else
			buffer = 0;
		while (keydown_any(KEY_RIGHT, KEY_LEFT, 0))
			clearevents();
	}
	return 0;
}

