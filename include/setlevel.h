#pragma once

void set_level(int id_level, char level[], int *startx, int *starty,
               char *gravity, int *appear, int *disappear, int *nbswitch);
void set_gravity(int id_level, char *default_gravity);
void del_level(char level[]);
