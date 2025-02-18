#include <stdlib.h>

/* Test selected values. */
extern int __avr_libc_sqrtfxhi(int arg);

int main()
{
	int res = -1;
	res = __avr_libc_sqrtfxhi(0);
	if (res != 0) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(1);
	if (res != 1) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(4);
	if (res != 2) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(9);
	if (res != 3) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(16);
	if (res != 4) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(25);
	if (res != 5) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(225);
	if (res != 15) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(256);
	if (res != 16) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(625);
	if (res != 25) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(16129);
	if (res != 127) exit(__LINE__);
	res = __avr_libc_sqrtfxhi(16383);
	if (res != 127) exit(__LINE__);
	return 0;
}
