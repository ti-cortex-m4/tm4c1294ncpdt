#include "../../main.h"


/*
MdUns muCodeBitArr(unsigned char pdataout, unsigned char pdatain, MdUns length) {
  MdUns            wiId = 0, woId = 0;
  UINT8_BITS       in_data, out_data;

  if (length == 0) return 0;

  for (;;) {
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b0 = in_data.bits.b0;
    out_data.bits.b1 = in_data.bits.b1;
    out_data.bits.b2 = in_data.bits.b2;
    out_data.bits.b3 = in_data.bits.b3;
    out_data.bits.b4 = in_data.bits.b4;
    out_data.bits.b5 = in_data.bits.b5;
    out_data.bits.b6 = in_data.bits.b6;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b1 = in_data.bits.b0;
    out_data.bits.b2 = in_data.bits.b1;
    out_data.bits.b3 = in_data.bits.b2;
    out_data.bits.b4 = in_data.bits.b3;
    out_data.bits.b5 = in_data.bits.b4;
    out_data.bits.b6 = in_data.bits.b5;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b6;
    out_data.bits.b1 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b2 = in_data.bits.b0;
    out_data.bits.b3 = in_data.bits.b1;
    out_data.bits.b4 = in_data.bits.b2;
    out_data.bits.b5 = in_data.bits.b3;
    out_data.bits.b6 = in_data.bits.b4;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b5;
    out_data.bits.b1 = in_data.bits.b6;
    out_data.bits.b2 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b3 = in_data.bits.b0;
    out_data.bits.b4 = in_data.bits.b1;
    out_data.bits.b5 = in_data.bits.b2;
    out_data.bits.b6 = in_data.bits.b3;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b4;
    out_data.bits.b1 = in_data.bits.b5;
    out_data.bits.b2 = in_data.bits.b6;
    out_data.bits.b3 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b4 = in_data.bits.b0;
    out_data.bits.b5 = in_data.bits.b1;
    out_data.bits.b6 = in_data.bits.b2;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b3;
    out_data.bits.b1 = in_data.bits.b4;
    out_data.bits.b2 = in_data.bits.b5;
    out_data.bits.b3 = in_data.bits.b6;
    out_data.bits.b4 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b5 = in_data.bits.b0;
    out_data.bits.b6 = in_data.bits.b1;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b2;
    out_data.bits.b1 = in_data.bits.b3;
    out_data.bits.b2 = in_data.bits.b4;
    out_data.bits.b3 = in_data.bits.b5;
    out_data.bits.b4 = in_data.bits.b6;
    out_data.bits.b5 = in_data.bits.b7;
    in_data.Val = pdatain[wiId++];
    if (wiId > length) break;
    out_data.bits.b6 = in_data.bits.b0;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;

    out_data.bits.b0 = in_data.bits.b1;
    out_data.bits.b1 = in_data.bits.b2;
    out_data.bits.b2 = in_data.bits.b3;
    out_data.bits.b3 = in_data.bits.b4;
    out_data.bits.b4 = in_data.bits.b5;
    out_data.bits.b5 = in_data.bits.b6;
    out_data.bits.b6 = in_data.bits.b7;
    out_data.bits.b7 = 1;
    pdataout[woId++] = out_data.Val; out_data.Val = 0;
  }

  if (out_data.Val == 0) {
    woId--;
    out_data.Val = pdataout[woId];
  }
  out_data.bits.b7 = 0;
  pdataout[woId++] = out_data.Val;

  return woId;
}
*/


unsigned char  pucDecodeBitArr(unsigned char *pOut, unsigned char *pIn) {
  unsigned char  bIn, bOut = 0;
  unsigned int   boId = 0, i = 0, o = 0;

  for (;;) {
    bIn = pIn[i++];

    uchar t;
    for (t=0; t<8; t++) {
      if (bIn & (0x01 << t)) {
        if (t != 7)
          bOut |= (0x01 << boId++);
      }
      else {
        if (t == 7) {
          pOut[o] = bOut;
          return i; //&(pIn[i]);
        }
        bOut &= ~(0x01 << boId++);
      }
      if (boId >=8) {
        pOut[o++] = bOut;
        bOut = boId = 0;
      }
    }
    if (i > 256) break;
  }
  return 0xFF; //NUL;
}
