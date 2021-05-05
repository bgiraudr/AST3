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
float level_time[] = {\n\t""")

dest.write("{}".format(',\n\t'.join(times)))

dest.write("\n};")
