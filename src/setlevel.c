#include "setlevel.h"
#include <gint/std/string.h>

void set_level(int id_level, char level[])
{
	switch(id_level)
	{
		case 1:
			memcpy(level,"11111111111111111111111111000000000000000000000001100000000000000000000002110000000000000000000000011000000000000000000000001100000000000000000000000110000000000000000000000011000000000000000000000001100000000000000000000000110000000000000000000000011000000000000000000000001100000000000000000000000110000000000000000000000011111111111111111111111111",350);
			break;
		case 2:
			memcpy(level,"000001110",350);
			break;
	}
}
