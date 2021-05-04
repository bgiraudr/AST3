#include "friction.h"
#include "collide.h"

void mod_accel_and_fric(float *acceleration, float *friction, int x, int y,
                        char level[])
{
	*acceleration = HACCELERATION;
	*friction = HFRICTION;
	if (!mod_ice(acceleration, friction, x, y, level))
		mod_solid(acceleration, friction, x, y, level);
}

int mod_ice(float *acceleration, float *friction, int x, int y, char level[])
{
	if (collide(x, y - 1, level, 'i') || collide(x, y + 1, level, 'i')) {
		*friction /= 4.0;
		*acceleration /= 2.0;
		return 1;
	}
	return 0;
}

int mod_solid(float *acceleration, float *friction, int x, int y, char level[])
{
	if (collide_solid(x, y - 1, level) || collide_solid(x, y + 1, level)) {
		*friction *= 2.0;
		*acceleration *= 2.0;
		return 1;
	}
	return 0;
}
