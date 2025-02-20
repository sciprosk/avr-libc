#include "asmdef.h"

/*
 * Implementation of the "Fast Integer Square Root" algorithm for AVR.
 * See Ross M. Folsler, DS91040A, Microchip Technology (2000).
 * https://ww1.microchip.com/downloads/en/AppNotes/91040a.pdf
*/

/*
 * Integer part of a square root from a 16-bit unsigned integer.
*/

#define arg_hi  r25
#define arg_lo  r24
#define res_hi  r23
#define res_lo  r22
#define cbit    r20
#define prod_hi __zero_reg__
#define prod_lo __tmp_reg__

FUNCTION __avr_libc_sqrtfxhi
ENTRY    __avr_libc_sqrtfxhi
	ldi  cbit, 0x80      ; set initial msb bit
	clr  res_lo          ; load the initial guess
.Lnextbit:
	or   res_lo, cbit    ; set current bit in the guess
#ifdef __AVR_HAVE_MUL__
	mul  res_lo, res_lo  ; take the square of the guess
#else
	; Call 16 = 8 x 8 libgcc widening multiplication
	push arg_hi
	push arg_lo
	push res_hi
	push res_lo
	mov arg_lo, res_lo
	XCALL __umulqihi3
	X_movw prod_lo, arg_lo
	pop res_lo
	pop res_hi
	pop arg_lo
	pop arg_hi
#endif /* __AVR_HAVE_MUL__ */
	cp   arg_lo, prod_lo
	cpc  arg_hi, prod_hi
	brsh 1f              ; if square less than arg, set next bit
	com  cbit            ; mask to negate current bit
	and  res_lo, cbit    ; clear current bit in the guess
	com  cbit            ; revert current bit back
1:	lsr  cbit            ; shift bit for the next iteration
	breq .Lexit          ; if all bits done, break the cycle
	XJMP .Lnextbit
.Lexit:
	mov  arg_lo, res_lo
	clr  arg_hi          ; msb of the result is always zero
	clr  __zero_reg__
	ret
ENDFUNC

#undef prod_lo
#undef prod_hi
#undef cbit
#undef res_lo
#undef res_hi
#undef arg_lo
#undef arg_hi

/*
 * Square root of a 8-bit unsigned fract.
*/

#define res_hi r25
#define res_lo r24

;FUNCTION __avr_libc_sqrtfxur
;ENTRY    __avr_libc_sqrtfxur
	ASSEMBLY_CLIB_SECTION
	.type   _U(__avr_libc_sqrtfxhur), "function"
	.global _U(__avr_libc_sqrtfxhur)
_U(__avr_libc_sqrtfxhur):
	mov  res_hi, res_lo       ; reinterpret short fract as uint16_t
	clr  res_lo
	XCALL __avr_libc_sqrtfxhi ; take integer square root;
	ret                       ; return low 8-bit as unsigned fract
	.size _U(__avr_libc_sqrtfxhur), . - _U(__avr_libc_sqrtfxhur)
;ENDFUNC
