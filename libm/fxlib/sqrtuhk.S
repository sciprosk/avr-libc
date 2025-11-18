#include "asmdef.h"

ENTRY sqrtuhk
    clr     r22
    mov     r23, r24
    mov     r24, r25
    clr     r25
    XJMP    _U(__sqrtsi)
ENDFUNC
