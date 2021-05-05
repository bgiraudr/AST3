#include "define.h"
#include "times.h"
#include <gint/display.h>

extern bopti_image_t img_medals;

extern float level_time[];

static const float medal_multiplier[4] = {1.0, 1.2, 1.5, 2};

void check_medal(unsigned int frame_level, int id_level, int x, int y)
{
	const float time = level_time[id_level - 1];
	const int player_time = (int)((float)frame_level / FPS * 100.0);
	int i;

	/* OK, this doesn't have the exact same behavior than the previously
	 * generated code had. But the conditions were so dirty and hard to
	 * understand than I simplified it.
	 *         -- KikooDX */
	for (i = 0; i < 4; i += 1) {
		const int mtime = (int)(time * medal_multiplier[i] * 100.0);
		if (player_time <= mtime) {
			dsubimage(x + 15 * (3 - i), y, &img_medals,
			          12 * (3 - i), 0, 12, 12, DIMAGE_NONE);
		}
	}
}

void draw_time(int id_level)
{
	const float time = level_time[id_level - 1];
	int draw_y = 140;
	int medal_x = 36;
	int i;

	for (i = 0; i < 4; i += 1) {
		dsubimage(340, draw_y, &img_medals, medal_x, 0, 12, 12,
		          DIMAGE_NONE);
		dprint(355, draw_y + 1, C_BLACK, "%.2j",
		       (int)(time * medal_multiplier[i] * 100));
		draw_y += 20;
		medal_x -= 12;
	}
}
