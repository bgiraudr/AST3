#include "times.h"
#include "define.h"
#include <gint/display.h>
#include <gint/keyboard.h>

extern bopti_image_t img_medals;
void check_medal(unsigned int frame_level, int id_level, int x, int y)
{
float time=1.0;
float framefloat = frame_level;
float level_time[] = {5.80,8.62,5.14,3.22,3.25,8.20,6.60,7.18,9.20,5.22,6.04,10.38,5.34,7.61,6.05};
time = level_time[id_level-1];

if(frame_level/FPS < (unsigned int)time || (frame_level/FPS <= (unsigned int)time && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time)*100-(int)(time)*100))) dsubimage(x+45,y,&img_medals,36,0,12,12,DIMAGE_NONE);
if(frame_level/FPS < (unsigned int)(time*1.2) || (frame_level/FPS <= (unsigned int)(time*1.2) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.2)*100-(int)(time*1.2)*100))) dsubimage(x+30,y,&img_medals,24,0,12,12,DIMAGE_NONE);
if(frame_level/FPS < (unsigned int)(time*1.5) || (frame_level/FPS <= (unsigned int)(time*1.5) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.5)*100-(int)(time*1.5)*100))) dsubimage(x+15,y,&img_medals,12,0,12,12,DIMAGE_NONE);
if(frame_level/FPS < (unsigned int)(time*2) || (frame_level/FPS <= (unsigned int)(time*2) && 
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*2)*100-(int)(time*2)*100))) dsubimage(x,y,&img_medals,0,0,12,12,DIMAGE_NONE);
}

void draw_time(int id_level)
{
dclear(C_WHITE);
float time=1.0;
float level_time[] = {5.80,8.62,5.14,3.22,3.25,8.20,6.60,7.18,9.20,5.22,6.04,10.38,5.34,7.61,6.05};
time = level_time[id_level-1];

dsubimage(172,90,&img_medals,36,0,12,12,DIMAGE_NONE);
dprint(187,90,C_BLACK,"%.2j",(int)(time*100));
dsubimage(172,110,&img_medals,24,0,12,12,DIMAGE_NONE);
dprint(187,110,C_BLACK,"%.2j",(int)(time*1.2*100));
dsubimage(172,130,&img_medals,12,0,12,12,DIMAGE_NONE); 
dprint(187,130,C_BLACK,"%.2j",(int)(time*1.5*100));
dsubimage(172,150,&img_medals,0,0,12,12,DIMAGE_NONE); 
dprint(187,150,C_BLACK,"%.2j",(int)(time*2*100));
dupdate();
getkey();
}