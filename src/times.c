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
float level_time[] = {5.88,8.31,6.12,8.72,3.92,3.51,6.76,7.48,12.26,9.25};
time = level_time[id_level-1];

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
float level_time[] = {5.88,8.31,6.12,8.72,3.92,3.51,6.76,7.48,12.26,9.25};
time = level_time[id_level-1];

dimage(160,90,&img_createur);
dprint(175,90,C_BLACK,"%.2j",(int)(time*100));
dimage(160,110,&img_or);
dprint(175,110,C_BLACK,"%.2j",(int)(time*1.1*100));
dimage(160,130,&img_argent); 
dprint(175,130,C_BLACK,"%.2j",(int)(time*1.2*100));
dimage(160,150,&img_bronze); 
dprint(175,150,C_BLACK,"%.2j",(int)(time*1.5*100));
dupdate();
getkey();
}