#include "replace.h"
#include "define.h"
#include <gint/keyboard.h>

void replace_all_block(char a, char b, char level[])
{
	for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++) {
		if (level[i] == a)
			level[i] = b;
	}
}

void replace_xy_block(int x, int y, char block, char level[])
{
	level[(x / TILE_HEIGHT) + ((y / TILE_HEIGHT) * LEVEL_WIDTH)] = block;
}