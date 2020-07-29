ids = 1

save = open("src/setlevel.c","w+")
save.write("#include \"setlevel.h\"\n#include <gint/std/string.h>\nvoid set_level(int id_level, char level[], int *startx, \
int *starty, char *gravity, int *appear, int *disappear){\nswitch(id_level){")
while 1:
    try:
        lv = open(f"editor/levels/{ids}.lvl","r")
        ide = lv.readlines()
        if len(ide)==1: save.write(f"case {ids}:\nmemcpy(level,\"{str(ide[0][:-1])}\",350);\nbreak;\n")
        elif ide[1]!='\n':
            save.write(f"case {ids}:\nmemcpy(level,\"{str(ide[0][:-2])}\",350);\n*appear={ide[1][:-1]};\n*disappear={ide[2]};\nbreak;\n")
        else:
            save.write(f"case {ids}:\nmemcpy(level,\"{str(ide[0][:-2])}\",350);\n*appear={ide[2][:-1]};\n*disappear={ide[3]};\nbreak;\n")
        ids+=1
    except FileNotFoundError:
        lv.close()
        break
save.write("}\n\
set_gravity(id_level, gravity);\n\
unsigned int x = 0;\n\
unsigned int y = 0;\n\
unsigned int i = 0;\n\
while (i!=strlen(level)){\n\
switch(level[i]){\n\
case 's':\n\
*startx = x;\n\
*starty = y;\n\
break;}\n\
x+=16;\n\
if(x==16*25){x=0;\n\
y+=16;}i++;}}\n\
void set_gravity(int id_level, char *default_gravity){\n\
switch(id_level){")
ids = 1
gravity = 0
while 1:
    try:
        lv = open(f"editor/levels/{ids}.lvl","r")
        ide = lv.read()
        if ide[350]=="6": gravity=0
        else: gravity = 1
        save.write(f"case {ids}:\n*default_gravity = {gravity};\nbreak;\n")
        ids+=1
    except FileNotFoundError:
        break
save.write("}}\nvoid del_level(char level[])\n{memcpy(level,\"\
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\",350);}")
