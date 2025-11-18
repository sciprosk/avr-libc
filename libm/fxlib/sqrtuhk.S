#include "asmdef.h"

ENTRY sqrtuhk
    clr     r22
    clr     r23
    XJMP    _U(__sqrtsi)
ENDFUNC
