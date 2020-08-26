#include <gint/bfile.h>
#include <gint/gint.h>
#include <gint/std/stdlib.h>
#include "define.h"

int retcode;
int valeur = 0;
int times[LEVEL_MAX]; //moche et je le sais... A essayer l'allocution dynamique

void savefile(void)
{
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	int descriptor;
	
	descriptor = BFile_Open(filepath, BFile_WriteOnly);
	for(int i = 0; i != 14; i++) BFile_Write(descriptor, &times[i], sizeof(times[i]));
	BFile_Close(descriptor);
}

void loadfile(void)
{
	int descriptor;
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	descriptor = BFile_Open(filepath, BFile_ReadOnly);
	BFile_Read(descriptor, &retcode, 4, 4*valeur);
	BFile_Close(descriptor);
}

void savetimes(float framelevel, int id_level)
{
	if(times[id_level-1]>(int)(framelevel/FPS*100) || times[id_level-1]==0) 
	{
		times[id_level-1]=(int)(framelevel/FPS*100);
		gint_switch(savefile);
	}
}

void restore()
{
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	struct BFile_FileInfo fileInfo;
	int handle;
	uint16_t foundpath[30];
	int size = 500;
	int descriptor;
	char checkfile = BFile_FindFirst(filepath, &handle, foundpath, &fileInfo);
	BFile_FindClose(handle);
	if(checkfile == -1) BFile_Create(filepath, BFile_File, &size);
	else
	{
		descriptor = BFile_Open(filepath, BFile_ReadOnly);
		for(int i = 0; i != 14; i++) 
		{
			BFile_Read(descriptor, &retcode, 4, 4*i);
			times[i] = (int)retcode;
		}
		BFile_Close(descriptor);
	}
}

int loadtime(int a)
{
	valeur = a;
	gint_switch(loadfile);
	return (int)retcode;
}
