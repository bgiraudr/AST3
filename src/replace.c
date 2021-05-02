#include "replace.h"

void replace_all_block(char a, char b, char level[]) {
	for (int i = 0; level[i] != '\0'; i++) {
		if (level[i] == a)
			level[i] = b;
	}
}

void replace_xy_block(int x, int y, char block, char level[]) {
	level[(x/16)+((y/16)*25)] = block;
}