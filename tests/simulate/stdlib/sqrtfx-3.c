#include <stdfix.h>
#include <stdlib.h>

extern unsigned short fract __avr_libc_sqrtfxhur(unsigned short fract);

int main()
{
	unsigned short fract res;
	res = __avr_libc_sqrtfxhur(0.0UHR);
	if (res != 0.0UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(0.25UHR);
	if (res != 0.5UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(0.0625UHR);
	if (res != 0.25UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(USFRACT_MAX);
	if (res != USFRACT_MAX) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(USFRACT_EPSILON);
	if (res != 0.0625UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(0.5UHR);
	/* 8-bit representation of 1/sqrt(2) = 0.70710678... */
	if (res != 0.70703125UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(0.1UHR);
	if (res != 0.3125UHR) exit(__LINE__);
	res = __avr_libc_sqrtfxhur(0.9UHR);
	if (res != 0.9453125UHR) exit(__LINE__);
	return 0;
}
