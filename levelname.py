f = open("times.lvl","r+")
lvm = open(f"include/define.h","r")
ids=f.readlines()
names=[]
for i in ids: 
	names.append(i.rstrip()) 
for i in range(int(''.join(list(filter(str.isdigit, lvm.readline()))))):
	hop=names[i].find("-")
	if hop!=-1: names[i]=names[i][hop+1:]
	else: names[i]=""
print(names)