#include "times.h"
#include "define.h"
#include <gint/display.h>
#include <gint/clock.h>
#include <gint/keyboard.h>

extern bopti_image_t img_bronze;
extern bopti_image_t img_argent;
extern bopti_image_t img_or;
extern bopti_image_t img_createur;

void check_medal(unsigned int frame_level, int id_level)
{
	int time=1, time2=1;
	switch(id_level)
	{
		case 1:
			time = 5;
			time2 = 60;
			break;
		case 2:
			time = 8;
			time2 = 13;
			break;
		case 3:
			time = 6;
			time2 = 12;
			break;
		case 4:
			time = 8;
			time2 = 57;
			break;
		case 5:
			time = 4;
			time2 = 15;
			break;
		case 6:
			time = 3;
			time2 = 62;
			break;
		case 7:
			time = 8;
			time2 = 25;
			break;
		case 8:
			time = 7;
			time2 = 62;
			break;	
				
	}
	if(frame_level/FPS < (unsigned int)time || (frame_level/FPS <= (unsigned int)time && frame_level%FPS <= (unsigned int)time2)) dimage(380,8,&img_createur);
	if(time2*2.5>=100) 
	{ 
		if(frame_level/FPS < (unsigned int)(time*1.05+0.5+1) || (frame_level/FPS <= (unsigned int)(time*1.05+0.5+1) && frame_level%FPS <= (unsigned int)(time2*2.5+0.5-100))) dimage(360,8,&img_or);
	}
	else if(frame_level/FPS < (unsigned int)(time*1.05+0.5) || (frame_level/FPS <= (unsigned int)(time*1.05+0.5) && frame_level%FPS <= (unsigned int)(time2*2.5+0.5))) dimage(360,8,&img_or);
	if(time2*1.2>=100) 
	{
		if(frame_level/FPS < (unsigned int)(time*1.2+0.5)+1 || (frame_level/FPS <= (unsigned int)(time*1.2+0.5)+1 && frame_level%FPS <= (unsigned int)(time2*1.2+0.5)-100)) dimage(340,8,&img_argent);
	}
	else if(frame_level/FPS < (unsigned int)(time*1.2+0.5) || (frame_level/FPS <= (unsigned int)(time*1.2+0.5) && frame_level%FPS <= (unsigned int)(time2*1.2+0.5))) dimage(340,8,&img_argent);
	if(time2*1.5>=100) 
	{
		if(frame_level/FPS < (unsigned int)(time*1.5+0.5)+1 || (frame_level/FPS <= (unsigned int)(time*1.5+0.5)+1 && frame_level%FPS <= (unsigned int)(time2*1.5+0.5)-100)) dimage(320,8,&img_bronze);
	}
	else if(frame_level/FPS < (unsigned int)(time*1.5+0.5) || (frame_level/FPS <= (unsigned int)(time*1.5+0.5) && frame_level%FPS <= (unsigned int)(time2*1.5+0.5))) dimage(320,8,&img_bronze);
	
}

void draw_time(int id_level)
{
	dclear(C_WHITE);
	int time=1, time2=1;
	switch(id_level)
	{
		case 1:
			time = 5;
			time2 = 60;
			break;
		case 2:
			time = 8;
			time2 = 13;
			break;
		case 3:
			time = 6;
			time2 = 12;
			break;
		case 4:
			time = 8;
			time2 = 57;
			break;
		case 5:
			time = 4;
			time2 = 15;
			break;
		case 6:
			time = 3;
			time2 = 62;
			break;	
		case 7:
			time = 8;
			time2 = 25;
			break;	
		case 8:
			time = 7;
			time2 = 62;
			break;	
	}
	dimage(160,90,&img_createur); 
	dprint(175,90,C_BLACK,"%d.%02d",time,time2);
	dimage(160,110,&img_or);
	if(time2*2.5>=100) dprint(175,110,C_BLACK,"%d.%02d",(int)(time*1.05+0.5)+1, (int)(time2*2.5+0.5)-100);
	else dprint(175,110,C_BLACK,"%d.%02d",(int)(time*1.05+0.5), (int)(time2*2.5+0.5));
	dimage(160,130,&img_argent); 
	if(time2*1.2>=100) dprint(175,110,C_BLACK,"%d.%02d",(int)(time*1.05+0.5)+1, (int)(time2*1.2+0.5)-100);
	else dprint(175,130,C_BLACK,"%d.%02d",(int)(time*1.2+0.5), (int)(time2*1.2+0.5));
	dimage(160,150,&img_bronze); 
	if(time2*1.5>=100) dprint(175,110,C_BLACK,"%d.%02d",(int)(time*1.05+0.5)+1, (int)(time2*1.5+0.5)-100);
	else dprint(175,150,C_BLACK,"%d.%02d",(int)(time*1.5+0.5), (int)(time2*1.5+0.5));
	dupdate();
	getkey();
}
