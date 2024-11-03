/* Copyright (c) 2013 Joerg Wunsch
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/* $Id$ */

#ifndef _STDFIX_AVRLIBC_H
#define _STDFIX_AVRLIBC_H

/*
 * AVR-LibC addendum file for Embedded C Fixed-Point support
 *
 * See: ISO/IEC TR 18037
 * http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1169.pdf
 */

#ifndef _AVRGCC_STDFIX_H  /* Defined in stdfix.h from avr-gcc */
#warning please include <stdfix.h> directly rather than <stdfix-avrlibc.h>
#endif /* _AVRGCC_STDFIX_H */

/* Room for AVR-LibC specific extensions */

/* 7.18a.6.8 Numeric conversion functions */

extern short fract strtofxhr(const char* restrict nptr, char ** restrict endptr);

extern fract strtofxr(const char * restrict nptr, char ** restrict endptr);

extern long fract strtofxlr(const char * restrict nptr, char ** restrict endptr);

extern short accum strtofxhk(const char * restrict nptr, char ** restrict endptr);

extern accum strtofxk(const char * restrict nptr, char ** restrict endptr);

extern long accum strtofxlk(const char * restrict nptr, char ** restrict endptr);

extern unsigned short fract strtofxuhr(const char* restrict nptr, char ** restrict endptr);

extern unsigned fract strtofxur(const char * restrict nptr, char ** restrict endptr);

extern unsigned long fract strtofxulr(const char * restrict nptr, char ** restrict endptr);

extern unsigned short accum strtofxuhk(const char * restrict nptr, char ** restrict endptr);

extern unsigned accum strtofxuk(const char * restrict nptr, char ** restrict endptr);

extern unsigned long accum strtofxulk(const char * restrict nptr, char ** restrict endptr);

#endif /* _STDFIX_AVRLIBC_H */
