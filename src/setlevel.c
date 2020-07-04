#include "setlevel.h"
#include <gint/std/string.h>

/*How to add your level ? 

You must to copy + paste your level info into the switch(id_level) The number after "case" correspond to the number of your level
Then you must to set the default gravity into the function set_gravity() like the previous one. 0 down and 1 is up.
*/

void set_level(int id_level, char level[], int *startx, int *starty, char *gravity)
{
	switch(id_level)
	{
		case 1:
		memcpy(level,"111111110011111111111111110000000000000300000000011000000000000030000000001100000000000003000000000110000000000000300000000e11000000000000k3000000mmm1112211aaaaaa113000000mcc1m00000dddddd0m0000000mc0mm000000000000m0000000mc0m1000000000000m0000000mcc11000000000000m0000000mmm11000000000000m0000000000110s0000K00000m000000000011111ddd10011111ddddd11111",350);
			break;
		case 2:
			memcpy(level,"1210011111111002110011122200000111ddd000111000000120000000000000011100000e1111111ddd111112211111121100000000000000000000d0000122111111dd111111200d000210002100000000011200d000200002100000000012100d000000000000000000011100d00001111dd11200000011100112222000011211ddd0021100111111000011111ddd00211001111110s0021111ddd0012100211111110021111111001110021111",350);
			break;
		case 3:
			memcpy(level,"11010011111011111111111111101001dd10001111dddd11110001001dd10001000000000001111001dd100010001111ddd110s00010010001000000000011dddd110010001000dd00000100000000010e01000dd00000011111100011111dddddddd1111ddddd00010000111001111111111111101000000000111111000100000100000000000000011010000010001110000001111101000001000111000ddd1111101001111101111111111111",350);
			break;
	}
	
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
			*default_gravity = 0; //0 down - 1 up
			break;
		case 2:
			*default_gravity = 0; //0 down - 1 up
			break;
		case 3:
			*default_gravity = 1; //0 down - 1 up
			break;
	}
}
