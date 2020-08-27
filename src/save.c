#include <gint/bfile.h>
#include <gint/gint.h>
#include "define.h"
#include "drawlevel.h"

int retcode;
int valeur = 0;
int times[LEVEL_MAX]; //moche et je le sais... A essayer l'allocution dynamique


/*savefile() write the time of all the player's times in the savefile
savefile() is long to execute. That's why it must be call once per new record only to avoid loading times.*/
void savefile(void)
{
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	int descriptor;
	
	descriptor = BFile_Open(filepath, BFile_WriteOnly);
	for(int i = 0; i != 15; i++) BFile_Write(descriptor, &times[i], sizeof(times[i]));
	BFile_Close(descriptor);
}

/*loadfile() is only call by the function loadtime() because loadtime() set the value of "valeur".
It store in the global retcode the time of the player. This function is call once per level
in the level selection menu to avoid loading time.*/
void loadfile(void)
{
	int descriptor;
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	descriptor = BFile_Open(filepath, BFile_ReadOnly);
	BFile_Read(descriptor, &retcode, 4, 4*valeur);
	BFile_Close(descriptor);
}

/*savetimes() is call when the player has reached the end of a level. 
If his time is better than the save time, it will call the function savefile
else, nothing append to avoid loading time*/
void savetimes(float framelevel, int id_level)
{
	if(times[id_level-1]>(int)(framelevel/FPS*100) || times[id_level-1]==0) 
	{
		times[id_level-1]=(int)(framelevel/FPS*100);
		draw_end((int)framelevel, id_level, 1);
		gint_switch(savefile);
	}
}

/*restore() is call when the app is load, it will create the save file if it doesn't exist.
If the file exist, it will read all times from the save and store them in the global times[]*/
void restore()
{
	uint16_t *filepath = u"\\\\fls0\\AST3.sav";
	struct BFile_FileInfo fileInfo;
	int handle;
	uint16_t foundpath[30];
	int size = 80;
	int descriptor;
	char checkfile = BFile_FindFirst(filepath, &handle, foundpath, &fileInfo);
	BFile_FindClose(handle);
	if(checkfile == -1) BFile_Create(filepath, BFile_File, &size);
	else
	{
		descriptor = BFile_Open(filepath, BFile_ReadOnly);
		for(int i = 0; i != 15; i++) 
		{
			BFile_Read(descriptor, &retcode, 4, 4*i);
			times[i] = (int)retcode;
		}
		BFile_Close(descriptor);
	}
}

/*loadtime is changing the current value of the global "valeur" to set it to the current level
then it execute loadfile and read and stock in the global retcode 4 bits
at the place 4*level (times are in 4 bits)  */
int loadtime(int a)
{
	valeur = a;
	gint_switch(loadfile);
	return (int)retcode;
}
