#include "define.h"
#include "drawlevel.h"
#include <gint/bfile.h>
#include <gint/gint.h>
#include <gint/keyboard.h>

int retcode;

int times[LEVEL_MAX];
static const uint16_t *filepath = u"\\\\fls0\\AST3.sav";

/* savefile() write the time of all the player's times in the savefile.
 * savefile() is long to execute. That's why it must be call once per
 * new record only to avoid loading times. */
void savefile(void)
{
	int descriptor;

	descriptor = BFile_Open(filepath, BFile_WriteOnly);
	BFile_Write(descriptor, times, sizeof(times));
	BFile_Close(descriptor);
}

<<<<<<< HEAD
/* savetime() is call when the player has reached the end of a level.
 * If his time is better than the save time, it will save it in the array
 */
void savetime(float framelevel, int id_level)
=======
/* loadfile() is only called by the function loadtime() because
 * loadtime() set the value of "id_leveltab".  It store in the global retcode
 * the time of the player. This function is called once per level in the
 * level selection menu to avoid loading time. */
void loadfile(void)
{
	int descriptor;
	descriptor = BFile_Open(filepath, BFile_ReadOnly);
	BFile_Read(descriptor, &retcode, sizeof(times[0]),
	           sizeof(times[0]) * id_leveltab);
	BFile_Close(descriptor);
}

/* savetimes() is call when the player has reached the end of a level.
 * If his time is better than the save time, it will call the function
 * savefile() else, nothing append to avoid loading time. */
void savetimes(float framelevel, int id_level)
>>>>>>> dd8e25d259480e2e6761ff105d419e40e2382bda
{
	if (times[id_level - 1] > (int)(framelevel / FPS * 100) ||
	    times[id_level - 1] == 0 || keydown(KEY_7)) {
		times[id_level - 1] = (int)(framelevel / FPS * 100);
		draw_end((int)framelevel, id_level, 1);
	}
}

/* restore() is call when the app is load, it will create the save file
 * if it doesn't exist. If the file exist, it will read all times from
 * the save and store them in the global times[] */
void restore(void)
{
	struct BFile_FileInfo fileInfo;
	int handle;
	uint16_t foundpath[30];
	int size = sizeof(times);
	int descriptor;
	char checkfile =
	    BFile_FindFirst(filepath, &handle, foundpath, &fileInfo);
	BFile_FindClose(handle);
	if (checkfile == -1)
		BFile_Create(filepath, BFile_File, &size);
	else {
		descriptor = BFile_Open(filepath, BFile_ReadOnly);
		BFile_Read(descriptor, times, sizeof(times), 0);
		BFile_Close(descriptor);
	}
}

int loadtime(int idlevel)
{
    return times[idlevel];
}
