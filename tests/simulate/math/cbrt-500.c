/* Copyright (c) 2009  Dmitry Xmelkov
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

/* Test of cbrt() function: 500 random cases. */

#define	ULPMAX	1	/* max possible error in units at last position	*/

#include <math.h>
#include <stdlib.h>
#include "progmem.h"

#ifndef	__AVR__
# include <stdio.h>
# define PRINTFLN(fmt, ...)	\
    printf ("\nLine %d: " fmt "\n", __LINE__, ##__VA_ARGS__)
# define EXIT(code)	exit ((code) < 255 ? (code) : 100 + (code) % 100)
#else
# define PRINTFLN(args...)
# define EXIT	exit
#endif

union float_u {
    unsigned long u32;
    float flt;
};

/* Result is placed into SRAM variable, allocated at the start of
   memory. This is convenient to debug: read a core dump.	*/
volatile union float_u v = {.u32 = 1};

PROGMEM const struct {
    unsigned long x;
    unsigned long z;
} t[] = {

    /* x, cbrt(x)	*/
    { 0xbfde6fcd,0xbf99e3b2 }, /*   1: -1.7377869e+00 -1.2022612e+00 */
    { 0x40b47585,0x3fe3d5a4 }, /*   2:  5.6393456e+00  1.7799573e+00 */
    { 0xbf408a98,0xbf68cf52 }, /*   3: -7.5211477e-01 -9.0941346e-01 */
    { 0x4136c57c,0x4010231f }, /*   4:  1.1423214e+01  2.2521436e+00 */
    { 0x5d4503c1,0x496a9958 }, /*   5:  8.8727517e+17  9.6091750e+05 */
    { 0xbde4615f,0xbef670e3 }, /*   6: -1.1151385e-01 -4.8133001e-01 */
    { 0x3e89fc52,0x3f255bea }, /*   7:  2.6950318e-01  6.4593375e-01 */
    { 0xbfc71b28,0xbf944f29 }, /*   8: -1.5555162e+00 -1.1586658e+00 */
    { 0xbf112d36,0xbf53e5b9 }, /*   9: -5.6709611e-01 -8.2772404e-01 */
    { 0xc9b75739,0xc2e50a75 }, /*  10: -1.5019271e+06 -1.1452042e+02 */
    { 0x4747f170,0x4214844a }, /*  11:  5.1185438e+04  3.7129189e+01 */
    { 0xc00eb72a,0xbfa73a2c }, /*  12: -2.2299294e+00 -1.3064628e+00 */
    { 0xd5f33235,0xc6fba8aa }, /*  13: -3.3424620e+13 -3.2212332e+04 */
    { 0xbf49a5b1,0xbf6c6c6e }, /*  14: -7.8768450e-01 -9.2352951e-01 */
    { 0xc0c95c3b,0xbfec4fb4 }, /*  15: -6.2925086e+00 -1.8461823e+00 */
    { 0x3f1d00a3,0x3f59805f }, /*  16:  6.1329097e-01  8.4961504e-01 */
    { 0xbdf15a6e,0xbefb0585 }, /*  17: -1.1784826e-01 -4.9027649e-01 */
    { 0x3e94da1a,0x3f29972a }, /*  18:  2.9072648e-01  6.6246283e-01 */
    { 0xd85ccbbf,0xc7c1691e }, /*  19: -9.7107056e+14 -9.9026234e+04 */
    { 0x411579e6,0x4006cabd }, /*  20:  9.3422604e+00  2.1061242e+00 */
    { 0xc274564a,0xc07c0d41 }, /*  21: -6.1084267e+01 -3.9383090e+00 */
    { 0x3fe84025,0x3f9c1ec1 }, /*  22:  1.8144575e+00  1.2196885e+00 */
    { 0xbbba939e,0xbe36da67 }, /*  23: -5.6938669e-03 -1.7856751e-01 */
    { 0x3e5a4e4e,0x3f18ee4d }, /*  24:  2.1318933e-01  5.9738618e-01 */
    { 0xc0084416,0xbfa4ab52 }, /*  25: -2.1291556e+00 -1.2864783e+00 */
    { 0xbfced92d,0xbf963509 }, /*  26: -1.6160027e+00 -1.1734935e+00 */
    { 0xb7b3d819,0xbce39350 }, /*  27: -2.1439091e-05 -2.7780205e-02 */
    { 0x3f989188,0x3f87b712 }, /*  28:  1.1919413e+00  1.0602744e+00 */
    { 0x4180ee9a,0x4021a90f }, /*  29:  1.6116505e+01  2.5259435e+00 */
    { 0xbfdcde51,0xbf9986e4 }, /*  30: -1.7255346e+00 -1.1994290e+00 */
    { 0x417dbc5b,0x4020cb04 }, /*  31:  1.5858485e+01  2.5123911e+00 */
    { 0x423acb6f,0x40667860 }, /*  32:  4.6698666e+01  3.6010971e+00 */
    { 0x3b0e70f0,0x3e04a4ac }, /*  33:  2.1734796e-03  1.2953442e-01 */
    { 0xbdd0a4da,0xbeef2082 }, /*  34: -1.0187693e-01 -4.6704489e-01 */
    { 0xbccce5da,0xbe95bbca }, /*  35: -2.5011946e-02 -2.9244834e-01 */
    { 0xbc5ab0c6,0xbe72e7b5 }, /*  36: -1.3347810e-02 -2.3721202e-01 */
    { 0x3f023258,0x3f4c57d4 }, /*  37:  5.0858068e-01  7.9821515e-01 */
    { 0xc001ac1c,0xbfa1f81c }, /*  38: -2.0261297e+00 -1.2653842e+00 */
    { 0x3d7a7d95,0x3ec9b819 }, /*  39:  6.1154921e-02  3.9398268e-01 */
    { 0xbe292c09,0xbf0c7842 }, /*  40: -1.6520704e-01 -5.4870999e-01 */
    { 0x3fde4e09,0x3f99dbe8 }, /*  41:  1.7367564e+00  1.2020235e+00 */
    { 0xba09092f,0xbda4fa91 }, /*  42: -5.2275037e-04 -8.0556042e-02 */
    { 0x3e4079a2,0x3f12a4e9 }, /*  43:  1.8796399e-01  5.7282883e-01 */
    { 0x3ff7924b,0x3f9f7af0 }, /*  44:  1.9341520e+00  1.2459393e+00 */
    { 0x6d3e6be2,0x4eb819c2 }, /*  45:  3.6832859e+27  1.5443479e+09 */
    { 0x40916bce,0x3fd40428 }, /*  46:  4.5444098e+00  1.6563768e+00 */
    { 0xbdda59c9,0xbef2c77b }, /*  47: -1.0661656e-01 -4.7417817e-01 */
    { 0x3ff54a35,0x3f9efd22 }, /*  48:  1.9163271e+00  1.2421000e+00 */
    { 0x3bfd70c0,0x3e4a8205 }, /*  49:  7.7343881e-03  1.9776161e-01 */
    { 0xbaa162ab,0xbddb81c1 }, /*  50: -1.2312731e-03 -1.0718108e-01 */
    { 0x3d07c795,0x3ea4791c }, /*  51:  3.3149321e-02  3.2123649e-01 */
    { 0xbd411127,0xbeb8f304 }, /*  52: -4.7135498e-02 -3.6122906e-01 */
    { 0x3fe92f83,0x3f9c5451 }, /*  53:  1.8217624e+00  1.2213231e+00 */
    { 0x3f44e185,0x3f6a8bc1 }, /*  54:  7.6906615e-01  9.1619498e-01 */
    { 0x44a99fa9,0x4131235f }, /*  55:  1.3569894e+03  1.1071136e+01 */
    { 0xc37398e4,0xc0c7d9fc }, /*  56: -2.4359723e+02 -6.2453594e+00 */
    { 0xc1cdf077,0xc03cf8b7 }, /*  57: -2.5742414e+01 -2.9526803e+00 */
    { 0xc18812f7,0xc0249787 }, /*  58: -1.7009260e+01 -2.5717485e+00 */
    { 0xbfd6f5e0,0xbf982548 }, /*  59: -1.6793785e+00 -1.1886377e+00 */
    { 0xbe328c9e,0xbf0f04c6 }, /*  60: -1.7436454e-01 -5.5866659e-01 */
    { 0x3fdd516f,0x3f99a18c }, /*  61:  1.7290477e+00  1.2002425e+00 */
    { 0xc1b30e81,0xc0345cdc }, /*  62: -2.2382082e+01 -2.8181677e+00 */
    { 0xc2cce896,0xc095bc74 }, /*  63: -1.0245427e+02 -4.6792545e+00 */
    { 0x3dc1ff37,0x3ee96520 }, /*  64:  9.4725065e-02  4.5584965e-01 */
    { 0x43aa17a7,0x40df62af }, /*  65:  3.4018478e+02  6.9807963e+00 */
    { 0xbc9297eb,0xbe85eb78 }, /*  66: -1.7894706e-02 -2.6156211e-01 */
    { 0x4749aab2,0x4214f13c }, /*  67:  5.1626695e+04  3.7235580e+01 */
    { 0x3c823de4,0x3e80be31 }, /*  68:  1.5898652e-02  2.5145105e-01 */
    { 0xc155c5ce,0xc017dd69 }, /*  69: -1.3360792e+01 -2.3728888e+00 */
    { 0xb5ac2bb0,0xbc320537 }, /*  70: -1.2827713e-06 -1.0865501e-02 */
    { 0x3fe8e168,0x3f9c42db }, /*  71:  1.8193789e+00  1.2207903e+00 */
    { 0xbea3780a,0xbf2ef820 }, /*  72: -3.1927520e-01 -6.8347359e-01 */
    { 0xbdef6ac8,0xbefa5939 }, /*  73: -1.1690289e-01 -4.8896196e-01 */
    { 0xbf301c85,0xbf61fd6e }, /*  74: -6.8793517e-01 -8.8277328e-01 */
    { 0xbb995fb3,0xbe2b4a6a }, /*  75: -4.6805977e-03 -1.6727605e-01 */
    { 0x4125591e,0x400b673f }, /*  76:  1.0334257e+01  2.1781766e+00 */
    { 0xc12af08d,0xc00cf512 }, /*  77: -1.0683728e+01 -2.2024579e+00 */
    { 0x3f12063d,0x3f544f1b }, /*  78:  5.7040769e-01  8.2933205e-01 */
    { 0xc15aea73,0xc01912ba }, /*  79: -1.3682239e+01 -2.3917680e+00 */
    { 0x52bd9edf,0x45e7a06a }, /*  80:  4.0720712e+11  7.4120518e+03 */
    { 0x3f10eb00,0x3f53c57d }, /*  81:  5.6608582e-01  8.2723218e-01 */
    { 0x3f217cd9,0x3f5b8d9f }, /*  82:  6.3081127e-01  8.5762972e-01 */
    { 0xbf1ec33e,0xbf5a4fae }, /*  83: -6.2016666e-01 -8.5277832e-01 */
    { 0x3ff35288,0x3f9e9004 }, /*  84:  1.9009562e+00  1.2387700e+00 */
    { 0x412a2429,0x400cbccd }, /*  85:  1.0633828e+01  2.1990235e+00 */
    { 0x3ef0b5d0,0x3f470f10 }, /*  86:  4.7013712e-01  7.7757359e-01 */
    { 0xc1bbcb3a,0xc0373ffa }, /*  87: -2.3474232e+01 -2.8632798e+00 */
    { 0xbe6d6021,0xbf1d4297 }, /*  88: -2.3181202e-01 -6.1429733e-01 */
    { 0xc27fcc32,0xc07feeba }, /*  89: -6.3949409e+01 -3.9989457e+00 */
    { 0xbd24b58c,0xbeaf691f }, /*  90: -4.0212199e-02 -3.4259889e-01 */
    { 0xbf0e1eda,0xbf526661 }, /*  91: -5.5515826e-01 -8.2187468e-01 */
    { 0x3cf378e2,0x3e9e9859 }, /*  92:  2.9720727e-02  3.0975607e-01 */
    { 0xc0626c54,0xbfc30a3b }, /*  93: -3.5378618e+00 -1.5237497e+00 */
    { 0x42ce617d,0x4096180b }, /*  94:  1.0319041e+02  4.6904349e+00 */
    { 0x3eb07a7b,0x3f337e2d }, /*  95:  3.4468445e-01  7.0114404e-01 */
    { 0x3c4c4773,0x3e6d729c }, /*  96:  1.2468207e-02  2.3188251e-01 */
    { 0xbe20f99a,0xbf0a29d0 }, /*  97: -1.5720215e-01 -5.3970051e-01 */
    { 0xc278e345,0xc07d9b62 }, /*  98: -6.2221943e+01 -3.9626088e+00 */
    { 0xc0c2a193,0xbfe9a62b }, /*  99: -6.0822234e+00 -1.8253835e+00 */
    { 0xb90cb09e,0xbd51b10a }, /* 100: -1.3417235e-04 -5.1194228e-02 */
    { 0x4096a92a,0x3fd6885c }, /* 101:  4.7081499e+00  1.6760364e+00 */
    { 0xbe18f6d6,0xbf07d516 }, /* 102: -1.4937910e-01 -5.3059518e-01 */
    { 0x3fc58137,0x3f93e91a }, /* 103:  1.5430058e+00  1.1555512e+00 */
    { 0x46421edd,0x41b948fc }, /* 104:  1.2423716e+04  2.3160637e+01 */
    { 0xc20c31fe,0xc051720f }, /* 105: -3.5048820e+01 -3.2725866e+00 */
    { 0xc12de535,0xc00dc3dd }, /* 106: -1.0868459e+01 -2.2150795e+00 */
    { 0x4122e59f,0x400ab606 }, /* 107:  1.0181060e+01  2.1673598e+00 */
    { 0xc1355a3f,0xc00fc364 }, /* 108: -1.1334533e+01 -2.2463007e+00 */
    { 0x3e0bb713,0x3f03caa8 }, /* 109:  1.3644056e-01  5.1481104e-01 */
    { 0xbc7e34a7,0xbe7f6686 }, /* 110: -1.5515483e-02 -2.4941453e-01 */
    { 0x3ffc00d1,0x3fa06d1c }, /* 111:  1.9687749e+00  1.2533298e+00 */
    { 0xbfe06630,0xbf9a5736 }, /* 112: -1.7531185e+00 -1.2057865e+00 */
    { 0x3ff451b1,0x3f9ec75e }, /* 113:  1.9087430e+00  1.2404592e+00 */
    { 0x3f203c5b,0x3f5afc00 }, /* 114:  6.2592095e-01  8.5540771e-01 */
    { 0x46cc45c2,0x41ed71f4 }, /* 115:  2.6146879e+04  2.9680641e+01 */
    { 0x3daa9f36,0x3edf9df7 }, /* 116:  8.3311483e-02  4.3675205e-01 */
    { 0xc1f2a62a,0xc0479785 }, /* 117: -3.0331135e+01 -3.1186230e+00 */
    { 0x3c746a53,0x3e7c1425 }, /* 118:  1.4917928e-02  2.4617060e-01 */
    { 0xc907e7f7,0xc2a4862e }, /* 119: -5.5667144e+05 -8.2262070e+01 */
    { 0xbe667a1b,0xbf1bb8c2 }, /* 120: -2.2507517e-01 -6.0828793e-01 */
    { 0xc0d09b50,0xbfef1cdd }, /* 121: -6.5189590e+00 -1.8680683e+00 */
    { 0xbfe56bf9,0xbf9b7bd3 }, /* 122: -1.7923576e+00 -1.2147163e+00 */
    { 0x3d6602b5,0x3ec4108b }, /* 123:  5.6154925e-02  3.8293871e-01 */
    { 0xbf007060,0xbf4b6b5a }, /* 124: -5.0171471e-01 -7.9460680e-01 */
    { 0x3ee2cc3d,0x3f4325c1 }, /* 125:  4.4296446e-01  7.6229483e-01 */
    { 0xbfd96bbf,0xbf98b953 }, /* 126: -1.6986006e+00 -1.1931556e+00 */
    { 0x3fe8b0e5,0x3f9c3800 }, /* 127:  1.8178984e+00  1.2204590e+00 */
    { 0x251e2a88,0x36ad0e74 }, /* 128:  1.3718726e-16  5.1574843e-06 */
    { 0xbf1233fe,0xbf546545 }, /* 129: -5.7110584e-01 -8.2967025e-01 */
    { 0x3f261e3f,0x3f5da1c6 }, /* 130:  6.4889902e-01  8.6574972e-01 */
    { 0x3fce4394,0x3f9610ca }, /* 131:  1.6114373e+00  1.1723874e+00 */
    { 0xba285dad,0xbdb0b302 }, /* 132: -6.4226502e-04 -8.6278930e-02 */
    { 0xbfd02945,0xbf968638 }, /* 133: -1.6262594e+00 -1.1759710e+00 */
    { 0xc06ec572,0xbfc685df }, /* 134: -3.7308011e+00 -1.5509604e+00 */
    { 0x412c5172,0x400d55cf }, /* 135:  1.0769884e+01  2.2083623e+00 */
    { 0x495870a0,0x42c02159 }, /* 136:  8.8653800e+05  9.6065132e+01 */
    { 0xc9465130,0xc2ba9c5c }, /* 137: -8.1230700e+05 -9.3305389e+01 */
    { 0xbfe9b716,0xbf9c7297 }, /* 138: -1.8258998e+00 -1.2222470e+00 */
    { 0x3e5e1619,0x3f19cf00 }, /* 139:  2.1688117e-01  6.0081482e-01 */
    { 0xbe4ee5a5,0xbf16380e }, /* 140: -2.0204790e-01 -5.8679283e-01 */
    { 0xbd3cf306,0xbeb79ffe }, /* 141: -4.6130203e-02 -3.5864252e-01 */
    { 0x4177ca73,0x401f86fe }, /* 142:  1.5486926e+01  2.4926143e+00 */
    { 0xbfe31738,0xbf9af48e }, /* 143: -1.7741461e+00 -1.2105882e+00 */
    { 0xbdfbd86e,0xbefe9b8b }, /* 144: -1.2297140e-01 -4.9728045e-01 */
    { 0x421549f7,0x4055e127 }, /* 145:  3.7322231e+01  3.3418672e+00 */
    { 0xc0ae9614,0xbfe155f0 }, /* 146: -5.4558201e+00 -1.7604351e+00 */
    { 0xbe4a7390,0xbf15229f }, /* 147: -1.9770646e-01 -5.8255953e-01 */
    { 0xbfaefdcd,0xbf8e0ff4 }, /* 148: -1.3671204e+00 -1.1098619e+00 */
    { 0xe6dd243a,0xcc999715 }, /* 149: -5.2215563e+23 -8.0525480e+07 */
    { 0xc1742ade,0xc01ebef5 }, /* 150: -1.5260466e+01 -2.4804051e+00 */
    { 0xc090a375,0xbfd3a29e }, /* 151: -4.5199533e+00 -1.6534002e+00 */
    { 0xc554bda7,0xc170ae97 }, /* 152: -3.4038533e+03 -1.5042624e+01 */
    { 0x3efda0bd,0x3f4a8ecc }, /* 153:  4.9536696e-01  7.9124141e-01 */
    { 0xb5da448a,0xbc40ab6a }, /* 154: -1.6262213e-06 -1.1759618e-02 */
    { 0x42972248,0x408749d6 }, /* 155:  7.5566956e+01  4.2277632e+00 */
    { 0xbf283c68,0xbf5e91df }, /* 156: -6.5717173e-01 -8.6941332e-01 */
    { 0x3f063860,0x3f4e6d3f }, /* 157:  5.2429771e-01  8.0635446e-01 */
    { 0x4097f9e5,0x3fd727b9 }, /* 158:  4.7492547e+00  1.6808997e+00 */
    { 0x4137346c,0x40104043 }, /* 159:  1.1450298e+01  2.2539222e+00 */
    { 0x3f4fce8c,0x3f6ece86 }, /* 160:  8.1174541e-01  9.3283880e-01 */
    { 0x3af23541,0x3dfb514b }, /* 161:  1.8479006e-03  1.2271365e-01 */
    { 0x38e53517,0x3d43d60d }, /* 162:  1.0929460e-04  4.7811557e-02 */
    { 0x43e2c951,0x40f5ddc5 }, /* 163:  4.5357278e+02  7.6833215e+00 */
    { 0x412904b8,0x400c6d5f }, /* 164:  1.0563652e+01  2.1941755e+00 */
    { 0xbd9f6a7a,0xbeda9c3a }, /* 165: -7.7839807e-02 -4.2697316e-01 */
    { 0xb473b026,0xbbc7e058 }, /* 166: -2.2695221e-07 -6.0997419e-03 */
    { 0x3dfbf704,0x3efea5d9 }, /* 167:  1.2302974e-01  4.9735907e-01 */
    { 0xbdef3d21,0xbefa494f }, /* 168: -1.1681581e-01 -4.8884055e-01 */
    { 0x400abc56,0x3fa5a87a }, /* 169:  2.1677451e+00  1.2942040e+00 */
    { 0xbf278aee,0xbf5e4380 }, /* 170: -6.5446365e-01 -8.6821747e-01 */
    { 0x3ff757c2,0x3f9f6e5d }, /* 171:  1.9323657e+00  1.2455555e+00 */
    { 0x413a7ee5,0x40111c11 }, /* 172:  1.1655980e+01  2.2673380e+00 */
    { 0xbdaee17a,0xbee1765b }, /* 173: -8.5391000e-02 -4.4035611e-01 */
    { 0xbe2516f5,0xbf0b54a5 }, /* 174: -1.6122039e-01 -5.4426032e-01 */
    { 0x3fe02c7b,0x3f9a49fa }, /* 175:  1.7513574e+00  1.2053826e+00 */
    { 0xc0b2856d,0xbfe3041c }, /* 176: -5.5787873e+00 -1.7735629e+00 */
    { 0xc233cf27,0xc0638f8a }, /* 177: -4.4952297e+01 -3.5556359e+00 */
    { 0xbeffc28b,0xbf4b1fb1 }, /* 178: -4.9953112e-01 -7.9345232e-01 */
    { 0xbfd9bb30,0xbf98cbea }, /* 179: -1.7010250e+00 -1.1937230e+00 */
    { 0xc3431b3c,0xc0b99925 }, /* 180: -1.9510638e+02 -5.7999444e+00 */
    { 0xbe5697ec,0xbf180f1b }, /* 181: -2.0956391e-01 -5.9398049e-01 */
    { 0xc13d3106,0xc011ce34 }, /* 182: -1.1824469e+01 -2.2782106e+00 */
    { 0xbd494a98,0xbebb89ff }, /* 183: -4.9143404e-02 -3.6628720e-01 */
    { 0xb743d231,0xbcb9d316 }, /* 184: -1.1671845e-05 -2.2683661e-02 */
    { 0x47aeca2c,0x4232eb24 }, /* 185:  8.9492344e+04  4.4729630e+01 */
    { 0xbef0d304,0xbf47171d }, /* 186: -4.7035992e-01 -7.7769643e-01 */
    { 0x417bfe29,0x40206c8c }, /* 187:  1.5749551e+01  2.5066252e+00 */
    { 0xbefd6dd8,0xbf4a813f }, /* 188: -4.9497867e-01 -7.9103464e-01 */
    { 0xc0214eaa,0xbfae31d0 }, /* 189: -2.5204263e+00 -1.3608952e+00 */
    { 0xbee364fc,0xbf435186 }, /* 190: -4.4412982e-01 -7.6296270e-01 */
    { 0xbe030251,0xbf00fec9 }, /* 191: -1.2793852e-01 -5.0388771e-01 */
    { 0xc9a5f539,0xc2dd8f86 }, /* 192: -1.3595271e+06 -1.1078032e+02 */
    { 0xbd67b95c,0xbec48ce0 }, /* 193: -5.6573257e-02 -3.8388729e-01 */
    { 0x447dd085,0x4120cf46 }, /* 194:  1.0152581e+03  1.0050604e+01 */
    { 0xc123da89,0xc00afb67 }, /* 195: -1.0240853e+01 -2.1715944e+00 */
    { 0x488a85fd,0x42836a74 }, /* 196:  2.8369591e+05  6.5707916e+01 */
    { 0x3f0063c6,0x3f4b64b3 }, /* 197:  5.0152242e-01  7.9450530e-01 */
    { 0x3f01a902,0x3f4c0fe1 }, /* 198:  5.0648510e-01  7.9711729e-01 */
    { 0xc360a3aa,0xc0c286c3 }, /* 199: -2.2463931e+02 -6.0789504e+00 */
    { 0xbf295d66,0xbf5f1108 }, /* 200: -6.6158140e-01 -8.7135363e-01 */
    { 0xbfaedddd,0xbf8e074f }, /* 201: -1.3661457e+00 -1.1095980e+00 */
    { 0x3f5f1531,0x3f748541 }, /* 202:  8.7141711e-01  9.5515829e-01 */
    { 0xbf39eec9,0xbf661d7d }, /* 203: -7.2629982e-01 -8.9888746e-01 */
    { 0xb8da8f06,0xbd40c152 }, /* 204: -1.0421690e-04 -4.7059365e-02 */
    { 0xbd74399d,0xbec805e7 }, /* 205: -5.9625257e-02 -3.9067003e-01 */
    { 0x3e0fb97e,0x3f050a5a }, /* 206:  1.4035603e-01  5.1968920e-01 */
    { 0x3f800000,0x3f800000 }, /* 207:  1.0000000e+00  1.0000000e+00 */
    { 0x3b63f430,0x3e1b26c1 }, /* 208:  3.4782998e-03  1.5151502e-01 */
    { 0xc19ec38c,0xc02d4631 }, /* 209: -1.9845482e+01 -2.7074091e+00 */
    { 0x3fe9092d,0x3f9c4bbf }, /* 210:  1.8205925e+00  1.2210616e+00 */
    { 0xbe8728d2,0xbf2438e8 }, /* 211: -2.6398331e-01 -6.4149332e-01 */
    { 0xbf13380c,0xbf54e2e9 }, /* 212: -5.7507396e-01 -8.3158737e-01 */
    { 0xbe1d06bf,0xbf090636 }, /* 213: -1.5334605e-01 -5.3525102e-01 */
    { 0x3f06f973,0x3f4ed00b }, /* 214:  5.2724379e-01  8.0786198e-01 */
    { 0xc0091480,0xbfa4ff1b }, /* 215: -2.1418762e+00 -1.2890352e+00 */
    { 0xc20a0a50,0xc0505de9 }, /* 216: -3.4510071e+01 -3.2557318e+00 */
    { 0x3da7eddc,0x3ede6f36 }, /* 217:  8.1996650e-02  4.3444222e-01 */
    { 0xc8e3f2b6,0xc29b266b }, /* 218: -4.6683769e+05 -7.7575035e+01 */
    { 0xc159dc9c,0xc018d3bb }, /* 219: -1.3616360e+01 -2.3879230e+00 */
    { 0xbf1295aa,0xbf549487 }, /* 220: -5.7259619e-01 -8.3039135e-01 */
    { 0x3f13a324,0x3f55167c }, /* 221:  5.7670808e-01  8.3237433e-01 */
    { 0xc000aa3e,0xbfa18c77 }, /* 222: -2.0103908e+00 -1.2620991e+00 */
    { 0xbff61997,0xbf9f29e3 }, /* 223: -1.9226559e+00 -1.2434658e+00 */
    { 0x3da5d988,0x3edd8333 }, /* 224:  8.0981314e-02  4.3264160e-01 */
    { 0xbfeff51d,0xbf9dd408 }, /* 225: -1.8746678e+00 -1.2330332e+00 */
    { 0x4288c178,0x4082dabd }, /* 226:  6.8377869e+01  4.0892015e+00 */
    { 0x95c9bc7f,0xb194f59d }, /* 227: -8.1480648e-26 -4.3352899e-09 */
    { 0x3ff94a34,0x3f9fd92e }, /* 228:  1.9475770e+00  1.2488153e+00 */
    { 0x44402f41,0x41129203 }, /* 229:  7.6873834e+02  9.1606474e+00 */
    { 0x3cff0eba,0x3ea1125e }, /* 230:  3.1134952e-02  3.1459326e-01 */
    { 0xbc503b6e,0xbe6ef835 }, /* 231: -1.2709482e-02 -2.3336871e-01 */
    { 0xb0b317b8,0xba8f29e1 }, /* 232: -1.3030705e-09 -1.0922515e-03 */
    { 0x3e1bf412,0x3f08b622 }, /* 233:  1.5229824e-01  5.3402913e-01 */
    { 0xc0f37d65,0xbffbc296 }, /* 234: -7.6090569e+00 -1.9668758e+00 */
    { 0xbce0bab7,0xbe9a6a95 }, /* 235: -2.7432783e-02 -3.0159441e-01 */
    { 0xbd81f737,0xbecc38e0 }, /* 236: -6.3459806e-02 -3.9887142e-01 */
    { 0xbf45f153,0xbf6af77e }, /* 237: -7.7321357e-01 -9.1783893e-01 */
    { 0xbd448384,0xbeba0b1d }, /* 238: -4.7976986e-02 -3.6336604e-01 */
    { 0x3f146818,0x3f557513 }, /* 239:  5.7971334e-01  8.3381766e-01 */
    { 0xbeeb009a,0xbf45790c }, /* 240: -4.5898896e-01 -7.7137828e-01 */
    { 0x3e60c9a0,0x3f1a6dff }, /* 241:  2.1951914e-01  6.0324091e-01 */
    { 0x43591de6,0x40c05491 }, /* 242:  2.1711679e+02  6.0103230e+00 */
    { 0x3d6e28ee,0x3ec65a74 }, /* 243:  5.8144502e-02  3.8740885e-01 */
    { 0x3f1fa0c7,0x3f5ab50a }, /* 244:  6.2354702e-01  8.5432494e-01 */
    { 0x3f1708e5,0x3f56b5c2 }, /* 245:  5.8997947e-01  8.3871090e-01 */
    { 0xc099eb19,0xbfd8115d }, /* 246: -4.8099484e+00 -1.6880299e+00 */
    { 0x3f227d1d,0x3f5c0185 }, /* 247:  6.3472158e-01  8.5939819e-01 */
    { 0x40fa7fed,0x3ffe273d }, /* 248:  7.8281159e+00  1.9855725e+00 */
    { 0x377ff462,0x3ccb2ce2 }, /* 249:  1.5256084e-05  2.4801675e-02 */
    { 0x339cfa1d,0x3b89028a }, /* 250:  7.3098114e-08  4.1812109e-03 */
    { 0xbe4fa62c,0xbf166698 }, /* 251: -2.0278233e-01 -5.8750296e-01 */
    { 0x41d18c81,0x403e11b7 }, /* 252:  2.6193605e+01  2.9698312e+00 */
    { 0x3fff12d2,0x3fa1133a }, /* 253:  1.9927619e+00  1.2583992e+00 */
    { 0xbefd8d1f,0xbf4a8993 }, /* 254: -4.9521729e-01 -7.9116172e-01 */
    { 0x4157f595,0x40186185 }, /* 255:  1.3497457e+01  2.3809521e+00 */
    { 0xc0861603,0xbfce5b9f }, /* 256: -4.1901870e+00 -1.6121711e+00 */
    { 0x41e48c40,0x4043a5ec }, /* 257:  2.8568481e+01  3.0570021e+00 */
    { 0xbba66369,0xbe300134 }, /* 258: -5.0777686e-03 -1.7187959e-01 */
    { 0x4cfc5899,0x43fec6b4 }, /* 259:  1.3230202e+08  5.0955237e+02 */
    { 0xc13db2b0,0xc011ef7c }, /* 260: -1.1856125e+01 -2.2802420e+00 */
    { 0x6332066e,0x4b62ce3b }, /* 261:  3.2839838e+21  1.4863931e+07 */
    { 0x39757fbf,0x3d7c7360 }, /* 262:  2.3412610e-04  6.1633468e-02 */
    { 0x3fdc0ab1,0x3f9955cc }, /* 263:  1.7190763e+00  1.1979308e+00 */
    { 0xc0ba5494,0xbfe64774 }, /* 264: -5.8228245e+00 -1.7990556e+00 */
    { 0x3feba066,0x3f9cdf7a }, /* 265:  1.8408325e+00  1.2255700e+00 */
    { 0x3e5f7348,0x3f1a1f72 }, /* 266:  2.1821320e-01  6.0204232e-01 */
    { 0x46c10b8a,0x41e9033f }, /* 267:  2.4709770e+04  2.9126585e+01 */
    { 0x3e3117da,0x3f0ea0fa }, /* 268:  1.7294255e-01  5.5714381e-01 */
    { 0xbfcff506,0xbf96799f }, /* 269: -1.6246650e+00 -1.1755866e+00 */
    { 0x3e204ccb,0x3f09f84e }, /* 270:  1.5654294e-01  5.3894508e-01 */
    { 0xba8237fb,0xbdcc5ac6 }, /* 271: -9.9348964e-04 -9.9782512e-02 */
    { 0xc48cd8f1,0xc1267e91 }, /* 272: -1.1267794e+03 -1.0405900e+01 */
    { 0xc0ff3972,0xbfffbdc0 }, /* 273: -7.9757624e+00 -1.9979782e+00 */
    { 0x43f7727c,0x40fd1de1 }, /* 274:  4.9489441e+02  7.9098973e+00 */
    { 0xc16e283d,0xc01d6ebc }, /* 275: -1.4884824e+01 -2.4598837e+00 */
    { 0x4aaa797b,0x43316f11 }, /* 276:  5.5861095e+06  1.7743385e+02 */
    { 0x3e748588,0x3f1ed298 }, /* 277:  2.3879063e-01  6.2040091e-01 */
    { 0x3c36154b,0x3e648418 }, /* 278:  1.1113475e-02  2.2316015e-01 */
    { 0x39e7b993,0x3d9c0094 }, /* 279:  4.4198017e-04  7.6172978e-02 */
    { 0xbde45175,0xbef66b29 }, /* 280: -1.1148349e-01 -4.8128632e-01 */
    { 0x3f13be29,0x3f55237b }, /* 281:  5.7712036e-01  8.3257264e-01 */
    { 0xc1f21394,0xc0476f4c }, /* 282: -3.0259560e+01 -3.1161680e+00 */
    { 0x3e6372f2,0x3f1b0969 }, /* 283:  2.2211817e-01  6.0561234e-01 */
    { 0x43276f38,0x40b05f6f }, /* 284:  1.6743445e+02  5.5116496e+00 */
    { 0x4067a817,0x3fc487fe }, /* 285:  3.6196344e+00  1.5354002e+00 */
    { 0x3e755400,0x3f1eff3f }, /* 286:  2.3957825e-01  6.2108225e-01 */
    { 0xc183b313,0xc022cf11 }, /* 287: -1.6462439e+01 -2.5438883e+00 */
    { 0xbc7aba8d,0xbe7e3b0f }, /* 288: -1.5303266e-02 -2.4827217e-01 */
    { 0xbe803ffd,0xbf215ff3 }, /* 289: -2.5048819e-01 -6.3037032e-01 */
    { 0x44037831,0x4101256e }, /* 290:  5.2587799e+02  8.0716381e+00 */
    { 0x342b7d4a,0x3bb1c907 }, /* 291:  1.5971196e-07  5.4255757e-03 */
    { 0x412ae0e7,0x400cf0c5 }, /* 292:  1.0679908e+01  2.2021954e+00 */
    { 0xc581a221,0xc1808aca }, /* 293: -4.1482661e+03 -1.6067768e+01 */
    { 0xc10eff66,0xc004d0d6 }, /* 294: -8.9373531e+00 -2.0752463e+00 */
    { 0xbf179827,0xbf56f98f }, /* 295: -5.9216541e-01 -8.3974546e-01 */
    { 0x3eff5149,0x3f4b01b1 }, /* 296:  4.9866703e-01  7.9299456e-01 */
    { 0x39b1914f,0x3d8ec18d }, /* 297:  3.3868334e-04  6.9705106e-02 */
    { 0xc1bce286,0xc0379aa6 }, /* 298: -2.3610607e+01 -2.8688140e+00 */
    { 0xbfd34146,0xbf97442f }, /* 299: -1.6504295e+00 -1.1817683e+00 */
    { 0xac0a14f6,0xb90346ac }, /* 300: -1.9622615e-12 -1.2519461e-04 */
    { 0xbd1fe9d6,0xbeadb0ff }, /* 301: -3.9041363e-02 -3.3924100e-01 */
    { 0xbf3fe8dc,0xbf688e10 }, /* 302: -7.4964690e-01 -9.0841770e-01 */
    { 0x40e63c42,0x3ff71b3d }, /* 303:  7.1948557e+00  1.9305187e+00 */
    { 0x3e5120dd,0x3f16c1ce }, /* 304:  2.0422693e-01  5.8889472e-01 */
    { 0x3daf1df1,0x3ee19054 }, /* 305:  8.5506327e-02  4.4055426e-01 */
    { 0xbf066127,0xbf4e8224 }, /* 306: -5.2491993e-01 -8.0667329e-01 */
    { 0x3fd4fce9,0x3f97adc8 }, /* 307:  1.6639682e+00  1.1849909e+00 */
    { 0x3c686d34,0x3e77e34a }, /* 308:  1.4186192e-02  2.4207798e-01 */
    { 0x41538386,0x401753fd }, /* 309:  1.3219610e+01  2.3645012e+00 */
    { 0xbc15a0a8,0xbe560a86 }, /* 310: -9.1325417e-03 -2.0902452e-01 */
    { 0xbd997240,0xbed7d8c2 }, /* 311: -7.4924946e-02 -4.2157561e-01 */
    { 0x4053ccbc,0x3fbebf51 }, /* 312:  3.3093710e+00  1.4902135e+00 */
    { 0x413e4072,0x401213cd }, /* 313:  1.1890734e+01  2.2824585e+00 */
    { 0xc07ec394,0xbfcadc1c }, /* 314: -3.9806871e+00 -1.5848422e+00 */
    { 0x3f38c5c5,0x3f65a2b3 }, /* 315:  7.2176772e-01  8.9701384e-01 */
    { 0x4330eb8d,0x40b3a47a }, /* 316:  1.7692012e+02  5.6138277e+00 */
    { 0x40b8158b,0x3fe5599b }, /* 317:  5.7526298e+00  1.7917970e+00 */
    { 0xbf4a6325,0xbf6cb661 }, /* 318: -7.9057533e-01 -9.2465788e-01 */
    { 0x3dbd92a7,0x3ee79b71 }, /* 319:  9.2564873e-02  4.5235780e-01 */
    { 0x40fdfda5,0x3fff5419 }, /* 320:  7.9372125e+00  1.9947540e+00 */
    { 0x3e8786cb,0x3f245eef }, /* 321:  2.6470026e-01  6.4207357e-01 */
    { 0x3d6f6192,0x3ec6b11a }, /* 322:  5.8442660e-02  3.8806993e-01 */
    { 0xc1a629fa,0xc02fecf1 }, /* 323: -2.0770496e+01 -2.7488368e+00 */
    { 0x3f3bc8a7,0x3f66e055 }, /* 324:  7.3353046e-01  9.0186054e-01 */
    { 0x3b8b4208,0x3e25dda0 }, /* 325:  4.2498149e-03  1.6197824e-01 */
    { 0xb8b3a2c5,0xbd348e96 }, /* 326: -8.5657033e-05 -4.4081293e-02 */
    { 0x415ecbc7,0x4019f8e5 }, /* 327:  1.3924750e+01  2.4058163e+00 */
    { 0xbfd3ddbe,0xbf97697e }, /* 328: -1.6552045e+00 -1.1829069e+00 */
    { 0x415b0acc,0x40191a44 }, /* 329:  1.3690136e+01  2.3922281e+00 */
    { 0x3e26c1d6,0x3f0bcc55 }, /* 330:  1.6284880e-01  5.4608661e-01 */
    { 0x3e076072,0x3f0269c3 }, /* 331:  1.3220385e-01  5.0942630e-01 */
    { 0xbcb392a1,0xbe8f4a99 }, /* 332: -2.1920504e-02 -2.7986601e-01 */
    { 0x43ca096b,0x40ec9361 }, /* 333:  4.0407358e+02  7.3929906e+00 */
    { 0xbfa247ac,0xbf8a8922 }, /* 334: -1.2678123e+00 -1.0823100e+00 */
    { 0xbf244460,0xbf5cce3f }, /* 335: -6.4166832e-01 -8.6252207e-01 */
    { 0x3e74a217,0x3f1ed8c7 }, /* 336:  2.3889957e-01  6.2049526e-01 */
    { 0x3fc41617,0x3f938e3c }, /* 337:  1.5319241e+00  1.1527781e+00 */
    { 0xb35dae17,0xbb7401c7 }, /* 338: -5.1613906e-08 -3.7232505e-03 */
    { 0xbd715338,0xbec73a6b }, /* 339: -5.8917254e-02 -3.8911757e-01 */
    { 0x3f226024,0x3f5bf470 }, /* 340:  6.3427949e-01  8.5919857e-01 */
    { 0xb9b589d0,0xbd8fcff4 }, /* 341: -3.4625689e-04 -7.0220858e-02 */
    { 0xbf2a4506,0xbf5f768a }, /* 342: -6.6511571e-01 -8.7290251e-01 */
    { 0xbfd3886c,0xbf975528 }, /* 343: -1.6526008e+00 -1.1822863e+00 */
    { 0x3f219f9a,0x3f5b9d5e }, /* 344:  6.3134158e-01  8.5786998e-01 */
    { 0xbe162f74,0xbf07013a }, /* 345: -1.4666539e-01 -5.2736247e-01 */
    { 0xc0ec5e65,0xbff9480e }, /* 346: -7.3865228e+00 -1.9475114e+00 */
    { 0x3dd20edc,0x3eefaa7f }, /* 347:  1.0256740e-01  4.6809766e-01 */
    { 0xc1dcb1c7,0xc0416189 }, /* 348: -2.7586805e+01 -3.0215781e+00 */
    { 0x3d845764,0x3ecd7581 }, /* 349:  6.4619809e-02  4.0128711e-01 */
    { 0x43cc6308,0x40ed7d4b }, /* 350:  4.0877368e+02  7.4215446e+00 */
    { 0x3fddc2b3,0x3f99bbbc }, /* 351:  1.7325042e+00  1.2010417e+00 */
    { 0xbf2eb221,0xbf616201 }, /* 352: -6.8240553e-01 -8.8040167e-01 */
    { 0x3e3279e0,0x3f0effc5 }, /* 353:  1.7429304e-01  5.5859023e-01 */
    { 0xbfe67b0c,0xbf9bb8f8 }, /* 354: -1.8006301e+00 -1.2165823e+00 */
    { 0x4f062bee,0x44a3d23c }, /* 355:  2.2510259e+09  1.3105698e+03 */
    { 0xbe55bd2d,0xbf17db5e }, /* 356: -2.0872946e-01 -5.9319103e-01 */
    { 0xbf29e98a,0xbf5f4e7d }, /* 357: -6.6371977e-01 -8.7229139e-01 */
    { 0xbf1fa0c4,0xbf5ab508 }, /* 358: -6.2354684e-01 -8.5432482e-01 */
    { 0x3b7324fa,0x3e1e861f }, /* 359:  3.7100897e-03  1.5480851e-01 */
    { 0x3f1fcd4a,0x3f5ac95c }, /* 360:  6.2422621e-01  8.5463500e-01 */
    { 0xbe85c469,0xbf23a80f }, /* 361: -2.6126412e-01 -6.3928312e-01 */
    { 0xbce1e702,0xbe9aaf3e }, /* 362: -2.7575973e-02 -3.0211824e-01 */
    { 0xdb3478ad,0xc8b4d625 }, /* 363: -5.0798180e+16 -3.7035316e+05 */
    { 0x3d5b8f72,0x3ec10c96 }, /* 364:  5.3603597e-02  3.7704915e-01 */
    { 0xbdbf8d75,0xbee8691e }, /* 365: -9.3531527e-02 -4.5392698e-01 */
    { 0x3ff4e5ca,0x3f9ee76d }, /* 366:  1.9132626e+00  1.2414376e+00 */
    { 0x3f1bcbbd,0x3f58f15c }, /* 367:  6.0857755e-01  8.4743285e-01 */
    { 0x43cc1ca5,0x40ed6205 }, /* 368:  4.0822379e+02  7.4182153e+00 */
    { 0x3f2663fc,0x3f5dc0c6 }, /* 369:  6.4996314e-01  8.6622274e-01 */
    { 0xbff7b3ce,0xbf9f8222 }, /* 370: -1.9351747e+00 -1.2461588e+00 */
    { 0x3d1d4ae1,0x3eacbcbc }, /* 371:  3.8401488e-02  3.3737743e-01 */
    { 0xbf22a1cb,0xbf5c1211 }, /* 372: -6.3528126e-01 -8.5965067e-01 */
    { 0xbf800000,0xbf800000 }, /* 373: -1.0000000e+00 -1.0000000e+00 */
    { 0xbf29fffb,0xbf5f5851 }, /* 374: -6.6406220e-01 -8.7244135e-01 */
    { 0x41e67238,0x40443036 }, /* 375:  2.8805771e+01  3.0654426e+00 */
    { 0x3a376eb1,0x3db5d1f5 }, /* 376:  6.9973903e-04  8.8779368e-02 */
    { 0xbbd5fdf1,0xbe3f6736 }, /* 377: -6.5305163e-03 -1.8691716e-01 */
    { 0xbda5743a,0xbedd5610 }, /* 378: -8.0788091e-02 -4.3229723e-01 */
    { 0xb481dc27,0xbbcc2ab2 }, /* 379: -2.4188304e-07 -6.2306756e-03 */
    { 0xc2416096,0xc0692572 }, /* 380: -4.8344322e+01 -3.6429105e+00 */
    { 0xc30a6f42,0xc0a589c7 }, /* 381: -1.3843460e+02 -5.1730685e+00 */
    { 0x3f067d74,0x3f4e90a3 }, /* 382:  5.2535176e-01  8.0689448e-01 */
    { 0x335b38b1,0x3b7319fd }, /* 383:  5.1041471e-08  3.7094348e-03 */
    { 0xbf4ea70a,0xbf6e5d1e }, /* 384: -8.0723631e-01 -9.3110836e-01 */
    { 0x4149f6b2,0x401503ef }, /* 385:  1.2622728e+01  2.3283651e+00 */
    { 0x3ea1478f,0x3f2e2f41 }, /* 386:  3.1499907e-01  6.8040854e-01 */
    { 0x3e689d72,0x3f1c33a6 }, /* 387:  2.2716311e-01  6.1016309e-01 */
    { 0x3ddc9588,0x3ef39aab }, /* 388:  1.0770708e-01  4.7578940e-01 */
    { 0xc20bcfb3,0xc0514110 }, /* 389: -3.4952831e+01 -3.2695961e+00 */
    { 0xc0db6fa4,0xbff32e4b }, /* 390: -6.8573780e+00 -1.8998502e+00 */
    { 0xbd602eaf,0xbec264f9 }, /* 391: -5.4732021e-02 -3.7967661e-01 */
    { 0xbf3b4cc8,0xbf66ad86 }, /* 392: -7.3164034e-01 -9.0108526e-01 */
    { 0x40c0c024,0x3fe8e4e5 }, /* 393:  6.0234547e+00  1.8194853e+00 */
    { 0x4649e85a,0x41bbbaf0 }, /* 394:  1.2922088e+04  2.3466278e+01 */
    { 0xc272542d,0xc07b5bfc }, /* 395: -6.0582203e+01 -3.9274893e+00 */
    { 0xbe3fe49b,0xbf127f07 }, /* 396: -1.8739550e-01 -5.7225078e-01 */
    { 0x3e40a41d,0x3f12afb2 }, /* 397:  1.8812604e-01  5.7299340e-01 */
    { 0xc243a901,0xc06a0f65 }, /* 398: -4.8915043e+01 -3.6571896e+00 */
    { 0x3d26766a,0x3eb007e7 }, /* 399:  4.0640272e-02  3.4381029e-01 */
    { 0x4a22637c,0x430a910b }, /* 400:  2.6605750e+06  1.3856657e+02 */
    { 0xd0b22e6f,0xc5341180 }, /* 401: -2.3915100e+10 -2.8810938e+03 */
    { 0x3f0cc73a,0x3f51bc45 }, /* 402:  5.4991496e-01  8.1927902e-01 */
    { 0xbfb115cc,0xbf8ea06c }, /* 403: -1.3834777e+00 -1.1142707e+00 */
    { 0xc190f112,0xc028179f }, /* 404: -1.8117710e+01 -2.6264417e+00 */
    { 0x3e3b9dbf,0x3f116651 }, /* 405:  1.8321894e-01  5.6796747e-01 */
    { 0x3f1cf5e4,0x3f597b68 }, /* 406:  6.1312699e-01  8.4953928e-01 */
    { 0x42742e47,0x407bff7e }, /* 407:  6.1045193e+01  3.9374690e+00 */
    { 0xb748f776,0xbcbb702a }, /* 408: -1.1978545e-05 -2.2880632e-02 */
    { 0xbd92565b,0xbed475e8 }, /* 409: -7.1453772e-02 -4.1496205e-01 */
    { 0xbf126957,0xbf547f18 }, /* 410: -5.7191986e-01 -8.3006430e-01 */
    { 0xbf0968f6,0xbf500c9a }, /* 411: -5.3675783e-01 -8.1269228e-01 */
    { 0x3f800000,0x3f800000 }, /* 412:  1.0000000e+00  1.0000000e+00 */
    { 0x3fbe97f3,0x3f922a2f }, /* 413:  1.4890121e+00  1.1419123e+00 */
    { 0x3e42a105,0x3f13306d }, /* 414:  1.9006737e-01  5.7495767e-01 */
    { 0x466dcf81,0x41c6419e }, /* 415:  1.5219876e+04  2.4782040e+01 */
    { 0x42892289,0x4082f9ac }, /* 416:  6.8567451e+01  4.0929775e+00 */
    { 0xa9f1323c,0xb8473157 }, /* 417: -1.0711264e-13 -4.7491249e-05 */
    { 0xc3027058,0xc0a249a7 }, /* 418: -1.3043884e+02 -5.0714908e+00 */
    { 0xc31a5438,0xc0aba541 }, /* 419: -1.5432898e+02 -5.3639226e+00 */
    { 0xbc9fc0b7,0xbe89d012 }, /* 420: -1.9501073e-02 -2.6916558e-01 */
    { 0x407292c5,0x3fc79234 }, /* 421:  3.7902081e+00  1.5591493e+00 */
    { 0x3e48400d,0x3f1497bf }, /* 422:  1.9555683e-01  5.8044046e-01 */
    { 0x44abf26f,0x4131f179 }, /* 423:  1.3755760e+03  1.1121453e+01 */
    { 0xbd0ab66f,0xbea5a621 }, /* 424: -3.3865388e-02 -3.2353309e-01 */
    { 0xb10656a8,0xbaa3e39e }, /* 425: -1.9548825e-09 -1.2503748e-03 */
    { 0xbd13f138,0xbea93e8b }, /* 426: -3.6118716e-02 -3.3055529e-01 */
    { 0x42c2586b,0x40931e1d }, /* 427:  9.7172691e+01  4.5974259e+00 */
    { 0xc0041a14,0xbfa2f978 }, /* 428: -2.0640917e+00 -1.2732382e+00 */
    { 0xbff8413f,0xbf9fa078 }, /* 429: -1.9394912e+00 -1.2470846e+00 */
    { 0x29be80bf,0x3838207b }, /* 430:  8.4600289e-14  4.3899268e-05 */
    { 0xc6d5194f,0xc1f0d122 }, /* 431: -2.7276654e+04 -3.0102116e+01 */
    { 0x3ded6ec2,0x3ef9a7a9 }, /* 432:  1.1593391e-01  4.8760727e-01 */
    { 0xbfe9a1cc,0xbf9c6dd7 }, /* 433: -1.8252501e+00 -1.2221020e+00 */
    { 0xbe23234e,0xbf0ac785 }, /* 434: -1.5931436e-01 -5.4210693e-01 */
    { 0xbe556ab5,0xbf17c7d4 }, /* 435: -2.0841487e-01 -5.9289289e-01 */
    { 0xc20649f3,0xc04e7641 }, /* 436: -3.3572216e+01 -3.2259676e+00 */
    { 0x42400544,0x40689989 }, /* 437:  4.8005142e+01  3.6343710e+00 */
    { 0xbc7cddfa,0xbe7ef390 }, /* 438: -1.5433783e-02 -2.4897599e-01 */
    { 0xc19fa339,0xc02d976a }, /* 439: -1.9954699e+01 -2.7123666e+00 */
    { 0xb65ee486,0xbc747378 }, /* 440: -3.3213596e-06 -1.4920108e-02 */
    { 0xc1b814d2,0xc03608c8 }, /* 441: -2.3010166e+01 -2.8442860e+00 */
    { 0xbf223286,0xbf5bdfd5 }, /* 442: -6.3358343e-01 -8.5888416e-01 */
    { 0xbe0c7d5d,0xbf0408e3 }, /* 443: -1.3719697e-01 -5.1576060e-01 */
    { 0x3d43ec5a,0x3eb9db5c }, /* 444:  4.7832824e-02  3.6300170e-01 */
    { 0x3ff06567,0x3f9deca3 }, /* 445:  1.8780946e+00  1.2337841e+00 */
    { 0x415db336,0x4019b828 }, /* 446:  1.3856253e+01  2.4018650e+00 */
    { 0xbd95f85b,0xbed6344f }, /* 447: -7.3227607e-02 -4.1836783e-01 */
    { 0xbe9291e0,0xbf28b826 }, /* 448: -2.8626919e-01 -6.5905988e-01 */
    { 0xc0b4feef,0xbfe40f69 }, /* 449: -5.6561198e+00 -1.7817203e+00 */
    { 0x425c8bf5,0x40739724 }, /* 450:  5.5136677e+01  3.8060999e+00 */
    { 0xbe10e20a,0xbf05659c }, /* 451: -1.4148727e-01 -5.2108169e-01 */
    { 0xe1071d46,0xcaa4343b }, /* 452: -1.5577624e+20 -5.3806375e+06 */
    { 0xbe192579,0xbf07e2e2 }, /* 453: -1.4955701e-01 -5.3080571e-01 */
    { 0xc4be5a3b,0xc1381411 }, /* 454: -1.5228197e+03 -1.1504899e+01 */
    { 0x42d65b6f,0x409800d0 }, /* 455:  1.0717858e+02  4.7500992e+00 */
    { 0x41e512c0,0x4043cc45 }, /* 456:  2.8634155e+01  3.0593426e+00 */
    { 0xbd18bf81,0xbeab0eb2 }, /* 457: -3.7292007e-02 -3.3409649e-01 */
    { 0xbfe09bb0,0xbf9a637a }, /* 458: -1.7547512e+00 -1.2061608e+00 */
    { 0x3bb74191,0x3e35c30b }, /* 459:  5.5925329e-03  1.7750184e-01 */
    { 0x409c5470,0x3fd930bd }, /* 460:  4.8853073e+00  1.6967999e+00 */
    { 0xbfcdf459,0xbf95fd91 }, /* 461: -1.6090194e+00 -1.1718007e+00 */
    { 0xc2ee945a,0xc09d868b }, /* 462: -1.1928975e+02 -4.9226737e+00 */
    { 0x4a1b3907,0x43087f65 }, /* 463:  2.5431698e+06  1.3649763e+02 */
    { 0x3e284142,0x3f0c3728 }, /* 464:  1.6431144e-01  5.4771662e-01 */
    { 0x401bf5a1,0x3fac3f76 }, /* 465:  2.4368670e+00  1.3456867e+00 */
    { 0xbd2c7172,0xbeb21d3e }, /* 466: -4.2100377e-02 -3.4787935e-01 */
    { 0xc1047b24,0xc0017a01 }, /* 467: -8.2800636e+00 -2.0230715e+00 */
    { 0xbd8b24a9,0xbed0eb99 }, /* 468: -6.7941017e-02 -4.0804747e-01 */
    { 0xc553ecb5,0xc1705fb1 }, /* 469: -3.3907942e+03 -1.5023362e+01 */
    { 0x3ae8ed4e,0x3df810cc }, /* 470:  1.7770918e-03  1.2112579e-01 */
    { 0xc05d03a5,0xbfc1796f }, /* 471: -3.4533474e+00 -1.5115184e+00 */
    { 0x3da3c24f,0x3edc93e8 }, /* 472:  7.9960458e-02  4.3081594e-01 */
    { 0x3c263cee,0x3e5daf6b }, /* 473:  1.0146363e-02  2.1648948e-01 */
    { 0x4257ff66,0x4071e76a }, /* 474:  5.3999413e+01  3.7797494e+00 */
    { 0x3e3a14d0,0x3f110088 }, /* 475:  1.8172002e-01  5.6641436e-01 */
    { 0xcabea454,0xc3382bf1 }, /* 476: -6.2469540e+06 -1.8417165e+02 */
    { 0xc1b2ac36,0xc0343bd5 }, /* 477: -2.2334087e+01 -2.8161519e+00 */
    { 0xc11e65af,0xc0096bff }, /* 478: -9.8998251e+00 -2.1472166e+00 */
    { 0x3efeabd2,0x3f4ad5cd }, /* 479:  4.9740463e-01  7.9232484e-01 */
    { 0x324f209b,0x3b164651 }, /* 480:  1.2056399e-08  2.2930095e-03 */
    { 0xbf138787,0xbf550932 }, /* 481: -5.7628673e-01 -8.3217156e-01 */
    { 0xc3960542,0xc0d63a73 }, /* 482: -3.0004108e+02 -6.6946349e+00 */
    { 0x3f2dc6a7,0x3f60fc8f }, /* 483:  6.7881244e-01  8.7885374e-01 */
    { 0xc0f95120,0xbffdc0ac }, /* 484: -7.7911530e+00 -1.9824424e+00 */
    { 0x3f1bae54,0x3f58e3b5 }, /* 485:  6.0812879e-01  8.4722453e-01 */
    { 0x4123e085,0x400afd18 }, /* 486:  1.0242314e+01  2.1716976e+00 */
    { 0xc33266bb,0xc0b42475 }, /* 487: -1.7840129e+02 -5.6294503e+00 */
    { 0x3f0e5f7f,0x3f528643 }, /* 488:  5.5614465e-01  8.2236117e-01 */
    { 0xbbf96b05,0xbe496e4b }, /* 489: -7.6116347e-03 -1.9670980e-01 */
    { 0x40c972a1,0x3fec5877 }, /* 490:  6.2952428e+00  1.8464497e+00 */
    { 0xbddb39f6,0xbef31a75 }, /* 491: -1.0704415e-01 -4.7481123e-01 */
    { 0x3f218ace,0x3f5b93f2 }, /* 492:  6.3102424e-01  8.5772622e-01 */
    { 0xbe868fe3,0xbf23fae1 }, /* 493: -2.6281652e-01 -6.4054686e-01 */
    { 0x3fc413cb,0x3f938da9 }, /* 494:  1.5318540e+00  1.1527606e+00 */
    { 0x3e685782,0x3f1c23fd }, /* 495:  2.2689632e-01  6.0992414e-01 */
    { 0x4264b37f,0x40768e69 }, /* 496:  5.7175289e+01  3.8524420e+00 */
    { 0x45fc25ea,0x41a074fb }, /* 497:  8.0687393e+03  2.0057119e+01 */
    { 0xbff10e85,0xbf9e11a3 }, /* 498: -1.8832556e+00 -1.2349132e+00 */
    { 0xc10124fb,0xc000615f }, /* 499: -8.0715284e+00 -2.0059431e+00 */
    { 0x3f214571,0x3f5b7480 }, /* 500:  6.2996584e-01  8.5724640e-01 */

};

int main ()
{
    int i;
    union float_u tx, tz;

    for (i = 0;  (size_t)i < sizeof(t) / sizeof(t[0]); i++) {
	tx.u32 = pgm_read_dword (& t[i].x);
	tz.u32 = pgm_read_dword (& t[i].z);
	v.flt = cbrt (tx.flt);
	if ((v.u32 - tz.u32) > ULPMAX && (tz.u32 - v.u32) > ULPMAX) {
	    PRINTFLN ("t1[%d]={0x%08lx,0x%08lx} --> 0x%08lx\n",
		      i, tx.u32, tz.u32, v.u32);
	    EXIT (i + 1);
	}
    }

    return 0;
}
