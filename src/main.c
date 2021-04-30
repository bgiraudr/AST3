#include <gint/clock.h>
#include <gint/display.h>
#include <gint/gint.h>
#include <gint/keyboard.h>
#include <gint/std/string.h>
#include <gint/timer.h>

#include "collide.h"
#include "define.h"
#include "drawlevel.h"
#include "menu.h"
#include "save.h"
#include "setlevel.h"
#include "times.h"

#define VACCELERATION 0.2
#define HACCELERATION 0.4
#define MAX_VSPD 9.0
#define FRICTION 0.2

int main(void);
void end(unsigned int frame);

char run = 0;

int callback(volatile int *frame_elapsed)
{
	*frame_elapsed = 1;
	return TIMER_CONTINUE;
}

void game(int *id_level, char mode, char *type)
{
	volatile int frame_elapsed = 1;
	int timer = timer_configure(TIMER_ANY, 1000000 / FPS,
	                            GINT_CALL(callback, &frame_elapsed));
	timer_start(timer);

	char game_loop = 1;
	unsigned int frame = 0;
	int framelevel = 0;
	int player_x = 20, player_y = 20;
	char level[351];
	char gravity = 0; // 0 down 1 up
	char check = 1;
	char blackout = 0;
	int start_x;
	int start_y;
	int death_count = 0;

	int coin = 0;
	char check_coin = 0;
	char double_check = 1;
	char chock = 0;

	int appear = 10;
	int disappear = 13;
	int nbswitch = 0;

	char check_nbswitch = 0;
	float vspd = 1.0;
	float hspd = 0.0;
	if (*id_level == 10 && *type != 3)
		*type = 2;
	else if (*type != 3)
		*type = 1;
	extern bopti_image_t img_speedrun;
	set_level(*id_level, level, &start_x, &start_y, &gravity, &appear,
	          &disappear, &nbswitch);
	player_x = start_x;
	player_y = start_y;
	draw_level(level);
	while (game_loop) {
		while (!frame_elapsed)
			sleep();
		frame_elapsed = 0;

		frame++;
		framelevel++;
		if (!(frame % 2)) {
			draw_level(level);
			if (blackout)
				draw_blackout(player_x, player_y);

			if (blackout && *id_level == 0) {
				dtext(20, 20, C_WHITE,
				      "You have touched the blackout item");
				dtext(20, 40, C_WHITE,
				      "it makes you partially blind");
				dtext(20, 60, C_WHITE, "until your death :p");
			}
			if (chock > 0 && *id_level == 0) {
				dtext(20, 165, C_BLACK,
				      "You have touched the chock");
				dtext(20, 180, C_BLACK,
				      "item. It rotates your screen");
				dtext(20, 195, C_BLACK,
				      "horizontally and vertically");
			}

			draw_player(player_x, player_y, *type);
			if (!mode)
				draw_timer(frame);
			else
				draw_timer(framelevel);

			if (!mode)
				dprint_opt(330, 0, C_RGB(255, 190, 0), C_BLACK,
				           DTEXT_LEFT, DTEXT_TOP, "Coin : %d",
				           coin);
			if (check_nbswitch)
				draw_nbswitch(nbswitch);
			dupdate();
		}

		pollevent();

		if (keydown(KEY_OPTN)) {
			level[((player_x + 6) / 16) +
			      ((player_y + 6) / 16) * 25] = 'd';
			death_count--;
		}
		// Right collision
		if (keydown(KEY_RIGHT)) {
			hspd *= 1 - FRICTION;
			hspd += (keydown(KEY_RIGHT) - keydown(KEY_LEFT)) *
				HACCELERATION;
			if (!collide_solid(player_x + round(hspd) + 1, player_y,
			                   level))
				player_x += round(hspd);
			else if (!collide_solid(player_x + 1, player_y, level))
				player_x += 1;
			if (player_x >= 388)
				player_x = -4;
		}
		// Left collision
		else if (keydown(KEY_LEFT)) {
			hspd *= 1 - FRICTION;
			hspd += (keydown(KEY_RIGHT) - keydown(KEY_LEFT)) *
				HACCELERATION;
			if (!collide_solid(player_x + round(hspd) - 1, player_y,
			                   level))
				player_x += round(hspd);
			else if (!collide_solid(player_x - 1, player_y, level))
				player_x -= 1;
			if (player_x < -9)
				player_x = 384;
		} else
			hspd = 0;
		// Action key
		if (keydown(KEY_SHIFT) && !check &&
		    (nbswitch > 0 || nbswitch == -1) &&
		    ((collide_solid(player_x, player_y - 1, level) &&
		      gravity) ||
		     (collide_solid(player_x, player_y + 1, level) &&
		      !gravity))) {
			vspd = 1;
			if (!gravity)
				gravity = 1;
			else
				gravity = 0;
			if (check_nbswitch && nbswitch != 0) {
				nbswitch -= 1;
			}
			check = 1;
		} else if (!keydown(KEY_SHIFT) && check)
			check = 0;
		// Gravity
		if (!gravity) {
			if (!collide_solid(player_x, player_y + (int)vspd + 1,
			                   level)) {
				if (vspd < MAX_VSPD)
					vspd += VACCELERATION;
				if (collide(player_x + 1, player_y, level, 'i'))
					vspd += 0.15;
				if (collide(player_x - 1, player_y, level, 'i'))
					vspd += 0.15;
				player_y += (int)vspd;
			} else if (!collide_solid(
				       player_x, player_y + (int)vspd, level)) {
				vspd -= VACCELERATION;
				player_y += (int)vspd;
			} else if (!collide_solid(player_x, player_y + 1,
			                          level)) {
				vspd = 1;
				player_y += 1;
			} else
				vspd = 1;
		} else {
			if (!collide_solid(player_x, player_y - (int)vspd - 1,
			                   level)) {
				if (vspd < MAX_VSPD)
					vspd += VACCELERATION;
				if (collide(player_x + 1, player_y, level, 'i'))
					vspd += 0.15;
				if (collide(player_x - 1, player_y, level, 'i'))
					vspd += 0.15;
				player_y -= (int)vspd;
			} else if (!collide_solid(
				       player_x, player_y - (int)vspd, level)) {
				vspd -= VACCELERATION;
				player_y -= (int)vspd;
			} else if (!collide_solid(player_x, player_y - 1,
			                          level)) {
				vspd = 1;
				player_y -= 1;
			} else
				vspd = 1;
		}
		// Collide with red block
		if (collide_dead(player_x, player_y, level)) {
			vspd = 1;
			player_x = start_x;
			player_y = start_y;
			if (check_coin)
				coin--;
			check_coin = 0;
			set_level(*id_level, level, &start_x, &start_y,
			          &gravity, &appear, &disappear, &nbswitch);
			blackout = 0;
			check_nbswitch = 0;
			death_count++;
			double_check = 1;
			framelevel = 0;
			if (*id_level == 1 && !mode)
				frame = 0;
		}
		// Collide with the end
		if (collide_end(player_x, player_y, level)) {
			if (!mode && *id_level != 0)
				*id_level += 1;
			else
				break;
			check_coin = 0;
			set_level(*id_level, level, &start_x, &start_y,
			          &gravity, &appear, &disappear, &nbswitch);
			player_x = start_x;
			player_y = start_y;
			blackout = 0;
			double_check = 1;
			framelevel = 0;
			if (*id_level == 10 && *type == 1)
				*type = 2;
			else if (*type != 3)
				*type = 1;
			if (*id_level == LEVEL_MAX + 1) {
				timer_stop(timer);
				end(frame);
			}
		}
		if (collide(player_x, player_y, level,
		            'k')) // Collide with key1 = disappearance of blocks
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == '3')
					level[i] = '0';
				if (level[i] == 'k')
					level[i] = '0';
			}
		}
		if (collide(player_x, player_y, level,
		            'K')) // Collide with key2 = appearance of blocks
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 'a')
					level[i] = '4';
				if (level[i] == 'K')
					level[i] = '0';
			}
		}
		if (collide(player_x, player_y, level, 't') &&
		    !check_coin) // Collide with coin
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 't') {
					level[i] = '0';
					break;
				}
			}
			check_coin = 1;
			coin++;
		}
		if (collide(player_x, player_y, level,
		            'b')) // Collide with blackout block
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 'b') {
					level[i] = '0';
					break;
				}
			}
			blackout = 1;
		}
		if (collide(player_x, player_y, level,
		            'z')) // Collide with nbswitch block
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 'z') {
					level[i] = '0';
				}
			}
			check_nbswitch = 1;
		}
		if (level[((player_x + 6) / 16) + ((player_y + 6) / 16) * 25] ==
		    'l') // Collide with change block
		{
			int x = 0;
			int y = 0;
			char level2[351] = {0};
			int j = 0;
			level[((player_x + 6) / 16) +
			      ((player_y + 6) / 16) * 25] = 'P';
			for (int i = 349; i != -1; i--) {
				level2[j] = level[i];
				j++;
			}
			del_level(level);
			strncpy(level, level2, 351);
			del_level(level2);
			int i = 0;
			while (i != 350) {
				switch (level[i]) {
				case 'P':
					player_x = x;
					player_y = y;
					level[i] = '0';
					break;
				}
				x += 16;
				if (x == 16 * 25) {
					x = 0;
					y += 16;
				}
				i++;
			}
			if (!gravity)
				gravity = 1;
			else
				gravity = 0;
			chock++;
		}

		if (collide(player_x, player_y + (int)vspd + 2, level, 'B') &&
		    vspd >= 5) // Damaged block
		{
			if (level[((player_x) / 16) +
			          ((player_y + 25) / 16) * 25] == 'B')
				level[((player_x) / 16) +
				      ((player_y + 25) / 16) * 25] = '0';
			if (level[((player_x + 12) / 16) +
			          ((player_y + 25) / 16) * 25] == 'B' &&
			    collide_point(player_x + 12, player_y + 22, level,
			                  'B'))
				level[((player_x + 12) / 16) +
				      ((player_y + 25) / 16) * 25] = '0';
			vspd = 1.0;
		}
		if (collide(player_x, player_y - (int)vspd - 2, level, 'B') &&
		    vspd >= 5) // Damaged block
		{
			if (level[((player_x) / 16) +
			          ((player_y - (int)vspd - 2) / 16) * 25] ==
			    'B')
				level[((player_x) / 16) +
				      ((player_y - (int)vspd - 2) / 16) * 25] =
				    '0';
			if (level[((player_x + 12) / 16) +
			          ((player_y - (int)vspd - 2) / 16) * 25] ==
			        'B' &&
			    collide_point(player_x + 12, player_y - 12, level,
			                  'B'))
				level[((player_x + 12) / 16) +
				      ((player_y - (int)vspd - 2) / 16) * 25] =
				    '0';
			vspd = 1.0;
		}

		collide_replace(player_x, player_y, level, 'h',
		                'y'); // Appear block
		if (!collide(player_x, player_y, level, 'y') &&
		    double_check) // Appear block
		{
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 'y') {
					double_check = 1;
					break;
				} else if (level[i] == 'h') {
					double_check = 1;
					break;
				} else
					double_check =
					    0; // This loop is executed only
					       // when an h or y is on the level
			}
			for (int i = 0; level[i] != '\0'; ++i) {
				if (level[i] == 'y') {
					level[i] = 'H';
				}
			}
		}
		if (level[((player_x + 6) / 16) + ((player_y + 6) / 16) * 25] ==
		    'S') // Switch block
		{
			level[((player_x + 6) / 16) +
			      ((player_y + 6) / 16) * 25] = '0';
			vspd = 1.0;
			if (!gravity)
				gravity = 1;
			else
				gravity = 0;
		}

		if ((framelevel / FPS) > disappear)
			for (int i = 0; level[i] != '\0'; i++)
				if (level[i] == 'c')
					level[i] = '0'; // after x seconds
					                // blocks disappear
		if ((framelevel / FPS) > appear)
			for (int i = 0; level[i] != '\0'; i++)
				if (level[i] == 'm')
					level[i] = 'C'; // after x seconds
					                // blocks appear

		if (player_y >= 212)
			player_y = -4;
		if (player_y < -6)
			player_y = 212;

		// Menu
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			char menu_loop = 1;
			char selected = 0;
			int Y_POS = 18;
			char buffer = 1;
			while (menu_loop) {
				clearevents();
				dclear(C_WHITE);
				draw_level(level);
				draw_player(player_x, player_y, *type);
				dimage(0, 0, &img_speedrun);
				selected += keydown(KEY_DOWN) - keydown(KEY_UP);
				if (selected == 2)
					selected = 0;
				else if (selected == -1)
					selected = 1;
				dtext(32, Y_POS, C_BLACK, "CONTINUE");
				if (!mode)
					dtext(32, Y_POS + 12, C_BLACK, "MENU");
				else
					dtext(32, Y_POS + 12, C_BLACK,
					      "SPEEDRUN MENU");
				dtext(16, Y_POS + (selected * 12), C_BLACK,
				      ">");
				dprint(180, 45, C_RGB(83, 255, 0), "LEVEL : %d",
				       *id_level);
				dprint(320, 3, C_RGB(255, 178, 0), "COIN : %d",
				       coin);
				dprint(311, 17, C_RGB(150, 16, 16),
				       "DEATH : %d", death_count);
				dupdate();
				if (keydown_any(KEY_SHIFT, KEY_EXE, 0)) {
					switch (selected) {
					case 0:
						menu_loop = 0;
						break;
					case 1:
						menu_loop = 0;
						game_loop = 0;
						break;
					}
				}
				if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
					if (!buffer) {
						menu_loop = 0;
						game_loop = 0;
						break;
					}
				} else
					buffer = 0;
				while (keydown_any(KEY_UP, KEY_DOWN, 0))
					clearevents();
			}
		}
	}
	timer_stop(timer);
	// when a level is quit
	if (mode) {
		if (*id_level == 0) {
			game_loop = 0;
			draw_end(framelevel, *id_level, 0);
			sleep_ms(2500);
			*id_level = 1;
		}
		if (game_loop) // end of a level with level selection
		{
			float framefloat = framelevel;
			draw_end(framelevel, *id_level, 0);
			savetime(framefloat, *id_level);
			sleep_ms(2500);
		}
		if (!speed_menu(id_level)) {
			mode = 1;
			death_count = 0;
			game(id_level, mode, type);
		} else
			main();
	} else
		main();
}

void end(unsigned int frame)
{
	draw_end((int)frame, 15, 2);
	sleep_ms(7000);
	main();
}

int main(void)
{
	if (!run) {
		gint_world_switch(GINT_CALL(restore));
		run = 1;
	}
	char mode = 0;
	char type = 1;
	char valeur = start_menu(&type);
	if (!valeur) // normal game (level selection)
	{
		int id_level = 1;
		if (!speed_menu(&id_level)) {
			mode = 1;
			game(&id_level, mode, &type);
		} else
			main();
	} else if (valeur == 1) // all mode
	{
		int id_level = 1;
		mode = 0;
		game(&id_level, mode, &type);
	} else if (valeur == 2) // tutorial
	{
		int id_level = 0;
		mode = 1;
		game(&id_level, mode, &type);
	} else if (valeur == 3) // exit
		gint_world_switch(GINT_CALL(savefile));
	return 0;
}
