#include <stdlib.h>
#include <stdfix.h>

static char s1[] = "  	 00000";
static char s2[] = "0x000";
static char s3[] = "  03";
static char s4[] = " -0x0A";

int main(void) {
	short fract ret = 0hr;

	ret = strtofxhr(s1, NULL);
	if (ret != 0hr)
		return __LINE__;
	
	ret = strtofxhr(s2, NULL);
	if (ret != 0hr)
		return __LINE__;

	ret = strtofxhr(s3, NULL);
	if (ret != SFRACT_MAX)
		return __LINE__;

	ret = strtofxhr(s4, NULL);
	if (ret != SFRACT_MIN)
		return __LINE__;
	return 0;
}
