#include "friction.h"
#include "collide.h"

float apply_friction(int x, int y, char level[]) {
	float friction = 0.2;
	mod_solid(x, y, level, &friction);
	mod_ice(x, y, level, &friction);
	return friction;
}

void mod_ice(int x, int y, char level[], float *friction) {
	if (collide(x, y - 1, level, 'i') ||
    	collide(x, y + 1, level, 'i')) {
		*friction = 0.15;
    }
}

void mod_solid(int x, int y, char level[], float *friction) {
	if(collide_solid(x, y - 1, level) || 
		collide_solid(x, y + 1, level)) {
		*friction = 0.2;
	}
}