#include "times.h"
#include "define.h"
#include <gint/display.h>

extern bopti_image_t img_bronze;
extern bopti_image_t img_argent;
extern bopti_image_t img_or;
extern bopti_image_t img_createur;

void check_medal(unsigned int frame_level, int id_level)
{
	switch(id_level)
	{
		case 1:
		{
			unsigned int time = 6;
			unsigned int time2 = 5;
			if(frame_level/FPS < time || (frame_level/FPS <= time && frame_level%FPS <= time2)) dimage(380,8,&img_createur);
			if(frame_level/FPS < time*1.05 || (frame_level/FPS <= time*1.05 && frame_level%FPS <= time2*1.05)) dimage(360,8,&img_or);
			if(frame_level/FPS < time*1.2 || (frame_level/FPS <= time*1.2 && frame_level%FPS <= time2*1.2)) dimage(340,8,&img_argent);
			if(frame_level/FPS < time*1.5|| (frame_level/FPS <= time*1.5 && frame_level%FPS <= time2*1.5)) dimage(320,8,&img_bronze);
			break;
		}
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;		
	}
}
