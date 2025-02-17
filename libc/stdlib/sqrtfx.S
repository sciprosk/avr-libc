#ifdef __AVR_HAVE_MUL__

#include "asmdef.h"

#define arg_hi  r25
#define arg_lo  r24
#define res_hi  r23
#define res_lo  r22
#define cbit    r20
#define mask    r18
#define prod_hi r1
#define prod_lo r0

FUNCTION __avr_libc_sqrtfxhi
ENTRY    __avr_libc_sqrtfxhi
	ldi  cbit, 0x80      ; set initial msb bit
	clr  res_lo          ; load the initial guess
.Lnextbit:
	or   res_lo, cbit    ; set current bit in the guess
	mul  res_lo, res_lo  ; take the square of the guess
	cp   arg_lo, prod_lo
	cpc  arg_hi, prod_hi
	brsh 1f              ; if square less than arg, set next bit
	mov  mask, cbit      ; otherwise, save current bit position
	com  mask            ; mask to negate current bit
	and  res_lo, mask    ; clear current bit
1:	lsr  cbit            ; shift bit for the next iteration
	breq .Lexit          ; if all bits done, break the cycle
	XJMP .Lnextbit
.Lexit:
	mov  arg_lo, res_lo
	clr  arg_hi          ; msb of the result is always zero
	clr  __zero_reg__
	ret
ENDFUNC

#endif /* !__AVR_HAVE_MUL__ */
