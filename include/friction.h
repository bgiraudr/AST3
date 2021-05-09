#pragma once

#define MAX_HSPD 2.0
#define HFRICTION 0.2
#define HACCELERATION (MAX_HSPD * HFRICTION)

void mod_accel_and_fric(float *acceleration, float *friction, int x, int y,
                        char level[]);
int mod_ice(float *acceleration, float *friction, int x, int y, char level[]);
int mod_rough(float *acceleration, float *friction, int x, int y, char level[]);
int mod_solid(float *acceleration, float *friction, int x, int y, char level[]);
