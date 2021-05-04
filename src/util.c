#include "util.h"
#include <gint/std/stdlib.h>

int round(float num) {
	return (num < 0) ? (num - 0.5) : (num + 0.5);
}

int round_sup(float num) {
	return (int)(num+1);
}

int rand_range(int low, int high) {
	return (rand() % (high - low)) + low;
}