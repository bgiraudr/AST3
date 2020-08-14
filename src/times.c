#include "times.h"
#include "define.h"
#include <gint/display.h>
#include <gint/keyboard.h>

extern bopti_image_t img_bronze;
extern bopti_image_t img_argent;
extern bopti_image_t img_or;
extern bopti_image_t img_createur;

void check_medal(unsigned int frame_level, int id_level)
{
float time=1.0;
float framefloat = frame_level;
switch(id_level)
{
	case 1:
        time = 5.88;
        break;
	case 2:
        time = 8.31;
        break;
	case 3:
        time = 6.12;
        break;
	case 4:
        time = 8.72;
        break;
	case 5:
        time = 3.92;
        break;
	case 6:
        time = 3.51;
        break;
	case 7:
        time = 6.76;
        break;
	case 8:
        time = 7.48;
        break;
	case 9:
        time = 12.26;
        break;
}

if(frame_level/FPS < (unsigned int)time || (frame_level/FPS <= (unsigned int)time && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time)*100-(int)(time)*100))) dimage(380,8,&img_createur);
if(frame_level/FPS < (unsigned int)(time*1.1) || (frame_level/FPS <= (unsigned int)(time*1.1) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.1)*100-(int)(time*1.1)*100))) dimage(360,8,&img_or);
if(frame_level/FPS < (unsigned int)(time*1.2) || (frame_level/FPS <= (unsigned int)(time*1.2) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.2)*100-(int)(time*1.2)*100))) dimage(340,8,&img_argent);
if(frame_level/FPS < (unsigned int)(time*1.5) || (frame_level/FPS <= (unsigned int)(time*1.5) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.1)*100-(int)(time*1.1)*100))) dimage(320,8,&img_bronze);
}

void draw_time(int id_level)
{
dclear(C_WHITE);
float time=1.0;
switch(id_level)
{
	case 1:
        time = 5.88;
        break;
	case 2:
        time = 8.31;
        break;
	case 3:
        time = 6.12;
        break;
	case 4:
        time = 8.72;
        break;
	case 5:
        time = 3.92;
        break;
	case 6:
        time = 3.51;
        break;
	case 7:
        time = 6.76;
        break;
	case 8:
        time = 7.48;
        break;
	case 9:
        time = 12.26;
        break;
}
dimage(160,90,&img_createur);
dprint(175,90,C_BLACK,"%d.%02d",(int)(time),(int)((time)*100-(int)(time)*100));
dimage(160,110,&img_or);
dprint(175,110,C_BLACK,"%d.%02d",(int)(time*1.1),(int)((time*1.1)*100-(int)(time*1.1)*100));
dimage(160,130,&img_argent); 
dprint(175,130,C_BLACK,"%d.%02d",(int)(time*1.2),(int)((time*1.2)*100-(int)(time*1.2)*100));
dimage(160,150,&img_bronze); 
dprint(175,150,C_BLACK,"%d.%02d",(int)(time*1.5),(int)((time*1.5)*100-(int)(time*1.5)*100));
dupdate();
getkey();
}