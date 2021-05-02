#include "util.h"

int round(float num)
{
	return (num < 0) ? (num - 0.5) : (num + 0.5);
}
