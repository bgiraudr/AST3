gold = 1.2
silver = 1.5
bronze = 2

x = 340
y = 140

timeslevel = open("times.lvl","r+")
dest = open("generated/times.c","w")
lvm = open("generated/include/define.h","r")
ids=timeslevel.readlines()
times=[]

for i in ids:
	times.append(i.rstrip())

nblvl = int(''.join(filter(str.isdigit,lvm.readline())))

while(len(times) < nblvl):
    times.append("0.00")

dest.write("""#include "times.h"
#include "define.h"
#include <gint/display.h>
#include <gint/keyboard.h>
extern bopti_image_t img_medals;
float level_time[] = {""")

dest.write(f"{','.join(times)}")

dest.write("};\n\
void check_medal(unsigned int frame_level, int id_level, int x, int y)\n\
{\n\
float time=1.0;\n\
float framefloat = frame_level;")

dest.write("\ntime = level_time[id_level-1];\n\n\
if(frame_level/FPS < (unsigned int)time || (frame_level/FPS <= (unsigned int)time && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time)*100-(int)(time)*100))) dsubimage(x+45,y,&img_medals,36,0,12,12,DIMAGE_NONE);\n\
if(frame_level/FPS < (unsigned int)(time*"+str(gold)+") || (frame_level/FPS <= (unsigned int)(time*"+str(gold)+") && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*"+str(gold)+")*100-(int)(time*"+str(gold)+")*100))) dsubimage(x+30,y,&img_medals,24,0,12,12,DIMAGE_NONE);\n\
if(frame_level/FPS < (unsigned int)(time*"+str(silver)+") || (frame_level/FPS <= (unsigned int)(time*"+str(silver)+") && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*"+str(silver)+")*100-(int)(time*"+str(silver)+")*100))) dsubimage(x+15,y,&img_medals,12,0,12,12,DIMAGE_NONE);\n\
if(frame_level/FPS < (unsigned int)(time*"+str(bronze)+") || (frame_level/FPS <= (unsigned int)(time*"+str(bronze)+") && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*"+str(bronze)+")*100-(int)(time*"+str(bronze)+")*100))) dsubimage(x,y,&img_medals,0,0,12,12,DIMAGE_NONE);\n\
}\n")

