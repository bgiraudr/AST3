#include "times.h"
#include <gint/display.h>

extern bopti_image_t img_medals;

extern float level_time[];

void draw_time(int id_level)
{
	static const float medal_multiplier[4] = {1.0, 1.2, 1.5, 2};
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
