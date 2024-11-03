#include <ctype.h>
#include <errno.h>
#include <stdfix.h>
#include "sectionname.h"

ATTRIBUTE_CLIB_SECTION
short
fract strtofxhr(const char* restrict nptr, char ** restrict endptr)
{
	union {
		unsigned short u8;
		fract ffx;
	} x;
	unsigned char c;
	short exp = 0;
	unsigned short base = 10;
	unsigned char flag = 0x0;
#define FL_NEG    0x01    /* number is negative */
#define FL_0X     0x02    /* number has Ox prefix */
	if (endptr)
		*endptr = (char *)nptr;
	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * Allow 0x or 0X for hex, else assume decimal.
	*/
	do {
		c = *nptr++;
	} while (isspace(c));
	
	if (c == '-') {
		flag = FL_NEG;
		c = *nptr++;
	} else if (c == '+')
		c = *nptr++;
	if (c == '0' && (*nptr == 'x' || *nptr == 'X')) {
		c = nptr[1];
		nptr += 2;
		base = 16;
		flag |= FL_0X;
	}
	x.u8 = 0;
	/*
	 * The Report requires that the expected form of the subject sequence
	 * has a non-empty sequence of decimal or hexadecimal digits. For
	 * frac, we admit any positive number of trailing zeroes.
	*/
	while (c == '0')
		c = *nptr++;
	if (isdigit(c) || (isxdigit(c) && base == 16)) {
		if (flag & FL_NEG)
			return SFRACT_MIN;
		return SFRACT_MAX;
	}
	if (c == '.') {
		//
	}
	if (c == 'P' || c == 'p') {
		//
	}	
	return 0hr;
}

