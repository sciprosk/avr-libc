#include <stdfix.h>
#include <stdlib.h>

int main(void)
{
	unsigned short accum r;
	r = sqrtuhk(0.0UHK);
	if (r != 0.0UHK) exit(__LINE__);
	r = sqrtuhk(1.0UHK);
	if (r != 1.0UHK) exit(__LINE__);
	r = sqrtuhk(225.0UHK);
	if (r != 15.0UHK) exit(__LINE__);
	return 0;
}
