gold = 1.2
argent = 1.5
bronze = 2

timeslevel = open("times.lvl","r+")
dest = open("src/times.c","w")
lvm = open("include/define.h","r")
ids=timeslevel.readlines()
times=[]

for i in ids: 
	times.append(i.rstrip())

nblvl = int(''.join(filter(str.isdigit,lvm.readline())))

while(len(times) < nblvl):
    times.append("0.00")

dest.write("#include \"times.h\"\n\
#include \"define.h\"\n\
#include <gint/display.h>\n\
#include <gint/keyboard.h>\n\n\
extern bopti_image_t img_medals;\n\
float level_time[] = {")

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
if(frame_level/FPS < (unsigned int)(time*"+str(argent)+") || (frame_level/FPS <= (unsigned int)(time*"+str(argent)+") && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*"+str(argent)+")*100-(int)(time*"+str(argent)+")*100))) dsubimage(x+15,y,&img_medals,12,0,12,12,DIMAGE_NONE);\n\
if(frame_level/FPS < (unsigned int)(time*"+str(bronze)+") || (frame_level/FPS <= (unsigned int)(time*"+str(bronze)+") && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*"+str(bronze)+")*100-(int)(time*"+str(bronze)+")*100))) dsubimage(x,y,&img_medals,0,0,12,12,DIMAGE_NONE);\n\
}\n\
\n\
void draw_time(int id_level)\n\
{\n\
dclear(C_WHITE);\n\
float time=1.0;\n")

dest.write("\ntime = level_time[id_level-1];\n\n\
dsubimage(172,90,&img_medals,36,0,12,12,DIMAGE_NONE);\n\
dprint(187,90,C_BLACK,\"%.2j\",(int)(time*100));\n\
dsubimage(172,110,&img_medals,24,0,12,12,DIMAGE_NONE);\n\
dprint(187,110,C_BLACK,\"%.2j\",(int)(time*"+str(gold)+"*100));\n\
dsubimage(172,130,&img_medals,12,0,12,12,DIMAGE_NONE); \n\
dprint(187,130,C_BLACK,\"%.2j\",(int)(time*"+str(argent)+"*100));\n\
dsubimage(172,150,&img_medals,0,0,12,12,DIMAGE_NONE); \n\
dprint(187,150,C_BLACK,\"%.2j\",(int)(time*"+str(bronze)+"*100));\n\
dupdate();\n\
getkey();\n\
}")
