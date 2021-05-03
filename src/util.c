#include "util.h"
#include <gint/std/stdlib.h>
#include <gint/rtc.h>

int round(float num) {
	return (num < 0) ? (num - 0.5) : (num + 0.5);
}

int round_sup(float num) {
	return (int)(num+1);
}

/*maybe illegal*/
int rand_range(int low, int high)
{
	srand(rtc_ticks());
	return (rand() % (high - low)) + low;
}