#pragma once

char collide(int x, int y, char level[], char block);
char collide_gravity(int x, int y, char level[], char gravity, char block);
char collide_solid_gravity(int x, int y, char level[], char gravity);
char collide_solid(int x, int y, char level[]);
char collide_dead(int x, int y, char level[]);
char collide_point(int x, int y, char level[], char block);
char collide_end(int x, int y, char level[]);
void collide_replace(int x, int y, char level[], char collide, char replace);
char collide_center(int x, int y, char level[], char block);
