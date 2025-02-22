#!/usr/bin/env python3

# To get the input, run e.g.
#
#     $ ./mcus-to-isrs.sh ../../tmp-device-info

import sys, re, time
from functools import cmp_to_key
from vect_to_desc import vect_to_desc

isr_names = frozenset()

HEADER = r"""/* Note: this file has been automatically generated by means of:
   $ ./gen-vectortable-dox.sh
   DO NOT EDIT, or your changes WILL BE LOST! */

/* Copyright (c) %d Joerg Wunsch
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

/* %sId%s */


/** \addtogroup avr_interrupts

@{

\anchor avr_signames
Go down to the \ref avr_mcu_signames "MCU &rarr; Vector Names" table.<br>
\ref avr_skip_signames "Skip tables".

""" % (time.localtime()[0], "$", "$") # Avoid CVS munging on $.

FOOTER = r"""
@}
*/"""


TABLE_START = r"""
<small>
<table>
  <caption>
\latexonly
  Due to its sheer size, the following table is only available in the
  HTML version of the documentation.
\endlatexonly
\htmlonly
  Vector Names defined with <tt>#include &lt;avr/io.h&gt;</tt>
\endhtmlonly
  </caption>
  <tr>
    <th width="15%">Vector Name</th>
    <th width="20%">Description</th>
    <th width="65%">Applicable for Device</th>
  </tr>
\htmlonly"""

TABLE_TR = """  <tr>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
  </tr>"""

TABLE_END = r"""\endhtmlonly
</table>
</small>
"""

###################################################################

HEADER2 = r"""
/** \addtogroup avr_interrupts

@{
\anchor avr_mcu_signames
Go up to the \ref avr_signames "Vector Name &rarr; MCUs" table.<br>
\ref avr_skip_signames "Skip this table".

"""

FOOTER2 = r"""
\anchor avr_skip_signames
Go up to the \ref avr_signames "Vector Name &rarr; MCUs" table.<br>
Go up to the \ref avr_mcu_signames "MCU &rarr; Vector Names" table.
@}
*/"""


TABLE2_START = r"""
<small>
<table>
  <caption>
\latexonly
  Due to its sheer size, the following table is only available in the
  HTML version of the documentation.
\endlatexonly
\htmlonly
  Vector Names defined with <tt>#include &lt;avr/io.h&gt;</tt><br/>
  Append <tt>_vect</tt> to get the full vector name
\endhtmlonly
  </caption>
  <tr>
    <th>AVR Device</th>
    <th>Vector Names</th>
  </tr>
\htmlonly"""

TABLE2_TR = """  <tr>
    <td>%s</td>
    <td>%s</td>
  </tr>"""

TABLE2_END = r"""\endhtmlonly
</table>
</small>
"""


def canonicalize_comment (txt):
    """Try to canonicalize the documentation of IRQ in a try
       to use the same string for the same purpose.
       Also fixes some typos and overly lengthy descriptions. """

    repls = (("Time-Out", "Timeout"),
             ("Time-out", "Timeout"),
             (" - ", " "),
             ("-", " "),
             # Fix lower-case.
             ("interrupt", "Interrupt"),
             ("register", "Register"),
             ("timer", "Timer"),
             ("change", "Change"),
             ("capture", "Capture"),
             ("complete", "Complete"),
             ("comparator", "Comparator"),
             ("conversion", "Conversion"),
             ("overflow", "Overflow"),
             ("underflow", "Underflow"),
             (" end ", " End "),
             (" error ", " Error "),
             ("vector", "Vector"),
             ("monitor", "Monitor"),
             ("ready", "Ready"),
             ("wire", "Wire"),
             ("regulator", "Regulator"),
             ("receiver", "Receiver"),
             ("transmission", "Transmission"),
             ("transfer", "Transfer"),
             ("RX", "Rx"),
             ("TX", "Tx"),
             ("START", "Start"),
             ("Alias", "alias"),
             ("window", "Window"),
             (" Of ", " of "),
             # Punctuations
             ("UART, ", "UART "),
             ("USART, ", "USART "),
             ("0, ", "0 "),
             ("1, ", "1 "),
             (", Tx", " Tx"),
             (", Rx", " Rx"),
             # Timer/Counter
             ("TimerCounter", "Timer/Counter"),
             ("Timer1/Counter1", "Timer/Counter1"),
             ("Timer/Counter 0", "Timer/Counter0"),
             ("Timer/Counter 1", "Timer/Counter1"),
             ("Timer Counter 0", "Timer/Counter0"),
             ("Timer 0", "Timer0"),
             ("Timer 1", "Timer1"),
             (" A Match", " Match A"),
             (" B Match", " Match B"),
             # Use shorter terms / abbreviations.
             ("2 Wire", "Two Wire"),
             ("Interruption", "Interrupt"),
             ("Interrupt Vectors", "IRQs"),
             ("Interrupt Request", "IRQ"),
             ("External Interrupt", "External IRQ"),
             ("Pin Change Interrupt", "Pin Change IRQ"),
             ("External Oscillator Failure Interrupt (NMI)", "External Oscillator Failure (NMI)"),
             ("Oscillator Failure Interrupt (NMI)", "External Oscillator Failure (NMI)"),
             # Typos
             ("Couner", "Counter"),
             ("Comapre", "Compare"),
             )
    for (a,b) in repls:
        txt = txt.replace (a, b)

    # Trailing "Interrupt" is somewhat redundant in this context.
    prunes = (" Interrupt", )
    for a in prunes:
        if txt.endswith(a):
            txt = txt[:-len(a)]
            break

    typos = (("Store Program Memory Read", "Store Program Memory Ready"),
             ("SPI Serial Transfer Complet", "SPI Serial Transfer Complete"),
             ("EE", "EEPROM"),
             ("SOF, suspend, resume, reset bus event Interrupts, crc, underflow, Overflow and stall error Interrupts", "USB Bus Event"),
             )
    for a in typos:
        if txt == a[0]:
            txt = a[1]

    return txt


class Isr (object):
    """One specific ISR"""

    pat_0_args = (("ADC",         "ADC Conversion Complete"),
                  ("USART_START", "USART Start Edge"),
                  ("USART_RX",    "USART Rx Complete"),
                  ("USART_TX",    "USART Tx Complete"),
                  ("USI_START",   "USI Start Condition"),
                  ("USI_STR",     "USI Start Condition"),
                  ("USI_OVF",     "USI Counter Overflow"),
                  ("TWI_SLAVE",   "TWI Slave"),
                  )
    pat_1_arg = tuple((re.compile(p), desc) for (p,desc) in (
        (r"PCINT(\d)",       "Pin Change IRQ %s"),
        (r"TIM(\d)_CAPT",    "Timer/Counter%s Input Capture"),
        (r"TIMER(\d)_CAPT",  "Timer/Counter%s Input Capture"),
        (r"TIMER(\d)_IC",    "Timer/Counter%s Input Capture"),
        (r"TIMER(\d)_OVF",   "Timer/Counter%s Overflow"),
        (r"UART(\d)_UDRE",   "UART%s Data Register Empty"),
        (r"UART(\d)_RX",     "UART%s Rx Complete"),
        (r"UART(\d)_TX",     "UART%s Tx Complete"),
        (r"USART(\d)_RX",    "USART%s Rx Complete"),
        (r"USART(\d)_TX",    "USART%s Tx Complete"),
        (r"USART(\d)_RXC",   "USART%s Rx Complete"),
        (r"USART(\d)_TXC",   "USART%s Tx Complete"),
        (r"USART(\d)_START", "USART%s Start Frame Detection"),
        (r"USART(\d)_DRE",   "USART%s Data Register Empty"),
        (r"USART(\d)_UDRE",  "USART%s Data Register Empty"),
        (r"TWI(\d)",         "Two Wire Serial Interface %s"),
    ))
    pat_2_args = tuple((re.compile(p), desc) for (p,desc) in (
        (r"TIM(\d)_COMP([A-Z])",   "Timer/Counter%s Compare Match %s"),
        (r"TIMER(\d)_COMP([A-Z])", "Timer/Counter%s Compare Match %s"),
        ))

    def __init__(self, mcu, isr, num, text):
        # AVR device, in lower case.
        self.mcu = mcu

        # ISR name, without trailing _vect
        self.isr = isr

        # Number of the ISR, as a string.
        self.num = num

        # Text describing the ISR; may be empty.

        vect = self.isr + "_vect"
        if (not text) and (vect in vect_to_desc):
            text = vect_to_desc[vect]

        self.text = canonicalize_comment (text)
        self.text = self.fixup()

    def fixup (self):
        """ Some descriptions are obviously wrong.  Reconstruct them. """
        # 0 Arguments
        for (pat, desc) in self.pat_0_args:
            if self.isr == pat:
                return desc

        # 1 Argument
        for (pat, desc) in self.pat_1_arg:
            m = pat.fullmatch (self.isr)
            if m:
                return desc % m.group(1)

        # 2 Arguments
        for (pat, desc) in self.pat_2_args:
            m = pat.fullmatch (self.isr)
            if m:
                return desc % (m.group(1), m.group(2))

        return self.text

    def ignore (self):
        """ Ignore some ISRs for brevity.  These are double defined vectors
            that are aliases, and "reserved for future" ones. """
        if re.search ("reserved", self.text, re.IGNORECASE):
            return True
        return self.text in ("Keep for backward compatibility",
                             "For compatability only",
                             "alias")

    def __str__(self):
        return "%s:%s:%s:%s" % (self.mcu, self.isr, self.num, self.text)

    def __repr__(self):
        return "%s:%s:%s:%s" % (self.mcu, self.isr, self.num, self.text)


def to_Mcu (mcu):
    """ Turn lower-case like atmega8 into its proper spelling ATmega8. """
    mcu = mcu.upper()
    mcu = mcu.replace ("TINY", "tiny")
    mcu = mcu.replace ("XMEGA", "xmega")
    mcu = mcu.replace ("MEGA", "mega")
    mcu = mcu.replace ("AUTO", "auto")
    return mcu

# #define %s_vect _VECTOR(%d) /* %s */
pat_vect = re.compile(r"#\s*define\s+(\w+)_vect\s+_VECTOR\s*\(\s*(\d+)\s*\)(.*)")

# #define %s_vect_num %d
pat_vect_num = re.compile(r"#\s*define\s+(\w+)_vect_num\s+(\d+)(.*)")

# /* %s */
pat_comment = re.compile(r"\s*/\*(.*)\*/\s*")

# ::%s::
pat_mcu = re.compile(r"::(.*)::")

#############################################################################
# Step 1: Read stdin and build Isr objects from the pre-processed avr/io*.h
# Outcome is to set  mcu_to_isrs  which maps MCU names to array of IRQs.

# Map mcu to array of Isr's.
mcu_to_isrs = {}

mcu = None
cmt = ""

for line in sys.stdin.readlines():
    line = line.strip()

    # ::mcu:: starts a new MCU.
    m = re.match (pat_mcu, line)
    if m:
        mcu = m.group(1)
        mcu_to_isrs[mcu] = []
        cmt = ""
        continue

    # /* cmt */
    m = re.fullmatch (pat_comment, line)
    if m:
        cmt = m.group(1).strip()
        if "0 is the reset vector" in cmt:
            cmt = ""
        continue

    # #define *_vect_num *
    m = re.match (pat_vect_num, line)
    if m:
        # The only effect of a vect_num is that it does not invalidate
        # the comment that might be present before it.
        continue

    # #define *_vect _VECTOR(*) /* ... */
    m = re.match (pat_vect, line)
    if m:
        # Try find a comment after the macro that describes the IRQ.
        tail = m.group(3).strip()
        if tail.startswith("/*") and tail.endswith("*/"):
            tail = tail[2:-2].strip()

        isr = Isr (mcu, m.group(1), m.group(2), tail if len(tail) else cmt)

        # Ignore "alias" and "backward compatibility" IRQs.
        if isr.ignore():
            continue

        isr_names |= set([isr.text])

        isrs = mcu_to_isrs[mcu]
        num = int(isr.num)
        while len(isrs) < 1 + num:
            isrs.append (None)
        mcu_to_isrs[mcu][num] = isr

        continue

    # Anything that's not recognized is ignored, but also invalidates cmt.
    cmt = ""


#############################################################################
# Use an AVR-friendly MCU string comparator.

avr_prefixes = ("attiny", "atmega", "atxmega", "avr", "at90can",
                "at90usb", "at90", "ata", "at8", "m")

avr_sizes = (384, 256, 192, 128, 103, 64, 48, 32, 16)

def str_cmp (a, b):
    # Starship string comparison like C's strcmp."""
    for i in range (min (len(a), len(b))):
        if a[i] != b[i]:
            return ord(a[i]) - ord(b[i])
    return len(a) - len(b)

def avr_prefix_id (avr, prefixes):
    for i in range (len(prefixes)):
        if avr.startswith (prefixes[i]):
            return i
    return -1

def avr_flash_size (a):
    # Try to determine the flash size.
    for s in avr_sizes:
        if a.startswith (str(s)):
            if s == 48:
                return 48 if a.startswith("480") else 4
            return s
    return int(a[0]) if a[0].isdigit() else 0

def avr_comparator (a, b):
    # 0: Special cases.
    tinys = ("attiny4", "attiny5", "attiny9")
    ida = tinys.index(a) if a in tinys else len(tinys)
    idb = tinys.index(b) if b in tinys else len(tinys)
    if ida != len(tinys) or idb != len(tinys):
        return ida - idb

    # 1: Sort according to prefix like "atmega" or "attiny".
    ida = avr_prefix_id (a, avr_prefixes)
    idb = avr_prefix_id (b, avr_prefixes)
    if ida < 0 or idb < 0:
        return str_cmp (a, b)
    if ida != idb:
        return ida - idb

    # Consume prefix.
    a = a[len(avr_prefixes[ida]):]
    b = b[len(avr_prefixes[idb]):]

    # 2: Sort according to flash size.
    sa = avr_flash_size(a)
    sb = avr_flash_size(b)

    if sa == 0 or sb == 0:
        return str_cmp (a, b)
    elif sa != sb:
        return sa - sb

    # Consume flash size.
    a = a[len(str(sa)):]
    b = b[len(str(sb)):]

    # 3: Sort according to suffix; letters go before digits.
    if len(a) == 0 or len(b) == 0:
        return str_cmp (a, b)

    if bool(a[0].isdigit()) != bool(b[0].isdigit()):
        return str_cmp (b, a)
    return str_cmp (a, b)

def sorted_mcus (ms):
    return sorted (ms, key=cmp_to_key(avr_comparator))

def cmp1_mcu (vs1_mcu1, vs2_mcu2):
    return avr_comparator (vs1_mcu1[1], vs2_mcu2[1])

def sorted_vecs (vs):
    # Sort all  "vec1, vecs" -> (mcu0, mcu1, ...)
    # according to mcu0.
    vs_mcus = []
    for v in vs:
        if v:  vs_mcus.append ((v, vs[v][0]))

    return sorted (vs_mcus, key=cmp_to_key (cmp1_mcu))


#############################################################################
# Step 2: Build all IRQ:Description Pairs and map them to MCU lists.

# Map "vect:Description" key to list of mcus.
key_to_mcus = {}

for mcu in mcu_to_isrs:
    for isr in mcu_to_isrs[mcu]:
        if not isr:
            # Some ISRs are void, e.g. in avr/ioa5272.h (ATA5272)
            continue

        key = isr.isr + ":" + isr.text

        if not key in key_to_mcus:
            key_to_mcus[key] = frozenset()
        key_to_mcus[key] |= set([isr.mcu])

mcus_SIG_only = []

for mcu in mcu_to_isrs:
    if (not mcu_to_isrs[mcu]) and mcu != "unknown":
        mcus_SIG_only.append (mcu)

#############################################################################
# Step 3: Print the ISR -> MCU table

print (HEADER)
print (TABLE_START)

for key in sorted(key_to_mcus.keys()):
    irq, desc = key.split (":", 2)
    mcus = [ to_Mcu(mcu) for mcu in sorted_mcus (key_to_mcus[key]) ]
    print (TABLE_TR % (irq + "_vect", desc, ", ".join(mcus)))

print (TABLE_END)

if mcus_SIG_only:
    print (r"\note For the following devices, only the deprecated \c SIG_ names"
           + r" are available:",
           ", ".join (to_Mcu(m) for m in sorted(mcus_SIG_only)) + ".")

print (FOOTER)


#############################################################################
# Step 4: Print the MCU -> ISR table


print (HEADER2)
print (TABLE2_START)

vecs_to_mcus = {}

for mcu in mcu_to_isrs.keys():
    vecs = set()
    for vec in mcu_to_isrs[mcu]:
        if vec:
            #print (vec.isr)
            vecs |= set ([vec.isr])

    # A string with all ISRs sorted is the key.
    s_vecs = ", ".join(sorted(vecs))
    if s_vecs in vecs_to_mcus.keys():
        vecs_to_mcus[s_vecs] |= set([mcu])
    else:
        vecs_to_mcus[s_vecs] = set([mcu])

for v in vecs_to_mcus:
    vecs_to_mcus[v] = sorted_mcus (vecs_to_mcus[v])

for vs_mcu in sorted_vecs (vecs_to_mcus):
    mcus = [ to_Mcu (mcu) for mcu in vecs_to_mcus[vs_mcu[0]] ]
    print (TABLE2_TR % (", ".join (mcus), vs_mcu[0]))

print (TABLE2_END)

if mcus_SIG_only:
    print (r"\note For the following devices, only the deprecated \c SIG_ names"
           + r" are available:",
           ", ".join (to_Mcu(m) for m in sorted(mcus_SIG_only)) + ".")

print (FOOTER2)
