#include "menu.h"
#include "define.h"
#include "util.h"
#include "drawlevel.h"
#include "save.h"
#include "setlevel.h"
#include "times.h"
#include "util.h"
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
	int Y_POS = 145;

	char level[351];
	int start_x;
	int start_y;

	set_level(rand_range(1,LEVEL_MAX), level, &start_x, &start_y, NULL,
		          NULL, NULL, NULL);
	while (menu_loop) {
		clearevents();
		dclear(C_WHITE);
		draw_level(level);
		dimage(0, 0, &img_menu);
		selection += keydown(KEY_DOWN) - keydown(KEY_UP);
		if (selection == 4)
			selection = 0;
		else if (selection == -1)
			selection = 3;
		dtext(160, Y_POS, C_WHITE, "PLAY");
		dtext(160, Y_POS + 12, C_WHITE, "ALL MODE");
		dtext(160, Y_POS + 24, C_WHITE, "TEST LEVEL");
		dtext(160, Y_POS + 36, C_WHITE, "EXIT GAME");
		dtext(145, Y_POS + (selection * 12), C_WHITE, ">");
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			if (!buffer2)
				return selection;
		} else
			buffer2 = 0;
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if (!buffer)
				return MenuExit;
		} else
			buffer = 0;
		if (keydown_all(KEY_5, KEY_6))
			*type = 3;
		while (keydown_any(KEY_UP, KEY_DOWN, 0))
			clearevents();
	}
	return MenuExit;
}

char level_selection(int *id_level)
{
	char level[351];
	int start_x;
	int start_y;
	char buffer = 1;
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
		set_level(*id_level, level, &start_x, &start_y, NULL,
		          NULL, NULL, NULL);
		draw_level(level);
		dimage(0, 0, &img_speedrun);
		if (sto != 0)
			check_medal(round(sto * 0.01 * FPS), *id_level, 335, 8);
		dtext(190, 45, C_BLACK, "Time : ");
		dprint(80, 20, C_BLACK, "Level : %d", *id_level);
		if (sto != 0)
			dprint(194, 60, C_RED, "%.2j", sto);
		else
			dprint(202, 60, C_RED, "/");
		draw_time(*id_level);
		dupdate();
		
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			if (!check) {
				del_level(level);
				return 1;
			}
		} else
			check = 0;

		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if (!buffer)
				return 0;
		} else
			buffer = 0;
		while (keydown_any(KEY_RIGHT, KEY_LEFT, 0))
			clearevents();
	}
	return 0;
}


enum MenuPause pause_menu(char level[], int id_level, int coin, int death_count) {

	extern bopti_image_t img_speedrun;

	char menu_loop = 1;
	char selected = 0;
	int Y_POS = 18;
	char buffer = 1;

	while (menu_loop) {
		clearevents();
		dclear(C_WHITE);
		draw_level(level);
		dimage(0, 0, &img_speedrun);
		selected += keydown(KEY_DOWN) - keydown(KEY_UP);
		if (selected == 2)
			selected = 0;
		else if (selected == -1)
			selected = 1;
		dtext(32, Y_POS, C_BLACK, "CONTINUE");
		dtext(32, Y_POS + 12, C_BLACK, "BACK");
		dtext(16, Y_POS + (selected * 12), C_BLACK,
		      ">");
		dprint(176, 45, C_BLACK, "LEVEL : %d",
		       id_level);
		dprint(320, 3, C_RGB(255, 178, 0), "COIN : %d",
		       coin);
		dprint(311, 17, C_RGB(150, 16, 16),
		       "DEATH : %d", death_count);
		draw_time(id_level);
		dupdate();
		if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
			return selected;
		}
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			if (!buffer) {
				return MenuBack;
			}
		} else
			buffer = 0;
		while (keydown_any(KEY_UP, KEY_DOWN, 0))
			clearevents();
	}
	return MenuBack;
}