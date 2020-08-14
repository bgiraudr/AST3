f = open("times.lvl","r+")
d = open("src/times.c","w")
ids=f.readlines()

d.write("#include \"times.h\"\n\
#include \"define.h\"\n\
#include <gint/display.h>\n\
#include <gint/keyboard.h>\n\n\
extern bopti_image_t img_bronze;\n\
extern bopti_image_t img_argent;\n\
extern bopti_image_t img_or;\n\
extern bopti_image_t img_createur;\n\n\
void check_medal(unsigned int frame_level, int id_level)\n\
{\n\
float time=1.0;\n\
float framefloat = frame_level;\n\
switch(id_level)\n\
{\n")

for i in range(len(ids)):
	if ids[i]!='\n': d.write(f"	case {i+1}:\n        time = {ids[i].rstrip()};\n        break;\n")

d.write("}\n\n\
if(frame_level/FPS < (unsigned int)time || (frame_level/FPS <= (unsigned int)time && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time)*100-(int)(time)*100))) dimage(380,8,&img_createur);\n\
if(frame_level/FPS < (unsigned int)(time*1.1) || (frame_level/FPS <= (unsigned int)(time*1.1) && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.1)*100-(int)(time*1.1)*100))) dimage(360,8,&img_or);\n\
if(frame_level/FPS < (unsigned int)(time*1.2) || (frame_level/FPS <= (unsigned int)(time*1.2) && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.2)*100-(int)(time*1.2)*100))) dimage(340,8,&img_argent);\n\
if(frame_level/FPS < (unsigned int)(time*1.5) || (frame_level/FPS <= (unsigned int)(time*1.5) && \n\
(unsigned int)((framefloat)/FPS*100-frame_level/FPS*100) <= (unsigned int)((time*1.1)*100-(int)(time*1.1)*100))) dimage(320,8,&img_bronze);\n\
}\n\
\n\
void draw_time(int id_level)\n\
{\n\
dclear(C_WHITE);\n\
float time=1.0;\n\
switch(id_level)\n\
{\n")

for i in range(len(ids)):
	if ids[i]!='\n': d.write(f"	case {i+1}:\n        time = {ids[i].rstrip()};\n        break;\n")

d.write("}\n\
dimage(160,90,&img_createur);\n\
dprint(175,90,C_BLACK,\"%d.%02d\",(int)(time),(int)((time)*100-(int)(time)*100));\n\
dimage(160,110,&img_or);\n\
dprint(175,110,C_BLACK,\"%d.%02d\",(int)(time*1.1),(int)((time*1.1)*100-(int)(time*1.1)*100));\n\
dimage(160,130,&img_argent); \n\
dprint(175,130,C_BLACK,\"%d.%02d\",(int)(time*1.2),(int)((time*1.2)*100-(int)(time*1.2)*100));\n\
dimage(160,150,&img_bronze); \n\
dprint(175,150,C_BLACK,\"%d.%02d\",(int)(time*1.5),(int)((time*1.5)*100-(int)(time*1.5)*100));\n\
dupdate();\n\
getkey();\n\
}")