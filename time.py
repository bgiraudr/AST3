timeslevel = open("times.lvl","r+")
dest = open("generated/times.c","w")
define = open("generated/include/define.h","r")
times=[]

for i in timeslevel.readlines():
	times.append(i.rstrip())

nblvl = int(''.join(filter(str.isdigit,define.readline())))

while(len(times) < nblvl):
    times.append("0.00")

dest.write("""#include "times.h"
float level_time[] = {\n\t""")

dest.write("{}".format(',\n\t'.join(times)))

dest.write("\n};")
