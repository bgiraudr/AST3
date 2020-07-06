#include "setlevel.h"
#include <gint/std/string.h>

/*How to add your level ? 

You must to copy + paste your level info into the switch(id_level) The number after "case" correspond to the number of your level
Then you must to set the default gravity into the function set_gravity() like the previous one. 0 down and 1 is up.
*/

void set_level(int id_level, char level[], int *startx, int *starty, char *gravity, char check_coin)
{
	switch(id_level)
	{
		case 1:
		memcpy(level,"10001011111011111111111111000101dd10001111dddd11110000101dd100010000000000011111m1dd1aaa1000ccccddd110s00010013331000000000011dddd110010001000dd00000100000000010e01000dd00000011111100011111dddddddd1111k000000010000111001111111111111101000000000111111000010000100000000000000010K010000100011100000011110t0100001000111000ddd1111000101111101111111111111",350);
			break;
		case 2:
			memcpy(level,"111001111111100d0d0011111100000111ddd000d0d0000001100000000000000dtd00000e1111111ddd111111111111111100000000000000000000d0000111111111dd111110100d000110001100000000010100d0001000011000000000d0d00d0000000000000000000d0d00d00001111dd111000000d0d00111111000011111ddd00d0d00111111000011111ddd00d0d001111110s0011111ddd00d0d0011111111001111111100d0d0011111",350);
			break;
		case 3:
			memcpy(level,"11010011111011111111111111101001dd10001111dddd11110001001dd10001000000000001111001dd100010001111ddd110s00010010001000000000011dddd110010001000dd00000100000000010e01000dd00000011111100011111dddddddd1111ddddd00010000111001111111111111101000000000111111000100000100000000000000011010000010001110000001111101000001000111000ddd1111101001111101111111111111",350);
			break;
	}
	
	if(check_coin) for (int i = 0; level[i]!='\0' ; i++) if(level[i]=='t') level[i]='0';
	
	set_gravity(id_level, gravity);
	
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int i = 0;
	while (i!=strlen(level))
	{
		switch(level[i])
		{
			case 's':
				*startx = x;
				*starty = y;
				break;
		}
		x+=16;
		if(x==16*25)
		{
			x=0;
			y+=16;
		}
		i++;
	}
}

void set_gravity(int id_level, char *default_gravity)
{
	switch(id_level)
	{
		case 1:
			*default_gravity = 1; //0 down - 1 up
			break;
		case 2:
			*default_gravity = 0; //0 down - 1 up
			break;
		case 3:
			*default_gravity = 1; //0 down - 1 up
			break;
	}
}
