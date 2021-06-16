/*
 * @author : Tituya x KikooDX
 */

#include <gint/clock.h>
#include <gint/display.h>
#include <gint/gint.h>
#include <gint/keyboard.h>
#include <gint/rtc.h>
#include <gint/std/stdlib.h>
#include <gint/std/string.h>
#include <gint/timer.h>
#include <gint/usb-ff-bulk.h>

#include "collide.h"
#include "define.h"
#include "drawlevel.h"
#include "friction.h"
#include "menu.h"
#include "replace.h"
#include "save.h"
#include "setlevel.h"
#include "times.h"
#include "util.h"

#define VACCELERATION 0.2
#define MAX_VSPD 9.0

static void startmenu_launcher();
static int callback(volatile int *frame_elapsed);
static void game(int *id_level, char mode, char *type);

int main(void)
{
	/* open USB for fxlink screenshots */
	usb_interface_t const *interfaces[] = {&usb_ff_bulk, NULL};
	usb_open(interfaces, GINT_CALL_NULL);

	gint_world_switch(GINT_CALL(restore));
	srand(rtc_ticks());

	startmenu_launcher();
	gint_world_switch(GINT_CALL(savefile));

	/* close USB */
	usb_close();
	return 0;
}

static void startmenu_launcher()
{
	char type = 1;
	int menu_run = 1;
	int id_level = 1;
	while (menu_run) {
		const enum MenuCode valeur = start_menu(&type);
		switch (valeur) {
		case MenuLevelSel: {
			if (id_level == 0)
				id_level = 1;
			int doIRun = level_selection(&id_level);
			if (doIRun)
				game(&id_level, 1, &type);
		} break;
		case MenuAllMode: {
			id_level = 1;
			game(&id_level, 0, &type);
		} break;
		case MenuTutorial: {
			id_level = 0;
			game(&id_level, 1, &type);
		} break;
		case MenuExit: {
			menu_run = 0;
		} break;
		}
	}
}

static int callback(volatile int *frame_elapsed)
{
	*frame_elapsed = 1;
	return TIMER_CONTINUE;
}

static void game(int *id_level, char mode, char *type)
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
	char gravity = -1; // 1 down -1 up
	char check = 1;
	char blackout = 0;
	int start_x;
	int start_y;
	int death_count = 0;

	char hasReachedEnd = 0;

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
	float hrem = 0.0;
	float friction;
	float acceleration;

	if (*id_level == 10 && *type != 3)
		*type = 2;
	else if (*type != 3)
		*type = 1;
	set_level(*id_level, level, &start_x, &start_y, &gravity, &appear,
	          &disappear, &nbswitch);
	player_x = start_x;
	player_y = start_y;

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
			dprint(330, 0, C_RED, "%d", collide_solid(player_x, player_y - 1, level));
			dprint(350, 0, C_RED, "%d", collide_solid(player_x, player_y + 1, level));
			dupdate();
			if (keydown(KEY_VARS) && usb_is_open())
				usb_fxlink_screenshot(1);
		}
		pollevent();

		if (keydown(KEY_OPTN)) {
			replace_xy_block(player_x + 6, player_y + 6, 'd',
			                 level);
			death_count--;
		}

		// right and left movement + collision
		int signe = (keydown(KEY_RIGHT) - keydown(KEY_LEFT));
		mod_accel_and_fric(&acceleration, &friction, player_x, player_y,
		                   level);

		hspd *= (1 - friction);
		hspd += signe * acceleration;

		/* speed reminder */
		const float spd_n_rem_x = hspd + hrem;
		const int spd_x = (int)spd_n_rem_x;
		hrem = spd_n_rem_x - (float)spd_x;

		player_x += spd_x;
		while (collide_solid(player_x, player_y, level)) {
			player_x -= sign(spd_x);
			hspd = 0;
			hrem = 0;
		}
		if (player_x >= 388)
			player_x = -4;
		if (player_x < -9)
			player_x = 384;

		// Action key
		if (keydown(KEY_SHIFT) && !check && nbswitch > 0 &&
		    (collide_solid_gravity(player_x, player_y - 1, level, gravity) ||
		     collide_solid_gravity(player_x, player_y + 1, level, gravity))) {
			vspd = 1;
			if (gravity == -1)
				gravity = 1;
			else
				gravity = -1;
			if (check_nbswitch && nbswitch > 0) {
				nbswitch -= 1;
			}
			check = 1;
		} else if (!keydown(KEY_SHIFT) && check)
			check = 0;

		// gravity
		if (!collide_solid(player_x,
		                   player_y + ((int)vspd) * gravity + gravity,
		                   level)) {
			if (vspd < MAX_VSPD)
				vspd += VACCELERATION;
			if (collide(player_x + 1, player_y, level, 'i') ||
			    collide(player_x - 1, player_y, level, 'i'))
				vspd += 0.15;
			player_y += ((int)vspd) * gravity;
		} else if (!collide_solid(player_x,
		                          player_y + ((int)vspd) * gravity,
		                          level)) {
			vspd -= VACCELERATION;
			player_y += ((int)vspd) * gravity;
		} else if (!collide_solid(player_x, player_y + gravity,
		                          level)) {
			vspd = 1;
			player_y += 1 * gravity;
		} else
			vspd = 1;

		// Collide with dead block
		if (collide_dead(player_x, player_y, level)) {
			vspd = 1;
			player_x = start_x;
			player_y = start_y;
			if (check_coin)
				coin--;
			check_coin = 0;
			blackout = 0;
			check_nbswitch = 0;
			death_count++;
			double_check = 1;
			framelevel = 0;
			hrem = 0.00;

			set_level(*id_level, level, &start_x, &start_y,
			          &gravity, &appear, &disappear, &nbswitch);
			if (*id_level == 1 && !mode)
				frame = 0;
		}
		// Collide with the end
		if (collide_end(player_x, player_y, level)) {
			// if all mode
			if (!mode) {
				*id_level += 1;
				check_coin = 0;
				check_nbswitch = 0;
				blackout = 0;
				double_check = 1;
				framelevel = 0;
				hrem = 0.00;

				set_level(*id_level, level, &start_x, &start_y,
				          &gravity, &appear, &disappear,
				          &nbswitch);
				player_x = start_x;
				player_y = start_y;

				if (*id_level == 10 && *type == 1)
					*type = 2;
				else if (*type != 3)
					*type = 1;
				// End of all mode
				if (*id_level == LEVEL_MAX + 1) {
					timer_stop(timer);
					game_loop = 0;
				}
			} else {
				game_loop = 0;
			}
			hasReachedEnd = 1;
		}
		// Collide with key1 = disappearance of blocks
		if (collide(player_x, player_y, level, 'k')) {
			replace_all_block('3', '0', level);
			replace_all_block('k', '0', level);
		}
		// Collide with key2 = appearance of blocks
		if (collide(player_x, player_y, level, 'K')) {
			replace_all_block('a', '4', level);
			replace_all_block('K', '0', level);
		}
		// Collide with coin
		if (collide(player_x, player_y, level, 't') && !check_coin) {
			replace_all_block('t', '0', level);
			check_coin = 1;
			coin++;
		}
		// Collide with blackout block
		if (collide(player_x, player_y, level, 'b')) {
			replace_all_block('b', '0', level);
			blackout = 1;
		}
		// Collide with nbswitch block
		if (collide(player_x, player_y, level, 'z')) {
			replace_all_block('z', '0', level);
			check_nbswitch = 1;
		}
		// Collide with change block
		if (collide_center(player_x, player_y, level, 'l')) {
			int x = 0;
			int y = 0;
			char level2[351] = {0};
			int j = 0;
			replace_xy_block(player_x + 6, player_y + 6, 'P',
			                 level);
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
				x += TILE_HEIGHT;
				if (x == TILE_HEIGHT * LEVEL_WIDTH) {
					x = 0;
					y += TILE_HEIGHT;
				}
				i++;
			}
			if (gravity == -1)
				gravity = 1;
			else
				gravity = -1;
			chock++;
		}

		// Damaged block
		if (collide(player_x, player_y + (int)vspd + 2, level, 'B') &&
		    vspd >= 5) {
			if (level[((player_x) / 16) +
			          ((player_y + 25) / 16) * 25] == 'B')
				replace_xy_block(player_x, player_y + 25, '0',
				                 level);

			if (level[((player_x + 12) / 16) +
			          ((player_y + 25) / 16) * 25] == 'B' &&
			    collide_point(player_x + 12, player_y + 22, level,
			                  'B'))
				replace_xy_block(player_x + 12, player_y + 25,
				                 '0', level);
			vspd = 1.0;
		}
		// Damaged block
		if (collide(player_x, player_y - (int)vspd - 2, level, 'B') &&
		    vspd >= 5) {
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

		// Appear block
		collide_replace(player_x, player_y, level, 'h', 'y');
		if (!collide(player_x, player_y, level, 'y') && double_check) {
			for (int i = 0; level[i] != '\0'; i++) {
				if (level[i] == 'y' || level[i] == 'h') {
					double_check = 1;
					break;
				} else
					double_check = 0;
			}
			replace_all_block('y', 'H', level);
		}

		// Switch block
		if (collide_center(player_x, player_y, level, 'S')) {
			replace_xy_block(player_x + 6, player_y + 6, '0',
			                 level);
			vspd = 1.0;
			if (gravity == -1)
				gravity = 1;
			else
				gravity = -1;
		}

		if ((framelevel / FPS) > disappear - 1) {
			replace_all_block('c', '0', level);
		}
		if ((framelevel / FPS) > appear - 1) {
			replace_all_block('m', 'C', level);
		}

		// warp
		if (player_y >= 210)
			player_y = -4;
		if (player_y < -6)
			player_y = 209;

		// Pause menu
		if (keydown_any(KEY_EXIT, KEY_MENU, 0)) {
			timer_pause(timer);
			const enum MenuPause valeur =
			    pause_menu(level, *id_level, coin, death_count);
			switch (valeur) {
			case MenuContinue: {
				timer_start(timer);
				check = 1; // prevent for switch when back to
				           // the level
			} break;
			case MenuBack: {
				game_loop = 0;
				hasReachedEnd = 0;
			} break;
			}
		}
	}
	timer_stop(timer);
	// when a level is quit

	// if level selection
	if (mode == 1 && *id_level != 0) {

		if (hasReachedEnd) {
			float framefloat = framelevel;
			draw_end(framelevel, *id_level, 0);
			savetime(framefloat, *id_level);
			sleep_ms(2500);
		}

		int doIRun = level_selection(id_level);
		if (doIRun)
			game(id_level, 1, type);
	} else if (mode == 0 && hasReachedEnd == 1) {
		draw_end((int)frame, LEVEL_MAX, 2);
		sleep_ms(7000);
	}
}
